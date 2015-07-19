dnl Copyright (C) 2015, The MaW Team
dnl
dnl This program is free software: you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation, either version 3 of the License, or
dnl (at your option) any later version.
dnl
dnl This program is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.
dnl
dnl You should have received a copy of the GNU General Public License
dnl along with this program.  If not, see <http://www.gnu.org/licenses/>.
dnl
dnl All unit types inherit unit_type
dnl They also inherit a specific type, depending on if they are air, land, sea or amphibious units.
class name : public unit_type {
  public:
  name`()': unit_type(
    translit(supertype, `[a-z]', `[A-Z]'), // stype
    movement,  // movs
    attack,    // atk
    defense,   // dfns
    health,    // hlth
    ifdef(`upgrades_to', `UPPER(`upgrades_to')', `MAW_UNIT_TYPE_NONE'), // upgrd
    ifdef(`splash_damage', `splash_damage', `0'),  // splsh
    {ifdef(`requires', `UPPER(`requires')', `MAW_RESC_NONE')}, // req_rescs
    {ifdef(can_see, `UPPER(`can_see')', `MAW_UNIT_TYPE_NONE')}, // can_see
    ifelse(movement_class, `land', `LAND', movement_class, `air', `AIR', movement_class, `helicopter', `HELI', movement_class, `sea', `SEA'), // mvmt_cls
    ifdef(worker_unit, `worker_unit', `false'), // worker
    ifdef(settler, `settler', `false'), // settler
    ifdef(hidden, `hidden', `false'), // hidden
    ifdef(oneshot, `oneshot', `false') // oneshot
  )  {}

  virtual float atk_bonus_unit(const maw_unit_info target) const {
    switch(maw_get_unit_type(target)) {ifdef(`attack_bonus_unit', `attack_bonus_unit')
    default: return 0f;
    }
  }
  virtual float def_bonus_unit(maw_unit_info target) const {
    switch(get_unit_supertype(target)) {ifdef(`defense_bonus_unit', `defense_bonus_unit')
    default: return 0f;
    }
  }
  virtual float def_bonus_terr(const map::maw_tile on) const {
    switch(maw_get_terr(on)) {ifdef(`defense_bonus_terrain', `defense_bonus_terrain')
    default: return 0f;
    }
  }
  virtual float atk_bonus_terr(map::maw_tile from,
                               map::maw_tile to) const {
    ifdef(`attack_bonus_terrain', `attack_bonus_terrain')
    return 0f;
  }
  virtual unisgned mov
  virtual movp mov_cst(map::tile_t to) const {
    get_uniq_mov_cst(to)
};

