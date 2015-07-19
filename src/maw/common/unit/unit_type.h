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

#include "unit_glbl.h"
#include <vector>

namespace maw {
namespace common {
namespace unit {

class unit_type {
private:
  /*! supertype of this unit type */
  const supertype stype;
  /*! base movement points the unit gets each turn.  */
  const unsigned movs;
  /*! the base attack strength */
  const unsigned atk;
  /*! the base defense strength */
  const unsigned dfns;
  /*! the base health points */
  const unsigned hlth;
  /*! what unit this unit becomes when it upgrades */
  const maw_unit_type upgrd;
  /*! splash damage */
  const unsigned splsh;
  /*! resources required to build this unit */
  const std::vector<maw_resc> req_resc;
  /*! a vector of units that this unit type can see even if they are 'hidden' */
  const std::vector<maw_unit_type> can_see;
  /*! movement class */
  const maw_mvmt_cls mvmt_cls;

  // special cases we will need to handle somehow
  
  /* is this unit a worker? */
  const bool worker;
  /* is this unit a settler? */
  const bool settler;
  /*! This unit can only be seen at a distance by those units which have it in
    their 'can_see' vector */
  const bool hidden;
  /*! is this unit a 'oneshot'? This means it is destroyed on attack/defense */
  const bool oneshot;
  /*! Can this unit attack air units? */
  const bool anti_air;

  // these are virtual functions, meant to be overridden by the individual
  // unit types
  
  /*! defensive modifier on tile `on'. */
  virtual float def_bonus_terr(map::maw_tile on) const = 0;
  
  /*! defensive modifier against unit `against' */
  virtual float def_bonus_unit(maw_unit_info against) const = 0;
  
  /*! attack modifier when attacking unit target. */
  virtual float atk_bonus_unit(maw_unit_info target) const = 0;
  
  /*! attack modifier when attacking from tile `from' to tile `to'. */
  virtual float atk_bonus_terr(map::maw_tile from, map::maw_tile to) const = 0;
  
public:
  /*! this is the interface for a unit */
  unit_type(maw_supertype stype,
            unsigned movs,
            unsigned atk,
            unsigned dfns,
            unsigned hlth,
            unsigned upgrd,
            unsigned splsh,
            const std::initializer_list<maw_resc> req_rescs,
            const std::initializer_list<maw_unit_type> can_see,
            maw_mvmt_cls mvmt_cls,
            bool worker,
            bool settler,
            bool hidden,
            bool oneshot,
            bool anti_air
            ):
    stype(stype), movs(movs), atk(atk), dfns(dfns),
    hlth(hlth), upgrd(upgrd), splsh(splsh),
    req_resc(req_rescs), can_see(can_see), worker(worker),
    settler(settler), hidden(hidden), oneshot(oneshot),
    anti_air(anti_air)
  {}
  
  /* Getters */
  // get supertype
  inline supertype get_stype() const {return stype;}
  
  // get the unit this upgrades to
  inline maw_unit_type get_upgrd() const {return upgrd;}

  // get base health
  inline hlth_t get_hlth() const {return hlth;}

  /* functions implemented in maw_unit_stateype.cpp */
  // how many moves does the unit has left?
  movp get_rem_movs(maw_unit_state unit) const;

  // get attack strength for unit `unit' when it is attacking from tile `from'
  // to  tile `to' and it is attacking unit `against',
  unsigned get_atk(maw_unit_state unit, maw_unit_state against,
                   map::maw_tile from, map::maw_tile to) const;

  // get defensive strength
  unsigned get_dfns(maw_unit_state unit, maw_unit_state attacker,
                    map::maw_tile tile) const;

  // the cost of moving to tile `to'. A return value of 0 shall mean that it is
  // not possible for this unit to make this move.
  virtual movp mov_cst(map::maw_tile to) const = 0;
};
} // end namespace unit
} // end namespace common
} // end namespace maw
#endif // ifndef UNIT_TYPE_H
