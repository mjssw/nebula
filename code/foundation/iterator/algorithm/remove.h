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
#ifndef NIC_B2A50821AE4C623A_NIC
#define NIC_B2A50821AE4C623A_NIC

#include "../traits.h"
#include "remove_if.h"

namespace nebula { namespace foundation { namespace iterator {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
template <class I>
struct remove_impl
{
    template <class T>
    inline static I apply(const I first, const I last, const T &x)
    {
        return iterator::remove_if(first, last,
            [&] (const typename iterator_value<I>::type &y) -> bool 
            {
                return y == x;
            }
        );
    }
};
//------------------------------------------------------------------------------
/** Removes all elements in the range [first, last) that are equal to x.
 * @param I Must be an incrementable iterator.
 * @param x Object to compare elements to.
 * @return An iterator one past the last element of the 'new' range.
 * @note Comparison of elements with x must not throw.
 * @note Moving of elements must not throw.
 * @throw nothing
 * */
template <class I, class T>
inline I remove(I first, I last, const T &x)
{
    return remove_impl<I>::apply(first, last, x);
}

/** @} */

}}} // namespaces

#endif // NIC_B2A50821AE4C623A_NIC
