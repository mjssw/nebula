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
#ifndef NIC_A85C86DE6640D04B_NIC
#define NIC_A85C86DE6640D04B_NIC

#include "find_if.h"
#include "../../move.h"

namespace nebula { namespace foundation { namespace iterator {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
template <class I>
struct remove_if_impl
{
    template <class F_>
    inline static I apply(I first, const I last, F_ &&f)
    {
        first = iterator::find_if(first, last, f);
        if(first != last)
        {
            for(I i = first; ++i != last; )
            {
                if(!f(*i))
                    *first++ = foundation::move(*i);
            }
        }
        return first;
    }
};
//------------------------------------------------------------------------------
/** Removes all elements in the range [first, last) that satisfies the unary
 * predicate f.
 * @param I Must be an incrementable iterator.
 * @param f A unary predicate to filter a certain element.
 * @return An iterator one past the last element of the 'new' range.
 * @note The supplied functor f must not throw.
 * @note Moving of elements must not throw.
 * @note Will not throw.
 * */
template <class I, class F>
inline I remove_if(I first, I last, F &&f)
{
    return remove_if_impl<I>::apply(first, last, f);
}

/** @} */

}}} // namespaces

#endif // NIC_A85C86DE6640D04B_NIC
