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
dnl This file defines some common macros, which can be useful in all the
dnl different packages.
dnl 
dnl This is the epitome of elegance, no?
define(`QUOTEIT', ```$*''')
define(`UPPER', `translit(QUOTEIT($1), `[a-z]', `[A-Z]')')
