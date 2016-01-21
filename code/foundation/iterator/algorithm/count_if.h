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
#ifndef NIC_49FE3AC9954AA2CE_NIC
#define NIC_49FE3AC9954AA2CE_NIC

#include "../traits.h"

namespace nebula { namespace foundation { namespace iterator {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
template <class I>
struct count_if_impl
{
    template <class F_>
    inline static typename iterator_difference<I>::type apply(
        I first, const I last, F_ &&f)
    {
        typename iterator_difference<I>::type r = 0;
        while(first != last)
            if(f(*first++))
                r++;
        return r;
    }
};
//------------------------------------------------------------------------------
/** Calculates the number elements e in the range where f(x) returns true.
 * @param I Must be an incrementable iterator.
 * @param f A simple unary predicate.
 * @return The number elements e in the range where f(e) returns true.
 * @note Does not throw if f() does not throw either.
 * @note Strong exception guarantee.
 * */
template <class I, class F>
inline typename iterator_difference<I>::type count_if(I first, I last, F &&f)
{
    return count_if_impl<I>::apply(first, last, f);
}

/** @} */

}}} // namespaces

#endif // NIC_49FE3AC9954AA2CE_NIC
