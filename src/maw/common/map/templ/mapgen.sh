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


###############################################################################
##                                                                           ##
##   Generate the definitions for the map package                            ##
##                                                                           ##
###############################################################################

echo_usage()
{
    echo "Usage: mapgen.sh path_to_defs_dir generated_file"
    exit 1
}

if [ "$#" -ne 2 ]
then
    echo_usage
fi

# Get the full path of the file
GENFILE=`realpath "$2"`
# Change to the def or mocks directory... just so we know where we are
cd "$1"

# Load all the "generic" functions
source ../../scripts/gen_funcs.sh 

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

# $1: suffix
# $2: filename to write it to
# $3: name of the enum
# $4: datatype of the enum
gen_enum terr "$GENFILE" terrain_e terr_t
gen_enum resc "$GENFILE" resource_e resc_t
gen_enum imprv "$GENFILE" improvement_e imprv_t

# $1: class name to generate
# $2: file to write to
# $3: file ending
# $4: directory with templates
gen_classes terrain "$GENFILE" terr ../templ
gen_classes improvement "$GENFILE" imprv ../templ
gen_classes resource "$GENFILE" resc ../templ

# $1: suffix
# $2: name of the constant
# $3: file to write to
NTERRAINS=`count_stuff terr NTERRAINS "$GENFILE"`
NRESOURCES=`count_stuff resc NRESOURCES "$GENFILE"`
NIMPROVENTS=`count_stuff imprv NIMPROVENTS "$GENFILE"`

# $1: file suffix
# $2: file to write to
# $3: data type of the vector
# $4: number of elements
gen_vector terr "$GENFILE" terrain "$NTERRAINS"
gen_vector resc "$GENFILE" resource "$NRESOURCES"
gen_vector imprv "$GENFILE" improvement "$NIMPROVENTS"

# close namespaces
cat >> "$GENFILE" <<EOF
} // end namespace map
} // end namespace common
} // end namespace maw
EOF
