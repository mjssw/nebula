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
#ifndef NIC_AC0EAFC02F276306_NIC
#define NIC_AC0EAFC02F276306_NIC

#include "../../config.h"
#if defined(N_NET_posix_socket) && defined(N_NET_epoll)

#include "../posix_socket.h"
#include "../../../async.h"
#include "../../../ptr.h"
#include "../../../carray.h"
#include "../../../variant.h"

#include <sys/epoll.h>

namespace nebula { namespace foundation { namespace net { namespace posix {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
class epoll_proactor;

//------------------------------------------------------------------------------
class n_foundation_dll epoll_socket
{
public:
    struct callback_base : public ref_counted
    {
        callback_base() = default;
        callback_base(callback_base &) = delete;
        callback_base(const callback_base &) = delete;
        callback_base(callback_base &&) = delete;
        inline virtual ~callback_base() noexcept {}
        
        callback_base &operator = (callback_base &) = delete;
        callback_base &operator = (const callback_base &) = delete;
        callback_base &operator = (callback_base &&) = delete;
        
        inline virtual void on_send_completion()
        {
            std::terminate();
        }
        inline virtual void on_recv_completion(size_t n)
        {
            std::terminate();
        }
        inline virtual void on_connect_completion()
        {
            std::terminate();
        }
        inline virtual void on_accept_completion_(epoll_socket &&)
        {
            std::terminate();
        }
        
        inline virtual void on_recv_from_completion_(endpoint &&ep, size_t n)
        {
            std::terminate();
        }
        inline virtual void on_send_to_completion(size_t n)
        {
            std::terminate();
        }
        
        virtual void on_error(errc err) noexcept = 0;
        virtual void on_error(exception_ptr exc) noexcept = 0;   
    };

    epoll_socket() = default;
    epoll_socket(epoll_socket &) = delete;
    epoll_socket(const epoll_socket &) = delete;
    epoll_socket(epoll_socket &&) = default;
    
    template <class ProcPtr, class CB, class ... SocketOptions>
    inline epoll_socket(ProcPtr &&proc,
        CB &&cb,
        const address_family addr_fam,
        const socket_category sock_cat,
        const protocol_type proto,
        const SocketOptions & ... sock_opts)
    :   async_proc(foundation::forward<ProcPtr>(proc)),
        sock(addr_fam, sock_cat, proto, sock_opts...),
        callb(foundation::forward<CB>(cb))
    {
        sock.set_option(socket_option::blocking{false});
    }
    template <class ProcPtr, class ... SocketOptions>
    inline epoll_socket(ProcPtr &&proc,
        const address_family addr_fam,
        const socket_category sock_cat,
        const protocol_type proto,
        const SocketOptions & ... sock_opts)
    :   async_proc(foundation::forward<ProcPtr>(proc)),
        sock(addr_fam, sock_cat, proto, sock_opts...)
    {
        sock.set_option(socket_option::blocking{false});
    }
    
    inline virtual ~epoll_socket() noexcept {}
    
    epoll_socket &operator = (epoll_socket &) = delete;
    epoll_socket &operator = (const epoll_socket &) = delete;
    epoll_socket &operator = (epoll_socket &&) = default;
    
    inline void swap(epoll_socket &other) noexcept {
        foundation::swap(sock, other.sock);
        foundation::swap(async_proc, other.async_proc);
        foundation::swap(callb, other.callb);
        foundation::swap(data, other.data);
    }
    
    inline void close() noexcept {
        sock.close();
    }
    inline void shutdown(const channel ch) noexcept {
        sock.shutdown(ch);
    }
    
    inline errc bind(const endpoint &ep) {
        return sock.bind(ep);
    }
    inline errc listen(const size_t backlog) {
        return sock.listen(backlog);
    }
    void accept() noexcept;
    void connect(const endpoint &ep) noexcept;
    void send(const char *x, size_t n) noexcept;
    void recv(char *x, size_t n) noexcept;
    void send_to(endpoint ep, const char *x, size_t n) noexcept;
    void recv_from(char *x, size_t n) noexcept;
    
