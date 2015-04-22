#ifndef UNIT_TYPE_H
#define UNIT_TYPE_H
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


class unit_type {
private:
  // supertype of this unit type
  const supertype stype;
  // base movement points the unit gets each turn. 
  const movp_num_t movs;
  // the base attack strength
  const unsigned atk;
  // the base defense strength
  const unsigned dfns;
  // the base health points
  const hlth_t hlth;
  // what unit this unit becomes when it upgrades
  const type_t upgrd;
  // splash damage
  const unsigned splsh;
  
  // these are virtual functions, meant to be overridden by the individual
  // unit types

  // the cost of moving to tile `to'. A return value of 0 shall mean that it is
  // not possible for this unit to make this move.
  virtual movp mov_cst(const map::tile_t to) const = 0;

  // defensive modifier on tile `on'.
  virtual float def_bonus_terr(const map::tile_t on)
    const = 0;
  
  // defensive modifier against unit `against'
  virtual float def_bonus_unit(const unit_t against)
    const = 0;
  
  
  // attack modifier when attacking unit target.
  virtual float atk_bonus_unit(const unit_t target) const = 0;
  
  // attack modifier when attacking from tile `from' to tile `to'.
  virtual float atk_bonus_terr(const map::tile_t from,
                               const map::tile_t to) const = 0;
  
public:
  // this is the interface for a unit
  unit_type(const supertype stype, const movp_num_t movs,
           const unsigned atk, const unsigned dfns,
            const hlth_t hlth, const type_t upgrd,
            const unsigned splsh = 0):
    stype(stype), movs(movs), atk(atk), dfns(dfns),
    hlth(hlth), upgrd(upgrd), splsh(splsh) {}
  
  /* Getters */
  // get supertype
  inline supertype get_stype() const {return stype;}
  
  // get the unit this upgrades to
  inline type_t get_upgrd() const {return upgrd;}

  // get base health
  inline hlth_t get_hlth() const {return hlth;}

  /* functions implemented in unit_type.cpp */
  // how many moves does the unit has left?
  movp get_rem_movs(const unit_t unit) const;

  // get attack strength for unit `unit' when it is attacking from tile `from'
  // to  tile `to' and it is attacking unit `against',
  unsigned get_atk(const unit_t unit, const unit_t against,
                const map::tile_t from, const map::tile_t to) const;

  // get defensive strength
  unsigned get_dfns(const unit_t unit, const unit_t attacker,
                    const map::tile_t tile) const;


  
};
} // end namespace unit
} // end namespace common
} // end namespace maw
#endif // ifndef UNIT_TYPE_H
