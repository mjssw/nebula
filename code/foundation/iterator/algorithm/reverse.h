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
#ifndef NIC_49BE2D37ACC6D0CD_NIC
#define NIC_49BE2D37ACC6D0CD_NIC

#include "iter_swap.h"

namespace nebula { namespace foundation { namespace iterator {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
template <class I>
struct reverse_impl
{
    inline static void apply(I first, I last)
    {
        while((first != last) && (first != --last))
            iterator::iter_swap(first++, last);
    }
};
//------------------------------------------------------------------------------
template <class I>
inline void reverse(I first, I last)
{
    reverse_impl<I>::apply(first, last);
}

/** @} */

}}} // namespaces

#endif // NIC_49BE2D37ACC6D0CD_NIC
