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
#ifndef NIC_E9A0E77D40870A0B_NIC
#define NIC_E9A0E77D40870A0B_NIC

#include "utf8_basics.h"

namespace nebula { namespace foundation { namespace utf {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
/** A simple wrapper around the iterator I which traverses a range
 *  bidirectionally from codepoint to codepoint.
 *
 *  @warning This class works only for valid utf-8 ranges.
 * */
template <class I>
class codepoint_iterator : public iterator::iterator_facade<
    codepoint_iterator<I>,
    char32_t,
    iterator::bidirectional_traversal_tag,
    iterator::readable_iterator_tag,
    char32_t,
    char32_t *,
    iterator::_iterator_difference<I>>
{
    n_static_assert(n_arg(
        has_tag<iterator::_iterator_traversal<I>,
        iterator::random_access_traversal_tag>::type::value),
        "");
    
public:
    /** @param i_ Must point to the start of a valid utf code point. */
    inline explicit codepoint_iterator(I i_) noexcept
    : i(i_)
    {}
    
    codepoint_iterator(codepoint_iterator &) = default;
    codepoint_iterator(const codepoint_iterator &) = default;
    codepoint_iterator(codepoint_iterator &&) = default;
    
    codepoint_iterator &operator = (const codepoint_iterator &) = default;
    codepoint_iterator &operator = (codepoint_iterator &&) = default;
    
    inline char32_t dereference() const
    {
        return utf::unsafe_widen(i);
    }
    
    inline void increment()
    {
        n_assert(utf_detail::is_leading(*i));
        
        const iterator::_iterator_difference<I> n
            = utf_detail::sequence_length(*i);
        if(n == 0)
            n_throw(utf_error);
        iterator::advance(i, n);
    }
    inline void decrement()
    {
        n_assert(utf_detail::is_leading(*i));
        
        for(size_t k = 0; k < 4; ++k)
            if(utf_detail::is_leading(*--i))
                return;
        n_throw(utf_error);
    }
    
    inline bool equal(const codepoint_iterator &other) const
    {
        return i == other.i;
    }
    
    inline I get() const {
        return i;
    }

private:
    I i;
};

//------------------------------------------------------------------------------
template <class I>
inline codepoint_iterator<I> make_codepoint_iterator(I i)
{
    return codepoint_iterator<I>(i);
}

/** @} */

}}} // namespaces

#endif // NIC_E9A0E77D40870A0B_NIC

