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
#ifndef NIC_258CB1070D2FB7D2_NIC
#define NIC_258CB1070D2FB7D2_NIC

#include "../vector.h"

namespace nebula { namespace foundation { namespace math { namespace linalg {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <class Matrix>
class transpose_impl
{
    using Ret = vec::_resize<Matrix,
        meta::seq<
            typename vec::size_at<Matrix,1>::type,
            typename vec::size_at<Matrix,0>::type>>;

public:
    template <class Matrix_,
        class M = Matrix,
        _enable_if_c<
            (vec::size_at<M,0>::type::value 
            != vec::size_at<M,1>::type::value)
            || is_lvalue_reference<Matrix_>::type::value>* = nullptr>
    inline static Ret apply(Matrix_ &&v)
    {
        Ret dst;
        for(size_t row = 0; row < vec::size_at<Matrix, 0>::type::value; ++row)
        {
            for(size_t col = 0; col < vec::size_at<Matrix, 1>::type::value;
                ++col)
            {
                dst(row, col) = v(col, row);
            }
        }
        return dst;
    }
    template <class Matrix_,
        _disable_if<is_lvalue_reference<Matrix_>>* = nullptr,
        class M = Matrix,
        _disable_if_c<vec::size_at<M,0>::type::value 
            != vec::size_at<M,1>::type::value>* = nullptr>
    inline static Matrix apply(Matrix_ &&v)
    {
        for(size_t row = 1; row < vec::size_at<Matrix, 0>::type::value; ++row)
        {
            for(size_t col = 0; col < row; ++col)
            {
                foundation::swap(v(row, col), v(col, row));
            }
        }
        return foundation::move(v);
    }
};
//------------------------------------------------------------------------------
template <class Matrix_,
    class Matrix = ctraits::_value<Matrix_>, 
    class Ret = vec::_resize<
        Matrix,
        meta::seq<
            typename vec::size_at<Matrix,1>::type,
            typename vec::size_at<Matrix,0>::type>>>
inline Ret transpose(Matrix_ &&m)
{    
    n_static_assert(vec::_order<Matrix>::value == 2,
        "Matrix required.");
    
    return transpose_impl<Matrix>::apply(
        foundation::forward<Matrix_>(m));
}

/** @} */

}}}} // namespaces

#endif // NIC_258CB1070D2FB7D2_NIC

