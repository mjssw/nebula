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
#ifndef NIC_388A186B641868AB_NIC
#define NIC_388A186B641868AB_NIC

#include "../defs.h"

namespace nebula { namespace foundation { namespace meta {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
template <class T> 
struct deref_;

template <class T>
using _deref = typename deref_<T>::type;

//------------------------------------------------------------------------------
template <class T, class N> 
struct advance_;

template <class T, class N>
using _advance = typename advance_<T, N>::type;

//------------------------------------------------------------------------------
template <class T> 
struct next_;

template <class T>
using _next = typename next_<T>::type;

//------------------------------------------------------------------------------
template <class T> 
struct prev_;

template <class T>
using _prev = typename prev_<T>::type;

//------------------------------------------------------------------------------
template <class S, class T> 
struct distance_;

template <class S, class T>
using _distance = typename distance_<S, T>::type;

/** @} */

}}} // namespaces

#endif // NIC_388A186B641868AB_NIC