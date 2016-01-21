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
#ifndef NIC_7A12DF9323A54C25_NIC
#define NIC_7A12DF9323A54C25_NIC

#include "../../format.h"
#include "../defs.h"

namespace nebula { namespace foundation { namespace net { namespace ip {
/** @ingroup Foundation
 * @{
 */  
//------------------------------------------------------------------------------
class ipv6_address
{
public:
    using octet_type = uint8_t;
    using hextet_type = uint16_t;
    using storage_type = array<hextet_type, 8>;
    
    constexpr static net::address_family address_family
        = net::address_family::inet6; 
    
    ipv6_address() = default;
    ipv6_address(ipv6_address &) = default;
    ipv6_address(const ipv6_address &) = default;
    ipv6_address(ipv6_address &&) = default;
    
    inline ipv6_address(
        const hextet_type x0,
        const hextet_type x1,
        const hextet_type x2,
        const hextet_type x3,
        const hextet_type x4,
        const hextet_type x5,
        const hextet_type x6,
        const hextet_type x7) noexcept
    {
        this->assign(x0,x1,x2,x3,x4,x5,x6,x7);
    }
    inline ipv6_address(const char *str)
    {
        this->assign(str, str + foundation::strlen(str));
    }
    inline ipv6_address(const char *beg, const char *end)
    {
        this->assign(beg, end);
    }
    template <class X, class Y>
    inline ipv6_address(const basic_string<char, X, Y> &str)
    {
        this->assign(str.begin(), str.end());
    }
    template <class X>
    inline ipv6_address(basic_cstring<char, X> str)
    {
        this->assign(str.begin(), str.end());
    }
    template <class X>
    inline ipv6_address(basic_cstring<const char, X> str)
    {
        this->assign(str.begin(), str.end());
    }
    
    ipv6_address &operator = (const ipv6_address &) = default;
    ipv6_address &operator = (ipv6_address &&) = default;
    
    inline void swap(ipv6_address &other) noexcept {
        foundation::swap(v, other.v);
    }
    
    inline ipv6_address &assign(
        const hextet_type x0,
        const hextet_type x1,
        const hextet_type x2,
        const hextet_type x3,
        const hextet_type x4,
        const hextet_type x5,
        const hextet_type x6,
        const hextet_type x7) noexcept
    {
        v[0] = x0;
        v[1] = x1;
        v[2] = x2;
        v[3] = x3;
        v[4] = x4;
        v[5] = x5;
        v[6] = x6;
        v[7] = x7;
        return *this;
    }
    inline ipv6_address &assign(const char *beg, const char *end)
    {        
        return this->assign(const_cstring(beg, end));
    }
    inline ipv6_address &assign(const char *str)
    {
        return this->assign(const_cstring(str, str + foundation::strlen(str)));
    }
    template <class X, class Y>
    inline ipv6_address &assign(const basic_string<char, X, Y> &str)
    {
        return this->assign(const_cstring(str.begin(), str.end()));
    }
    template <class X>
    inline ipv6_address &assign(basic_cstring<char, X> str)
    {
        return this->assign(const_cstring(str.begin(), str.end()));
    }
    template <class X>
    inline ipv6_address &assign(const basic_cstring<const char, X> str_)
    {        
        this->assign_(const_cstring(str_.begin(), str_.end()));
        return *this;
    }
    
    inline void set(const size_t i, const hextet_type x) {
        this->hextet(i, x);
    }
    inline hextet_type get(const size_t i) const {
        return this->hextet(i);
    }
    
    inline hextet_type operator [] (const size_t i) const {
        return this->hextet(i);
    }
    
    inline hextet_type hextet(const size_t i, const hextet_type x)
    {
        if(i > 7)
            n_throw(out_of_range);
        v[i] = x;
    }
    inline hextet_type hextet(const size_t i) const
    {
        if(i > 7)
            n_throw(out_of_range);
        return v[i];
    }
    inline void octet(const size_t i, const octet_type x)
    {
        if(i > 15)
            n_throw(out_of_range);
        const size_t idx = i/2;
        if((i & 1) == 0) {
            v[idx] = (v[idx] & 0xff) | (hextet_type(x) << 8);
            return;
        }
        v[idx] = (v[idx] & 0xff00) | x;
    }
    inline octet_type octet(const size_t i) const
    {
        if(i > 15)
            n_throw(out_of_range);
        const size_t idx = i/2;
        if((i & 1) == 0)
            return v[idx] >> 8;
        return v[idx] & 0xff;
    }
    
    inline bool operator == (const ipv6_address &other) const noexcept {
        return v == other.v;
    }
    inline bool operator != (const ipv6_address &other) const noexcept {
        return v != other.v;
    }
    inline bool operator < (const ipv6_address &other) const noexcept {
        return v < other.v;
    }
    inline bool operator <= (const ipv6_address &other) const noexcept {
        return v <= other.v;
    }
    inline bool operator > (const ipv6_address &other) const noexcept {
        return v > other.v;
    }
    inline bool operator >= (const ipv6_address &other) const noexcept {
        return v >= other.v;
    }
    
    template <class Stream>
    inline void operator () (Stream &s, fmt::fout_tag) const
    {        
        const tuple<size_t, size_t> skip = find_the_funky_skipper();
        
        if(foundation::get<0>(skip) == foundation::get<1>(skip)) {
            fmt::fwrite(s, fmt::hex(get(0)));
            for(size_t i = 1; i < 8; ++i) {
                fmt::fwrite(s, ':', fmt::hex(get(i)));
            }
        }
        else {
            if(foundation::get<0>(skip) == 0)
                io::put(s, ':');
            else {
                for(size_t i = 0; i < foundation::get<0>(skip); ++i)
                    fmt::fwrite(s, fmt::hex(get(i)), ':');
            }
            if(foundation::get<1>(skip) == 8)
                io::put(s, ':');
            else {
                for(size_t i = foundation::get<1>(skip); i < 8; ++i)
                    fmt::fwrite(s, ':', fmt::hex(get(i)));
            }
        }
    }
    
private:
    void assign_(const const_cstring);
    tuple<size_t, size_t> find_the_funky_skipper() const noexcept;
    
    storage_type v;
};

/** @} */    

}}}} // namespaces

#endif // NIC_7A12DF9323A54C25_NIC
