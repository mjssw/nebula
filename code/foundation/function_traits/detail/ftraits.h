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
#ifndef NIC_0527A0D45F1849EF_NIC
#define NIC_0527A0D45F1849EF_NIC

#include "../../meta.h"

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{
 */
namespace ftraits_detail {
//------------------------------------------------------------------------------
template <class Ret, class ... Args>
struct pointer_impl
{
    using type = Ret (*) (Args ...);
};
//------------------------------------------------------------------------------
template <class Class, class Ret, class ... Args>
struct member_pointer_impl
{
    using type = Ret (Class::*) (Args ...);
};
//------------------------------------------------------------------------------
template <class Ret, class Args>
struct traits_impl
{
    using args = Args;
    
    struct ret_ {
        using type = Ret;
    };
    using _ret = Ret;
    
    using arity_ = meta::size_<args>;
    using _arity = meta::_size<args>;
    
    template <class I>
    using arg_ = meta::at_<args, I>;
    template <class I>
    using _arg = meta::_at<args, I>;
    
    using RetArgs = meta::_push_front<args, Ret>;
    
    using pointer_ = meta::_expand<pointer_impl, RetArgs>;
    using _pointer = typename pointer_::type;
    
    template <class Class>
    using member_pointer_ = meta::_expand<
        member_pointer_impl, meta::_push_front<RetArgs, Class>>;
    template <class Class>
    using _member_pointer = typename member_pointer_<Class>::type;
};

//------------------------------------------------------------------------------
template <class F>
struct traits_dispatcher;

template <class Ret, class ... Args>
struct traits_dispatcher<Ret (Args ...)>
{
    using type = traits_impl<Ret, meta::seq<Args...>>;
};
template <class Ret, class ... Args>
struct traits_dispatcher<meta::seq<Ret, Args ...>>
{
    using type = traits_impl<Ret, meta::seq<Args...>>;
};

//------------------------------------------------------------------------------
template <class F>
struct traits : public traits_dispatcher<F>::type {};

} // ftraits_detail

/** @} */

}} // namespaces
 
#endif // NIC_0527A0D45F1849EF_NIC
