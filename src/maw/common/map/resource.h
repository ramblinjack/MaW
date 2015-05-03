#ifndef RESOURCE_H
#define RESOURCE_H

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
  This file contains the definition of the resource class. An instance of resource is
  a resource which can exist on a tile. A resource 
 */

#include "tile.hpp"

namespace maw {
namespace common {
namespace map {

class resource {
private:
  // hopefully this simplifies things... and lets the compiler optimize out code
  // at compile time, instead of having to do vtable lookups at runtime, but
  // hey, what do I know?
  const bool gives_food, gives_trade, gives_prod;
  const imprv_t provided_by;
public:
  resource(bool gives_food, bool gives_trade, bool gives_prod,
           imprv_t provided_by):
    gives_food(gives_food), gives_trade(gives_trade), gives_prod(gives_prod)
      ,provided_by(provided_by) {}
  inline bool is_food_bonus() const {return gives_food;}
  inline bool is_trade_bonus() const {return gives_trade;}
  inline bool is_prod_bonus() const {return gives_prod;}
  inline imprv_t is_provided_by() const {return provided_by;}
  virtual unsigned food_bonus(tile_t tile) const = 0;
  virtual unsigned prod_bonus(tile_t tile) const = 0;
  virtual unsigned trade_bonus(tile_t tile) const = 0;
}; // end class resource
} // end namespace map
} // end namespace common
} // end namespace maw
#endif // ifndef RESOURCE_H
