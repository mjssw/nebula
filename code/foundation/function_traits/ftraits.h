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
#ifndef NIC_60302B614FE528F0_NIC
#define NIC_60302B614FE528F0_NIC

#include "detail/ftraits.h"

namespace nebula { namespace foundation { namespace ftraits {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class F>
struct ret
{
    using type = typename ftraits_detail::traits<F>::_ret;
};

template <class F>
struct arity : public ftraits_detail::traits<F>::_arity
{};

template <class F, size_t N>
struct arg 
{
    using type = typename ftraits_detail::traits<F>
        ::template _arg<meta::size_t_<N>>;
};
    
template <class F>
struct pointer 
{
    using type = typename ftraits_detail::traits<F>::_pointer;
};
    
template <class C, class F>
struct member_pointer
{
    using type = typename ftraits_detail::traits<F>
        ::template _member_pointer<C>;
};

//------------------------------------------------------------------------------
n_meta_alias(ret);
n_meta_alias(arity);
n_meta_alias(pointer);
n_meta_alias(member_pointer);

template <class F, class N>
using arg_ = arg<F, N::value>;
template <class F, class N>
using _arg = typename arg_<F,N>::type;

/** @} */

}}} // namespaces
 
#endif // NIC_60302B614FE528F0_NIC
