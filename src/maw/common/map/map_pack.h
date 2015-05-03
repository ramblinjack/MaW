#ifndef MAP_PACK_H
#define MAP_PACK_H
/*
 * Copyright (C) 2015, The MaW Team
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
  This file declares some functions which provide an interface to the
  functionality in the map package. 
 */

// this includes almost everything we need
#include "gen/terrains.hpp"

namespace maw {
namespace common {
namespace map {

std::vector<terrain*> *all_terrains;
std::vector<improvement*> *all_improvements;
std::vector<resource*> *all_resources;


// initializes the map package
void init_map();

/*!
 * return the total food on tile `tile'
 */
unsigned food_on_tile(tile_t tile);

unsigned prod_on_tile(tile_t tile);

unsigned trade_on_tile(tile_t tile);

/*!
 * Returns the resource which \a tile provides. A resource is provided iff it
 * exists on the tile and the improvement which provides it exists on the tile.
 */
resource_t resource_on_tile(tile_t tile);

static inline terrain *get_terrain(tile_t tile) {
  return all_terrains->at(get_terr(tile));
}

static inline improvement *get_improvement(tile_t tile) {
  return all_improvements->at(get_imprv(tile));
}

static inline resource *get_resource(tile_t tile) {
  return all_resources->at(get_resc(tile));
}

} // end namespace map
} // end namespace common
} // end namespace maw
#endif // ifndef MAP_PACK_H
