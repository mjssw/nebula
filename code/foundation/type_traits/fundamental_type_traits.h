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
#ifndef NIC_34E7280F5B5FA2C0_NIC
#define NIC_34E7280F5B5FA2C0_NIC

#include <type_traits>

#include "../meta/integral_constant.h"
#include "../meta/identity.h"
#include "../meta/if.h"

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{ 
 * */
//------------------------------------------------------------------------------
using meta::integral_constant;
//------------------------------------------------------------------------------
template <class T>
using identity = meta::identity_<T>;
//------------------------------------------------------------------------------
using true_type = meta::true_;
using false_type = meta::false_;
//------------------------------------------------------------------------------
template <bool A, class B, class C>
using conditional = meta::if_c<A, B, C>;
//------------------------------------------------------------------------------
// STD Traits - Commented std traits are not implemented yet.
//------------------------------------------------------------------------------
using std::is_array;
using std::is_class;
using std::is_enum;
using std::is_floating_point;
using std::is_function;
using std::is_integral;
using std::is_lvalue_reference;
using std::is_member_function_pointer;
using std::is_member_object_pointer;
using std::is_pointer;
using std::is_rvalue_reference;
using std::is_union;
using std::is_void;
using std::is_arithmetic;
using std::is_compound;
using std::is_fundamental;
using std::is_member_pointer;
using std::is_object;
using std::is_reference;
using std::is_scalar;
using std::is_abstract;
using std::is_const;
using std::is_empty;
using std::is_literal_type;
using std::is_pod;
using std::is_polymorphic;
using std::is_signed;
using std::is_standard_layout;
using std::is_trivial;
//using std::is_trivially_copyable; 
using std::is_unsigned;
using std::is_volatile;
using std::has_virtual_destructor;
using std::is_assignable;
using std::is_constructible;
using std::is_copy_assignable;
using std::is_copy_constructible;
using std::is_destructible;
using std::is_default_constructible;
using std::is_move_assignable;
using std::is_move_constructible;
//using std::is_trivially_assignable;
//using std::is_trivially_constructible;
//using std::is_trivially_copy_assignable;
//using std::is_trivially_copy_constructible;
//using std::is_trivially_destructible;
//using std::is_trivially_default_constructible;
//using std::is_trivially_move_assignable;
//using std::is_trivially_move_constructible;
using std::is_nothrow_assignable;
using std::is_nothrow_constructible;
using std::is_nothrow_copy_assignable;
using std::is_nothrow_copy_constructible;
using std::is_nothrow_destructible;
using std::is_nothrow_default_constructible;
using std::is_nothrow_move_assignable;
using std::is_nothrow_move_constructible;
using std::is_base_of;
using std::is_convertible;
using std::is_same;
using std::alignment_of;
using std::extent;
using std::rank;
using std::add_const;
using std::add_cv;
using std::add_volatile;
using std::remove_const;
using std::remove_cv;
using std::remove_volatile;
using std::add_pointer;
using std::add_lvalue_reference;
using std::add_rvalue_reference;
using std::decay;
using std::make_signed;
using std::make_unsigned;
using std::remove_all_extents;
using std::remove_extent;
using std::remove_pointer;
using std::remove_reference;
using std::underlying_type;
using std::aligned_storage;
//using std::aligned_union;
using std::common_type;
using std::result_of;
//------------------------------------------------------------------------------
template <class T>
struct is_nothrow_movable : integral_constant<bool,
    is_nothrow_move_constructible<T>::value
    && is_nothrow_move_assignable<T>::value>
{};

//------------------------------------------------------------------------------
// aliasing
//------------------------------------------------------------------------------
n_meta_alias(is_nothrow_movable);
template <bool A, class B, class C>
using _conditional = typename meta::if_c<A, B, C>::type;

n_meta_alias(is_array);
n_meta_alias(is_class);
n_meta_alias(is_enum);
n_meta_alias(is_floating_point);
n_meta_alias(is_function);
n_meta_alias(is_integral);
n_meta_alias(is_lvalue_reference);
n_meta_alias(is_member_function_pointer);
n_meta_alias(is_member_object_pointer);
n_meta_alias(is_pointer);
n_meta_alias(is_rvalue_reference);
n_meta_alias(is_union);
n_meta_alias(is_void);
n_meta_alias(is_arithmetic);
n_meta_alias(is_compound);
n_meta_alias(is_fundamental);
n_meta_alias(is_member_pointer);
n_meta_alias(is_object);
n_meta_alias(is_reference);
n_meta_alias(is_scalar);
n_meta_alias(is_abstract);
n_meta_alias(is_const);
n_meta_alias(is_empty);
n_meta_alias(is_literal_type);
n_meta_alias(is_pod);
n_meta_alias(is_polymorphic);
n_meta_alias(is_signed);
n_meta_alias(is_standard_layout);
n_meta_alias(is_trivial);
//n_meta_alias(is_trivially_copyable); 
n_meta_alias(is_unsigned);
n_meta_alias(is_volatile);
n_meta_alias(has_virtual_destructor);
n_meta_alias(is_assignable);
n_meta_alias(is_constructible);
n_meta_alias(is_copy_assignable);
n_meta_alias(is_copy_constructible);
n_meta_alias(is_destructible);
n_meta_alias(is_default_constructible);
n_meta_alias(is_move_assignable);
n_meta_alias(is_move_constructible);
//n_meta_alias(is_trivially_assignable);
//n_meta_alias(is_trivially_constructible);
//n_meta_alias(is_trivially_copy_assignable);
//n_meta_alias(is_trivially_copy_constructible);
//n_meta_alias(is_trivially_destructible);
//n_meta_alias(is_trivially_default_constructible);
//n_meta_alias(is_trivially_move_assignable);
//n_meta_alias(is_trivially_move_constructible);
n_meta_alias(is_nothrow_assignable);
n_meta_alias(is_nothrow_constructible);
n_meta_alias(is_nothrow_copy_assignable);
n_meta_alias(is_nothrow_copy_constructible);
n_meta_alias(is_nothrow_destructible);
n_meta_alias(is_nothrow_default_constructible);
n_meta_alias(is_nothrow_move_assignable);
n_meta_alias(is_nothrow_move_constructible);
n_meta_alias(is_base_of);
n_meta_alias(is_convertible);
n_meta_alias(is_same);
n_meta_alias(alignment_of);
n_meta_alias(extent);
n_meta_alias(rank);
n_meta_alias(add_const);
n_meta_alias(add_cv);
n_meta_alias(add_volatile);
n_meta_alias(remove_const);
n_meta_alias(remove_cv);
n_meta_alias(remove_volatile);
n_meta_alias(add_pointer);
n_meta_alias(add_lvalue_reference);
n_meta_alias(add_rvalue_reference);
n_meta_alias(decay);
n_meta_alias(make_signed);
n_meta_alias(make_unsigned);
n_meta_alias(remove_all_extents);
n_meta_alias(remove_extent);
n_meta_alias(remove_pointer);
n_meta_alias(remove_reference);
n_meta_alias(underlying_type);
//n_meta_alias(aligned_storage);
//n_meta_alias(aligned_union);
n_meta_alias(common_type);
n_meta_alias(result_of);

/** @} */

}} // namespaces

#endif // NIC_34E7280F5B5FA2C0_NIC
