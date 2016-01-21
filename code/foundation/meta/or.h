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
#ifndef NIC_449F4C8AA6E3489D_NIC
#define NIC_449F4C8AA6E3489D_NIC

#include "integral_constant.h"

namespace nebula { namespace foundation { namespace meta {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
template <bool First, bool ... Rest>
struct or_c {
    using type = bool_<First || and_c<Rest...>::type::value>;
};
template <bool Last>
struct or_c<Last> {
    using type = bool_<Last>;
};
//------------------------------------------------------------------------------
template <class ... T>
struct or_ : public or_c<T::type::value ... > {};
//------------------------------------------------------------------------------
template <class ... T>
using _or = typename or_<T...>::type;

/** @} */

}}} // namespaces

#endif // NIC_449F4C8AA6E3489D_NIC