#ifndef MAP_GLBL_H
#define MAP_GLBL_H
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
#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>

typedef uint32_t maw_tile;

typedef uint16_t maw_coord;

typedef struct maw_pos {
  maw_coord x, y;
} maw_pos;

typedef struct maw_map {
  maw_coord xsize, ysize;
  maw_tile* map;
} maw_map;

#ifdef __cplusplus
} // extern C
#endif
#endif /* ifndef MAP_GLBL_H */
