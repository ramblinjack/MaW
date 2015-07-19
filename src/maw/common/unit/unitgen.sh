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

###############################################################################
##                                                                           ##
##              Generate the files for the unit package                      ##
##                                                                           ##
###############################################################################

GLBL_GEN_H="../unit_glbl_gen.h"
GLBL_GEN_CPP="../unit_glbl_gen.cpp"
INT_GEN_HPP="../unit_int_gen.hpp"

# $1 the templates directory to use, either the real or the mock
# Change to the def or mocks directory... just so we know where we are
cd "$1"
if [ $? -ne 0 ]
then
    echo "cd failed. Are you sure that's the right directory?"
    exit 1
fi

# Load all the "generic" functions
source ../../scripts/gen_funcs.sh 

# Count the number of units
NUNITS=`count_files unit`

################################################################################
##                              GLBL_GEN_H                                    ##
################################################################################

# replace any previous file
# Since this is a 'global' file meant to be a part of the C api we wrap it in
# extern C
cat > "$GLBL_GEN_H" <<EOF
/* This file is auto generated, DO NOT EDIT! */
#ifndef UNIT_GLBL_GEN_H
#define UNIT_GLBL_GEN_H
#ifdef __cplusplus
extern "C" {
#endif
#include "unit_glbl.h"
EOF

printf "\nconst uint32_t NMAW_UNIT_TYPE = %d;\n" $NUNITS >> "$GLBL_GEN_H"

gen_enum unit maw_unit_type "$GLBL_GEN_H"

echo "typedef enum maw_supertype {" >> "$GLBL_GEN_H"
N=0
# NUNITS includes the 'NONE' type, so the number of actual units is one less
NACTUAL=`expr "$NUNITS" - 1` 
for FILE in `ls *.unit`
do
    NAME=`grep supertype "$FILE" | cut -s -d"=" -f2 | tr [a-z] [A-Z]`
    echo -n "  $NAME" >> "$GLBL_GEN_H"
    N=`expr "$N" + 1`
    if [ "$N" -eq $NACTUAL ]
    then
        break
    else
        echo "," >> "$GLBL_GEN_H"
    fi
done
printf "\n} maw_supertype;\n" >> "$GLBL_GEN_H"

gen_bitfld maw_unit_info ../../scripts/bitfields_decl.m4 ../templ/unit.bits \
           "$GLBL_GEN_H"

cat >> "$GLBL_GEN_H" <<EOF
#ifdef __cplusplus
}
#endif
#endif /* ifndef MAP_GLBL_GEN_H */
EOF

################################################################################
##                               INT_GEN_HPP                                  ##
################################################################################
cat > "$INT_GEN_HPP" <<EOF
// This file is auto generated, DO NOT EDIT!
#ifndef MAP_INT_GEN_HPP
#define MAP_INT_GEN_HPP
#include "unit_glbl.h"
#include "map_glbl_gen.h"
#include <vector>
namespace maw {
namespace common {
namespace unit {
EOF

gen_classes unit unit "$INT_GEN_HPP"

gen_vector unit unit "$NUNITS" "$INT_GEN_HPP"

cat >> "$INT_GEN_HPP" <<EOF
} // end namespace unit
} // end namespace common
} // end namespace maw
#endif // ifndef MAP_INT_GEN_HPP
EOF

################################################################################
##                             GLBL_GEN_CPP                                   ##
################################################################################
echo '// This file is auto generated, DO NOT EDIT!' > "$GLBL_GEN_CPP"
echo '#include "map_glbl_gen.h"' >> "$GLBL_GEN_CPP"
echo '#include "map_glbl.h"' >> "$GLBL_GEN_CPP"
gen_bitfld maw_unit_type ../../scripts/bitfields_impl.m4 ../templ/unit.bits \
           "$GLBL_GEN_CPP"

