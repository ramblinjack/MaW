#ifndef GPHX_OBJ_H
#define GPHX_OBJ_H

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
  This file defines a grapics object. A grpahic object is something which has
  graphics basically. The idea is that the unit and terrain classes and stuff
  which are compiled in should be conditionally compiled so that when they are
  compiled for the client they can extend this class. That way we don't need to
  pull in a lot of sdl dependencies in the server. So in the autogenerated files
  for the different unit types we should have something like this:

  class tank : public unit_type
  #ifdef CLIENT
  ,client::gphx_obj
  #endif
  {
    // stuff
  };
  
 */

// TODO: include sdl stuff here...
#include <string>

namespace maw {
namespace client {

class gphx_obj {
private:
  // The icon and an optional background. We need this background for terrain
  // types which have a background, like forrest. This whole thing is compiled
  // in, not sent over the network, so it doesn't really matter.
  const SDL_surface *icon, *bkgrnd;

  // Description of this object.
  const std::string descr;

  // Name of this object
  const std::string name;

public:
  gphx_obj(SDL_surface icon, SDL_surface bkgrnd = nullptr,
           std::string descr, std::string name):
    icon(icon),
    bkgrnd(bkgrnd),
    descr(descr),
    name(name) {}

  std::string get_name() const {return name;}
  std::string get_descr() const {return descr;}
  SDL_surface get_icon() const {return icon;}
  SDL_surface get_bkgrnd() const {return bkgrnd;}
};
#endif // ifndef GPHX_OBJ_H
