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
#ifndef NIC_21EDB7A9E5DF7121_NIC
#define NIC_21EDB7A9E5DF7121_NIC

#include "for_each.h"
#include "../../move.h"

namespace nebula { namespace foundation { namespace iterator {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
template <class I, class O>
struct swap_impl
{
    inline static O apply(I first, I last, O dest)
    {
        iterator::for_each(first, last, 
            [&] (typename iterator_reference<I>::type x) 
            { 
                foundation::swap(*dest++, x);
            }
        );
        return dest;
    }
};
//------------------------------------------------------------------------------
/** Swaps ranges. */
template <class I, class O>
inline O swap(I first, I last, O dest)
{
    return swap_impl<I, O>::apply(first, last, dest);
}
//------------------------------------------------------------------------------
/** Only for std compliance. It calls iterator::swap(). */
template <class I, class O>
inline O swap_ranges(I first, I last, O dest)
{
    return iterator::swap(first, last, dest);
}

/** @} */

}}} // namespaces

#endif // NIC_21EDB7A9E5DF7121_NIC