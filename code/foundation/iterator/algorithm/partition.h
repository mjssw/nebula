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
#ifndef NIC_E8B6001A1AD175FE_NIC
#define NIC_E8B6001A1AD175FE_NIC

#include "swap.h"

namespace nebula { namespace foundation { namespace iterator {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
template <class I>
struct partition_impl
{
    template <class F>
    inline static I apply(I first, I last, F &&f)
    {
        while(true) {
            while((first != last) && f(*first)) {
                ++first;
            }
            if(first == last--)
                break;
            while ((first != last) && !f(*last)) {
                --last;
            }
            if(first == last)
                break;
            iterator::swap(first++, last);
        }
        return first;
    }
};
//------------------------------------------------------------------------------
/** Reorders the elements in the range [first, last) in such a way that all 
 * elements for which the predicate f returns true precede the elements for 
 * which predicate f returns false. 
 * Relative order of the elements is not preserved.
 * @param I Must be a bidir iterator.
 * @note The supplied functor f is allowed to throw.
 * @note Weak exception guarantee.
 * */
template <class I, class F>
inline I partition(I first, I last, F &&f)
{
    return partition_impl<I>::apply(first, last, f);
}

/** @} */

}}} // namespaces

#endif // NIC_E8B6001A1AD175FE_NIC