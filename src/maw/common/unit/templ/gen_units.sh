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

# This file contains a script which turns maw definition files into m4 macro
# files, which are then fed through m4 together with a template to create output
# files.

#
gen_land_unit()
{
    
}

# $1: path to terrain defs dir
# $2: file to write to
gen_sea_unit()
{
    
}

echo_usage()
{
    echo "Usage: gen_units.sh path_to_unit_defs path_to_terrain_defs generated_file"
    exit 1
}

###############################################################################
##                                                                           ##
##   Generate the definitions for the unit package                           ##
##                                                                           ##
###############################################################################

if [ "$#" -ne 2 ]
then
    echo_usage
fi

# Get the full path of the file
GENFILE=`realpath "$3"`
# Get the path to the terrain defs dir
TERRAIN_DEFS_DIR=`realpath "$2"`
# Change to the def or mocks directory... just so we know where we are
cd "$1"

# Load all the "generic" functions
source ../../scripts/gen_funcs.sh 

# replace any previous file
# Includes and opening of namespaces
cat > "$GENFILE" <<EOF
/* this file is auto generated */
#ifndef UNIT_TYPES_H
#define UNIT_TYPES_H
#include "map/terrain.hpp"
#include "map/improvement.h"
#include "map/resource.h"
#include "unit_type.h"
#include <vector>
#ifdef CLIENT
#include "gphx_obj.hpp"
#endif
namespace maw {
namespace common {
namespace unit {
EOF

# $1: suffix
# $2: filename to write it to
# $3: name of the enum
# $4: datatype of the enum
gen_enum unit "$GENFILE" unit_e type_t

gen_classes unit "$GENFILE" unit ../templ

NUNIT_TYPES=`count_stuff unit NUNIT_TYPES "$GENFILE"`

# $1: file suffix
# $2: file to write to
# $3: data type of the vector
# $4: number of enum elements for this class
gen_vector unit "$GENFILE" unit_type $NUNIT_TYPES

# close namespaces
cat >> "$GENFILE" <<EOF
} // end namespace unit
} // end namespace common
} // end namespace maw
#endif // ifndef UNIT_TYPES_H
EOF
