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
#ifndef NIC_B84837E3FAEE0A24_NIC
#define NIC_B84837E3FAEE0A24_NIC

#include "ip/ipv4_address.h"
#include "ip/ipv6_address.h"
#include "../variant.h"

namespace nebula { namespace foundation { namespace net {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
class address
{
    using variant_t = variant<
        ip::ipv4_address,
        ip::ipv6_address>;
    
public:
    inline address() noexcept
    : fam(net::address_family::unspecified) {}
    address(address &ep) = default;
    address(const address &ep) = default;
    address(address &&ep) = default;
    
    template <class X>
    inline address(X &&x)
    : v(foundation::forward<X>(x)),
    fam(ctraits::value<X>::type::address_family)
    {}
    
    address &operator = (address &other) = default;
    address &operator = (const address &other) = default;
    address &operator = (address &&other) = default;
    
    template <class X>
    inline address &operator = (X &&x) {
        v = foundation::forward<X>(x);
        fam = ctraits::value<X>::type::address_family;
        return *this;
    }
    
    inline void swap(address &other) noexcept {
        v.swap(other.v);
        foundation::swap(fam, other.fam);
    }
    
    inline bool empty() const noexcept {
        return v.empty();
    }
    
    inline net::address_family address_family() const noexcept {
        return fam;
    }
    
    inline void clear() noexcept {
        v.clear();
        fam = net::address_family::unspecified;
    }
    
    template <class Stream>
    inline void operator () (Stream &s, fmt::fout_tag) const
    {
        switch(fam)
        {
        case net::address_family::inet:
            fmt::fwrite(s, variant_cast<ip::ipv4_address>(v));
            break;
        case net::address_family::inet6:
            fmt::fwrite(s, variant_cast<ip::ipv6_address>(v));
            break;
        default:
            break;
        }
    }

private:
    net::address_family fam;
    variant_t v;
    
    template <class X>
    friend X &address_cast(address &);
    template <class X>
    friend const X &address_cast(const address &);
    template <class X>
    friend X address_cast(address &&);
};

//------------------------------------------------------------------------------
template <class X>
inline X &address_cast(address &x)
{
    return variant_cast<X>(x.v);
}
//------------------------------------------------------------------------------
template <class X>
inline const X &address_cast(const address &x)
{
    return variant_cast<X>(x.v);;
}
//------------------------------------------------------------------------------
template <class X>
inline X address_cast(address &&x)
{
    return variant_cast<X>(foundation::move(x.v));
}

/** @} */

}}} // namespaces

#endif // NIC_B84837E3FAEE0A24_NIC
