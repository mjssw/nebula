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
#ifndef NIC_123511BBACAA0A47_NIC
#define NIC_123511BBACAA0A47_NIC

#include "../type_traits.h"
#include "../defs.h"

namespace nebula { namespace foundation { namespace memory {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
/** The type of the objects an allocator can create. Each allocator type can
 * only allocate a single type of objects.
 * */
template <class Alloc>
struct allocator_value
{
    using type = typename Alloc::value_type;
};

//------------------------------------------------------------------------------
namespace memory_detail {
//------------------------------------------------------------------------------
template <class Alloc>
inline constexpr bool has_pocca_(
    typename Alloc::propagate_on_container_copy_assignment *) noexcept
{
    return true;
}
//------------------------------------------------------------------------------
template <class>
inline constexpr bool has_pocca_(...) noexcept
{
    return false;
}
//------------------------------------------------------------------------------
template <class Alloc, bool HasMember = has_pocca_<Alloc>(nullptr)>
struct pocca_ : public false_type {};
template <class Alloc>
struct pocca_<Alloc, true> 
: public Alloc::propagate_on_container_copy_assignment 
{};
} // memory_detail
//------------------------------------------------------------------------------
template <class Alloc>
struct pocca : public memory_detail::pocca_<Alloc> {};

//------------------------------------------------------------------------------
namespace memory_detail {
//------------------------------------------------------------------------------
template <class Alloc>
inline constexpr bool has_pocma_(
    typename Alloc::propagate_on_container_move_assignment *) noexcept
{
    return true;
}
//------------------------------------------------------------------------------
template <class>
inline constexpr bool has_pocma_(...) noexcept
{
    return false;
}
//------------------------------------------------------------------------------
template <class Alloc, bool HasMember = has_pocma_<Alloc>(nullptr)>
struct pocma_ : public false_type {};
template <class Alloc>
struct pocma_<Alloc, true> 
: public Alloc::propagate_on_container_move_assignment 
{};
} // memory_detail
//------------------------------------------------------------------------------
template <class Alloc>
struct pocma : public memory_detail::pocma_<Alloc> {};

//------------------------------------------------------------------------------
namespace memory_detail {
//------------------------------------------------------------------------------
template <class Alloc>
inline constexpr bool has_pocs_(
    typename Alloc::propagate_on_container_swap *) noexcept
{
    return true;
}
//------------------------------------------------------------------------------
template <class>
inline constexpr bool has_pocs_(...) noexcept
{
    return false;
}
//------------------------------------------------------------------------------
template <class Alloc, bool HasMember = has_pocs_<Alloc>(nullptr)>
struct pocs_ : public false_type {};
template <class Alloc>
struct pocs_<Alloc, true> : public Alloc::propagate_on_container_swap {};
} // memory_detail
//------------------------------------------------------------------------------
template <class Alloc>
struct pocs : public memory_detail::pocs_<Alloc> {};

//------------------------------------------------------------------------------
namespace memory_detail {
//------------------------------------------------------------------------------
template <class Alloc>
inline constexpr bool has_is_always_equal_(
    typename Alloc::is_always_equal *) noexcept
{
    return true;
}
//------------------------------------------------------------------------------
template <class>
inline constexpr bool has_is_always_equal_(...) noexcept
{
    return false;
}
//------------------------------------------------------------------------------
template <class Alloc, bool HasMember = has_is_always_equal_<Alloc>(nullptr)>
struct is_always_equal_ : public is_empty<Alloc> {};
template <class Alloc>
struct is_always_equal_<Alloc, true> : public Alloc::is_always_equal {};
} // memory_detail
//------------------------------------------------------------------------------
/** Indicates if allocator objects of a given type will always compare equal.
 * */
template <class Alloc>
struct is_always_equal : public memory_detail::is_always_equal_<Alloc> {};

//------------------------------------------------------------------------------
n_meta_alias(allocator_value);
n_meta_alias(pocca);
n_meta_alias(pocma);
n_meta_alias(pocs);
n_meta_alias(is_always_equal);

/** @} */

}}} // namespaces

#endif // NIC_123511BBACAA0A47_NIC
