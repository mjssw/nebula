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
#ifndef NIC_72545B5EB6028DC0_NIC
#define NIC_72545B5EB6028DC0_NIC

#include "../vector.h"

namespace nebula { namespace foundation { namespace math { namespace linalg {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <class Matrix>
struct forward_substitution_impl
{
    template <class Vector>
    inline static Vector apply(const Matrix &m, Vector b)
    {
        b[0] = b[0] / m(0,0);
    
        for(size_t i = 1; i < vec::_size<Vector>::value; ++i)
        {
            vec::_scalar_value<Vector> tmp = m(i,0) * b[0];
            for(size_t j = 1; j < i; ++j)
                tmp += m(i,j) * b[j];
            b[i] = (b[i] - tmp) / m(i,i);
        }
        
        return foundation::move(b);
    }
};

//------------------------------------------------------------------------------
template <class Matrix, class Vector_,
    class Vector = ctraits::_value<Vector_>>
inline Vector forward_substitution(const Matrix &m, Vector_ &&b)
{    
    n_static_assert(vec::_order<Matrix>::value == 2,
        "Matrix required.");
    n_static_assert(
        n_arg(vec::size_at<Matrix,0>::type::value
            == vec::size_at<Matrix,1>::type::value),
        "Square matrix required.");
    n_static_assert(
        n_arg(vec::_size<Vector>::value == vec::size_at<Matrix,0>::type::value),
        "Invalid vector size.");
    
    return forward_substitution_impl<Matrix>::apply(m,
        foundation::forward<Vector_>(b));
}

/** @} */

}}}} // namespaces

#endif // NIC_72545B5EB6028DC0_NIC

