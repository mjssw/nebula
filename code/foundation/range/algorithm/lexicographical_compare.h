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
#ifndef NIC_E9346193F94B0403_NIC
#define NIC_E9346193F94B0403_NIC

#include "../common.h"

namespace nebula { namespace foundation { namespace range {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class R0, class R1>
struct lexicographical_compare_impl
{
    template <class F_>
    inline static bool apply(const R0 &r0, const R1 &r1, F_ &&f)
    {
        return ins_::lexicographical_compare(
            range::begin(r0), range::end(r0),
            range::begin(r0), range::end(r0),
            f);
    }
};
//------------------------------------------------------------------------------
/**
 * */
template <class R0, class R1, class F>
inline bool lexicographical_compare(const R0 &r0, const R1 &r1, F &&f)
{
    return lexicographical_compare_impl<
        R0,
        R1
    >::apply(r0, r1, f);
}

/** @} */

}}} // namespaces

#endif // NIC_E9346193F94B0403_NIC
