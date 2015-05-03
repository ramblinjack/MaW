#ifndef IMPROVEMENT_H
#define IMPROVEMENT_H

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
  This file contains the definition of the improvement class. An instance of
  improvement is an improvement which can be built on a tile. An improvement has
  an effect, it adds output to the tile, therefore this class is abstract.
 */

#include "tile.hpp"

namespace maw {
namespace common {
namespace map {

class improvement {
private:
  // the number of turns it takes to build the improvment
  // TODO: how do we handle that newer worker units should build stuff faster?
  const unsigned turns;
  // the value of this improvment when pillaged
  const unsigned value;
  const bool gives_food, gives_trade, gives_prod;
  
public:
  improvement(unsigned turns, unsigned value, bool gives_food = false,
        bool gives_trade = false, bool gives_prod = false):
    turns(turns), value(value), gives_food(gives_food),
    gives_trade(gives_trade), gives_prod(gives_prod) {}
  inline unsigned get_turns() const {return turns;}
  inline unsigned get_value() const {return value;}
  inline bool is_food_bonus() const {return gives_food;}
  inline bool is_trade_bonus() const {return gives_trade;}
  inline bool is_prod_bonus() const {return gives_prod;}    
  virtual unsigned food_bonus(tile_t tile) const = 0;
  virtual unsigned prod_bonus(tile_t tile) const = 0;
  virtual unsigned trade_bonus(tile_t tile) const = 0;  
}; // end class improvement
} // end namespace map
} // end namespace common
} // end namespace maw
#endif // ifndef IMPROVEMENT_H
