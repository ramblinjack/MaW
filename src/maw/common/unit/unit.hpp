#ifndef UNIT_HPP
#define UNIT_HPP

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

#include "macros/bitmask_macros.h"
#include <cstdint>
#include <utility>
#include "map/map.h"
#include "plyr/plyr.h"

namespace maw {
namespace common {
namespace unit {

#undef LAST_FIELD
#define LAST_FIELD unit_t
MAW_DECL_DUMMY_OFFS(unit_t)

typedef uint64_t unit_t;

// type: the type of the unit, archer or tank or whatever
MAW_DECL_BITS(unit_t, type, 10, uint16_t)
#undef LAST_FIELD
#define LAST_FIELD type

// movp: movement points left
// We divide this into a numerator and a denominator, so that we can
// have turns cost less than one movement point, like in civII where
// moving on a road only costs 1/3 movement point. This is the numerator.
// Any moves larger than hundred or so should probably be handled some other
// way. 
MAW_DECL_BITS(unit_t, movp_num, 7, uint8_t)
#undef LAST_FIELD
#define LAST_FIELD movp_num

// This is the denominator, it doesn't need to be huge
MAW_DECL_BITS(unit_t, movp_den, 4, uint8_t)
#undef LAST_FIELD
#define LAST_FIELD movp_den

// here we make a special typedef for the movements, together with a hand hacked
// function for constructing it easily.
typedef std::pair<movp_num_t, movp_den_t> movp;
inline movp get_movp(const unit_t unit) {
  return std::make_pair(get_movp_num(unit), get_movp_den(unit));
}

// Health: how many hp this unit has left
MAW_DECL_BITS(unit_t, hlth, 10, uint16_t)
#undef LAST_FIELD
#define LAST_FIELD hlth

// XP: current xperience points of the unit
MAW_DECL_BITS(unit_t, xp, 8, uint8_t)
#undef LAST_FIELD
#define LAST_FIELD xp

// Units can have medals. There are three "paths", one
// for mobility or something, maybe one for attack and one for defense
// or maybe vision. I don't know...
// This is the first path.
MAW_DECL_BITS(unit_t, mdl1, 2, uint8_t)
#undef LAST_FIELD
#define LAST_FIELD mdl1

// and the second
MAW_DECL_BITS(unit_t, mdl2, 2, uint8_t)
#undef LAST_FIELD
#define LAST_FIELD mdl2

// and the third
MAW_DECL_BITS(unit_t, mdl3, 2, uint8_t)
#undef LAST_FIELD
#define LAST_FIELD mdl3

// the state the unit is in
MAW_DECL_BITS(unit_t, state, 5, uint8_t)
#undef LAST_FIELD
#define LAST_FIELD state

// turns spent in the current state. We only keep track of this up to some
// number of turns.
MAW_DECL_BITS(unit_t, tu_cur_st, 5, uint8_t)
#undef LAST_FIELD
#define LAST_FIELD tu_cur_st

typedef uint32_t unit_id_t;

typedef struct unit {
  // The position of this unit, if it is aboard another unit or escorting
  // another unit, it has the same psition as that unit, so we don't need to
  // store it.
  union {
    map::pos_t pos;
    unit_id_t escorting;
    unit_id_t aboard;
  };
  // the actual unit
  unit_t unit;
  // the id of the unit
  unit_id_t id;
  // the player the unit belongs to
  plyr::plyr_id_t plyr;
} unit;

// Movement orders: if a unit is in s state of GOTO, it has an entry of this
// struct with its id.
typedef struct mvmt_ordrs {
  unit_id_t unit;
  map::pos_t to;
} mvmt_ordrs;

// Patrol orders, if a unit is in a state of PATROL, it will have a
// corresponding instance of this struct. This can also be reused for trade
// units conneting two cities.
typedef struct ptrl_ordrs {
  unit_id_t unit;
  map::pos_t from;
  map::pos_t to;
} ptrl_ordrs;

// every unit will have a supertype, which is a sort of grouping of similar
// units, so for example a tank may be of supertype `armored', and there may be
// an anti tank gun which gets an attack bonus against all units which are of
// supertype armored, like tank, modern tank, APC or whatever. This enum will be
// defined in "supertypes.h" which will be auto genereated form configuration
// files, this is just the forward declaration;
enum class supertype;

// This enum defines the states a unit can be in. 
enum state : state_t {
  // active, the default state, unit is ready to take orders
  ACTIVE,
    // the unit has orders to go somewhere
    GOTO,
    // the unit is in a state of patrolling. This means it is moving between two
    // positions, if a unit of another player comes into view, this unit should
    // should transfer to the ACTIVE state.
    PATROL,
    // the unit is watching. This is like PATROL, except the unit doesn't move.
    // When an enemy unit comes into sight, it will still wake up.
    WATCH,
    // The unit is escorting another unit. It will follow the escorted unit.
    ESCORT,
    // the unit is fortified, it recieves a defensive bonus.
    FORTIFIED,
    // The unit is aboard another unit
    BOARDED,
    // this is a state for air units. They can only be in this state for a finite
    // number of turns before they crash. I also have an idea about a helicpoter
    // unit which can be in this state infinitely as long as it is over land, but
    // only for a finite nr of turns over water. just an idea...
    IN_FLIGHT,
    // The user has requsted that this unit skip its turn. But it can be woken
    // and become ACTIVE.
    SKIP,
    // ok, this is a state for worker units. They will also need a state for
    // what they are working on, but the problem is that this has to be
    // autogenerated because it depends on what improvements we defined in the
    // conf files. The hole we dug ourself is getting deeper and deeper...
    WORKING,
    // this is a state for trade units, it is essentially the same as PATROL,
    // but I figure it might be convenient.
    TRADE
};

} // end namespace unit
} // end namespace common
} // end namespace maw
#endif // ifndef UNIT_HPP
