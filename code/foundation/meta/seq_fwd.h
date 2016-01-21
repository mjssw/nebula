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
#ifndef NIC_C9D61F0A8F8FE004_NIC
#define NIC_C9D61F0A8F8FE004_NIC

namespace nebula { namespace foundation { namespace meta {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
template <class ... T> struct seq;

//------------------------------------------------------------------------------
template <class T> 
struct size_;

template <class T>
using _size = typename size_<T>::type;

//------------------------------------------------------------------------------
template <class T> 
struct empty_ {
    using type = bool_<_size<T>::value == 0>;
};

template <class T>
using _empty = typename empty_<T>::type;

//------------------------------------------------------------------------------
template <class T, class N> 
struct at_;

template <class T, class N>
using _at = typename at_<T, N>::type;

//------------------------------------------------------------------------------
template <class T, class X> 
struct push_front_;

template <class T, class X>
using _push_front = typename push_front_<T, X>::type;

//------------------------------------------------------------------------------
template <class T, class X> 
struct push_back_;

template <class T, class X>
using _push_back = typename push_back_<T, X>::type;

//------------------------------------------------------------------------------
template <class T> 
struct pop_front_;

template <class T>
using _pop_front = typename pop_front_<T>::type;

//------------------------------------------------------------------------------
template <class T> 
struct pop_back_;

template <class T>
using _pop_back = typename pop_back_<T>::type;

//------------------------------------------------------------------------------
template <class T> 
struct front_;

template <class T>
using _front = typename front_<T>::type;

//------------------------------------------------------------------------------
template <class T> 
struct back_;

template <class T>
using _back = typename back_<T>::type;

//------------------------------------------------------------------------------
template <class T> 
struct begin_;

template <class T>
using _begin = typename begin_<T>::type;

//------------------------------------------------------------------------------
template <class T> 
struct end_;

template <class T>
using _end = typename end_<T>::type;

//------------------------------------------------------------------------------
template <class T> 
struct rbegin_;

template <class T>
using _rbegin = typename rbegin_<T>::type;

//------------------------------------------------------------------------------
template <class T> 
struct rend_;

template <class T>
using _rend = typename rend_<T>::type;

//------------------------------------------------------------------------------
template <class T> 
struct clear_;

template <class T>
using _clear = typename clear_<T>::type;


/** @} */

}}} // namespaces

#endif // NIC_C9D61F0A8F8FE004_NIC