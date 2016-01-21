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
#ifndef NIC_1061AE3837E38B77_NIC
#define NIC_1061AE3837E38B77_NIC

#include "protect.h"

namespace nebula { namespace foundation { namespace meta {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
template <class T>
struct lazy
{
    using type = T;
};

template <class T>
struct lazy<protect<T>>
{
    using type = T;
};

template <template <class ...> class C, class ... T>
struct lazy<C<T...>>
: public C<typename lazy<T>::type...>
{};

/** @} */

}}} // namespaces

#endif // NIC_1061AE3837E38B77_NIC