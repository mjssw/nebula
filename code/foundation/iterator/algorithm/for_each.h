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
#ifndef NIC_520D8FACD43BCDD8_NIC
#define NIC_520D8FACD43BCDD8_NIC

#include "../traits.h"
#include "../../call_traits.h"
#include "../../move.h"

namespace nebula { namespace foundation { namespace iterator {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
template <class I, class F, class ... J>
struct for_each_impl
{
    template <class F_>
    inline static void apply(I first, const I last, F_ &&f, J ... rest)
    {
        while(first != last) {
            f(*first++, *rest++...);
        }
    }
};
//------------------------------------------------------------------------------
/** Invoke f(*i++, *rest++...) for each element i in [first, last).
 * @return The functor which has been passed to the function.
 * @note It is guaranteed that this function doesn't throw iff f doesn't throw.
 * */
template <class I, class F, class ... J>
inline F &&for_each(I first, I last, F &&f, J ... rest)
{
    for_each_impl<
        I,
        typename ctraits::value<F>::type,
        J...
    >::apply(first, last, f, rest...);
    return foundation::forward<F>(f);
}

/** @} */

}}} // namespaces

#endif // NIC_520D8FACD43BCDD8_NIC
