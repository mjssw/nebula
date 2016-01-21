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
#ifndef NIC_29C55A7884BBDA5D_NIC
#define NIC_29C55A7884BBDA5D_NIC

#include "advance.h"
#include "../../ops.h"

namespace nebula { namespace foundation { namespace iterator {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
template <class I>
struct upper_bound_impl
{
    template <class T, class P>
    inline static I apply(I first, I last, const T &x, P &&p)
    {
        I i;
        typename iterator_difference<I>::type 
            count = distance(first, last),
            step;
    
        while(count > 0) {
            i = first;
            step = count / 2;
            iterator::advance(i, step);
            if(!p(x, *i)) {
                first = ++i;
                count -= step + 1;
            } 
            else
                count = step;
        }
        return first;
    }
};
//------------------------------------------------------------------------------
/** Similar to lower_bound().
 * @param I Must be a forward iterator.
 * @note The supplied functor p is allowed to throw.
 * @note Strong exception guarantee.
 * */
template <class I, class T, class P = less_equal<>>
inline I upper_bound(I first, I last, const T &x, P &&p = P())
{
    return upper_bound_impl<I>::apply(
        first, last, x, p);
}

/** @} */

}}} // namespaces

#endif // NIC_29C55A7884BBDA5D_NIC
