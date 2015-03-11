#ifndef MAP_H
#define MAP_H

/*
 * Copyright (C) 2015, the MaW Team
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

#include "tile.hpp"
#include <cstdio>

namespace maw {
namespace common {
namespace map {

typedef uint16_t coord_t;

typedef struct pos_t {
  coord_t x, y;
} pos_t;

typedef struct map {
  coord_t xsize, ysize;
  tile_t* map;
} map;

map* read_map(const char* file);

bool write_map(const char* file);

map* read_map(FILE* file);

bool write_map(FILE* file);

bool update_map(FILE* file, map& themap, pos_t pos, tile_t tile);

} // end namespace map
} // end namespace common
} // end namespace maw
#endif // ifndef MAP_H
