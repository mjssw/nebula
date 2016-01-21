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
#ifndef NIC_E49A613B7E8E91CB_NIC
#define NIC_E49A613B7E8E91CB_NIC

#include "../common.h"

namespace nebula { namespace foundation { namespace range {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class R>
struct fill_impl
{
    template <class T>
    inline static void apply(R &r, const T &x)
    {
        ins_::fill(range::begin(r), range::end(r), x);
    }
};
//------------------------------------------------------------------------------
/**
 * */
template <class R, class T>
inline void fill(R &&r, const T &x)
{
    return fill_impl<
        typename ctraits::value<R>::type
    >::apply(r, x);
}

/** @} */

}}} // namespaces

#endif // NIC_E49A613B7E8E91CB_NIC
