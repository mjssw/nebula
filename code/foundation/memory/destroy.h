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
#ifndef NIC_D4E64CAF4521DCEB_NIC
#define NIC_D4E64CAF4521DCEB_NIC

#include "traits.h"
#include "../call_traits.h"

namespace nebula { namespace foundation { namespace memory {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
namespace memory_detail {
//------------------------------------------------------------------------------
template <class Alloc>
inline constexpr bool has_destroy_(
    typename Alloc::destroy &) noexcept
{
    return true;
}
//------------------------------------------------------------------------------
template <class>
inline constexpr bool has_destroy_(...) noexcept
{
    return false;
}
//------------------------------------------------------------------------------
template <class Alloc, 
    bool HasMember = has_destroy_<Alloc>(nullptr)>
struct destroy_ {
    template <class T>
    inline static void call_destructor(T *ptr) {
        ptr->~T();
    }
    inline static void apply(Alloc &a,
        typename allocator_value<Alloc>::type *ptr) 
    {
        call_destructor(ptr);
    }
};
template <class Alloc>
struct destroy_<Alloc, true> {
    inline static size_t apply(Alloc &a,
        typename allocator_value<Alloc>::type *ptr) {
        return a.destroy(ptr);
    }
};
//------------------------------------------------------------------------------
} // memory_detail
//------------------------------------------------------------------------------
template <class Alloc>
struct destroy_impl : public memory_detail::destroy_<Alloc> {};
//------------------------------------------------------------------------------
/** Destroy an object previously constructed by the same allocator object.
 * This function calls alloc.destroy() if available, otherwise just the 
 * destructor of the object in question is invoked.
 * @param alloc The allocator used to for construction.
 * @param ptr Pointer to the object which should be destructed.
 * @throw nothing
 * */
template <class Alloc>
inline void destroy(Alloc &&alloc, 
    typename allocator_value<
        typename ctraits::value<Alloc>::type>::type *ptr)
{
    destroy_impl<typename ctraits::value<Alloc>::type>::apply(alloc, ptr);
}

/** @} */

}}} // namespaces

#endif // NIC_D4E64CAF4521DCEB_NIC
