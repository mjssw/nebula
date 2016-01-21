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
#ifndef NIC_608DCD56B7386A6B_NIC
#define NIC_608DCD56B7386A6B_NIC

#include "../common.h"

namespace nebula { namespace foundation { namespace io {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
struct invalid_stream_operation : public virtual logic_error {};
//------------------------------------------------------------------------------
namespace stream_detail {
template <class Holder, class ... Tags> class generic_stream;
} // stream_detail
//------------------------------------------------------------------------------
class stream_base
{
public:
    using stream_size = streamsize;
    using stream_offset = streamoff;
    using stream_position = streampos;
    
protected:
    inline virtual ~stream_base() noexcept {}
    
    inline virtual stream_size read(char *x, stream_size n) {
        n_throw(invalid_stream_operation);
    }
    inline virtual ceof get() {
        n_throw(invalid_stream_operation);
    }
    inline virtual void unget() {
        n_throw(invalid_stream_operation);
    }
    inline virtual ceof peek() {
        n_throw(invalid_stream_operation);
    }
    
    inline virtual void seekg_beg(stream_offset off) {
        n_throw(invalid_stream_operation);
    }
    inline virtual void seekg_cur(stream_offset off) {
        n_throw(invalid_stream_operation);
    }
    inline virtual void seekg_end(stream_offset off) {
        n_throw(invalid_stream_operation);
    }
    
    inline virtual stream_position tellg() const {
        n_throw(invalid_stream_operation);
    }
    
    inline virtual void write(const char *x, stream_size n) {
        n_throw(invalid_stream_operation);
    }
    inline virtual void put(char x) {
        n_throw(invalid_stream_operation);
    }
    
    inline virtual void seekp_beg(stream_offset off) {
        n_throw(invalid_stream_operation);
    }
    inline virtual void seekp_cur(stream_offset off) {
        n_throw(invalid_stream_operation);
    }
    inline virtual void seekp_end(stream_offset off) {
        n_throw(invalid_stream_operation);
    }
    
    inline virtual stream_position tellp() const {
        n_throw(invalid_stream_operation);
    }
    
    inline virtual void flush() {
        n_throw(invalid_stream_operation);
    }
    
    inline virtual void sync() {
        n_throw(invalid_stream_operation);
    }
    
    template <class Holder, class ... Tags>
    friend class stream_detail::generic_stream;
};
//------------------------------------------------------------------------------
namespace stream_detail {
//------------------------------------------------------------------------------
class stream_ref_holder
{
public:
    template <class T>
    inline stream_ref_holder(T &s) noexcept
    : stream_(s)
    {}
    
    inline stream_base &stream() noexcept {
        return stream_;
    }
    inline const stream_base &stream() const noexcept {
        return stream_;
    }
private:
    stream_base &stream_;
};
//------------------------------------------------------------------------------
template <class Holder, class ... Tags>
class generic_stream
{
public:
    using stream_size = streamsize;
    using stream_offset = streamoff;
    using stream_position = streampos;
    using stream_category = tag<Tags...>;
    
private:
    using this_type = generic_stream<Holder, Tags...>;
    using holder_type = Holder;
    
    template <template <class> class F, class Stream>
    constexpr static bool is_superset() noexcept {
        return !F<this_type>::value || F<Stream>::value;
    }
    template <class Stream>
    constexpr static void check() noexcept {
        n_static_assert(n_arg(is_superset<has_read, Stream>()), "");
        n_static_assert(n_arg(is_superset<has_peek, Stream>()), "");
        n_static_assert(n_arg(is_superset<has_unget, Stream>()), "");
        n_static_assert(n_arg(is_superset<has_write, Stream>()), "");
        n_static_assert(n_arg(is_superset<has_flush, Stream>()), "");
        n_static_assert(n_arg(is_superset<has_sync, Stream>()), "");
        n_static_assert(n_arg(is_superset<has_seekg_beg, Stream>()), "");
        n_static_assert(n_arg(is_superset<has_seekg_cur, Stream>()), "");
        n_static_assert(n_arg(is_superset<has_seekg_end, Stream>()), "");
        n_static_assert(n_arg(is_superset<has_seekp_beg, Stream>()), "");
        n_static_assert(n_arg(is_superset<has_seekp_cur, Stream>()), "");
        n_static_assert(n_arg(is_superset<has_seekp_end, Stream>()), "");
        n_static_assert(n_arg(is_superset<is_direct, Stream>()), "");
    }
    
public:
    template <class Stream, class H = holder_type,
        typename enable_if<is_same<H, stream_ref_holder>, int>::type = 0>
    inline generic_stream(Stream &s) noexcept
    : holder(s)
    {
        check<Stream>();
    }
    
