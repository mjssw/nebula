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
#ifndef NIC_8BE0616F948960C0_NIC
#define NIC_8BE0616F948960C0_NIC

#include "ratio.h"
#include "../algorithm/for_each.h"

namespace nebula { namespace foundation { namespace meta {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
namespace meta_detail {
//------------------------------------------------------------------------------
template <class S, class T>
struct ratio_add_2_
{
    using type = ratio<
        S::type::num * T::type::den + T::type::num * S::type::den,
        S::type::den * T::type::den>;
};
//------------------------------------------------------------------------------
} // meta_detail
//------------------------------------------------------------------------------
template <class First, class ... T>
struct ratio_add_
{
private:
    template <class A, class B>
    struct F {
        using type = typename meta_detail::ratio_add_2_<A, B>::type;
    };
    
public:
    using type = _for_each<
        seq<T...>,
        F,
        First>;
};

template <class ... T>
using _ratio_add = typename ratio_add_<T...>::type;

/** @} */

}}} // namespaces

#endif // NIC_8BE0616F948960C0_NIC