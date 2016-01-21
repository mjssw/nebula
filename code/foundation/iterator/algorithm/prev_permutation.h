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
#ifndef NIC_944EC6CCAC726AA0_NIC
#define NIC_944EC6CCAC726AA0_NIC

#include "iter_swap.h"
#include "reverse.h"

#include "../../ops.h"

namespace nebula { namespace foundation { namespace iterator {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
template <class I>
struct prev_permutation_impl
{
    template <class F>
    inline static bool apply(I first, I last, F &&f)
    {
        if(first == last)
            return false;
        I i = last;
        if(first == --i)
            return false;
     
        while(true)
        {
            I a, b;
     
            a = i;
            if(f(*a, *--i))
            {
                b = last;
                
                while(!f(*--b, *i))
                    ;
                
                iterator::iter_swap(i, b);
                iterator::reverse(a, last);
                
                return true;
            }
            if(i == first)
            {
                iterator::reverse(first, last);
                return false;
            }
        }
    }
};
//------------------------------------------------------------------------------
template <class I, class F = less<>>
inline bool prev_permutation(I first, I last, F &&f = F())
{
    return prev_permutation_impl<I>::apply(first, last, f);
}

/** @} */

}}} // namespaces

#endif // NIC_944EC6CCAC726AA0_NIC
