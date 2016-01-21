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
#ifndef NIC_FCB6C5756F595D5A_NIC
#define NIC_FCB6C5756F595D5A_NIC

#include "stream.h"
#include "../../range.h"
#include "../../declval.h"

namespace nebula { namespace foundation { namespace io {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
/** Stream interface adaptor intended to work with vector<> and basic_string<>.
 *
 *  @param Container Must provide append() and push_back() members and be
 *  a bidirectional range, thus it should work with list<> as well (for lulz).
 * */
template <class Container>
class mstream : public stream_base
{
public:
    using container_type = Container;
    using stream_size = streamsize;
    using stream_offset = streamoff;
    using stream_position = streampos;
    using stream_category = tag<
        out_tag, 
        out_seek_tag,
        in_tag,
        peek_tag,
        unget_tag,
        in_seek_tag,
        shared_seq_tag,
        direct_tag>;
    
    n_static_assert(n_arg(
        _is_same<char, range::_range_value<container_type>>::value),
        "");     
    n_static_assert(n_arg(
        _is_same<stream_size, range::_range_size<container_type>>::value),
        "");
    n_static_assert(n_arg(
        _is_same<stream_offset,
            range::_range_difference<container_type>>::value),
        "");
    
    inline mstream()
    : pos(c.begin())
    {}
    mstream(mstream &) = default;
    mstream(const mstream &) = default;
    mstream(mstream &&) = default;
    
    template <class ... X>
    inline mstream(X && ... x)
    : c(foundation::forward<X>(x)...), pos(range::begin(c))
    {}
    
    mstream &operator = (mstream &) = default;
    mstream &operator = (const mstream &) = default;
    mstream &operator = (mstream &&) = default;
    
    inline void swap(mstream &other)
    noexcept(noexcept(
        foundation::swap(declval<container_type>(), declval<container_type>())
        ))
    {
        foundation::swap(c, other.c);
        foundation::swap(pos, other.pos);
    }
    
    inline const container_type &container() & noexcept {
        return c;
    }
    inline container_type container() && noexcept {
        return move(c);
    }
    inline const container_type &container() const & noexcept {
        return c;
    }
    template <class C>
    inline void container(C &&c_)
    {
        c = foundation::forward<C>(c_);
        reset();
    }
    
    inline void reset() noexcept
    {
        pos = range::begin(c);
    }
    
    inline void write(const char *x, stream_size n) final {
        const stream_size delta = iterator::distance(pos, range::end(c));
        if(n > delta)
        {
            iterator::copy(x, x+delta, pos);
            c.append(x+delta, x+n);
            pos = range::end(c);
        }
        else
        {
            iterator::copy(x, x+n, pos);
            iterator::advance(pos, n);
        }
    }
    inline void put(char c_) final {
        if(pos == range::end(c))
        {
            c.push_back(c_);
            pos = range::end(c);
        }
        else
            *pos++ = c_;
    }
    
    inline stream_size read(char *x, stream_size n) final {
        const stream_size delta = iterator::distance(pos, range::end(c));
        if(delta < n)
        {
            iterator::copy(pos, range::end(c), x);
            pos = range::end(c);
            return delta;
        }
        
        iterator::copy(pos, pos+n, x);
        iterator::advance(pos, n);
        return n;
    }
    inline ceof peek() final {
        if(pos != range::end(c))
        {
            range::_range_iterator<container_type> nxt
                = iterator::advanced(pos, 1);
            if(nxt != range::end(c))
                return *nxt;
        }
        return io::eof;
    }
    inline ceof get() final {
        if(pos != range::end(c))
            return *pos++;
        return io::eof;
    }
    inline void unget() final {
        if(pos != range::begin(c))
            --pos;
        else
            n_throw(io_error);
    }
    
    inline void seekg_beg(const stream_offset off) final {
        if(off < stream_offset(0))
            n_throw(logic_error);
        pos = stream_size(off) > range::size(c) ?
            range::end(c)
            : iterator::advanced(range::begin(c), off);
    }
    inline void seekg_cur(const stream_offset off) final {
        const stream_offset boff = iterator::distance(
            range::begin(c), pos)
            + off;
        seekg_beg(boff);
    }
    inline void seekg_end(const stream_offset off) final {
        const stream_offset boff = iterator::distance(
            range::begin(c), range::end(c))
            + off;
        seekg_beg(boff);
    }
    inline void seekp_beg(const stream_offset off) final {
        seekg_beg(off);
    }
    inline void seekp_cur(const stream_offset off) final {
        seekg_cur(off);
    }
    inline void seekp_end(const stream_offset off) final {
        seekg_end(off);
    }
    
    inline stream_position tellg() const final {
        return iterator::distance(range::begin(c),
            range::_range_iterator<const container_type>(pos));
    }
    inline stream_position tellp() const final {
        return tellg();
    }

private:
    container_type c;
    range::_range_iterator<container_type> pos;
};

/** @} */

}}} // namespaces

#endif // NIC_FCB6C5756F595D5A_NIC
