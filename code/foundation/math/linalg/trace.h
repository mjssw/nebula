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
#ifndef NIC_2C6CF46549A848DC_NIC
#define NIC_2C6CF46549A848DC_NIC

#include "../vector.h"

namespace nebula { namespace foundation { namespace math { namespace linalg {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <class Matrix>
struct trace_impl
{
    inline static vec::_scalar_value<Matrix> apply(const Matrix &m)
    {
        vec::_scalar_value<Matrix> res = m(0, 0);
        for(size_t i = 1; i < vec::size_at<Matrix, 0>::type::value; ++i)
            res += m(i, i);
        return res;
    }
};
//------------------------------------------------------------------------------
template <class Matrix>
inline vec::_scalar_value<Matrix> trace(const Matrix &m)
{    
    n_static_assert(vec::_order<Matrix>::value == 2,
        "Matrix required.");
    n_static_assert(
        n_arg(vec::size_at<Matrix,0>::type::value
            == vec::size_at<Matrix,1>::type::value),
        "Square matrix required.");
    
    return trace_impl<Matrix>::apply(m);
}

/** @} */

}}}} // namespaces

#endif // NIC_2C6CF46549A848DC_NIC

