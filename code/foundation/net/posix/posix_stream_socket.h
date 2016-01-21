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
#ifndef NIC_DB5623ED50862543_NIC
#define NIC_DB5623ED50862543_NIC

#include "../config.h"
#ifdef N_NET_posix_socket

#include "posix_socket.h"

namespace nebula { namespace foundation { namespace net { namespace posix {
/** @ingroup Foundation
 * @{
 */  
//------------------------------------------------------------------------------
template <class Endpoint>
class stream_socket
{
public:
    using native_handle_type = int;
    
    stream_socket() = delete;
    stream_socket(stream_socket &) = delete;
    stream_socket(const stream_socket &) = delete;
    stream_socket(stream_socket &&) = default;
    
    inline explicit stream_socket(int hndl)
    : sock(int(hndl))
    {}
    
    template <class ... Option>
    inline stream_socket(const protocol_type proto, const Option & ... opts)
    : sock(
        Endpoint::address_family,
        socket_category::stream,
        proto,
        opts...)
    {}
    
    stream_socket &operator = (stream_socket &) = delete;
    stream_socket &operator = (const stream_socket &) = delete;
    stream_socket &operator = (stream_socket &&) = default;
    
    void swap(stream_socket &other) noexcept
    {
        sock.swap(other.sock);
    }
    
    template <class EP>
    inline errc connect(EP &&ep)
    {
        return sock.connect(foundation::forward<EP>(ep));
    }
    inline expect<size_t, errc> send(const char *ptr, const size_t n)
    {
        return sock.send(ptr, n);
    }
    inline expect<size_t, errc> recv(char *ptr, const size_t n)
    {
        return sock.send(ptr, n);
    }
    inline void shutdown(const channel ch)
    {
        sock.shutdown(ch);
    }
    inline Endpoint peer_endpoint() const
    {
        endpoint ep = sock.peer_endpoint();
        return endpoint_cast<Endpoint>(ep);
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

//------------------------------------------------------------------------------
template <class Endpoint>
class stream_socket_acceptor
{
public:
    using native_handle_type = int;
    
    stream_socket_acceptor() = delete;
    stream_socket_acceptor(stream_socket_acceptor &) = delete;
    stream_socket_acceptor(const stream_socket_acceptor &) = delete;
    stream_socket_acceptor(stream_socket_acceptor &&) = default;
    
    inline explicit stream_socket_acceptor(int hndl)
    : sock(int(hndl))
    {}
    
    template <class ... Option>
    inline stream_socket_acceptor(
        const protocol_type proto, const Option & ... opts)
    : sock(
        Endpoint::address_family,
        socket_category::stream,
        proto,
        opts...)
    {}
    
    stream_socket_acceptor &operator = (stream_socket_acceptor &) = delete;
    stream_socket_acceptor &operator = (
        const stream_socket_acceptor &) = delete;
    stream_socket_acceptor &operator = (stream_socket_acceptor &&) = default;
    
    void swap(stream_socket_acceptor &other) noexcept
    {
        sock.swap(other.sock);
    }
    
    template <class EP>
    inline errc bind(EP &&ep)
    {
        return sock.bind(foundation::forward<EP>(ep));
    }
    inline errc listen(const size_t backlog)
    {
        return sock.listen(backlog);
    }
    inline expect<stream_socket<Endpoint>, errc> accept()
    {
        endpoint ep;
        expect<socket, errc> r = sock.accept(ep);
        if(!r.valid())
            return r.error();
        stream_socket<Endpoint> res(int(r.get().dismiss()));
        return move(res);
    }
    inline Endpoint bound_endpoint() const
    {
        endpoint ep = sock.bound_endpoint();
        return endpoint_cast<Endpoint>(ep);
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

#endif // NIC_DB5623ED50862543_NIC
