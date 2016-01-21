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
#ifndef NIC_8F4FF2BEDD0D0953_NIC
#define NIC_8F4FF2BEDD0D0953_NIC

#include "distance.h"

namespace nebula { namespace foundation { namespace iterator {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
namespace iterator_detail {
//------------------------------------------------------------------------------
template <class I, class Trav = typename iterator_traversal<I>::type>
struct advance_impl_
{
    template <class Offset>
    inline static void apply(I &i, const Offset &off) {
        for(Offset o = 0; o < off; ++o)
            i++;
    }
};
template <class I>
struct advance_impl_<I, bidirectional_traversal_tag> 
{
    template <class Offset>
    inline static void apply(I &i, const Offset &off) {
        if(off < 0) {
            for(Offset o = 0; o < -off; ++o)
                i--;
        } else {
            for(Offset o = 0; o < off; ++o)
                i++;
        }
    }
};
template <class I>
struct advance_impl_<I, random_access_traversal_tag> 
{
    template <class Offset>
    inline static void apply(I &i, const Offset &off) {
        i += off;
    }
};
//------------------------------------------------------------------------------
} // iterator_detail
//------------------------------------------------------------------------------
template <class I>
struct advance_impl : public iterator_detail::advance_impl_<I> {};
//------------------------------------------------------------------------------
template <class I, class Offset>
inline void advance(I &i, const Offset &off)
{
    advance_impl<I>::apply(i, off);
}

//------------------------------------------------------------------------------
template <class I, class Offset>
inline I advanced(I i, const Offset &off)
{
    iterator::advance(i, off);
    return i;
}

/** @} */

}}} // namespaces

#endif // NIC_8F4FF2BEDD0D0953_NIC