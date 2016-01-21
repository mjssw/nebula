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
#ifndef NIC_DB4D5C2D1A42103E_NIC
#define NIC_DB4D5C2D1A42103E_NIC

#include "traits.h"
#include "../call_traits.h"
#include "../move.h"

namespace nebula { namespace foundation { namespace memory {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <class Alloc>
class construct_impl
{   
public:
    template <class ... Args>
    inline static void apply(Alloc &a, 
        typename allocator_value<Alloc>::type *ptr,
        Args && ... args)
    {
        a.construct(ptr, foundation::forward<Args>(args)...);
    }
};
//------------------------------------------------------------------------------
/** In-place construction of an object.
 * This function calls alloc.construct() if available, otherwise it
 * constructs the object using placement new.
 * @param alloc The allocator used to for construction.
 * @param ptr Pointer to the memory region to construct the object there.
 * @param args Parameter list used for construction - typically the parameters
 * just get forwarded to the actual constructor of the type being constructed.
 * @note Strong exception guarantee.
 * */
template <class Alloc, class ... Args>
inline void construct(Alloc &&alloc, 
    typename allocator_value<typename ctraits::value<Alloc>::type>::type *ptr, 
    Args && ... args)
{
    construct_impl<
        typename ctraits::value<Alloc>::type
    >::apply(alloc, ptr,
        foundation::forward<Args>(args)...);
}

/** @} */

}}} // namespaces

#endif // NIC_DB4D5C2D1A42103E_NIC