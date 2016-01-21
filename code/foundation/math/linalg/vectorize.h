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
#ifndef NIC_B869065CC4D66EB7_NIC
#define NIC_B869065CC4D66EB7_NIC

#include "../vector.h"

namespace nebula { namespace foundation { namespace math { namespace mat {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <class Matrix>
class vectorize_impl
{
    using Ret = vec::_resize<
        Matrix,
        meta::seq<vec::_size<Matrix>>>;
    
public:
    inline static Ret apply(const Matrix &m)
    {
        Ret dst;
        // vectorization is column major.
        size_t k = 0;
        for(size_t i = 0; i < vec::size_at<Matrix, 1>::type::value; ++i)
            for(size_t j = 0; j < vec::size_at<Matrix, 0>::type::value; ++j)
                dst[k++] = m(j,i);
        return dst;
    }
};
//------------------------------------------------------------------------------
template <class Matrix,
    class DST = vec::_resize<
        Matrix,
        meta::seq<vec::_size<Matrix>>>>
inline DST vectorize(const Matrix &m)
{    
    n_static_assert(vec::_order<DST>::value == 1,
        "Matrix required.");
    n_static_assert(vec::_order<Matrix>::value == 2,
        "Matrix required.");
        
    n_static_assert(
        n_arg(vec::size<Matrix>::type::value
            == vec::size<DST>::type::value),
        "Invalid coordinate count.");
    
    return vectorize_impl<Matrix>::apply(m);
}

/** @} */

}}}} // namespaces

#endif // NIC_B869065CC4D66EB7_NIC

