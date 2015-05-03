#!/bin/sh

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

# This script generates terrains and also the classes for improvements and
# resources, in short all the classes in the map package.

# Generates one terrain class definition.
# $1 is a def file
# $2 is the filename to write the m4 defs to
# $3 is the class name to generate
gen_class_def()
{
    tr [a-z] [A-Z] < $1 \
        | sed -f ../templ/$3.sed > $2
    printf "\n" >> $2 # to stop m4 complaining about a trailing newline
    m4 $2 ../templ/$3.m4 
}

# $1 is the suffix
# $2 is the filename to write it to
# $3 is the name of the enum
# $4 is the datatype of the enum
gen_enum() 
{
    SUFLEN=`expr length $1`
    LENGTH=`expr $SUFLEN + 2`
    NAME_UP=`echo $3 | tr [a-z] [A-Z]`
    printf "enum $3 : $4 {\n%s_NONE,\n" "$NAME_UP" >> "$2"
    for FILE in `ls *.$1`
    do
        echo -n "$FILE" | rev | cut -c "$LENGTH-" | rev | tr [a-z] [A-Z] >> $2
        echo -n "," >> $2
    done
    sed -i '$s/,$//' "$2" # remove the last comma
    printf "};\n\n" >> "$2"
}


# $1 is the file suffix
# $2 is the file to write to
# $3 is the data type of the vector
# $4 is the number of enum elements for this class
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
# $1 is the class name to generate
# $2 is the file to write to
# $3 is the file ending
gen_classes()
{
    # A temporary file to write m4 defs to, we put it as a temp file in the hope
    # that the user building will (as any sane person would) have their /tmp
    # directory mounted in RAM.
    TMPFILE=`mktemp`

    # Class definitions.
    for FILE in `ls *.$3`
    do
        gen_class_def "$FILE" "$TMPFILE" "$1">> "$2"
    done
    rm $TMPFILE
    printf "\n" >> "$2"
}

# $1 is the suffix
# $2 is the name of the constant
# $3 is the file to write to
count_stuff()
{
    NFILES=`ls *.$1 | wc -l`
    NENUMS=`expr $NFILES + 1`
    echo "const unsigned $2 = $NENUMS;" >> "$3"
    echo "$NENUMS"
}

echo_usage()
{
    echo "Usage: mapgen.sh path_to_defs_dir generated_file"
    exit 1
}

###############################################################################
##     
##   Generate the definitions for the map package
##
###############################################################################

if [ "$#" -ne 2 ]
then
    echo_usage
fi

# Get the fullpath of the file
GENFILE=`realpath "$2"`
# Change to the def or mocks directory... just so we know where we are
cd "$1"

# replace any previous file
# Includes and opening of namespaces
cat > "$GENFILE" <<EOF
#include "map/terrain.hpp"
#include "map/improvement.h"
#include "map/resource.h"
#include <vector>
#ifdef CLIENT
#include "gphx_obj.hpp"
#endif
namespace maw {
namespace common {
namespace map {
EOF

# Generate enums. We do this first as they have no dependencies on other stuff,
# but it is nice to have them declared when we declare the rest of the stuff.

# $1 is the suffix
# $2 is the filename to write it to
# $3 is the name of the enum
# $4 is the datatype of the enum
gen_enum terr "$GENFILE" terrain_t terr_t
gen_enum resc "$GENFILE" resource_t resc_t
gen_enum imprv "$GENFILE" improvement_t imprv_t

# $1 is the class name to generate
# $2 is the file to write to
# $3 is the file ending
gen_classes terrain "$GENFILE" terr
gen_classes improvement "$GENFILE" imprv
gen_classes resource "$GENFILE" resc

# $1 is the suffix
# $2 is the name of the constant
# $3 is the file to write to
NTERRAINS=`count_stuff terr NTERRAINS "$GENFILE"`
NRESOURCES=`count_stuff resc NRESOURCES "$GENFILE"`
NIMPROVENTS=`count_stuff imprv NIMPROVENTS "$GENFILE"`

# $1 is the file suffix
# $2 is the file to write to
# $3 is the data type of the vector
gen_vector terr "$GENFILE" terrain "$NTERRAINS"
gen_vector resc "$GENFILE" resource "$NRESOURCES"
gen_vector imprv "$GENFILE" improvement "$NIMPROVENTS"


# close namespaces
cat >> "$GENFILE" <<EOF
} // end namespace map
} // end namespace common
} // end namespace maw
EOF
