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
#ifndef NIC_5948946F549D4578_NIC
#define NIC_5948946F549D4578_NIC

#include "distance.h"
#include "../../call_traits.h"
#include "../../type_traits.h"
#include "../../ops.h"
#include "../../enable_if.h"
#include "../../meta.h"
#include "../../str.h"

namespace nebula { namespace foundation { namespace iterator {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
namespace iterator_detail {
//------------------------------------------------------------------------------
template <class I0, class I1, class F, bool Can_memcmp>
struct equal_impl_
{
    template <class F_,
        class Cond = meta::_and<
            has_tag<typename iterator_category<I0>::type,
                random_access_traversal_tag>,
            has_tag<typename iterator_category<I1>::type,
                random_access_traversal_tag>>,
        typename enable_if<Cond>::type* = nullptr>
    inline static bool apply(
        I0 first0, I0 last0,
        I1 first1, I1 last1,
        F_ &&f)
    {
        if(iterator::distance(first0, last0)
            != iterator::distance(first1, last1))
            return false;
        for( ; first0 != last0; ++first0, ++first1)
            if(!f(*first0, *first1))
                return false;
        return true;
    }
    
    template <class F_,
        class Cond = meta::_and<
            has_tag<typename iterator_category<I0>::type,
                random_access_traversal_tag>,
            has_tag<typename iterator_category<I1>::type,
                random_access_traversal_tag>>,
        typename disable_if<Cond>::type* = nullptr>
    inline static bool apply(
        I0 first0, I0 last0,
        I1 first1, I1 last1,
        F_ &&f)
    {
        for( ; first0 != last0 && first1 != last1; ++first0, ++first1)
            if(!f(*first0, *first1))
                return false;
        if(first0 != last0 || first1 != last1)
            return false;
        return true;
    }
};
//------------------------------------------------------------------------------
template <class I0, class I1>
struct equal_impl_<I0, I1, equal_to<>, true>
{
    inline static bool apply(
        I0 first0, I1 last0,
        I0 first1, I1 last1,
        equal_to<>)
    {
        if(last0-first0 != last1-first1)
            return false;
        return memcmp(first0, first1, 
            sizeof(typename remove_pointer<I0>::type) * (last1 - first1)) == 0;
    }
};
//------------------------------------------------------------------------------
} // iterator_detail
//------------------------------------------------------------------------------
template <class I0, class I1>
struct equal_impl
{
    template <class F>
    inline static bool apply(
        I0 first0, I1 last0,
        I0 first1, I1 last1,
        F &&f)
    {
        return iterator_detail::equal_impl_<
            I0,
            I1, 
            typename ctraits::value<F>::type,
            is_pod<typename iterator_value<I0>::type>::value
            && is_pointer<I0>::value
            && is_pointer<I1>::value
            && is_same<typename iterator_value<I0>::type,
                typename iterator_value<I1>::type>::value
            >::apply(
                first0, last0,
                first1, last1,
                f);
    }
};
//------------------------------------------------------------------------------
template <class I0, class I1, 
    class F = equal_to<>>
inline bool equal(
    I0 first0, I0 last0,
    I1 first1, I1 last1,
    F &&f = F())
{
    return equal_impl<I0, I1>::apply(first0, last0, first1, last1, f);
}

/** @} */

}}} // namespaces

#endif // NIC_5948946F549D4578_NIC
