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
#ifndef NIC_16F981C014644E4B_NIC
#define NIC_16F981C014644E4B_NIC

#include "posix_async_service.h"
#include "../endpoint.h"

namespace nebula { namespace foundation { namespace net { namespace posix {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class Endpoint, class AsyncServ, class AsyncSocket>
class async_dgram_socket
{
public:
    using endpoint_type = Endpoint;
    
    struct callback_base : public AsyncSocket::callback_base
    {
        virtual void on_recv_from_completion(Endpoint &&ep, size_t n) = 0;
        
    private:
        inline void on_recv_from_completion_(endpoint &&ep, size_t n)
        {
            this->on_recv_from_completion(endpoint_cast<Endpoint>(move(ep)), n);
        }
        using AsyncSocket::callback_base::on_accept_completion_;
        using AsyncSocket::callback_base::on_connect_completion;
        using AsyncSocket::callback_base::on_recv_completion;
        using AsyncSocket::callback_base::on_send_completion;
    };
    
    async_dgram_socket() = delete;
    async_dgram_socket(async_dgram_socket &) = delete;
    async_dgram_socket(const async_dgram_socket &) = delete;
    async_dgram_socket(async_dgram_socket &&) = default;
    
    template <class AsyncServ_, class CB, class ... SocketOptions>
    inline async_dgram_socket(AsyncServ_ &&x,
        CB &&cb,
        protocol_type proto,
        const SocketOptions & ... opts)
    : async_sock(
        foundation::forward<AsyncServ_>(x).backend_(),
        foundation::forward<CB>(cb),
        Endpoint::address_family,
        socket_category::dgram,
        proto,
        opts...)
    {}
    template <class AsyncServ_, class ... SocketOptions>
    inline async_dgram_socket(AsyncServ_ &&x,
        protocol_type proto,
        const SocketOptions & ... opts)
    : async_sock(
        foundation::forward<AsyncServ_>(x).backend_(),
        Endpoint::address_family,
        socket_category::dgram,
        proto,
        opts...)
    {}

    async_dgram_socket &operator = (async_dgram_socket &) = delete;
    async_dgram_socket &operator = (const async_dgram_socket &) = delete;
    async_dgram_socket &operator = (async_dgram_socket &&) = default;
    
    inline void swap(async_dgram_socket &other) noexcept {
        foundation::swap(async_sock, other.async_sock);
    }
    
    inline void close() noexcept {
        async_sock.close();
    }
    
    template <class Endpoint_>
    inline errc bind(Endpoint_ &&ep) {
        return async_sock.bind(foundation::forward<Endpoint_>(ep));
    }
    inline Endpoint bound_endpoint() const {
        return endpoint_cast<Endpoint>(async_sock.bound_endpoint());
    }
    template <class Endpoint_>
    inline void send_to(
        Endpoint_ &&ep, const char *ptr, size_t n) noexcept
    {
        async_sock.send_to(foundation::forward<Endpoint_>(ep), ptr, n);
    }
    inline void recv_from(char *x, size_t n) noexcept {
        async_sock.recv_from(x, n);
    }
    
    inline AsyncServ async_service() & {
        return AsyncServ(async_sock.proactor_());
    }
    inline AsyncServ async_service() && noexcept {
        return AsyncServ(move(async_sock).proactor_());
    }
    inline AsyncServ async_service() const & {
        return AsyncServ(async_sock.proactor_());
    }
    
    inline void callback(intrusive_ptr<callback_base> &x) {
        async_sock.callback(x);
    }
    inline void callback(intrusive_ptr<callback_base> &&x) {
        async_sock.callback(move(x));
    }
    inline intrusive_ptr<callback_base> callback() & {
        return async_sock.callback();
    }
    inline intrusive_ptr<callback_base> callback() && {
        return move(async_sock).callback();
    }
    
private:
    AsyncSocket async_sock;
};

/** @} */    

}}}} // namespaces

#endif // NIC_16F981C014644E4B_NIC
