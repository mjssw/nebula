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
#ifndef NIC_806450BEB0F245BA_NIC
#define NIC_806450BEB0F245BA_NIC

#include "stream.h"
#include "../../assert.h"
#include "../../range.h"
#include "../../string.h"

#include <cstdio>

namespace nebula { namespace foundation { namespace io {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
/** */
class fstream : public stream_base
{    
public:
    using stream_size = typename stream_base::stream_size;
    using stream_offset = typename stream_base::stream_offset;
    using stream_position = typename stream_base::stream_position;
    using stream_category = tag<
        out_tag, flush_tag,
        in_tag, peek_tag, unget_tag,
        seek_tag,
        sync_tag>;
        
    inline fstream() noexcept 
    : h(nullptr)
    {}
    fstream(const string &filename, bool trunc = false);
    ~fstream() noexcept;
    
    fstream(const fstream &) = delete;
    inline fstream(fstream &&other) noexcept
    : h(other.h)
    {
        other.h = nullptr;
    }
    fstream &operator = (const fstream &) = delete;
    inline fstream &operator = (fstream &&other) noexcept 
    {
        this->close();
        h = other.h;
        other.h = nullptr;
        return *this;
    }
    
    void open(const string &filename, bool trunc = false);
    void close() noexcept;
    inline bool is_open() const noexcept { return h != nullptr; }
    
    stream_size read(char *x, stream_size n) final;
    ceof get() final;
    void unget() final;
    ceof peek() final;
   
    void seekg_beg(stream_offset off) final;
    void seekg_cur(stream_offset off) final;
    void seekg_end(stream_offset off) final;
    
    stream_position tellg() const final;
    
    void write(const char *x, stream_size n) final;
    void put(char x) final;
    
    void seekp_beg(stream_offset off) final;
    void seekp_cur(stream_offset off) final;
    void seekp_end(stream_offset off) final;
    
    stream_position tellp() const final;
    
    void flush() final;
    void sync() final;
    
private:
    FILE *h;
    
    void open_(const string &filename,
        const io_detail::mode m, const bool trunc = false);
    void open_ate_(const string &filename,
        const io_detail::mode m, const bool trunc = false);
    
    friend class ifstream;
    friend class ofstream;
    friend class ofstream_ate;
    friend class fstream_ate;
};
//------------------------------------------------------------------------------
class ifstream : public stream_base
{
public:
    using stream_size = typename stream_base::stream_size;
    using stream_offset = typename stream_base::stream_offset;
    using stream_position = typename stream_base::stream_position;
    using stream_category = tag<
        in_tag, unget_tag, peek_tag,
        in_seek_tag>;
        
    inline ifstream() noexcept
    {}
    inline ifstream(const string &filename)
    {
        f.open_(filename, io_detail::mode::in);
    }
    
    inline ifstream(ifstream &&other) = default;
    ifstream &operator = (ifstream &&other) = default;
    
    inline void open(const string &filename) {
        f.open_(filename, io_detail::mode::in);
    }
    inline void close() noexcept {
        f.close();
    }
    inline bool is_open() const noexcept { return f.is_open(); }
        
    inline stream_size read(char *x, stream_size n) final {
        return f.read(x, n);
    }
    inline ceof get() final {
        return f.get();
    }
    inline void unget() final {
        f.unget();
    }
    inline ceof peek() final {
        return f.peek();
    }
   
    inline void seekg_beg(stream_offset off) final {
        f.seekg_beg(off);
    }
    inline void seekg_cur(stream_offset off) final {
        f.seekg_cur(off);
    }
    inline void seekg_end(stream_offset off) final {
        f.seekg_end(off);
    }
    
    inline stream_position tellg() const final {
        return f.tellg();
    }
    
private:
    fstream f;  
};
//------------------------------------------------------------------------------
class ofstream : public stream_base
{
public:
    using stream_size = typename stream_base::stream_size;
    using stream_offset = typename stream_base::stream_offset;
    using stream_position = typename stream_base::stream_position;
    using stream_category = tag<
        out_tag, flush_tag,
        out_seek_tag>;
        
    inline ofstream() noexcept
    {}
    inline ofstream(const string &filename, const bool trunc = false)
    {
        f.open_(filename, io_detail::mode::out, trunc);
    }
    
