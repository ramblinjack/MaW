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

dnl We assume no field is larger than 32 bits... This will undoubtedly bite us
dnl in the ass later...
uint32_t `maw_get_'FIELD_NAME`('DATA_TYPE in);
void `maw_set_'FIELD_NAME`('DATA_TYPE *target, uint32_t value);
