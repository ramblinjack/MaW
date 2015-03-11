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
#include "map/map.h"

namespace maw {
namespace common {
namespace unit {

#undef LAST_FIELD
#define LAST_FIELD unit_t
MAW_DECL_DUMMY_OFFS(unit_t)

typedef uint64_t unit_t;

// type: the type of the unit, archer or tank or whatever
// 1024 should be plenty
MAW_DECL_BITS(unit_t, type, 10, uint16_t)
#undef LAST_FIELD
#define LAST_FIELD type

//player: the player the unit belongs to
// 64 different players
MAW_DECL_BITS(unit_t, plyr, 6, uint8_t)
#undef LAST_FIELD
#define LAST_FIELD plyr

// movp: movement points left
// We divide this into a numerator and a denominator, so that we can
// have turns cost less than one movement point, like in civII where
// moving on a road only costs 1/3 movement point. This is the numerator.
// 10 bits gives 1000 moves, I don't think anyone wants to move further
// than that.
MAW_DECL_BITS(unit_t, movp_num, 10, uint16_t)
#undef LAST_FIELD
#define LAST_FIELD movp_num

// This is the denominator, it doesn't need to be huge
MAW_DECL_BITS(unit_t, movp_den, 5, uint8_t)
#undef LAST_FIELD
#define LAST_FIELD movp_den

// Health: how many hp this unit has left
MAW_DECL_BITS(unit_t, hlth, 10, uint16_t)
#undef LAST_FIELD
#define LAST_FIELD hlth

// XP: current xperience points of the unit
MAW_DECL_BITS(unit_t, xp, 10, uint16_t)
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


typedef uint32_t unit_id_t;

typedef struct unit {
  map::pos_t pos;
  unit_t unit;
  unit_id_t id;
  union {
    map::pos_t going_to;
    unit_id_t escorting;
  };
} unit;


} // end namespace unit
} // end namespace common
} // end namespace maw
#endif // ifndef UNIT_HPP
