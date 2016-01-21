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
#ifndef NIC_7E2EB3440F7AE0AE_NIC
#define NIC_7E2EB3440F7AE0AE_NIC

#include "posix_async_service.h"
#include "../endpoint.h"

namespace nebula { namespace foundation { namespace net { namespace posix {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class Endpoint, class AsyncServ, class AsyncSocket>
class async_stream_socket
{
public:
    using endpoint_type = Endpoint;
    
    struct callback_base : public AsyncSocket::callback_base
    {
    private:
        using AsyncSocket::callback_base::on_accept_completion_;
        using AsyncSocket::callback_base::on_recv_from_completion_;
        using AsyncSocket::callback_base::on_send_to_completion;
    };

    async_stream_socket() = delete;
    async_stream_socket(async_stream_socket &) = delete;
    async_stream_socket(const async_stream_socket &) = delete;
    async_stream_socket(async_stream_socket &&) = default;
    
    template <class AsyncServ_, class CB, class ... SocketOptions>
    inline async_stream_socket(AsyncServ_ &&x,
        CB &&cb,
        protocol_type proto,
        const SocketOptions & ... opts)
    : async_sock(
        foundation::forward<AsyncServ_>(x).backend_(),
        foundation::forward<CB>(cb),
        Endpoint::address_family,
        socket_category::stream,
        proto,
        opts...)
    {}
    template <class AsyncServ_, class ... SocketOptions>
    inline async_stream_socket(AsyncServ_ &&x,
        protocol_type proto,
        const SocketOptions & ... opts)
    : async_sock(
        foundation::forward<AsyncServ_>(x).backend_(),
        Endpoint::address_family,
        socket_category::stream,
        proto,
        opts...)
    {}
    inline async_stream_socket(AsyncSocket &&x) noexcept
    : async_sock(move(x))
    {}

    async_stream_socket &operator = (async_stream_socket &) = delete;
    async_stream_socket &operator = (const async_stream_socket &) = delete;
    async_stream_socket &operator = (async_stream_socket &&) = default;
    
    inline void swap(async_stream_socket &other) noexcept {
        foundation::swap(async_sock, other.async_sock);
    }
    
    inline void close() noexcept {
        async_sock.close();
    }
    inline void shutdown(const channel ch) noexcept {
        async_sock.shutdown(ch);
    }
    
    template <class Endpoint_>
    inline void connect(Endpoint_ &&ep) noexcept {
        async_sock.connect(foundation::forward<Endpoint_>(ep));
    }
    inline Endpoint peer_endpoint() const {
        return endpoint_cast<Endpoint>(async_sock.peer_endpoint());
    }
    
    inline void send(const char *x, size_t n) noexcept {
        async_sock.send(x, n);
    }
    inline void recv(char *x, size_t n) noexcept {
        async_sock.recv(x, n);
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

//------------------------------------------------------------------------------
template <class Endpoint, class AsyncServ, class AsyncSocket>
class async_stream_socket_acceptor
{
    using client_type = async_stream_socket<Endpoint, AsyncServ, AsyncSocket>;
    
public:
    using endpoint_type = Endpoint;

    struct callback_base : public AsyncSocket::callback_base
    {
        virtual void on_accept_completion(client_type &&sock) = 0;
        
    private:
        inline void on_accept_completion_(AsyncSocket &&async_sock) {
            this->on_accept_completion(client_type(async_sock));
        }

        using AsyncSocket::callback_base::on_connect_completion;
        using AsyncSocket::callback_base::on_send_completion;
        using AsyncSocket::callback_base::on_recv_completion;
        using AsyncSocket::callback_base::on_recv_from_completion_;
        using AsyncSocket::callback_base::on_send_to_completion;
    };

    async_stream_socket_acceptor() = delete;
    async_stream_socket_acceptor(async_stream_socket_acceptor &) = delete;
    async_stream_socket_acceptor(
        const async_stream_socket_acceptor &) = delete;
    async_stream_socket_acceptor(async_stream_socket_acceptor &&) = default;
    
    template <class AsyncServ_, class CB, class ... SocketOptions>
    inline async_stream_socket_acceptor(AsyncServ_ &&x,
        CB &&cb,
        protocol_type proto,
        const SocketOptions & ... opts)
    : async_sock(
        foundation::forward<AsyncServ_>(x).backend_(),
        foundation::forward<CB>(cb),
        Endpoint::address_family,
        socket_category::stream,
        proto,
        opts...)
    {}
    template <class AsyncServ_, class ... SocketOptions>
    inline async_stream_socket_acceptor(AsyncServ_ &&x,
        protocol_type proto,
        const SocketOptions & ... opts)
    : async_sock(
        foundation::forward<AsyncServ_>(x).backend_(),
        Endpoint::address_family,
        socket_category::stream,
        proto,
        opts...)
    {}

    async_stream_socket_acceptor &operator = (
        async_stream_socket_acceptor &) = delete;
    async_stream_socket_acceptor &operator = (
        const async_stream_socket_acceptor &) = delete;
    async_stream_socket_acceptor &operator = (
        async_stream_socket_acceptor &&) = default;
    
    inline void swap(async_stream_socket_acceptor &other) noexcept {
        foundation::swap(async_sock, other.async_sock);
    }
    
    inline void close() noexcept {
        async_sock.close();
    }
    
    inline errc listen(const size_t backlog) {
        return async_sock.listen(backlog);
    }
    template <class Endpoint_>
    inline errc bind(Endpoint_ &&ep) {
        return async_sock.bind(foundation::forward<Endpoint_>(ep));
    }
    inline Endpoint bound_endpoint() const {
        return endpoint_cast<Endpoint>(async_sock.bound_endpoint());
    }
    inline void accept() noexcept {
        async_sock.accept();
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

#endif // NIC_7E2EB3440F7AE0AE_NIC
