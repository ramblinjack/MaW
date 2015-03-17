#ifndef TILE_HPP
#define TILE_HPP
/*
 * Copyright (C) 2015 The Maw Team
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
  This file defines the tile_t type and related functions.
  tile_t is the type of a tile on the MaW map. 
 */

#include "macros/bitmask_macros.h"
#include <cstdint>

namespace maw {
namespace common {
namespace map {

#undef LAST_FIELD
#define LAST_FIELD tile
MAW_DECL_DUMMY_OFFS(tile)

// a tile is an unsigned 32 bit integer. Would have been
// nice to fit it in 16 bits, but that is probably too tight.
typedef uint32_t tile_t;

// terrain: grassland, mountain, etc...
// 256 different should be enough...
MAW_DECL_BITS(tile_t, terr, 8, uint8_t)
#undef LAST_FIELD
#define LAST_FIELD terr

// resource: buffalo, iron, fish, etc...
MAW_DECL_BITS(tile_t, resc, 7, uint8_t)
#undef LAST_FIELD
#define LAST_FIELD resc

// improvement: mine, farm, etc...
MAW_DECL_BITS(tile_t, imprv, 7, uint8_t)
#undef LAST_FIELD
#define LAST_FIELD imprv

// road: road, paved road, railroad...
MAW_DECL_BITS(tile_t, road, 3, uint8_t)
#undef LAST_FIELD
#define LAST_FIELD road

// river: whether or not there is a river on the tile
// Maybe we should have more possibilities for this? Like canal maybe, for "man
// made" river tiles? Screw it, I'll put 2 bits for the heck of it.
MAW_DECL_BITS(tile_t, rivr, 2, uint8_t)
#undef LAST_FIELD
#define LAST_FIELD rivr

// vision: whether this tile is visible or not. This does not mean if the tile
// is completely black or not. If the tile has never been seen by a player, it
// should have terr = NONE. If the player has seen this tile, but cannot
// currently see it, it should be "in the shadow" and it should look like when
// he last saw it. Then visn is false.
MAW_DECL_BITS(tile_t, visn, 1, bool)
#undef LAST_FIELD
#define LAST_FIELD visn


} // end namespace maw::common::map
} // end namespace maw::common
} // end namespace maw
#endif // ifndef TILE_HPP


