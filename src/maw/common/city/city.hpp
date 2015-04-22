#ifndef CITY_HPP
#define CITY_HPP
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
  This files contains the definitions for MaW cities. We define two different
  city types: the regular city_t, which is a type with all the information on
  the city, and the simplified encity_t which represents an enemy city in the
  client. The encity_t doesn't need very much information, just the player who
  owns it, the size ,whether or not it has walls and whether or not it is empty,
  this is all the information which is needed to display the city.
 */

#include "macros/bitmask_macros.h"
#include "plyr.h"

namespace maw {
namespace common {
namespace city {
typedef uint64_t city_t;

#undef LAST_FIELD
#define LAST_FIELD city_t
MAW_DECL_DUMMY_OFFS(city_t)

// The current amount of shields (or production) that the city has saved
// up. 
MAW_DECL_BITS(city_t, 11, prod, uint16_t)
#undef LAST_FIELD
#define LAST_FIELD prod

// the amount of food currently stored in the city.
MAW_DECL_BITS(city_t, 11, food, uint16_t)
#undef LAST_FIELD
#define LAST_FIELD food

// the number of citizens in the city.
MAW_DECL_BITS(city_t, 8, nctzn, uint8_t)
#undef LAST_FIELD
#define LAST_FIELD nctzn

// the type of the current production, can be one of unit, building,
// wonder, food, trade
MAW_DECL_BITS(city_t, 4, tcprod, uint8_t)
#undef LAST_FIELD
#define LAST_FIELD tcprod

// the current production. It is basically the index of the type being produced.
// Now, this introduces a _VERY_ nasty dependency, since this puts a limit on
// the number of different types we can define, for _everything_. This is
// obviously kind of a problem, but I hope that we left enough headroom when
// defining most fields that, by the time, this becomes a problem, we will all
// be older and wiser.
MAW_DECL_BITS(city_t, 10, cprod, uint16_t)
#undef LAST_FIELD
#define LAST_FIELD cprod

// this is a typedef for an enemy city. We don't need that much information in
// this, pretty much only the player, to know which color the city should be,
// the size and whether or not there is a unit in the city. Now, on occasion, we
// will need to know what tiles an enemy city works, in order to know what tile
// our on city can work, but we can't send the information about what tiles each
// enemy city works. Partly because it will be redundant in like 99% of the
// cases and partly because that would give the client information it shouldn't
// have. So instead I think we will send all tiles which are within reach of one
// of our cities, but is being worked by an enemy city as separate pos_t instances.
typedef uint16_t en_city_t;
  
#undef LAST_FIELD
#define LAST_FIELD en_city_t
MAW_DECL_DUMMY_OFFS(en_city_t)

// number of citizens in the enemy city
MAW_DECL_BITS(en_city_t, en_nctzn, 8, uint8_t)
#undef LAST_FIELD
#define LAST_FIELD en_nctzn

// whether or not the city has any units in it
MAW_DECL_BITS(en_city_t, en_ppltd, 1, bool)
#undef LAST_FIELD
#define LAST_FIELD en_ppltd


// this is a typedef for a worked tile bitmask. Basically, this is to keep track
// of which tiles in the vicinity of a city are being worked by that city. It
// would have been nice to fit this in the city_t, but that would have been too
// tight. The nice thing about this is that we can make it a larger type if we
// want cities to be able to work tiles further away than 2, the default in civ
// 2.
// Anyway, this is a vector of bits, 1 if that tile is worked, 0 if it isn't.
// The tiles around the city will have to be numbered in some sensible way, but
// here we needn't concern ourselves with that.
typedef uint32_t w_tile_t;


typedef struct city {
  // the player the city belongs to
  plyr::plyr_id_t plyr;
  // the actual city_t
  city_t city;
  // worked tiles
  w_tile_t w_tiles;
} city;


typedef struct en_city {
  plyr::plyr_id_t plyr;
  en_city_t city;
}
} // end namespace city
} // end namespace common
} // end namespace maw
#endif // CITY_HPP