    inline ofstream(ofstream &&other) = default;
    ofstream &operator = (ofstream &&other) = default;
    
    inline void open(const string &filename, const bool trunc = true) {
        f.open_(filename, io_detail::mode::out, trunc);
    }
    inline void close() noexcept {
        f.close();
    }
    inline bool is_open() const noexcept { return f.is_open(); }

    inline void write(const char *x, stream_size n) final {
        f.write(x, n);
    }
    inline void put(char x) final {
        f.put(x);
    }
   
    inline void seekp_beg(stream_offset off) final {
        f.seekp_beg(off);
    }
    inline void seekp_cur(stream_offset off) final {
        f.seekp_cur(off);
    }
    inline void seekp_end(stream_offset off) final {
        f.seekp_end(off);
    }
    
    inline stream_position tellp() const final {
        return f.tellp();
    }
    
    inline void flush() final {
        f.flush();
    }
    
private:
    fstream f;  
};
//------------------------------------------------------------------------------
class fstream_ate : public stream_base
{
public:
    using stream_size = typename stream_base::stream_size;
    using stream_offset = typename stream_base::stream_offset;
    using stream_position = typename stream_base::stream_position;
    using stream_category = tag<
        out_tag, flush_tag,
        in_tag, peek_tag, unget_tag,
        in_seek_tag,
        shared_seq_tag,
        sync_tag>;
        
    inline fstream_ate() noexcept
    : pos(0)
    {}
    inline fstream_ate(const string &filename, const bool trunc = false)
    : pos(0)
    {
        f.open_ate_(filename, io_detail::mode::in_out, trunc);
    }
    
    inline fstream_ate(fstream_ate &&other) = default;
    fstream_ate &operator = (fstream_ate &&other) = default;
    
    inline void open(const string &filename, const bool trunc = true) {
        f.open_ate_(filename, io_detail::mode::in_out, trunc);
    }
    inline void close() noexcept {
        f.close();
    }
    inline bool is_open() const noexcept { return f.is_open(); }
    
    inline stream_size read(char *x, stream_size n) final {
        return f.read(x, n);
    }
    inline ceof get() final {
        return f.get();
    }
    inline void unget() final {
        f.unget();
    }
    inline ceof peek() final {
        return f.peek();
    }
   
    inline void seekg_beg(stream_offset off) final {
        f.seekg_beg(off);
    }
    inline void seekg_cur(stream_offset off) final {
        f.seekg_cur(off);
    }
    inline void seekg_end(stream_offset off) final {
        f.seekg_end(off);
    }
    
    inline stream_position tellg() const final {
        return f.tellg();
    }
    
    inline void write(const char *x, stream_size n) final {
        f.write(x, n);
    }
    inline void put(char x) final {
        f.put(x);
    }
    
    inline stream_position tellp() const final {
        return f.tellp();
    }
    
    inline void flush() final {
        f.flush();
    }
    inline void sync() final {
        f.sync();
    }
    
private:
    stream_position pos;
    fstream f;  
};
//------------------------------------------------------------------------------
class ofstream_ate : public stream_base
{
public:
    using stream_size = typename stream_base::stream_size;
    using stream_offset = typename stream_base::stream_offset;
    using stream_position = typename stream_base::stream_position;
    using stream_category = tag<
        out_tag, flush_tag>;
        
    inline ofstream_ate() noexcept
    {}
    inline ofstream_ate(const string &filename, const bool trunc = false)
    {
        f.open_ate_(filename, io_detail::mode::out, trunc);
    }
    
    inline ofstream_ate(ofstream_ate &&other) = default;
    ofstream_ate &operator = (ofstream_ate &&other) = default;
    
    inline void open(const string &filename, const bool trunc = true) {
        f.open_ate_(filename, io_detail::mode::out, trunc);
    }
    inline void close() noexcept {
        f.close();
    }
    inline bool is_open() const noexcept { return f.is_open(); }
    
    inline void write(const char *x, stream_size n) final {
        f.write(x, n);
    }
    inline void put(char x) final {
        f.put(x);
    }
    
    inline stream_position tellp() const final {
        return f.tellp();
    }
    
    inline void flush() final {
        f.flush();
    }
    
private:
    fstream f;  
};

/** @} */

}}} // namespaces

#endif // NIC_806450BEB0F245BA_NIC
