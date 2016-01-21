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
#ifndef NIC_A5CAF9FADC38E248_NIC
#define NIC_A5CAF9FADC38E248_NIC

namespace nebula { namespace foundation { namespace meta {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
namespace expand_detail {
//------------------------------------------------------------------------------
template <template <class ...> class F, class Expr>
struct expander_ {};

template <
    template <class ...> class F,
    template <class ...> class Expr, 
    class ... Params>
struct expander_<F, Expr<Params...>> {
    using type = F<Params...>;
};
//------------------------------------------------------------------------------
} // expand_detail
//------------------------------------------------------------------------------
template <template <class ...> class F, class Expr>
struct expand_
{
    using type = typename expand_detail::expander_<F, Expr>::type;
};
//------------------------------------------------------------------------------
/** Takes a template F and a type Expr<T...> and returns F<T...>. 
 * */
template <template <class ...> class F, class Expr>
using _expand = typename expand_<F, Expr>::type;

/** @} */

}}} // namespaces

#endif // NIC_A5CAF9FADC38E248_NIC