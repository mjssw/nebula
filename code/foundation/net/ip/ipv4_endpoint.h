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
#ifndef NIC_5D8ADB933A2E6D54_NIC
#define NIC_5D8ADB933A2E6D54_NIC

#include "ipv4_address.h"

namespace nebula { namespace foundation { namespace net { namespace ip {
/** @ingroup Foundation
 * @{
 */  
//------------------------------------------------------------------------------
class ipv4_endpoint
{
    using port_type = uint16_t;
    
public:
    constexpr static net::address_family address_family
        = net::address_family::inet; 
    
    inline ipv4_endpoint(const ipv4_address ip, const port_type p) noexcept
    : addr(ip), prt(p)
    {}
    
    ipv4_endpoint() = default;
    ipv4_endpoint(ipv4_endpoint &) = default;
    ipv4_endpoint(const ipv4_endpoint &) = default;
    ipv4_endpoint(ipv4_endpoint &&) = default;
    
    ipv4_endpoint &operator = (const ipv4_endpoint &) = default;
    ipv4_endpoint &operator = (ipv4_endpoint &&) = default;
    
    inline void swap(ipv4_endpoint &other) noexcept {
        addr.swap(other.addr);
        foundation::swap(prt, other.prt);
    }
    
    inline ipv4_endpoint &assign(
        const ipv4_address ip, const port_type p) noexcept
    {
        addr = ip;
        prt = p;
        return *this;
    }
    
    inline const ipv4_address &address() const noexcept {
        return addr;
    }
    inline void address(const ipv4_address x) noexcept {
        addr = x;
    }
    
    inline port_type port() const noexcept {
        return prt;
    }
    inline void port(const port_type x) noexcept {
        prt = x;
    }
    
    inline bool operator == (const ipv4_endpoint &other) const noexcept {
        return addr == other.addr && prt == other.prt;
    }
    inline bool operator != (const ipv4_endpoint &other) const noexcept {
        return addr != other.addr || prt != other.prt;
    }
    
    template <class Stream>
    inline void operator () (Stream &s, fmt::fout_tag) const
    {
        fmt::fwrite(s, addr, ':', prt);
    }
    
private:
    ipv4_address addr;
    port_type prt;
};

/** @} */    

}}}} // namespaces

#endif // NIC_5D8ADB933A2E6D54_NIC
