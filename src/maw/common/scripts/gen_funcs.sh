# Copyright (C) 2015, The MaW Team

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.


# Strip the suffix and uppercase the filename
# $1: The suffix
# $2: Filename
strip_and_upper()
{
    SUFLEN=`expr length $1`     # Length of the suffix
    LENGTH=`expr $SUFLEN + 2`   # ... plus one dot and one newline
    echo -n "$FILE" | rev | cut -c "$LENGTH-" | rev | tr [a-z] [A-Z] | tr -d '\n'
}

# $1: suffix
# $2: name of the enum
# $3: filename to write it to
gen_enum() 
{
    NAME_UP=`echo $2 | tr [a-z] [A-Z]` # Name of the enum in upper case
    printf "typedef enum $2 {\n  %s_NONE,\n" "$NAME_UP" >> "$3"
    for FILE in `ls *.$1`
    do
        printf "  " >> "$3"
        strip_and_upper "$1" "$FILE" >> "$3"
        echo "," >> "$3"
    done
    sed -i '$s/,$//' "$3" # remove the last comma
    printf "} $2;\n\n" >> "$3"
}

# Generate a function which returns a vector
# $1: file suffix
# $2: data type of the vector, ie the name of the base class
# $3: number of enum elements for this class
# $4: file to write to
gen_vector()
{
    cat >> "$4" <<EOF
std::vector<$2*> *init_$2s() {
  std::vector<$2*> *ret = new std::vector<$2*>($3);
  ret->at(0) = nullptr;
EOF
    for FILE in `ls *.$1`
    do
        NAME_UP=`strip_and_upper "$1" "$FILE"`
        NAME=`echo "$NAME_UP" | tr [A-Z] [a-z]`
        echo "  ret->at($NAME_UP) = new $NAME();" >> $4
    done
    printf "  return ret;\n}\n\n" >> $4
}

# Generates one class definition
# $1: a def file
# $2: name of the .sed and .m4 files, without suffix
gen_class_def()
{
    TMPFILE=`mktemp`
    sed -f "../templ/$2.sed" < "$1" > "$TMPFILE"
    printf "\n" >> "$TMPFILE" # to stop m4 complaining about a trailing newline
    m4 "$TMPFILE" "../templ/$2.m4"
    rm "$TMPFILE"
}

# Generates the classes for $1.
# $1: name of the .sed and .m4 files, without suffix
# $2: file suffix
# $3: file to write to
gen_classes()
{
    # Class definitions.
    for FILE in `ls *.$2`
    do
        gen_class_def "$FILE" "$1" >> "$3"
    done
    printf "\n" >> "$3"
}

# Counts the number of files with the given suffix, then adds one, for the first
# 'null' type.
# $1: suffix
count_files()
{
    NFILES=`ls *.$1 | wc -l`
    NFILES_PLUS_ONE=`expr $NFILES + 1`
    echo "$NFILES_PLUS_ONE"
}

# Generates implementaions or declarations for the bitfield access functions
# from a bitfield definition file
# $1: The data type
# $2: the file with the m4 definitions
# $3: The file with the field definitions
# $4: The file to write to
gen_bitfld()
{
    TMPFILE=`mktemp`
    OFFS=0
    while read FIELD
    do
        # Ignore comment lines
        FIRST=`expr substr "$FIELD" 1 1`
        if [ "$FIRST" = "#" ]
        then
            continue
        fi
        echo "define(DATA_TYPE,$1)define(OFFS,$OFFS)dnl" > "$TMPFILE"
        SIZE=`echo $FIELD | cut -s -d":" -f2`
        NAME=`echo $FIELD | cut -s -d":" -f1`
        echo "define(FIELD_NAME,$NAME)define(SIZE,$SIZE)dnl" >> "$TMPFILE"
        m4 "$TMPFILE" "$2" >> "$4"
        OFFS=`expr $OFFS + $SIZE`
    done < "$3"
    rm "$TMPFILE"
}
