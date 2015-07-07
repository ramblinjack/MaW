#ifndef RESC_H
#define RESC_H
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

#include "map_glbl.h" // for maw_tile
#include "map_glbl_gen.h" // for maw_imprv

namespace maw {
namespace common {
namespace map {

class resc {
private:
  /*! The improvement which provides this resource. This means that if there is
   * such an improvement built on this tile and it is in range of a city it
   * provides the owner of that city with this resource.
   */
  const maw_imprv provided_by;
public:
  resc(maw_imprv provided_by): provided_by(provided_by) {}
  maw_imprv is_provided_by() const {return provided_by;}
  virtual unsigned get_food_bonus(maw_tile tile) const = 0;
  virtual unsigned get_prod_bonus(maw_tile tile) const = 0;
  virtual unsigned get_trade_bonus(maw_tile tile) const = 0;
}; // end class resc
} // end namespace map
} // end namespace common
} // end namespace maw




#endif /* ifndef RESC_H */
