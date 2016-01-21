/*--!>
This file is part of Nebula, a multi-purpose library mainly written in C++.

Copyright 2015-2016 lis (lis@tutanota.com)
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
#ifndef NIC_8C73DBD3DD967699_NIC
#define NIC_8C73DBD3DD967699_NIC

#include "path.h"
#include "../vector.h"
#include "../function.h"
#include "../dll_interface.h"

namespace nebula { namespace foundation { namespace filesystem {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
using recursive_scan_callback = function<bool (path, size_t)>;
//------------------------------------------------------------------------------
extern void n_foundation_dll recursive_scan(
    const path &,
    const recursive_scan_callback &);
//------------------------------------------------------------------------------
extern void n_foundation_dll recursive_scan(
    const path &,
    const size_t max_depth,
    const recursive_scan_callback &);

/** @} */

}}}

#endif // NIC_8C73DBD3DD967699_NIC
