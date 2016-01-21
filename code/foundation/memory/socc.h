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
#ifndef NIC_3E0CA80757EEF133_NIC
#define NIC_3E0CA80757EEF133_NIC

#include "traits.h"

namespace nebula { namespace foundation { namespace memory {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
namespace memory_detail {
//------------------------------------------------------------------------------
template <class Alloc>
inline constexpr bool has_select_on_container_copy_construction_(
    typename Alloc::select_on_container_copy_construction &) noexcept
{
    return true;
}
//------------------------------------------------------------------------------
template <class>
inline constexpr bool has_select_on_container_copy_construction_(...) noexcept
{
    return false;
}
//------------------------------------------------------------------------------
template <class Alloc, 
    bool HasMember = has_select_on_container_copy_construction_<Alloc>(nullptr)>
struct select_on_container_copy_construction_ {
    inline static Alloc apply(const Alloc &a) noexcept {
        return a;
    }
};
template <class Alloc>
struct select_on_container_copy_construction_<Alloc, true> {
    inline static Alloc apply(const Alloc &a) noexcept {
        return a.select_on_container_copy_construction();
    }
};
//------------------------------------------------------------------------------
} // memory_detail
//------------------------------------------------------------------------------
template <class Alloc>
struct socc_impl
: public memory_detail::select_on_container_copy_construction_<Alloc>
{};
//------------------------------------------------------------------------------
/** Generates an allocator object when copy constructing an allocator aware
 * object. The returned allocator is then used for the newly created allocator 
 * aware object. This function calls 
 * alloc.select_on_container_copy_construction() if available, otherwise if
 * just returns a copy of the input allocator.
 * @param alloc The allocator of the allocator aware object we copy-construct
 * from.
 * @return New allocator object.
 * @note Strong exception guarantee.
 * */
template <class Alloc>
inline Alloc select_on_container_copy_construction(const Alloc &alloc)
{
    return socc_impl<Alloc>::apply(alloc);
}
template <class Alloc>
inline Alloc socc(const Alloc &alloc)
{
    return socc_impl<Alloc>::apply(alloc);
}

/** @} */

}}} // namespaces

#endif // NIC_3E0CA80757EEF133_NIC