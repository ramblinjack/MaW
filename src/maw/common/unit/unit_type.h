#ifndef UNIT_TYPE_HPP
#define UNIT_TYPE_HPP
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
  This file contains the definitions for the unit_type class. Here we define
  things that are common to all  unit types.
 */

#include "unit.hpp"

namespace maw {
namespace common {
namespace unit {

typedef uint16_t atk_t;
typedef uint16_t dfns_t;

class unit_type {
protected:
  // supertype of this unit type
  const supertype stype;
  // base movement points the unit gets each turn. 
  const movp_num_t movs;
  // the base attack strength
  const atk_t atk;
  // the base defense strength
  const dfns_t dfns;
  // the base health points
  const hlth_t hlth;

  // these are virtual functions, meant to be overridden by the individual
  // unit types

  // the cost of moving to tile `to'
  virtual const movp mov_cst(const map::tile_t to) const = 0;

  // defensive bonus on tile
  virtual const dfns_t def_bonus(const map::tile_t on) const = 0;

  // attack bonus when attacking unit target from tile `from' to tile `to'
  virtual const atk_t atk_bonus(const unit_t target,
                                       const map::tile_t from,
                                       const map::tile_t to) const = 0;

public:
  // this is the interface for a unit

  unit_type(const supertype stype,
            const movp_num_t movs,
            const atk_t atk,
            const dfns_t dfns,
            const hlth_t hlth):
  stype(stype),
    movs(movs),
    atk(atk),
    dfns(dfns),
    hlth(hlth)
    {}
    
  
  // how many moves does the unit has left?
  movp get_rem_movs(const unit_t unit) const;
  // get attack strength for unit `unit' when it is attacking from tile `from'
  // to  tile `to' and it is attacking unit `against',
  atk_t get_atk(const unit_t unit, const unit_t against,
                const map::tile_t from, const map::tile_t to) const;
  // get defensive strength
  dfns_t get_dfns(const unit_t unit,
                         const unit_t attacker,
                         map::tile_t tile) const;
};
} // end namespace unit
} // end namespace common
} // end namespace maw
#endif // ifndef UNIT_TYPE_HPP
