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
dnl This macro expects the following macros to be defined:
dnl FIELD_NAME: the field to generate getter and setters for
dnl DATA_TYPE: the data type the functions should opoerate on
dnl OFFS: the current offset in the bitmask
dnl SIZE: the size of the bitfield
dnl
dnl the use of unsigned long long here is no good for windoze compatibility, but
dnl we'll worry about that later
dnl
dnl This is a helper macro to generate a mask between $1 and $2
define(`BMASK', `((2ULL << (`$1')) - (1ULL<<(`$2')))')dnl
dnl This is a helper macro to calculate the upper limit
define(`UPPER', `OFFS + SIZE - 1')dnl
dnl
dnl We assume no field is larger than 32 bits... This will undoubtedly bite us
dnl in the ass later...
uint32_t `maw_get_'FIELD_NAME`('DATA_TYPE in) {
  return (uint32_t) ((in & BMASK(UPPER, OFFS)) >> OFFS);
}
void `maw_set_'FIELD_NAME`('DATA_TYPE *target, uint32_t value) {
  *target = (*target & ((DATA_TYPE)(~BMASK(UPPER, OFFS)) |
         (((uint64_t) value) << OFFS)));
}