    inline endpoint bound_endpoint() const {
        return sock.bound_endpoint();
    }
    inline endpoint peer_endpoint() const {
        return sock.peer_endpoint();
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
    
    inline const intrusive_ptr<epoll_proactor> &proactor_() & noexcept {
        return async_proc;
    }
    inline intrusive_ptr<epoll_proactor> proactor_() && noexcept {
        return move(async_proc);
    }
    inline const intrusive_ptr<epoll_proactor> &proactor_() const & noexcept {
        return async_proc;
    }
    
    inline void callback(intrusive_ptr<callback_base> x) {
        callb = move(x);
    }
    inline intrusive_ptr<callback_base> &callback() & noexcept {
        return callb;
    }
    inline intrusive_ptr<callback_base> callback() && noexcept {
        return move(callb);
    }
    inline const intrusive_ptr<callback_base> &
    callback() const & noexcept {
        return callb;
    }
    
private:
    inline void on_send_completion() noexcept
    {
        n_assert(callb);
        try {
            callb->on_send_completion();
        }
        catch(...)
        {
            this->on_error(current_exception());
        }
    }
    inline void on_recv_completion(size_t n) noexcept
    {
        n_assert(callb);
        try {
            callb->on_recv_completion(n);
        }
        catch(...)
        {
            this->on_error(current_exception());
        }
    }
    inline void on_connect_completion() noexcept
    {
        n_assert(callb);
        try {
            callb->on_connect_completion();
        }
        catch(...)
        {
            this->on_error(current_exception());
        }
    }
    inline void on_accept_completion(epoll_socket &&epsock) noexcept
    {
        n_assert(callb);
        try {
            callb->on_accept_completion_(move(epsock));
        }
        catch(...)
        {
            this->on_error(current_exception());
        }
    }
    
    inline void on_recv_from_completion(endpoint &&ep, size_t n) noexcept
    {
        n_assert(callb);
        try {
            callb->on_recv_from_completion_(move(ep), n);
        }
        catch(...)
        {
            this->on_error(current_exception());
        }
    }
    inline void on_send_to_completion(size_t n) noexcept
    {
        n_assert(callb);
        try {
            callb->on_send_to_completion(n);
        }
        catch(...)
        {
            this->on_error(current_exception());
        }
    }
    
    inline void on_error(errc err) noexcept
    {
        n_assert(callb);
        callb->on_error(err);
    }
    void on_error(exception_ptr exc) noexcept
    {
        n_assert(callb);
        callb->on_error(foundation::move(exc));
    }
    
    inline epoll_socket(intrusive_ptr<epoll_proactor> ap, socket &&s)
    : async_proc(move(ap)), sock(move(s))
    {}
    
    void finalize() noexcept;
    
    inline void reset(intrusive_ptr<epoll_proactor> ap, socket &&s)
    {
        n_assert(!async_proc);
        n_assert(!sock.is_open());
        
        async_proc = move(ap);
        sock = move(s);
        sock.set_option(socket_option::blocking{false});
    }
    
    intrusive_ptr<epoll_proactor> async_proc;
    socket sock;
    intrusive_ptr<callback_base> callb;
    
    struct recv_data_t {
        carray<char> buf;
    };
    struct send_data_t {
        carray<const char> buf;
        size_t sent_bytes;
    };
    struct connect_data_t {
        endpoint ep;
    };
    struct accept_data_t {
        // empty
    };
    
    struct recv_from_data_t {
        carray<char> buf;
    };
    struct send_to_data_t {
        carray<const char> buf;
        endpoint ep;
    };
    
    variant<
        recv_data_t,
        send_data_t,
        connect_data_t,
        accept_data_t,
        recv_from_data_t,
        send_to_data_t> data;
    
    constexpr static size_t recv_data_index = 0;
    constexpr static size_t send_data_index = 1;
    constexpr static size_t connect_data_index = 2;
    constexpr static size_t accept_data_index = 3;
    constexpr static size_t recv_from_data_index = 4;
    constexpr static size_t send_to_data_index = 5;
    
    friend class epoll_proactor;
};

/** @} */    

}}}} // namespaces

#endif

#endif // NIC_AC0EAFC02F276306_NIC