    template <class S = this_type,
        typename enable_if<has_read<S>, int>::type = 0>
    inline stream_size read(char *x, const stream_size n) {
        return this->stream().read(x, n);
    }
    template <class S = this_type,
        typename enable_if<has_read<S>, int>::type = 0>
    inline ceof get() {
        return this->stream().get();
    }
    template <class S = this_type,
        typename enable_if<has_unget<S>, int>::type = 0>
    inline void unget() {
        this->stream().unget();
    }
    template <class S = this_type,
        typename enable_if<has_peek<S>, int>::type = 0>
    inline ceof peek() {
        return this->stream().peek();
    }
    
    template <class S = this_type,
        typename enable_if<has_write<S>, int>::type = 0>
    inline void write(const char *x, const stream_size n) {
        this->stream().write(x, n);
    }
    template <class S = this_type,
        typename enable_if<has_put<S>, int>::type = 0>
    inline void put(char x) {
        this->stream().put(x);
    }
    
    template <class S = this_type,
        typename enable_if<has_seekg_beg<S>, int>::type = 0>
    inline void seekg_beg(const stream_offset off) {
        this->stream().seekg_beg(off);
    }
    template <class S = this_type,
        typename enable_if<has_seekg_cur<S>, int>::type = 0>
    inline void seekg_cur(const stream_offset off) {
        this->stream().seekg_cur(off);
    }
    template <class S = this_type,
        typename enable_if<has_seekg_end<S>, int>::type = 0>
    inline void seekg_end(const stream_offset off) {
       this->stream().seekg_end(off);
    }
    
    template <class S = this_type,
        typename enable_if<has_seekp_beg<S>, int>::type = 0>
    inline void seekp_beg(const stream_offset off) {
        this->stream().seekp_beg(off);
    }
    template <class S = this_type,
        typename enable_if<has_seekp_cur<S>, int>::type = 0>
    inline void seekp_cur(const stream_offset off) {
        this->stream().seekp_cur(off);
    }
    template <class S = this_type,
        typename enable_if<has_seekp_end<S>, int>::type = 0>
    inline void seekp_end(const stream_offset off) {
        this->stream().seekp_end(off);
    }
    
    template <class S = this_type,
        typename enable_if<has_read<S>, int>::type = 0>
    inline stream_position tellg() const {
        return this->stream().tellg();
    }
    template <class S = this_type,
        typename enable_if<has_write<S>, int>::type = 0>
    inline stream_position tellp() const {
        return this->stream().tellp();
    }
    
    template <class S = this_type,
        typename enable_if<has_flush<S>, int>::type = 0>
    inline void flush() {
        this->stream().flush();
    }
    template <class S = this_type,
        typename enable_if<has_sync<S>, int>::type = 0>
    inline void sync() {
        this->stream().sync();
    }

private:
    inline stream_base &stream() noexcept {
        return holder.stream();
    }
    inline const stream_base &stream() const noexcept {
        return holder.stream();
    }
    
    holder_type holder;
};
//------------------------------------------------------------------------------
} // stream_detail
//------------------------------------------------------------------------------
template <class ... Tags>
using stream_ref = stream_detail::generic_stream<
    stream_detail::stream_ref_holder, Tags...>;

/** @} */

}}} // namespaces

#endif // NIC_608DCD56B7386A6B_NIC
