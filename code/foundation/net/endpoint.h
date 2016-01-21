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
#ifndef NIC_2877FC6376B3BC02_NIC
#define NIC_2877FC6376B3BC02_NIC

#include "ip/ipv4_endpoint.h"
#include "ip/ipv6_endpoint.h"
#include "../variant.h"

namespace nebula { namespace foundation { namespace net {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
class endpoint
{
    using variant_t = variant<
        ip::ipv4_endpoint,
        ip::ipv6_endpoint>;
    
public:
    inline endpoint() noexcept
    : fam(net::address_family::unspecified) {}
    endpoint(endpoint &ep) = default;
    endpoint(const endpoint &ep) = default;
    endpoint(endpoint &&ep) = default;
    
    template <class X>
    inline endpoint(X &&x)
    : v(foundation::forward<X>(x)),
    fam(ctraits::value<X>::type::address_family)
    {}
    
    endpoint &operator = (endpoint &other) = default;
    endpoint &operator = (const endpoint &other) = default;
    endpoint &operator = (endpoint &&other) = default;
    
    template <class X>
    inline endpoint &operator = (X &&x) {
        v = foundation::forward<X>(x);
        fam = ctraits::value<X>::type::address_family;
        return *this;
    }
    
    inline void swap(endpoint &other) noexcept {
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
            fmt::fwrite(s, variant_cast<ip::ipv4_endpoint>(v));
            break;
        case net::address_family::inet6:
            fmt::fwrite(s, variant_cast<ip::ipv6_endpoint>(v));
            break;
        default:
            break;
        }
    }

private:
    net::address_family fam;
    variant_t v;
    
    template <class X>
    friend X &endpoint_cast(endpoint &);
    template <class X>
    friend const X &endpoint_cast(const endpoint &);
    template <class X>
    friend X endpoint_cast(endpoint &&);
};

//------------------------------------------------------------------------------
template <class X>
inline X &endpoint_cast(endpoint &x)
{
    return variant_cast<X>(x.v);
}
//------------------------------------------------------------------------------
template <class X>
inline const X &endpoint_cast(const endpoint &x)
{
    return variant_cast<X>(x.v);;
}
//------------------------------------------------------------------------------
template <class X>
inline X endpoint_cast(endpoint &&x)
{
    return variant_cast<X>(foundation::move(x.v));
}

//------------------------------------------------------------------------------
namespace net_detail {
//------------------------------------------------------------------------------
template <address_family AF>
struct dispatch_address_family {};

template <>
struct dispatch_address_family<address_family::inet> {
    using address_type = ip::ipv4_address;
    using endpoint_type = ip::ipv4_endpoint;
};

template <>
struct dispatch_address_family<address_family::inet6> {
    using address_type = ip::ipv6_address;
    using endpoint_type = ip::ipv6_endpoint;
};

} // net_detail

//------------------------------------------------------------------------------
template <address_family AF>
struct associated_address
{
    using type = typename net_detail::dispatch_address_family<
        AF>::address_type;
};
template <address_family AF>
struct associated_endpoint
{
    using type = typename net_detail::dispatch_address_family<
        AF>::endpoint_type;
};

/** @} */

}}} // namespaces

#endif // NIC_2877FC6376B3BC02_NIC
