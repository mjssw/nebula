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
#ifndef NIC_8B56C53F99223E53_NIC
#define NIC_8B56C53F99223E53_NIC

#include "generate_n.h"

namespace nebula { namespace foundation { namespace iterator {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
template <class I>
struct fill_n_impl
{
    template <class S, class T>
    inline static void apply(const I first, const S &n, const T &x)
    {
        iterator::generate_n(first, n,
            [&] () -> typename iterator_value<I>::type
            {
                return x;
            }
        );
    }
};
//------------------------------------------------------------------------------
/** Replaces all elements in the [first, first+n) with a copy of x.
 * @param I Must be an incrementable iterator.
 * @param x Objec which is copied to the range.
 * @return void
 * @return Weak exception safety - elements are replaces until the algo fails.
 * */
template <class I, class S, class T>
inline void fill_n(I first, const S &n, const T &x)
{
    fill_n_impl<I>::apply(first, n, x);
}

/** @} */

}}} // namespaces

#endif // NIC_8B56C53F99223E53_NIC
