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
#ifndef NIC_7ADF3BDA3CB65EFB_NIC
#define NIC_7ADF3BDA3CB65EFB_NIC

#include "../traits.h"
#include "../../type_traits.h"
#include "../../meta.h"
#include "../../mem.h"

namespace nebula { namespace foundation { namespace iterator {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
template <class I, class O>
struct copy_impl
{
private:
    using I_T = typename iterator_value<I>::type;
    using O_T = typename iterator_value<O>::type;
    
    template <class I_, class O_>
    inline static O_ apply_(I_ first, I_ last, O_ dest, false_type)
    {
        while(first != last)
            *dest++ = *first++;
        return dest;
    }
    template <class I_, class O_>
    inline static O_ apply_(I_ first, I_ last, O_ dest, true_type)
    {
        foundation::memmove(dest, first, (last-first) * sizeof(O_T));
        return dest + (last-first);
    }
    
public:
    inline static O apply(I first, I last, O dest)
    {
        return apply_(first, last, dest, 
            meta::_and<
                is_pointer<I>,
                is_pointer<O>,
                is_pod<I_T>,
                is_same<I_T, O_T>>());
    }
};
//------------------------------------------------------------------------------
template <class I, class O>
inline O copy(I first, I last, O dest)
{
    return copy_impl<I, O>::apply(first, last, dest);
}

/** @} */

}}} // namespaces

#endif // NIC_7ADF3BDA3CB65EFB_NIC