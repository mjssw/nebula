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
#ifndef NIC_9C0513281BC9536E_NIC
#define NIC_9C0513281BC9536E_NIC

#include "iterator.h"

namespace nebula { namespace foundation { namespace meta {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
template <size_t P0, class ... T0, size_t P1, class ... T1>
struct distance_<
    seq_iterator<P0, T0...>, 
    seq_iterator<P1, T1...>>
{
    using type = ptrdiff_t_<
        static_cast<ptrdiff_t>(P1)-static_cast<ptrdiff_t>(P0)>;
};

//------------------------------------------------------------------------------
template <size_t P0, class ... T0, size_t P1, class ... T1>
struct distance_<
    seq_reverse_iterator<P0, T0...>, 
    seq_reverse_iterator<P1, T1...>>
{
    using type = ptrdiff_t_<
        static_cast<ptrdiff_t>(P1)-static_cast<ptrdiff_t>(P0)>;
};

/** @} */

}}} // namespaces

#endif // NIC_9C0513281BC9536E_NIC