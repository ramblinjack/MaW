#ifndef TERRAIN_H
#define TERRAIN_H

/*
 * Copyright (C) 2015
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
  This file contains the definition of the terrain class. This is the class that
  describes some basic fields and methods which all terrain types should have.
  This class is abstract, it will  be overridden by each individual type of terrain.
 */

#include "tile.hpp"

namespace maw {
namespace common {
namespace map {

class terrain {
private:
  // base food
  const uint8_t food;
  // base production
  const uint8_t prod;
  // base trade
  const uint8_t trade;

public:
  terrain(const uint8_t food, const uint8_t prod, const uint8_t trade):
    food(food), prod(prod), trade(trade) {}
  
  virtual uint8_t get_food(tile_t tile) const = 0;
  virtual uint8_t get_prod(tile_t tile) const = 0;
  virtual uint8_t get_trade(tile_t tile) const = 0;  

}; // end class terrain
} // end namespace map
} // end namespace common
} // end namespace maw
#endif // TERRAIN_H
