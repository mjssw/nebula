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
#ifndef NIC_72694BE78743BA84_NIC
#define NIC_72694BE78743BA84_NIC

#include "allocate.h"
#include "deallocate.h"

namespace nebula { namespace foundation { namespace memory {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
namespace memory_detail {
//------------------------------------------------------------------------------
template <class Alloc>
inline constexpr bool has_reallocate_(
    typename Alloc::reallocate &) noexcept
{
    return true;
}
//------------------------------------------------------------------------------
template <class>
inline constexpr bool has_reallocate_(...) noexcept
{
    return false;
}
//------------------------------------------------------------------------------
template <class Alloc, 
    bool HasMember = has_reallocate_<Alloc>(nullptr)>
struct reallocate_ {
    inline static typename allocator_value<Alloc>::type *
    apply(
        Alloc &a,
        typename allocator_value<Alloc>::type *ptr,
        const size_t old_size, 
        const size_t new_size,
        typename allocator_value<Alloc>::type *hint)
    {
        return a.reallocate(ptr, old_size, new_size, hint);
    }
    inline static typename allocator_value<Alloc>::type *
    apply(
        Alloc &a,
        typename allocator_value<Alloc>::type *ptr,
        const size_t old_size, 
        const size_t new_size)
    {
        return a.reallocate(ptr, old_size, new_size);
    }
};
template <class Alloc>
struct reallocate_<Alloc, false> {
    inline static typename allocator_value<Alloc>::type *
    apply(
        Alloc &a,
        typename allocator_value<Alloc>::type *ptr,
        const size_t old_size, 
        const size_t new_size, 
        typename allocator_value<Alloc>::type *hint)
    {
        return memory::allocate(a, new_size, hint);;
    }
    inline static typename allocator_value<Alloc>::type *
    apply(
        Alloc &a,
        typename allocator_value<Alloc>::type *ptr,
        const size_t old_size, 
        const size_t new_size)
    {
        return memory::allocate(a, new_size);
    }
};
//------------------------------------------------------------------------------
} // memory_detail
//------------------------------------------------------------------------------
template <class Alloc>
struct reallocate_impl : public memory_detail::reallocate_<Alloc>
{};
//------------------------------------------------------------------------------
/** Trys to 're-allocate' a block of memory prev. allocated by allocate(...).
 * If the returned pointer is equal to the input pointer then the prev. alloc.
 * block of memory has been expanded (or shrinked, depending wether 
 * new_size > old_size), otherwise a new block of memory has been allocated,
 * and the old one remains unmodified - i.e. it still needs to be deallocated.
 * @param alloc The allocator used to for the allocation.
 * @param new_size The new size of the memory block, this can be anything
 * but 0.
 * @param old_size The old size of the memory block passed to this function,
 * which must not be 0.
 * @param ptr The pointer to the a. allocated block of memory.
 * @param hint If a new memory block has to be allocated it should be as close
 * as possible to hint (if supported by the platform).
 * @return A pointer to the start of the allocated memory chunk, which can be
 * equal to ptr if the prev. allocated memory block could be expanded or
 * shrinkged.
 * @throw bad_alloc If something goes south this exception is thrown.
 * @note Strong exception guarantee.
 * @note If an exception is thrown it is always bad_alloc, no other exceptions
 * are allowed to be thrown.
 * @see nebula::foundation::bad_alloc
 * */
template <class Alloc>
inline typename allocator_value<typename ctraits::value<Alloc>::type>::type *
reallocate(
    Alloc &&alloc, 
    typename allocator_value<typename ctraits::value<Alloc>::type>::type *ptr,
    const size_t old_size,
    const size_t new_size,
    typename allocator_value<typename ctraits::value<Alloc>::type>::type *hint)
{
    return reallocate_impl<typename ctraits::value<Alloc>::type>::apply(
        alloc, ptr, old_size, new_size, hint);
}
template <class Alloc>
inline typename allocator_value<typename ctraits::value<Alloc>::type>::type *
reallocate(
    Alloc &&alloc, 
    typename allocator_value<typename ctraits::value<Alloc>::type>::type *ptr,
    const size_t old_size,
    const size_t new_size)
{
    return reallocate_impl<typename ctraits::value<Alloc>::type>::apply(
        alloc, ptr, old_size, new_size);
}

/** @} */

}}} // namespaces

#endif // NIC_72694BE78743BA84_NIC