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
# See PACKAGE.org in the map directory for a description of what the files
# contain.

###############################################################################
##                                                                           ##
##   Generate the files for the map package                                  ##
##                                                                           ##
###############################################################################

GLBL_GEN_H="../map_glbl_gen.h"
GLBL_GEN_CPP="../map_glbl_gen.cpp"
INT_GEN_HPP="../map_int_gen.hpp"

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

# Count the number of each thing, this will be needed in multiple places, so we
# do it here before the real thing starts.
NTERRAINS=`count_files terr`
NRESCS=`count_files resc`
NIMPRVS=`count_files imprv`

################################################################################
##                              GLBL_GEN_H                                    ##
################################################################################

# replace any previous file
# Since this is a 'global' file meant to be a part of the C api we wrap it in
# extern C
cat > "$GLBL_GEN_H" <<EOF
/* This file is auto generated, DO NOT EDIT! */
#ifndef MAP_GLBL_GEN_H
#define MAP_GLBL_GEN_H
#ifdef __cplusplus
extern "C" {
#include <stdint.h>
#else
#include <cstdint>
#endif
#include "map_glbl.h"
EOF

printf "\nconst uint32_t NMAW_TERR = %d, NMAW_RESC = %d, NMAW_IMPRV = %d;\n" \
       $NTERRAINS $NRESCS $NIMPRVS >> "$GLBL_GEN_H"

gen_enum terr maw_terr "$GLBL_GEN_H"
gen_enum resc maw_resc "$GLBL_GEN_H"
gen_enum imprv maw_imprv "$GLBL_GEN_H"

gen_bitfld maw_tile ../../scripts/bitfields_decl.m4 ../templ/tile.bits \
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
#include "imprv.h"
#include "resc.h"
#include "terr.h"
#include "map_glbl.h"
#include "map_glbl_gen.h"
#include <vector>
namespace maw {
namespace common {
namespace map {
EOF

gen_classes terr terr "$INT_GEN_HPP"
gen_classes resc resc "$INT_GEN_HPP"
gen_classes imprv imprv "$INT_GEN_HPP"

gen_vector terr terr "$NTERRAINS" "$INT_GEN_HPP"
gen_vector resc resc "$NRESCS" "$INT_GEN_HPP"
gen_vector imprv imprv "$NIMPRVS" "$INT_GEN_HPP"

cat >> "$INT_GEN_HPP" <<EOF
} // end namespace map
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
gen_bitfld maw_tile ../../scripts/bitfields_impl.m4 ../templ/tile.bits \
           "$GLBL_GEN_CPP"

