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
#ifndef NIC_64A8766CE1FACC67_NIC
#define NIC_64A8766CE1FACC67_NIC

#include "../traits.h"
#include "../../swap.h"

namespace nebula { namespace foundation { namespace iterator {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
/** Swaps the values two iterators are referencing. 
 * This basically just calls foundation::swap().
 * @note Will not throw if iterators are valid and swapping does not throw.
 * @remark Deref'ing an valid iterator cannot (must not) fail.
 * */
template <class I>
inline void iter_swap(I lhs, I rhs)
{
    n_static_assert(
        n_arg(has_tag<typename iterator_category<I>::type, swapable_iterator_tag>::value
        || iterator_detail::_is_strict_std_iterator<I>::value), 
        "No iterator swap available.");
    foundation::swap(*lhs, *rhs);
}

/** @} */

}}} // namespaces

#endif // NIC_64A8766CE1FACC67_NIC