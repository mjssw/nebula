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
#ifndef NIC_8620B8A040B5BDE0_NIC
#define NIC_8620B8A040B5BDE0_NIC

#include "find_if.h"
#include "../../ops.h"

namespace nebula { namespace foundation { namespace iterator {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
template <class I>
struct find_impl
{
    template <class T, class P>
    inline static I apply(I first, const I last, const T &x, P &&p)
    {
        for( ; first != last; ++first)
        if(p(*first, x))
            return first;
        return last;
    }
};
//------------------------------------------------------------------------------
/** Find the first element in the range [first, last) that compares equal to x.
 * @param I Must be an incrementable iterator.
 * @note The supplied functor p is allowed to throw.
 * @note Strong exception guarantee.
 * */
template <class I, class T, class P = equal_to<>>
inline I find(I first, I last, const T &x, P &&p = P())
{
    return find_impl<I>::apply(first, last, x, p);
}

/** @} */

}}} // namespaces

#endif // NIC_8620B8A040B5BDE0_NIC
