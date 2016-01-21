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
#include "../fstream.h"
#include "../../exception.h"
#include "../../../assert.h"
#include "../../../system_error.h"

namespace nebula { namespace foundation { namespace io {
//------------------------------------------------------------------------------
fstream::fstream(const string &filename, bool trunc)
{
    h = nullptr;
    this->open(filename, trunc);
}
//------------------------------------------------------------------------------
fstream::~fstream() noexcept
{
    this->close();
}
//------------------------------------------------------------------------------
void fstream::open(const string &filename, bool trunc)
{
    this->open_(filename, io_detail::mode::in_out, trunc);
}
//------------------------------------------------------------------------------
void fstream::open_(const string &filename, 
    const io_detail::mode m, const bool trunc)
{
    this->close();
    switch(m)
    {
    case io_detail::mode::in:
        h = fopen(filename.c_str(), "rb");
        if(!h)
            n_throw(io_error) << ei_msg_c("fopen() failed.")
            // << ei_filename(filename)
            << system::ei_errno_code();
        break;
    case io_detail::mode::out:
        if(trunc)
        {
            h = fopen(filename.c_str(), "wb");
            if(!h)
                n_throw(io_error) << ei_msg_c("fopen() failed.")
                // << ei_filename(filename)
                << system::ei_errno_code();
        }
        else
        {
            h = fopen(filename.c_str(), "ab");
            if(!h)
                n_throw(io_error) << ei_msg_c("fopen() failed.")
                // << ei_filename(filename)
                << system::ei_errno_code();
            h = freopen(filename.c_str(), "r+b", h);
            if(!h) {
                this->close();
                n_throw(io_error) << ei_msg_c("freopen() failed.")
                // << ei_filename(filename)
                << system::ei_errno_code();
            }
        }
        break;
    default:
        if(trunc)
        {
            h = fopen(filename.c_str(), "w+b");
            if(!h)
                n_throw(io_error) << ei_msg_c("fopen() failed.")
                // << ei_filename(filename)
                << system::ei_errno_code();
        }
        else
        {
            h = fopen(filename.c_str(), "ab");
            if(!h)
                n_throw(io_error) << ei_msg_c("fopen() failed.")
                // << ei_filename(filename)
                << system::ei_errno_code();
            h = freopen(filename.c_str(), "r+b", h);
            if(!h) {
                this->close();
                n_throw(io_error) << ei_msg_c("freopen() failed.")
                // << ei_filename(filename)
                << system::ei_errno_code();
            }
        }
        break;
    }
}
//------------------------------------------------------------------------------
void fstream::open_ate_(const string &filename, 
    const io_detail::mode m, const bool trunc)
{
    this->close();
    switch(m)
    {
    case io_detail::mode::in_out:
        if(trunc)
        {
            h = fopen(filename.c_str(), "w+b");
            if(!h)
                n_throw(io_error) << ei_msg_c("fopen() failed.")
                // << ei_filename(filename)
                << system::ei_errno_code();
            h = freopen(filename.c_str(), "a+b", h);
            if(!h) {
                this->close();
                n_throw(io_error) << ei_msg_c("freopen() failed.")
                // << ei_filename(filename)
                << system::ei_errno_code();
            }
        }
        else
        {
            h = fopen(filename.c_str(), "a+b");
            if(!h)
                n_throw(io_error) << ei_msg_c("fopen() failed.")
                // << ei_filename(filename)
                << system::ei_errno_code();
        }
        break;
    case io_detail::mode::out:
        if(trunc)
        {
            h = fopen(filename.c_str(), "wb");
            if(!h)
                n_throw(io_error) << ei_msg_c("fopen() failed.")
                // << ei_filename(filename)
                << system::ei_errno_code();
            h = freopen(filename.c_str(), "ab", h);
            if(!h) {
                this->close();
                n_throw(io_error) << ei_msg_c("freopen() failed.")
                // << ei_filename(filename)
                << system::ei_errno_code();
            }
        }
        else
        {
            h = fopen(filename.c_str(), "ab");
            if(!h)
                n_throw(io_error) << ei_msg_c("fopen() failed.")
                // << ei_filename(filename)
                << system::ei_errno_code();
        }
        break;
    default:
        n_throw(logic_error);
        break;
    }
}
//------------------------------------------------------------------------------
void fstream::close() noexcept
{
    if(h)
    {
        fclose(h);
        h = nullptr;
    }
}
//------------------------------------------------------------------------------
streamsize fstream::read(char *x, streamsize n)
{
    n_assert(h);
    const size_t res = fread(x, 1, n, h);
    if(ferror(h))
        n_throw(io_error) << ei_msg_c("fread() failed.");
    return res;
}
//------------------------------------------------------------------------------
ceof fstream::get()
{
    n_assert(h);
    const int res = getc(h);
    if(EOF == res)
    {
        if(ferror(h))
            n_throw(io_error) << ei_msg_c("getc() failed.");
        return io::eof;
    }
    return res;
}
//------------------------------------------------------------------------------
void fstream::unget()
{
    this->seekg_cur(-1);
}
//------------------------------------------------------------------------------
ceof fstream::peek()
{
    n_assert(h);
    ceof c = this->get();
    if(io::eof != c)
        this->seekg_cur(-1);
    return move(c);
}
//------------------------------------------------------------------------------
void fstream::write(const char *x, streamsize n)
{
    n_assert(h);
    
    while(n > 0)
    {
        const size_t r = fwrite(x, 1, n, h);
        if(ferror(h))
            n_throw(io_error) << ei_msg_c("fwrite() failed.");
        x += r;
        n -= r;
    }
}
//------------------------------------------------------------------------------
void fstream::put(char x)
{
    n_assert(h);
    const int r = putc(x, h);
    if(r == EOF)
        n_throw(io_error) << ei_msg_c("putc() failed.");
}
//------------------------------------------------------------------------------
void fstream::flush() {
    n_assert(h);
    if(fflush(h))
        n_throw(io_error) << ei_msg_c("fflush() failed.");
}
//------------------------------------------------------------------------------
void fstream::sync() {
    this->seekg_cur(0);
}
//------------------------------------------------------------------------------
void fstream::seekg_beg(streamoff off)
{
    n_assert(h);
    if(fseek(h, off, SEEK_SET) != 0)
        n_throw(io_error) << ei_msg_c("fseek() failed.");
}
//------------------------------------------------------------------------------
void fstream::seekg_cur(streamoff off)
{
    n_assert(h);
    if(fseek(h, off, SEEK_CUR) != 0)
        n_throw(io_error) << ei_msg_c("fseek() failed.");
}
//------------------------------------------------------------------------------
void fstream::seekg_end(streamoff off)
{
    n_assert(h);
    if(fseek(h, off, SEEK_END) != 0)
        n_throw(io_error) << ei_msg_c("fseek() failed.");
}
//------------------------------------------------------------------------------
void fstream::seekp_beg(streamoff off)
{
    this->seekg_beg(off);
}
//------------------------------------------------------------------------------
void fstream::seekp_cur(streamoff off)
{
    this->seekg_cur(off);
}
//------------------------------------------------------------------------------
void fstream::seekp_end(streamoff off)
{
    this->seekg_end(off);
}
//------------------------------------------------------------------------------
streampos fstream::tellg() const
{
    n_assert(h);
    auto r = ftell(h);
    if(r == -1)
        n_throw(io_error) << ei_msg_c("ftell() failed.")
        << system::ei_errno_code();
    return r;
}
//------------------------------------------------------------------------------
streampos fstream::tellp() const
{
    return this->tellg();
}

}}} // namespaces
