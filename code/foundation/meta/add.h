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
#ifndef NIC_A30DA5C123A90FD6_NIC
#define NIC_A30DA5C123A90FD6_NIC

#include "integral_constant.h"

namespace nebula { namespace foundation { namespace meta {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
template <class First, class ... T>
struct add_ {
    using type = integral_constant<
        decltype(First::type::value + add_<T...>::type::value),
        First::type::value + add_<T...>::type::value
    >;
};

template <class T>
struct add_<T> {
    using type = integral_constant<
        typename T::type::value_type, T::type::value>;
};
//------------------------------------------------------------------------------
template <class ... T>
using _add = typename add_<T...>::type;

/** @} */

}}} // namespaces

#endif // NIC_A30DA5C123A90FD6_NIC