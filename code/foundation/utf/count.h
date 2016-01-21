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
#ifndef NIC_E57A276158B6D874_NIC
#define NIC_E57A276158B6D874_NIC

#include "config.h"
#include "codepoint_iterator.h"
#include "validate.h"

namespace nebula { namespace foundation { namespace utf {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <class String>
struct count_impl
{
    inline static range::_range_size<String> apply(const String &s)
    {
        const auto res = utf::validate(s);
        if(get<0>(res) != range::end(s))
            n_throw(utf_error);
        return get<1>(res);
    }
};
//------------------------------------------------------------------------------
/** @return Number of codepoints in s.
 * */
template <class String>
inline range::_range_size<String> count(const String &s)
{
    return count_impl<String>::apply(s);
}

//------------------------------------------------------------------------------
template <class String>
struct unsafe_count_impl
{
    inline static range::_range_size<String> apply(const String &s)
    {
        range::_range_size<String> res = 0;
        const auto end = make_codepoint_iterator(range::end(s));
        auto i = make_codepoint_iterator(range::begin(s));
        for( ; i != end; ++i)
            ++res;
        return res;
    }
};
//------------------------------------------------------------------------------
/** @return Number of codepoints in s.
 * */
template <class String>
inline range::_range_size<String> unsafe_count(const String &s)
{
    return unsafe_count_impl<String>::apply(s);
}

/** @} */

}}} // namespaces

#endif // NIC_E57A276158B6D874_NIC

