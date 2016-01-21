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
#ifndef NIC_4054A6C7EA6394F4_NIC
#define NIC_4054A6C7EA6394F4_NIC

#include "../vector.h"

#include "../basic/abs.h"
#include "../../array.h"

namespace nebula { namespace foundation { namespace math { namespace linalg {
/** @ingroup Foundation
 * @{
 * */
namespace determinant_detail {
//------------------------------------------------------------------------------
template <class T>
inline T det33(
    const T &e11, const T &e12, const T &e13,
    const T &e21, const T &e22, const T &e23,
    const T &e31, const T &e32, const T &e33)
{
    return
        e11 * (e22*e33 - e23*e32)
        + e12 * (e23*e31 - e21*e33)
        + e13 * (e21*e32 - e22*e31);
}
//------------------------------------------------------------------------------
template <class T>
inline T det44(
    const T &e11, const T &e12, const T &e13, const T &e14,
    const T &e21, const T &e22, const T &e23, const T &e24,
    const T &e31, const T &e32, const T &e33, const T &e34,
    const T &e41, const T &e42, const T &e43, const T &e44)
{
    return
        e11 * det33(
            e22,e23,e24,
            e32,e33,e34,
            e42,e43,e44)
        -     e12 * det33(
                e21,e23,e24,
                e31,e33,e34,
                e41,e43,e44)
        +     e13 * det33(
                e21,e22,e24,
                e31,e32,e34,
                e41,e42,e44)
        -     e14 * det33(
                e21,e22,e23,
                e31,e32,e33,
                e41,e42,e43);
}

//------------------------------------------------------------------------------
template <class Matrix>
inline vec::_scalar_value<Matrix> det(Matrix m)
{
    array<size_t, vec::size_at<Matrix,0>::type::value> im; // index map
    
    for(size_t i = 0; i < vec::size_at<Matrix,0>::type::value; ++i)
        im[i] = i;
    
    int signum = 1;
    
    for(size_t i = 0; i < vec::size_at<Matrix,1>::type::value-1; ++i)
    {
        // partial pivoting
        size_t K = i;
        vec::_scalar_value<Matrix> best = math::abs(m(im[i],i));
        
        for(size_t j = i+1; j < vec::size_at<Matrix,0>::type::value; ++j)
        {
            const vec::_scalar_value<Matrix> cur
                = math::abs(m(im[j],i));
            if(cur > best)
            {
                K = j;
                best = cur;
            }
        }
        if(K != i)
        {
            foundation::swap(im[i], im[K]);
            signum *= -1;
        }
         
        // Gauss elimination
        for(size_t j = i+1;
            j < vec::size_at<Matrix,0>::type::value;
            ++j)
        {
            const vec::_scalar_value<Matrix> _t 
                = -m(im[j],i) / m(im[i],i);

            for(size_t k = i+1;
                k < vec::size_at<Matrix,0>::type::value;
                ++k)
            {
                vm(im[j],k) += _t * m(im[i],k);
            }
        }
    }

    vec::_scalar_value<Matrix> r = m(im[0],0);
    for(size_t i = 1; i < vec::size_at<Matrix,0>::type::value; ++i)
        r *= m(im[i],i);

    return r * vec::_scalar_value<Matrix>(signum);
}

} // determinant_detail

//------------------------------------------------------------------------------
template <class Matrix>
struct determinant_impl
{
    template <class Matrix_>
    inline static vec::_scalar_value<Matrix> apply(Matrix_ &&m)
    {
        switch(vec::_size<Matrix>::value)
        {
        case 1: // 1x1
            return m(0,0);

        case 4: // 2x2
            return m(0,0)*m(1,1)
                - m(0,1)*m(1,0);

        case 9: // 3x3
            return determinant_detail::det33(
                m(0,0), m(0,1), m(0,2),
                m(1,0), m(1,1), m(1,2),
                m(2,0), m(2,1), m(2,2));

        case 16: // 4x4
            return determinant_detail::det44(
                m(0,0), m(0,1), m(0,2), m(0,3),
                m(1,0), m(1,1), m(1,2), m(1,3),
                m(2,0), m(2,1), m(2,2), m(2,3),
                m(3,0), m(3,1), m(3,2), m(3,3));

        default: // NxN
            return determinant_detail::det(
                foundation::forward<Matrix_>(m));
        }
    }
};
//------------------------------------------------------------------------------
template <class Matrix_,
    class Matrix = ctraits::_value<Matrix_>>
inline vec::_scalar_value<Matrix> determinant(Matrix_ &&m)
{    
    n_static_assert(vec::_order<Matrix>::value == 2,
        "Matrix required.");
    n_static_assert(
        n_arg(vec::size_at<Matrix,0>::type::value
            == vec::size_at<Matrix,1>::type::value),
        "Square matrix required.");
    
    return determinant_impl<Matrix>::apply(
        foundation::forward<Matrix_>(m));
}

/** @} */

}}}} // namespaces

#endif // NIC_4054A6C7EA6394F4_NIC

