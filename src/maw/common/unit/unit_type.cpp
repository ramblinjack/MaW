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
  This file is the implementation of the base unit type. This class is abstract,
  the idea is that it will be inherited by all the individual unit types in maw.
  
  In this class we define the base behaviours, then there are virtual functions
  which deal with all the unit specifics, like movement costs and such.
 */

#include "unit_type.h"

namespace maw {
namespace common {
namespace unit {

// TODO: make a real thing here
movp unit_type::get_rem_movs(const unit_t unit) const {
// if the unit is at less than half health we cut its movps
// in half. This is only for initial testing.
movp m = get_movp(unit);
if (get_hlth(unit) > hlth/2) {
return m;
} else {
return std::make_pair(m.first/2, m.second);
}
}
} // end namespace unit
} // end namespace common
} // end namespace maw

