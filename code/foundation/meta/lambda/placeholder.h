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
#ifndef NIC_9196B928D2B68F0F_NIC
#define NIC_9196B928D2B68F0F_NIC

namespace nebula { namespace foundation { namespace meta {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
/** Similar to the meta::_ template, but beware that counting starts at 0
 * for this template. I.e. placeholder<N> is the same type as _<N+1>.
 * */ 
template <size_t N>
struct placeholder {};

//------------------------------------------------------------------------------
/** Use this template when you want to use placeholders to generate new
 * templates. Or you can use the types _1, _2, ...
 * This placeholder is actually not doing anything on its own, but in
 * concert with meta functions like bind_<>.
 * @see nebula::foundation::meta::bind_
 * */
template <size_t N>
using _ = placeholder<N-1>;

/** @todo Do we need more than 10? */
using _1 = _<1>;
using _2 = _<2>;
using _3 = _<3>;
using _4 = _<4>;
using _5 = _<5>;
using _6 = _<6>;
using _7 = _<7>;
using _8 = _<8>;
using _9 = _<9>;
using _10 = _<10>;

//------------------------------------------------------------------------------
template <class T>
struct is_placeholder : public meta::false_ {};

template <size_t N>
struct is_placeholder<placeholder<N>> : public meta::true_ {};

/** @} */

}}} // namespaces

#endif // NIC_9196B928D2B68F0F_NIC