#ifndef TERRAIN_HPP
#define TERRAIN_HPP

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
  The terrain class is the simplest, it has no dependencies on anything else,
  and for this reason it should be the first to be generated.
 */

#include "tile.hpp"

namespace maw {
namespace common {
namespace map {

class terrain {
private:
  // base food
  const unsigned food;
  // base production
  const unsigned prod;
  // base trade
  const unsigned trade;

public:
  terrain(unsigned food, unsigned prod, unsigned trade):
    food(food), prod(prod), trade(trade) {}
  
  inline unsigned get_food() const {return food;}
  inline unsigned get_prod() const {return prod;}
  inline unsigned get_trade() const {return trade;}  
}; // end class terrain
} // end namespace map
} // end namespace common
} // end namespace maw
#endif // TERRAIN_HPP
