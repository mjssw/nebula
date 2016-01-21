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
#ifndef NIC_C66ADB933A548AD5_NIC
#define NIC_C66ADB933A548AD5_NIC

#include "../../format.h"
#include "../defs.h"

namespace nebula { namespace foundation { namespace net { namespace ip {
/** @ingroup Foundation
 * @{
 */  
//------------------------------------------------------------------------------
class ipv4_address
{
public:
    using octet_type = uint8_t;
    using storage_type = uint32_t;
    
    constexpr static net::address_family address_family
        = net::address_family::inet; 
    
    ipv4_address() = default;
    ipv4_address(ipv4_address &) = default;
    ipv4_address(const ipv4_address &) = default;
    ipv4_address(ipv4_address &&) = default;
    
    inline ipv4_address(const storage_type x) noexcept
    : v(x)
    {}
    inline ipv4_address(const storage_type a, 
        const storage_type b, 
        const storage_type c, 
        const storage_type d) noexcept
    : v((a << (3*8)) 
        | (b << (2*8))
        | (c << (1*8))
        | d)
    {}
    inline ipv4_address(const char *str)
    {
        this->assign(str, str + foundation::strlen(str));
    }
    inline ipv4_address(const char *beg, const char *end)
    {
        this->assign(beg, end);
    }
    template <class X, class Y>
    inline ipv4_address(const basic_string<char, X, Y> &str)
    {
        this->assign(str.begin(), str.end());
    }
    template <class X>
    inline ipv4_address(basic_cstring<char, X> str)
    {
        this->assign(str.begin(), str.end());
    }
    template <class X>
    inline ipv4_address(basic_cstring<const char, X> str)
    {
        this->assign(str.begin(), str.end());
    }
    
    ipv4_address &operator = (const ipv4_address &) = default;
    ipv4_address &operator = (ipv4_address &&) = default;
    
    inline ipv4_address &assign(const storage_type a, 
        const storage_type b, 
        const storage_type c, 
        const storage_type d) noexcept
    {
        v = (a << (3*8)) 
            | (b << (2*8))
            | (c << (1*8))
            | d;
        return *this;
    }
    inline ipv4_address &assign(const char *beg, const char *end)
    {        
        return this->assign(const_cstring(beg, end));
    }
    inline ipv4_address &assign(const char *str)
    {
        return this->assign(const_cstring(str, str + foundation::strlen(str)));
    }
    template <class X, class Y>
    inline ipv4_address &assign(const basic_string<char, X, Y> &str)
    {
        return this->assign(const_cstring(str.begin(), str.end()));
    }
    template <class X>
    inline ipv4_address &assign(basic_cstring<char, X> str)
    {
        return this->assign(const_cstring(str.begin(), str.end()));
    }
    template <class X>
    inline ipv4_address &assign(const basic_cstring<const char, X> str_)
    {        
        this->assign_(const_cstring(str_.begin(), str_.end()));
        return *this;
    }
    
    inline void swap(ipv4_address &other) noexcept {
        foundation::swap(v, other.v);
    }
    
    inline void set(const size_t i, const storage_type x) {
        if(i > 3)
            n_throw(out_of_range);
        static_cast<octet_type*>(static_cast<void *>(&v))[3-i] = x;
    }
    inline octet_type get(const size_t i) const {
        if(i > 3)
            n_throw(out_of_range);
        return v >> (8*(3-i));
    }
    
    inline octet_type operator [] (const size_t i) const {
        return this->get(i);
    }
    
    inline storage_type integer() const noexcept { return v; }
    
    inline bool operator == (const ipv4_address &other) const noexcept {
        return v == other.v;
    }
    inline bool operator != (const ipv4_address &other) const noexcept {
        return v != other.v;
    }
    inline bool operator < (const ipv4_address &other) const noexcept {
        return v < other.v;
    }
    inline bool operator <= (const ipv4_address &other) const noexcept {
        return v <= other.v;
    }
    inline bool operator > (const ipv4_address &other) const noexcept {
        return v > other.v;
    }
    inline bool operator >= (const ipv4_address &other) const noexcept {
        return v >= other.v;
    }

    template <class Stream>
    inline void operator () (Stream &s, fmt::fout_tag) const
    {
        fmt::fwrite(s,
            fmt::dec(this->get(0)), '.',
            fmt::dec(this->get(1)), '.',
            fmt::dec(this->get(2)), '.',
            fmt::dec(this->get(3)));
    }
    
private:
    void assign_(const const_cstring);
    
    storage_type v;
};

/** @} */    

}}}} // namespaces

#endif // NIC_C66ADB933A548AD5_NIC
