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
#ifndef NIC_E03EE66F1E7F0465_NIC
#define NIC_E03EE66F1E7F0465_NIC

#include "traits.h"
#include "../call_traits.h"

namespace nebula { namespace foundation { namespace memory {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <class Alloc>
struct allocate_impl
{
    inline static typename allocator_value<Alloc>::type *apply(Alloc &a, 
        const size_t n, const void *hint)
    {
        return a.allocate(n, hint);
    }
    inline static typename allocator_value<Alloc>::type *apply(Alloc &a, 
        const size_t n)
    {
        return a.allocate(n);
    }
};
//------------------------------------------------------------------------------
template <class Alloc>
inline typename allocator_value<typename ctraits::value<Alloc>::type>::type 
*allocate(
    Alloc &&a, const size_t n, const void *hint)
{
    return allocate_impl<
        typename ctraits::value<Alloc>::type>::apply(a, n, hint);
}
//------------------------------------------------------------------------------
/** Allocate a contiguous chunk of memory capable of holding an array of at
 * least n objects (of the type given by the actual allocator type).
 * @param alloc The allocator used to for the allocation.
 * @param n Allocate a memory chunk to store at least an array of n objects.
 * @return A pointer to the start of the allocated memory chunk.
 * @throw bad_alloc If something goes south this exception is thrown.
 * @note Strong exception guarantee.
 * @note If an exception is thrown it is always bad_alloc, no other exceptions
 * are allowed to be thrown.
 * @see nebula::foundation::bad_alloc
 * */
template <class Alloc>
inline typename allocator_value<typename ctraits::value<Alloc>::type>::type
*allocate(
    Alloc &&alloc, const size_t n)
{
    return allocate_impl<
        typename ctraits::value<Alloc>::type>::apply(alloc, n);
}

/** @} */

}}} // namespaces

#endif // NIC_E03EE66F1E7F0465_NIC