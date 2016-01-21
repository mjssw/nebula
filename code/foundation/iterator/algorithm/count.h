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
#ifndef NIC_16609A7245FF9AB8_NIC
#define NIC_16609A7245FF9AB8_NIC

#include "../traits.h"

namespace nebula { namespace foundation { namespace iterator {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
template <class I>
struct count_impl
{
    template <class T>
    inline static typename iterator_difference<I>::type apply(
        const I first, const I last, const T &x)
    {
        return iterator::count_if(first, last,
            [&] (const typename iterator_value<I>::type &y) -> bool
            {
                return y == x;
            }
        );
    }
};
//------------------------------------------------------------------------------
/** Calculates the number elements e in the range where e == x.
 * @param I Must be an incrementable iterator.
 * @param x The object we compare elements with.
 * @return The number elements e in the range where e == x.
 * @note Does not throw if the comparison elements does not throw either.
 * @note Strong exception guarantee.
 * */
template <class I, class T>
inline typename iterator_difference<I>::type count_if(
    I first, I last, const T &x)
{
    return count_impl<I>::apply(first, last, x);
}

/** @} */

}}} // namespaces

#endif // NIC_16609A7245FF9AB8_NIC
