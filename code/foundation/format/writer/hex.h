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
#ifndef NIC_6AF4975E76BB1889_NIC
#define NIC_6AF4975E76BB1889_NIC

#include "integer.h"
#include "real.h"
#include "../../enable_if.h"
#include "../../math/traits/is_integer.h"

namespace nebula { namespace foundation { namespace fmt {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <class T,
    typename enable_if<math::is_integer<T>>::type* = nullptr>
inline auto hex(const T &x)
{
    return fmt::integer(x, 16);
}
//------------------------------------------------------------------------------
template <class T,
    typename disable_if<math::is_integer<T>>::type* = nullptr>
inline auto hex(const T &x)
{
    return fmt::real(
        x,
        N_FORMAT_DEFAULT_PRECISION,
        N_FORMAT_DEFAULT_ROUNDING_STYLE,
        true,
        16);
}

/** @} */

}}} // namespaces

#endif // NIC_6AF4975E76BB1889_NIC