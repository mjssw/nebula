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
#ifndef NIC_3200E1E41145574A_NIC
#define NIC_3200E1E41145574A_NIC

#include "integral_constant.h"

namespace nebula { namespace foundation { namespace meta {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
template <bool Cond, class Then, class Else>
struct if_c {
    using type = Then;
};

template <class Then, class Else>
struct if_c<false, Then, Else> {
    using type = Else;
};
//------------------------------------------------------------------------------
template <
    class Cond,
    class Then,
    class Else>
struct if_ : public if_c<Cond::type::value, Then, Else> {};
//------------------------------------------------------------------------------
template <
    class Cond,
    class Then,
    class Else>
using _if = typename if_<Cond, Then, Else>::type;

//------------------------------------------------------------------------------
template <bool Cond, class Then, class Else>
struct l_if_c {
    using type = typename if_c<
        Cond, 
        Then, 
        Else>::type::type;
};
//------------------------------------------------------------------------------
template <
    class Cond,
    class Then,
    class Else>
struct l_if_ : public l_if_c<Cond::type::value, Then, Else> {};
//------------------------------------------------------------------------------
template <
    class Cond,
    class Then,
    class Else>
using _l_if = typename l_if_<Cond, Then, Else>::type;

/** @} */

}}} // namespaces

#endif // NIC_3200E1E41145574A_NIC