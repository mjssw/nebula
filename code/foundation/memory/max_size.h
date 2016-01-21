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
#ifndef NIC_AE9AE46520D3A853_NIC
#define NIC_AE9AE46520D3A853_NIC

#include "traits.h"
#include "../math/limits/maximum.h"

namespace nebula { namespace foundation { namespace memory {
/** @ingroup Foundation
 * @{
 * */
namespace memory_detail {
//------------------------------------------------------------------------------
template <class Alloc>
inline constexpr bool has_max_size_(
    typename Alloc::max_size &) noexcept
{
    return true;
}
//------------------------------------------------------------------------------
template <class>
inline constexpr bool has_max_size_(...) noexcept
{
    return false;
}
//------------------------------------------------------------------------------
template <class Alloc, bool HasMember = has_max_size_<Alloc>(nullptr)>
struct max_size_ {
    inline static size_t apply(const Alloc &) noexcept {
        return math::maximum<size_t>();
    }
};
template <class Alloc>
struct max_size_<Alloc, true> {
    inline static size_t apply(const Alloc &a) noexcept {
        return a.max_size();
    }
};
//------------------------------------------------------------------------------
} // memory_detail
//------------------------------------------------------------------------------
template <class Alloc>
struct max_size_impl : public memory_detail::max_size_<Alloc> {};
//------------------------------------------------------------------------------
/** Get the maximum (theoretical) size of a memory chunk that can be allocated,
 * by the allocator in question. This function calls alloc.max_size() if
 * available, otherwise it returns numeric_limits<size_t>::max(). 
 * @param alloc The allocator object.
 * @return Maximum possible size to allocate.
 * @throw nothing
 * */
template <class Alloc>
inline size_t max_size(const Alloc &a) noexcept
{
    return max_size_impl<Alloc>::apply(a);
}

/** @} */

}}} // namespaces

#endif // NIC_AE9AE46520D3A853_NIC