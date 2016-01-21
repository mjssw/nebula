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
#ifndef NIC_00701A16DDC3E5E5_NIC
#define NIC_00701A16DDC3E5E5_NIC

#include "utils.h"

namespace nebula { namespace foundation { namespace utf {
namespace unistring {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
inline block_t block(const char32_t c)
{
    const ::uc_block_t *r = ::uc_block(::ucs4_t(c));
    return block_t{r->start, r->end, r->name};
}

/** @} */

}}}} // namespaces

#endif // NIC_00701A16DDC3E5E5_NIC

