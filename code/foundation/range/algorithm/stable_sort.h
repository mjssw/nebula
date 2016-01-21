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
#ifndef NIC_EEF7DBBD8A083B48_NIC
#define NIC_EEF7DBBD8A083B48_NIC

#include "../common.h"

namespace nebula { namespace foundation { namespace range {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class R>
struct stable_sort_impl
{
    template <class F_>
    inline static void apply(R &r, F_ &&f)
    {
        ins_::stable_sort(range::begin(r), range::end(r), f);
    }
};
//------------------------------------------------------------------------------
/**
 * */
template <class R, class F>
inline void stable_sort(R &&r, F &&f)
{
    return stable_sort_impl<
        typename ctraits::value<R>::type
    >::apply(r, f);
}

/** @} */

}}} // namespaces

#endif // NIC_EEF7DBBD8A083B48_NIC
