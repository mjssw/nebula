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
#ifndef NIC_FDC6A66EB559FB94_NIC
#define NIC_FDC6A66EB559FB94_NIC

#include "traits.h"

namespace nebula { namespace foundation { namespace math { namespace perm {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <class P>
struct pow_impl
{
    template <class P_,
        size_t N = perm::_size<P>::value,
        _enable_if_c<N<=1>* = nullptr>
    inline static P apply(P_ &&x, const size_t n)
    {
        return foundation::forward<P_>(x);
    }
    
    template <class P_,
        size_t N = perm::_size<P>::value,
        _enable_if_c< (N > 1) >* = nullptr>
    inline static P apply(P_ &&x, const size_t n)
    {
        P y;
        if(n == 0)
            y = perm::make_identity<P>();
        else if(n == 1)
            y = foundation::forward<P_>(x);
        else
        {
            for(size_t i = 0; i < _size<P>::value; ++i)
            {
                size_t k = x[i];
                for(size_t j = 2; j < n; ++j)
                {
                    k = x[k];
                }
                y[i] = k;
            }
        }
        return y;
    }
};
//------------------------------------------------------------------------------
template <class P>
inline ctraits::_value<P> pow(P &&x, const size_t n)
{
    return pow_impl<ctraits::_value<P>>::apply(foundation::forward<P>(x), n);
}

/** @} */

}}}} // namespaces

#endif // NIC_FDC6A66EB559FB94_NIC

