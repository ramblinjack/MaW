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

// TODO: we have to include the file which gives us access to the base health of
// this type... welcome circular dependencies.
#include "units.hpp"

namespace maw {
namespace common {
namespace unit {

// this is where we define how the healing power is calculated.
unsigned medic::get_heal(const unit_t me) const {
  // TODO: make something better, for now heling power is proportional to the
  // health of the medic unit.
  // I really should learn the casting rules...
  hlth_t base_hlth = units->at(get_type(me))->get_hlth();// oh shit...
  float mod = (float) get_hlth(me) / (float) base_hlth;
  return (unsigned) (mod * heal); 
}

} // end namespace unit
} // end namespace common
} // end namespace maw
