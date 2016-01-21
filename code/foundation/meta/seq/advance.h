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
#ifndef NIC_FEC5968297B5E763_NIC
#define NIC_FEC5968297B5E763_NIC

#include "iterator.h"

namespace nebula { namespace foundation { namespace meta {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
template <size_t Pos, class ... T, class N>
struct advance_<seq_iterator<Pos, T...>, N> {
    using type = seq_iterator<_add<size_t_<Pos>, N>::value, T...>;
};

//------------------------------------------------------------------------------
template <size_t Pos, class ... T, class N>
struct advance_<seq_reverse_iterator<Pos, T...>, N> {
    using type = seq_reverse_iterator<_sub<size_t_<Pos>, N>::value, T...>;
};


/** @} */

}}} // namespaces

#endif // NIC_FEC5968297B5E763_NIC