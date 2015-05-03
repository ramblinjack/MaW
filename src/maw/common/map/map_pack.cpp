/*
 * Copyright (C) 2015, The Maw Team
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

#include "map_pack.h"

namespace maw {
namespace common {
namespace map {

void init_map() {
  all_terrains = init_terrains();
  all_resources = init_resources();
  all_terrains = init_terrains();
}    

unsigned food_on_tile(tile_t tile) {
  terrain *t = get_terrain(tile);
  resource *r = get_resource(tile);
  improvement *i = get_improvement(tile);
  unsigned food = t->get_food();
  if (r != nullptr && r->is_food_bonus()) food += r->food_bonus(tile);
  if (i != nullptr && i->is_food_bonus()) food += i->food_bonus(tile);
  return food;
}

unsigned prod_on_tile(tile_t tile) {
  terrain *t = get_terrain(tile);
  resource *r = get_resource(tile);
  improvement *i = get_improvement(tile);
  unsigned prod = t->get_prod();
  if (r != nullptr && r->is_prod_bonus()) prod += r->prod_bonus(tile);
  if (i != nullptr && i->is_prod_bonus()) prod += i->prod_bonus(tile);
  return prod;
}

unsigned trade_on_tile(tile_t tile) {
  terrain *t = get_terrain(tile);
  resource *r = get_resource(tile);
  improvement *i = get_improvement(tile);
  unsigned trade = t->get_trade();
  if (r != nullptr && r->is_trade_bonus()) trade += r->trade_bonus(tile);
  if (i != nullptr && i->is_trade_bonus()) trade += i->trade_bonus(tile);
  return trade;
}

resource_t resource_on_tile(tile_t tile) {
  const resc_t r = get_resc(tile);
  if (r == RESOURCE_T_NONE) return r;
  const imprvt_t rqd_imprv = all_resources->at(r)->is_provided_by();
  if (get_imprv(tile) == rqd_imprv) return r;
  else return RESOURCE_T_NONE;
}

} // end namespace map
} // end namespace common
} // end namespace maw
