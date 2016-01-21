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
#ifndef NIC_4E4E71ACA9B50078_NIC
#define NIC_4E4E71ACA9B50078_NIC

#include "mod.h"
#include "abs.h"
#include "algorithm/for_each.h"
#include "seq_fwd.h"

namespace nebula { namespace foundation { namespace meta {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
namespace meta_detail {
//------------------------------------------------------------------------------
template <class A, class B>
struct gcd_impl_ : public gcd_impl_<B, _mod<A,B>>
{};

template <class A>
struct gcd_impl_<A, integral_constant<typename A::value_type, 0>>
: public _abs<A>
{};

template <class A>
struct gcd_impl_<integral_constant<typename A::value_type, 0>, A>
: public _abs<A>
{};
//------------------------------------------------------------------------------
} // meta_detail
//------------------------------------------------------------------------------
template <class A, class B, class ... Rest>
struct gcd_
{
private:
    template <class Q, class R>
    struct F {
        using type = typename meta_detail::gcd_impl_<Q,R>::type;
    };
    
public:
    using type = _for_each<
        seq<Rest...>,
        F,
        typename meta_detail::gcd_impl_<A,B>::type
    >;
};

template <class ... T>
using _gcd = typename gcd_<T...>::type;

/** @} */

}}} // namespaces

#endif // NIC_4E4E71ACA9B50078_NIC