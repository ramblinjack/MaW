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


# Generates one class definition.
# $1: a def file
# $2: filename to write the m4 defs to
# $3: class name to generate
# $4: directory where the templates are
gen_class_def()
{
    tr [a-z] [A-Z] < "$1" \
        | sed -f "$4"/$3.sed > "$2"
    printf "\n" >> "$2" # to stop m4 complaining about a trailing newline
    m4 "$2" "$4"/"$3.m4"
}

# $1: suffix
# $2: filename to write it to
# $3: name of the enum
# $4: datatype of the enum
gen_enum() 
{
    SUFLEN=`expr length $1`
    LENGTH=`expr $SUFLEN + 2`
    NAME_UP=`echo $3 | tr [a-z] [A-Z]`
    printf "enum $3 : $4 {\n%s_NONE,\n" "$NAME_UP" >> "$2"
    for FILE in `ls *.$1`
    do
        echo -n "$FILE" | rev | cut -c "$LENGTH-" | rev | tr [a-z] [A-Z] >> "$2"
        echo -n "," >> "$2"
    done
    sed -i '$s/,$//' "$2" # remove the last comma
    printf "};\n\n" >> "$2"
}


# $1: file suffix
# $2: file to write to
# $3: data type of the vector
# $4: number of enum elements for this class
gen_vector()
{
    cat >> $2 <<EOF
std::vector<$3*> *init_$3s() {
  std::vector<$3*> *ret = new std::vector<$3*>($4);
  ret->at(0) = nullptr;
EOF
    SUFLEN=`expr length $1`
    LENGTH=`expr $SUFLEN + 2`
    for FILE in `ls *.$1`
    do
        NAME=`echo -n "$FILE" | rev | cut -c "$LENGTH-" | rev`
        NAME_UP=`echo "$NAME" | tr [a-z] [A-Z]`
        echo "  ret->at($NAME_UP) = new $NAME();" >> $2
    done
    printf "  return ret;\n}\n\n" >> $2
}

# Generates the classes for $1.
# $1: class name to generate
# $2: file to write to
# $3: file ending
# $4: templates directory
gen_classes()
{
    # A temporary file to write m4 defs to, we put it as a temp file in the hope
    # that the user building will (as any sane person would) have their /tmp
    # directory mounted in RAM.
    TMPFILE=`mktemp`

    # Class definitions.
    for FILE in `ls *.$3`
    do
        gen_class_def "$FILE" "$TMPFILE" "$1" "$4" >> "$2"
    done
    rm $TMPFILE
    printf "\n" >> "$2"
}

# $1: suffix
# $2: name of the constant
# $3: file to write to
count_stuff()
{
    NFILES=`ls *.$1 | wc -l`
    NENUMS=`expr $NFILES + 1`
    echo "const unsigned $2 = $NENUMS;" >> "$3"
    echo "$NENUMS"
}

