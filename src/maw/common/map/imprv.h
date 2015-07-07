#ifndef IMPRV_H
#define IMPRV_H
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

namespace maw {
namespace common {
namespace map {

#include "map_glbl.h" // for maw_tile

class imprv {
private:
  /*! The cost to build this improvement */
  const unsigned cost;
public:
  imprv(unsigned cost): cost(cost) {}
  inline unsigned get_cost() const {return cost;}
  virtual unsigned get_food_bonus(maw_tile tile) const = 0;
  virtual unsigned get_prod_bonus(maw_tile tile) const = 0;
  virtual unsigned get_trade_bonus(maw_tile tile) const = 0;  
}; // end class imprv
} // end namespace map
} // end namespace common
} // end namespace maw

#endif /* ifndef IMPRV_H */
