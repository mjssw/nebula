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
#ifndef NIC_05980E3D455096A2_NIC
#define NIC_05980E3D455096A2_NIC

#include "detail/swap_rows.h"
#include "../vector.h"
#include "../perm.h"

namespace nebula { namespace foundation { namespace math { namespace linalg {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <class Matrix>
struct lup_factorization_impl
{
    template <class Permutation>
    inline static tuple<int, Matrix, Permutation>
    apply(Matrix m, Permutation p)
    {        
        int signum = 1;
        
        for(size_t i = 0; i < vec::size_at<Matrix,1>::type::value-1; ++i)
        {
            // partial pivoting
            size_t K = i;
            auto best = math::abs(m(i,i));
            
            for(size_t j = i+1; j < vec::size_at<Matrix,0>::type::value; ++j)
            {
                auto cur = math::abs(m(j,i));
                if(cur > best)
                {
                    K = j;
                    best = foundation::move(cur);
                }
            }
            if(K != i)
            {
                linalg_detail::swap_rows(m, i, K);
                // inverse swap
                p = perm::transpose(foundation::move(p), K, i);            
                signum *= -1;
            }
            
            // Gauss elimination
            for(size_t j = i+1; j < vec::size_at<Matrix,0>::type::value; ++j)
            {
                m(j,i) = m(j,i) / m(i,i);
                const vec::_scalar_value<Matrix> _t = -m(j,i);

                for(size_t k = i+1;
                    k < vec::size_at<Matrix,1>::type::value;
                    ++k)
                {
                    m(j,k) += _t * m(i,k);
                }
            }
        }
        
        return foundation::make_tuple(
            signum,
            foundation::move(m),
            foundation::move(p));
    }
};

//------------------------------------------------------------------------------
/** Calculate the LU factorization of a matrix.
 *  @param m A non singular matrix.
 *  @param p Must be the identity permutation of magnitude equal to the number
 *  of rows in m.
 *  @return A tuple: (signum, LU, P) where signum is an int holding the
 *  signum of P. LU is simply L and U packed into a single matrix omitting
 *  the diag(L) which is just (1,1, ...). P is a permutation holding
 *  representing a reordering of rows, since partial pivoting is done
 *  on rows.
 * */
template <
    class Matrix_,
    class Permutation_,
    class Matrix = ctraits::_value<Matrix_>,
    class Permutation = ctraits::_value<Permutation_>>
inline tuple<int, Matrix, Permutation>
lup_factorization(Matrix_ &&m, Permutation_ &&p)
{
    n_static_assert(vec::_order<Matrix>::value == 2,
        "Matrix required.");
    n_static_assert(
        n_arg(vec::size_at<Matrix,0>::type::value
            == vec::size_at<Matrix,1>::type::value),
        "Square matrix required.");
    
    return lup_factorization_impl<Matrix>::apply(
        foundation::forward<Matrix_>(m),
        foundation::forward<Permutation_>(p));
}

//------------------------------------------------------------------------------
template <class Matrix_,
    class Matrix = ctraits::_value<Matrix_>>
inline _enable_if<is_lvalue_reference<Matrix_>, tuple<Matrix, Matrix>>
split_lu(Matrix_ &&lu)
{
    n_static_assert(vec::_order<Matrix>::value == 2,
        "Matrix required.");
    n_static_assert(
        n_arg(vec::size_at<Matrix,0>::type::value
            == vec::size_at<Matrix,1>::type::value),
        "Square matrix required.");
    
    tuple<Matrix, Matrix> r;
    Matrix &L = foundation::get<0>(r);
    Matrix &U = foundation::get<1>(r);
    
    // set diag(L)=(1, 1, ...).
    for(size_t i = 0; i < vec::size_at<Matrix,0>::type::value; ++i)
    {
        U(i,i) = lu(i,i);
        L(i,i) = vec::_scalar_value<Matrix>(1);
    }
    // set upper triangle of L to 0.
    for(size_t i = 0; i < vec::size_at<Matrix,0>::type::value-1; ++i)
        for(size_t j = i+1; j < vec::size_at<Matrix,1>::type::value; ++j)
        {
            U(i,j) = lu(i,j);
            L(i,j) = vec::_scalar_value<Matrix>(0);
        }
    // extract L and set lower triangle of U to 0
    for(size_t i = 1; i < vec::size_at<Matrix,0>::type::value; ++i)
        for(size_t j = 0; j < i; ++j)
        {
            L(i,j) = lu(i,j);
            U(i,j) = vec::_scalar_value<Matrix>(0);
        }
        
    return r;
}
//------------------------------------------------------------------------------
template <class Matrix_,
    class Matrix = ctraits::_value<Matrix_>>
inline _disable_if<is_lvalue_reference<Matrix_>, tuple<Matrix, Matrix>>
split_lu(Matrix_ &&U)
{
    n_static_assert(vec::_order<Matrix>::value == 2,
        "Matrix required.");
    n_static_assert(
        n_arg(vec::size_at<Matrix,0>::type::value
            == vec::size_at<Matrix,1>::type::value),
        "Square matrix required.");
    
    Matrix L;
    
    // set diag(L)=(1, 1, ...).
    for(size_t i = 0; i < vec::size_at<Matrix,0>::type::value; ++i)
        L(i,i) = vec::_scalar_value<Matrix>(1);
    // set upper triangle of L to 0.
    for(size_t i = 0; i < vec::size_at<Matrix,0>::type::value-1; ++i)
        for(size_t j = i+1; j < vec::size_at<Matrix,1>::type::value; ++j)
            L(i,j) = vec::_scalar_value<Matrix>(0);
    // extract L and set lower triangle of U to 0
    for(size_t i = 1; i < vec::size_at<Matrix,0>::type::value; ++i)
        for(size_t j = 0; j < i; ++j)
        {
            L(i,j) = U(i,j);
            U(i,j) = vec::_scalar_value<Matrix>(0);
        }
        
    return foundation::make_tuple(foundation::move(L), foundation::move(U));
}

/** @} */

}}}} // namespaces

#endif // NIC_05980E3D455096A2_NIC

