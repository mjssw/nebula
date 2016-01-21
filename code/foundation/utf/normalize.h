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
#ifndef NIC_4B22005E2575D892_NIC
#define NIC_4B22005E2575D892_NIC

#include "config.h"
#include "types.h"
#include "../range.h"

#ifdef N_UTF_unistring
#   include "unistring/normalize.h"
#endif

namespace nebula { namespace foundation { namespace utf {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <class String>
struct normalize_impl
{
    template <class OutString>
    inline static void apply(
        const String &s, const normal_form nf, OutString &out)
    {
        #ifdef N_UTF_unistring
        unistring::normalize(s.data(), range::size(s), nf, out);
        #endif
    }
};
//------------------------------------------------------------------------------
template <class InString, class OutString>
inline void normalize(const InString &s, const normal_form nf, OutString &out)
{
    return normalize_impl<InString>::apply(s, nf, out);
}

/** @} */

}}} // namespaces

#endif // NIC_4B22005E2575D892_NIC

