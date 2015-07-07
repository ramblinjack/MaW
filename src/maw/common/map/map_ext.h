#ifndef MAP_EXT_H
#define MAP_EXT_H
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

/*! Initializes the map package, this function _must_ be called before calling
 * any other function in the map package 
 */
int32_t init_map();

/*! Return the total amount of food produced on this tile */
uint32_t maw_total_food(maw_tile tile);
/*! Return the total amount of trade produced on this tile */
uint32_t maw_total_trade(maw_tile tile);
/*! Return the total amount of shields produced on this tile */
uint32_t maw_total_prod(maw_tile tile);

#ifdef __cplusplus
} // extern C
#endif

#endif /* ifndef MAP_EXT_H */
