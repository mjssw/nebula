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
#ifndef NIC_A8F14A83E0DECFE1_NIC
#define NIC_A8F14A83E0DECFE1_NIC

#include "../common.h"

namespace nebula { namespace foundation { namespace range {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class R>
struct find_impl
{
    template <class R_, class T>
    inline static 
    typename range_iterator<typename remove_reference<R_>::type>::type
    apply(R_ &&r, const T &x)
    {
        return ins_::find(range::begin(r), range::end(r), x);
    }
};
//------------------------------------------------------------------------------
/**
 * */
template <class R, class T>
inline typename range_iterator<typename remove_reference<R>::type>::type
find(R &&r, const T &x)
{
    return find_impl<
        typename ctraits::value<R>::type
    >::apply(foundation::forward<R>(r), x);
}

/** @} */

}}} // namespaces

#endif // NIC_A8F14A83E0DECFE1_NIC
