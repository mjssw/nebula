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
#ifndef NIC_2A165086B3AA71B4_NIC
#define NIC_2A165086B3AA71B4_NIC

#include "detail/traits_helper.h"

namespace nebula { namespace foundation { namespace iterator {
/** @ingroup Foundation
  * @{ 
  * */
//------------------------------------------------------------------------------
template <class I>
struct iterator_value {
    typedef typename iterator_detail::_iterator_value<I>::type type;
};
//------------------------------------------------------------------------------
template <class I>
struct iterator_reference {
    typedef typename iterator_detail::_iterator_reference<I>::type type;
};
//------------------------------------------------------------------------------
template <class I>
struct iterator_pointer {
    typedef typename iterator_detail::_iterator_pointer<I>::type type;
};
//------------------------------------------------------------------------------
template <class I>
struct iterator_difference {
    typedef typename iterator_detail::_iterator_difference<I>::type type;
};
//------------------------------------------------------------------------------
template <class I>
struct iterator_access {
    typedef typename iterator_detail::_iterator_access<I>::type type;
};
//------------------------------------------------------------------------------
template <class I>
struct iterator_traversal {
    typedef typename iterator_detail::_iterator_traversal<I>::type type;
};
//------------------------------------------------------------------------------
template <class I>
struct iterator_category {
    typedef typename iterator_detail::_iterator_category<I>::type type;
};

//------------------------------------------------------------------------------
n_meta_alias(iterator_value);
n_meta_alias(iterator_reference);
n_meta_alias(iterator_pointer);
n_meta_alias(iterator_difference);
n_meta_alias(iterator_access);
n_meta_alias(iterator_traversal);
n_meta_alias(iterator_category);

/** @} */

}}} // namespaces

#endif // NIC_2A165086B3AA71B4_NIC
