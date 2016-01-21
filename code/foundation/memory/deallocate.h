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
#ifndef NIC_D557FE5388A5CC84_NIC
#define NIC_D557FE5388A5CC84_NIC

#include "traits.h"
#include "../call_traits.h"

namespace nebula { namespace foundation { namespace memory {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <class Alloc>
struct deallocate_impl
{
    inline static void apply(Alloc &a, 
        typename allocator_value<Alloc>::type *ptr, const size_t n) noexcept
    {
        a.deallocate(ptr, n);
    }
};
//------------------------------------------------------------------------------
/** Deallocate a memory chunk previously allocated by the same allocator obj.
 * @param alloc The allocator used to for construction.
 * @param ptr Pointer to the memory region which should be deallocated.
 * @param n The size of the memory region (this parameter must not be omitted).
 * @throw nothing
 * */
template <class Alloc>
inline void deallocate(Alloc &&alloc, 
    typename allocator_value<typename ctraits::value<Alloc>::type>::type *ptr, 
    const size_t n) noexcept
{
    return deallocate_impl<
        typename ctraits::value<Alloc>::type
    >::apply(alloc, ptr, n);
}

/** @} */

}}} // namespaces

#endif // NIC_D557FE5388A5CC84_NIC