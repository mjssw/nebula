/*--!>
This file is part of Nebula, a multi-purpose library mainly written in C++.

Copyright 2015-2016 (lis@tutanota.com)
    (PGP: 0x98E65B43B03E8A6B68BA3132568ACAF1A05DE1CE)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
--------------------------------------------------------------------------<!--*/
#ifndef NIC_36DF8E65804B7CF8_NIC
#define NIC_36DF8E65804B7CF8_NIC

#include "path.h"
#include "types.h"
#include "../dll_interface.h"

namespace nebula { namespace foundation { namespace filesystem {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
extern void n_foundation_dll create_directory(
    const path &, file_permission_type);

/** @} */

}}}

#endif // NIC_36DF8E65804B7CF8_NIC