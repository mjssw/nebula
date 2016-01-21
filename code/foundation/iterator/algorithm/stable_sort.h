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
#ifndef NIC_607565C00302D4D5_NIC
#define NIC_607565C00302D4D5_NIC

#include "distance.h"
#include "iter_swap.h"

namespace nebula { namespace foundation { namespace iterator {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
namespace iterator_detail {
//------------------------------------------------------------------------------
template <class I, class F>
inline void asd(I first, I last, F &f)
{
    using D = typename iterator_difference<I>::type;
    const D dist = iterator::distance(first, last);
    if(dist < 2)
        return;
    const I pivot = last - 1;
    iterator::iter_swap(first + (dist/2), pivot);
    I i = first;
    I j = last - 2;
    do 
    {
        for( ; (i < last - 1) && f(*i, *pivot); ++i)
            ;
        for( ; (j > first) && !f(*j, *pivot); --j)
            ;
        if(i < j)
            iterator::iter_swap(i, j);
    } while(i < j);
    
    if(!f(*i, *pivot))
        iterator::iter_swap(i, pivot);
    iterator_detail::asd(first, i, f);
    iterator_detail::asd(i + 1, last, f);
}
//------------------------------------------------------------------------------
} // iterator_detail
//------------------------------------------------------------------------------
template <class I>
struct stable_sort_impl
{
    template <class Comp>
    inline static void apply(I first, I last, Comp &&c) 
    {
        iterator_detail::asd(first, last, c);
    }
};
//------------------------------------------------------------------------------
template <class I, class Comp>
inline void stable_sort(I first, I last, Comp &&c)
{
    stable_sort_impl<I>::apply(first, last, c);
}

/** @} */

}}} // namespaces

#endif // NIC_607565C00302D4D5_NIC