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
#ifndef NIC_F0682E757830E5A8_NIC
#define NIC_F0682E757830E5A8_NIC

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
struct copy_n_impl
{
private:
    using I_T = typename iterator_value<I>::type;
    using O_T = typename iterator_value<O>::type;
    
    template <class I_, class S, class O_>
    inline static O_ apply_(I_ first, const S &n, O_ dest, false_type)
    {
        if(n > 0) {
            *dest++ = *first++;
            for(S i = 1; i < n; ++i)
                *dest++ = *first++;
        }
        return dest;
    }
    template <class I_, class O_>
    inline static O_ apply_(I_ first, const size_t n, O_ dest, true_type)
    {
        foundation::memmove(dest, first, n * sizeof(O_T));
        return dest + n;
    }
    
public:
    template <class S>
    inline static O apply(I first, const S &n, O dest) {
        return apply_(first, n, dest,
            meta::_and<
                is_pointer<I>,
                is_pointer<O>,
                is_pod<I_T>,
                is_same<I_T, O_T>>());
    }
};
//------------------------------------------------------------------------------
template <class I, class O, class Size>
inline O copy_n(I first, const Size &n, O dest)
{
    return copy_n_impl<I, O>::apply(first, n, dest);
}

/** @} */

}}} // namespaces

#endif // NIC_F0682E757830E5A8_NIC
