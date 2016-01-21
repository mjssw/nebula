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
#ifndef NIC_8C5B98BB4FA896AA_NIC
#define NIC_8C5B98BB4FA896AA_NIC

#include "utf8_basics.h"

namespace nebula { namespace foundation { namespace utf {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <class String>
struct validate_impl
{
    template <class R>
    inline static auto apply(R &&s)
    -> tuple<decltype(range::begin(foundation::declval<R>())),
        range::_range_size<String>>
    {
        range::_range_size<String> cp_count = 0;
        
        if(range::empty(s))
            return make_tuple(range::end(s), cp_count);
        
        auto i = range::begin(s);
        const auto end = range::end(s);
        
        for( ; i != end; ++i)
        {
            const size_t n = utf_detail::sequence_length(*i);
            
            if(0 == n)
                return make_tuple(i, cp_count);
            
            auto old = i;
            
            for(size_t j = 1; j < n; ++j)
            {
                if(++i == end)
                    return make_tuple(old, cp_count);
                if(!utf_detail::is_trailing(*i))
                    return make_tuple(old, cp_count);
            }
            
            ++cp_count;
        }
        
        return make_tuple(i, cp_count);
    }
};
//------------------------------------------------------------------------------
/** Check if a string is utf-8 encoded.
 *  @return Tuple (i, n) where i is either range::end(s) if the utf sequence is
 *  valid or an iterator to the offending code unit, n is the number of valid
 *  code points counted such that:
 *  @code
 *      i == (make_codepoint_iterator(range::begin(s)) + n).get()
 *  @endcode
 * */
template <class String>
inline tuple<range::_range_iterator<_remove_reference<String>>,
    range::_range_size<ctraits::_value<String>>>
validate(String &&s)
{
    n_static_assert(is_lvalue_reference<String>::type::value, "");
    return validate_impl<ctraits::_value<String>>::apply(s);
}

/** @} */

}}} // namespaces

#endif // NIC_8C5B98BB4FA896AA_NIC

