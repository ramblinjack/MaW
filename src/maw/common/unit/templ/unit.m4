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
class NAME : public unit_type, ifdef(`LAND_UNIT', `land_unit', ifdef(`AIR_UNIT', `air_unit', ifdef(`SEA_UNIT', `sea_unit', ifdef(`AMPHIBIOUS_UNIT', `amphib_unit'))))
dnl If we are compiling the client, include all the graphics stuff
#ifdef CLIENT
,gphx_obj
#endif
{
  public:
  NAME`()': unit_type(SUPERTYPE, MOVEMENT, ATTACK, DEFENSE, HEALTH, ifdef(`UPGRADES_TO', `UPGRADES_TO', `UNIT_E_NONE'), ifdef(`SPLASH_DAMAGE', `SPLASH_DAMAGE', `0'), {ifdef(`REQUIRES', `REQUIRES', `RESOURCE_E_NONE')})
#ifdef CLIENT
  , gphx_obj(DATADIR "/resc/" "ICON", nullptr, "ifdef(`PRETTY_NAME', `PRETTY_NAME', `NAME')", "ifdef(`PLURAL', `PLURAL', `NAME')")
#endif            
  {}

  virtual float atk_bonus_unit(const unit_t target) const {
    switch(get_unit_type(target)->get_stype()) {ifdef(`ATTACK_BONUS_UNIT', `ATTACK_BONUS_UNIT')
    default: return 0f;
    }
  }
  virtual float def_bonus_unit(const unit_t target) const {
    switch(get_unit_type(target)->get_stype()) {ifdef(`DEFENSE_BONUS_UNIT', `DEFENSE_BONUS_UNIT')
    default: return 0f;
    }
  }
  virtual float def_bonus_terr(const map::tile_t on) const {
    switch(get_terr(on)) {ifdef(`DEFENSE_BONUS_TERRAIN', `DEFENSE_BONUS_TERRAIN')
    default: return 0f;
    }
  }
  virtual float atk_bonus_terr(const map::tile_t from,
                               const map::tile_t to) const { ifdef(`ATTACK_BONUS_TERRAIN', `ATTACK_BONUS_TERRAIN')
    return 0f;
  }
  virtual unisgned mov
  virtual movp mov_cst(map::tile_t to) const {
    get_uniq_mov_cst(to)
};
