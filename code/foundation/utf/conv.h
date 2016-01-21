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
#ifndef NIC_4B1435B200F3ABBB_NIC
#define NIC_4B1435B200F3ABBB_NIC

#include "utf8_basics.h"
#include "../array.h"

namespace nebula { namespace foundation { namespace utf {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <class Range>
class utf8_to_utf32_impl
{
private:
    using const_iterator = range::_range_iterator<const Range>;
    
public:
    template <class Sink>
    inline static const_iterator apply(const Range &r, Sink &&sink)
    {
        array<char, 4> cp;
        
        const const_iterator end_ = range::end(r);
        const_iterator i = range::begin(r);
        while(i != end_)
        {
            cp[0] = *i;
            const size_t n = utf_detail::sequence_length(cp[0]);
            n_assert(n < 4);
            if(n == 0)
                return i;
            
            ++i;
            
            for(size_t k = 1; k < n; ++k)
            {
                if(i == end_)
                    n_throw(utf_error, underflow_error);
                cp[k] = *i++;
            }
            
            utf_detail::u8_to_u32(cp.data(), n, sink);
        }
        
        return end_;
    }
};
//------------------------------------------------------------------------------
/** Simple utf converter.
 *
 *  This function may succeed even if the input range does not contain
 *  valid utf code. To thoroughly check for valid utf code use validate().
 *  @param r forward range.
 *  @param sink A functor accepting a codeunit.
 *  @return range::end(r) on success, or an iterator pointing to the offending
 *  codeunit.
 * */
template <class Range, class Sink>
inline range::_range_iterator<const Range> utf8_to_utf32(
const Range &r, Sink &&sink)
{
    return utf8_to_utf32_impl<Range>::apply(r, sink);
}

//------------------------------------------------------------------------------
template <class Range>
class utf32_to_utf8_impl
{
private:
    using const_iterator = range::_range_iterator<const Range>;
    
public:
    template <class Sink>
    inline static const_iterator apply(const Range &r, Sink &&sink)
    {
        const const_iterator end_ = range::end(r);
        for(const_iterator i = range::begin(r); i != range::end(r); ++i)
        {
            const char32_t c = *i;
            const size_t n = utf_detail::u32_to_u8_codeunit_count(c);
            if(n == 0)
                return i;
            utf_detail::u32_to_u8(*i, n, sink);
        }
        return end_;
    }
};
//------------------------------------------------------------------------------
/** @see utf8_to_utf32
 * */
template <class Range, class Sink>
inline range::_range_iterator<const Range> utf32_to_utf8(
    const Range &r, Sink &&sink)
{
    return utf32_to_utf8_impl<Range>::apply(r, sink);
}

//------------------------------------------------------------------------------
template <class Range>
class utf8_to_utf16_impl
{
private:
    using const_iterator = range::_range_iterator<const Range>;
    
public:
    template <class Sink>

    inline static const_iterator apply(const Range &r, Sink &sink)
    {
        array<char, 4> cp;
        
        const const_iterator end_ = range::end(r);
        const_iterator i = range::begin(r);
        while(i != end_)
        {        
            cp[0] = *i++;
            const size_t n = utf_detail::sequence_length(cp[0]);
            n_assert(n < 4);
            if(n == 0)
                return i;
            
            for(size_t k = 1; k < n; ++k)
            {
                if(i == end_)
                    n_throw(utf_error, underflow_error);
                cp[k] = *i++;
            }
            
            utf_detail::u8_to_u16(cp.data(), n, sink);
        }
        
        return end_;
    }
};
//------------------------------------------------------------------------------
/** @see utf8_to_utf32
 * */
template <class Range, class Sink>
inline range::_range_iterator<const Range> utf8_to_utf16(
    const Range &r, Sink &&sink)
{
    return utf8_to_utf16_impl<Range>::apply(r, sink);
}

//------------------------------------------------------------------------------
template <class Range>
class utf16_to_utf8_impl
{
private:
    using const_iterator = range::_range_iterator<const Range>;
    
public:
    template <class Sink>
    inline static const_iterator apply(const Range &r, Sink &sink)
    {
        array<char16_t, 2> cp;
        
        const const_iterator end_ = range::end(r);
        for(const_iterator i = range::begin(r); i != range::end(r); ++i)
        {
            const char32_t c = *i;
            const size_t n = utf_detail::u16_sequence_length(c);
            switch(n)
            {
            case 1:
                cp[0] = *i;
                break;
            case 2:
                cp[0] = *i++;
                if(i == end_)
                    n_throw(utf_error, underflow_error);
                cp[1] = *i;
                break;
            default:
                return i;
            }
            
            utf_detail::u16_to_u8(cp.data(), n, sink);
        }
        return end_;
    }
};
//------------------------------------------------------------------------------
/** @see utf8_to_utf32
 * */
template <class Range, class Sink>
inline range::_range_iterator<const Range> utf16_to_utf8(
    const Range &r, Sink &&sink)
{
    return utf16_to_utf8_impl<Range>::apply(r, sink);
}

/** @} */

}}} // namespaces

#endif // NIC_4B1435B200F3ABBB_NIC

