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
#ifndef NIC_8475901BE94B3F1A_NIC
#define NIC_8475901BE94B3F1A_NIC

#include "memory/allocator.h"
#include "memory/common.h"

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
/** @brief Everything within this namespaces is dealing with memory management
 * based on allocators.
 * 
 * An allocator is a class that allocates and deallocates memory which can
 * be used to construct/destruct instances of a given type. That type can be
 * queried using the allocator_value<> template.
 * 
 * Allocators must provide a default-constructor.
 * 
 * Instances of the same allocator template, if specialized for different
 * types using rebind, must be convertible to each other. Instances of the
 * same allocator type must be convertible to each other.
 * Convertible means, that copy/move construction and copy/move assignment must
 * be well formed. Note that rebind<> is allowed to fail, if the allocator
 * cannot be specialized for the requested type.
 * 
 * Keep in mind, that passing allocators by value is common practice.
 * 
 * If two allocators compare equal, then memory allocated by any of them, can
 * be managed by the other. If instances of an allocator always compare 
 * equal, then the compile time constant is_always_equal<Alloc> shall be 
 * true_type.
 * 
 * Move-construction and move-assignment of allocators must effectively transfer
 * resource ownership. If resources acquired by allocator A then B = move(A)
 * must enable to manage resources of A. Allocators must also swap
 * resource ownership if they are swapped using swap(). Further two allocators
 * compare equal if one has been copy constructed/assigned from the other.
 * 
 * Allocators must adhear to the following exception rules. 
 * Default construction, move construction/assignment, max_size(), deallocate() 
 * must not throw. destroy() must not throw except the destructor of the
 * element to destroy throws. If allocate() fails it must throw bad_alloc.
 *
 * Containers should, if reasonable, implement get_allocator() member function
 * that basically returns a copy of the internal allocator. If at all available,
 * then this member shall not throw.
 * 
 * pocca == true_type, then the allocator must be copied by copy-assignment,
 * if the container is copied by copy-assigned. Even if the container is empty!
 * If pocca == false_type, then copying of the underlying allocator can occurr
 * in above described circumstances, but it is not mandatory.
 * pocca == false_type by default.
 * 
 * pocma == true_type, then the allocator must be moved by move-assignment,
 * if the container is moved by move-assigned. Even if the container is empty!
 * If pocma == false_type, then moving-assignment of the underlying allocator
 * can occurr in above described circumstances, but it is not mandatory.
 * pocma == false_type by default.
 * 
 * pocs: same as pocma, regarding the swap() operation.
 * pocs == false_type by default.
 * 
 * socc: Creates a new allocator instance on container copy-construction, that
 * is used for the newly created container.
 * socc returns a copy of the allocator by default.
 * */
namespace memory {}

/** @} */

}} // namespaces

#endif // NIC_8475901BE94B3F1A_NIC