#ifndef AIR_UNIT_H
#define AIR_UNIT_H
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

#include "mvmnt_type.h" // for mvmnt_type

namespace maw {
namespace common {
namespace unit {

class air_unit: public mvmnt_type {
private:
  const unsigned max_air_mvs;
public:
  air_unit(unsigned max_air_mvs): mvmnt_type(mvmnt_t_e::AIR),
                                   max_air_mvs(max_air_mvs) {}
  virtual unsigned dflt_mv_cst(tile_t to) const {return 1;}
  inline get_max_air_mvs() const {return max_air_mvs;}
};
} // end namespace unit
} // end namespace common
} // end namespace maw
#endif // ifndef AIR_UNIT_H
