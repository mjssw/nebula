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
#ifndef NIC_B65CA44FF35A676D_NIC
#define NIC_B65CA44FF35A676D_NIC

#include "../config.h"
#ifdef N_NET_posix_socket

#include "posix_socket.h"

namespace nebula { namespace foundation { namespace net { namespace posix {
/** @ingroup Foundation
 * @{
 */  
//------------------------------------------------------------------------------
template <class Endpoint>
class dgram_socket
{
public:
    using native_handle_type = int;
    
    dgram_socket() = delete;
    dgram_socket(dgram_socket &) = delete;
    dgram_socket(const dgram_socket &) = delete;
    dgram_socket(dgram_socket &&) = default;
    
    inline explicit dgram_socket(int hndl)
    : sock(int(hndl))
    {}
    
    template <class ... Option>
    inline dgram_socket(const protocol_type proto, const Option & ... opts)
    : sock(
        Endpoint::address_family,
        socket_category::dgram,
        proto,
        opts...)
    {}
    
    dgram_socket &operator = (dgram_socket &) = delete;
    dgram_socket &operator = (const dgram_socket &) = delete;
    dgram_socket &operator = (dgram_socket &&) = default;
    
    void swap(dgram_socket &other) noexcept
    {
        sock.swap(other.sock);
    }
    
    template <class EP>
    inline errc bind(EP &&ep)
    {
        return sock.bind(foundation::forward<EP>(ep));
    }
    inline expect<size_t, errc> send_to(
        const Endpoint &ep,
        const char *ptr,
        const size_t n)
    {
        return sock.send_to(ep, ptr, n);
    }
    inline expect<tuple<size_t, Endpoint>, errc> recv_from(
        const Endpoint &ep,
        char *ptr,
        const size_t n)
    {
        endpoint epx = ep;
        expect<size_t, errc> res = sock.recv_from(epx, ptr, n);
        if(!res.valid())
            return res.error();
        return make_tuple(res.get(), endpoint_cast<Endpoint>(epx));
    }
    
    template <class ... Options>
    inline void option(const Options & ... opts)
    {
        sock.set_option(opts ...);
    }
    template <class Option>
    inline Option option() const
    {
        return sock.get_option<Option>();
    }
    
    inline int native_handle() const noexcept
    {
        return sock.native_handle();
    }
    inline int dismiss() noexcept
    {
        return sock.dismiss();
    }
    inline void adopt(int x) noexcept
    {
        sock.adopt(x);
    }

private:
    socket sock;
};

/** @} */    

}}}} // namespaces

#endif // N_NET_posix_socket

#endif // NIC_B65CA44FF35A676D_NIC
