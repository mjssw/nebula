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
#ifndef NIC_D12B6CDE08668BD8_NIC
#define NIC_D12B6CDE08668BD8_NIC

#include "stream.h"

namespace nebula { namespace foundation { namespace io {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
template <class Stream>
class stream_adaptor
{
public:
    using stream_type = Stream;
    using stream_size = typename stream_size<stream_type>::type;
    using stream_offset = typename stream_offset<stream_type>::type;
    using stream_position = typename stream_position<stream_type>::type;
    using stream_category = typename stream_category<stream_type>::type;
    
    inline stream_adaptor(stream_type &s) noexcept
    : stream_(s)
    {}
    
    inline stream_type &stream() noexcept {
        return stream_;
    }
    inline const stream_type &stream() const noexcept {
        return stream_;
    }
    
    template <class S = stream_type,
        typename enable_if<has_read<S>, int>::type = 0>
    inline stream_size read(char *x, const stream_size n) {
        return io::read(this->stream(), x, n);
    }
    template <class S = stream_type,
        typename enable_if<has_read<S>, int>::type = 0>
    inline ceof get() {
        return io::get(this->stream());
    }
    template <class S = stream_type,
        typename enable_if<has_unget<S>, int>::type = 0>
    inline void unget() {
        io::get(this->stream());
    }
    template <class S = stream_type,
        typename enable_if<has_peek<S>, int>::type = 0>
    inline ceof peek() {
        return io::peek(this->stream());
    }
    
    template <class S = stream_type,
        typename enable_if<has_write<S>, int>::type = 0>
    inline void write(const char *x, const stream_size n) {
        io::write(this->stream(), x, n);
    }
    template <class S = stream_type,
        typename enable_if<has_write<S>, int>::type = 0>
    inline void put(const char x) {
        io::put(this->stream(), x);
    }
    
    template <class S = stream_type,
        typename enable_if<has_seekg_beg<S>, int>::type = 0>
    inline void seekg_beg(const stream_offset off) {
        io::seekg_beg(this->stream(), off);
    }
    template <class S = stream_type,
        typename enable_if<has_seekg_cur<S>, int>::type = 0>
    inline void seekg_cur(const stream_offset off) {
        io::seekg_cur(this->stream(), off);
    }
    template <class S = stream_type,
        typename enable_if<has_seekg_end<S>, int>::type = 0>
    inline void seekg_end(const stream_offset off) {
        io::seekg_end(this->stream(), off);
    }
    
    template <class S = stream_type,
        typename enable_if<has_seekp_beg<S>, int>::type = 0>
    inline void seekp_beg(const stream_offset off) {
        io::seekp_beg(this->stream(), off);
    }
    template <class S = stream_type,
        typename enable_if<has_seekp_cur<S>, int>::type = 0>
    inline void seekp_cur(const stream_offset off) {
        io::seekp_cur(this->stream(), off);
    }
    template <class S = stream_type,
        typename enable_if<has_seekp_end<S>, int>::type = 0>
    inline void seekp_end(const stream_offset off) {
        io::seekp_end(this->stream(), off);
    }
    
    template <class S = stream_type,
        typename enable_if<has_read<S>, int>::type = 0>
    inline stream_position tellg() {
        return io::tellg(this->stream());
    }
    template <class S = stream_type,
        typename enable_if<has_write<S>, int>::type = 0>
    inline stream_position tellp() {
        return io::tellp(this->stream());
    }
    
    template <class S = stream_type,
        typename enable_if<has_flush<S>, int>::type = 0>
    inline void flush() {
        io::flush(this->stream());
    }
    template <class S = stream_type,
        typename enable_if<has_sync<S>, int>::type = 0>
    inline void sync() {
        io::sync(this->stream());
    }
    
private:
    Stream &stream_;
};

/** @} */

}}} // namespaces

#endif // NIC_D12B6CDE08668BD8_NIC
