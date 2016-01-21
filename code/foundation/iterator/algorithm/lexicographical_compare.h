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
#ifndef NIC_1EA1D241B6DE2BDE_NIC
#define NIC_1EA1D241B6DE2BDE_NIC

#include "../traits.h"
#include "../../call_traits.h"
#include "../../ops.h"

namespace nebula { namespace foundation { namespace iterator {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
template <class I0, class I1>
struct lexicographical_compare_impl
{
    template <class F_>
    inline static bool apply(
        I0 first0, I0 last0,
        I1 first1, I1 last1,
        F_ &&f)
    {
        for( ; (first0 != last0) && (first1 != last1); first0++, first1++ )
        {
            if(f(*first0, *first1)) return true;
            if(f(*first1, *first0)) return false;
        }
        return (first0 == last0) && (first1 != last1);
    }
};
//------------------------------------------------------------------------------
template <class I0, class I1, 
    class F = less<typename iterator_value<I0>::type>>
inline bool lexicographical_compare(
    I0 first0, I0 last0,
    I1 first1, I1 last1,
    F &&f = F())
{
    return lexicographical_compare_impl<
        I0, 
        I1
    >::apply(first0, last0, first1, last1, f);
}

/** @} */

}}} // namespaces

#endif // NIC_1EA1D241B6DE2BDE_NIC
