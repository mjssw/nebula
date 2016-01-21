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
#include "epoll_proactor.h"

#if defined(N_NET_posix_socket) && defined(N_NET_epoll)

namespace nebula { namespace foundation { namespace net { namespace posix {
//------------------------------------------------------------------------------
void epoll_socket::connect(const endpoint &ep) noexcept
{
    n_assert(!!async_proc);
    n_assert(sock.is_open());
    
    try
    {
        const errc err = sock.connect(ep);
        if(errc::success == err)
        {
            this->on_connect_completion();
        }
        else if(errc::again == err)
        {
            data = connect_data_t{ep};
            async_proc->add(this, ::EPOLLIN | ::EPOLLOUT);
        }
        else
        {
            this->on_error(err);
        }
    }
    catch(...)
    {
        this->on_error(current_exception());
    }
}
//------------------------------------------------------------------------------
void epoll_socket::send(const char *x, size_t n) noexcept
{
    n_assert(!!async_proc);
    n_assert(sock.is_open());
    
    try
    {
        expect<size_t, errc> r = sock.send(x, n);
        if(r.valid())
        {
            const size_t n_ = r.get();
            
            if(n_ == n)
            {
                this->on_send_completion();
            }
            else
            {
                data = send_data_t{carray<const char>(x+n_, n-n_), n_};
                async_proc->add(this, ::EPOLLOUT);
            }
        }
        else
        {
            const errc err = r.error();
            if(errc::again == err)
            {
                data = send_data_t{carray<const char>(x, n), 0};
                async_proc->add(this, ::EPOLLOUT);
            }
            else
            {
                this->on_error(err);   
            }
        }
    }
    catch(...)
    {
        this->on_error(current_exception());
    }
}
//------------------------------------------------------------------------------
void epoll_socket::recv(char *x, size_t n) noexcept
{
    n_assert(!!async_proc);
    n_assert(sock.is_open());
    
    try
    {
        expect<size_t, errc> r = sock.recv(x, n);
        if(r.valid())
        {
            const size_t n = r.get();
            if(n == 0)
                this->on_error(net::errc::connection_aborted);
            else
                this->on_recv_completion(r.get());
        }
        else
        {
            const errc err = r.error();
            if(errc::again == err)
            {
                data = recv_data_t{carray<char>(x, n)};
                async_proc->add(this, ::EPOLLIN);
            }
            else
            {
                this->on_error(err);   
            }
        }
    }
    catch(...)
    {
        this->on_error(current_exception());
    }
}
//------------------------------------------------------------------------------
void epoll_socket::accept() noexcept
{
    n_assert(!!async_proc);
    n_assert(sock.is_open());
    
    try
    {
        endpoint ep;
        expect<socket, errc> r = sock.accept(ep);
        
        if(r.valid())
        {
            this->on_accept_completion(epoll_socket(async_proc, r.get()));
            return;
        }
        else
        {
            const errc err = r.error();
            if(errc::again == err)
            {
                data = accept_data_t{};
                async_proc->add(this, ::EPOLLIN);
            }
            else
            {
                this->on_error(err);
            }
        }
    }
    catch(...)
    {
        this->on_error(current_exception());
    }
}
//------------------------------------------------------------------------------
void epoll_socket::send_to(endpoint ep, const char *x, size_t n) noexcept
{
    n_assert(!!async_proc);
    n_assert(sock.is_open());
    
    try
    {
        expect<size_t, errc> r = sock.send_to(ep, x, n);
        if(r.valid())
        {
            this->on_send_to_completion(r.get());
        }
        else
        {
            const errc err = r.error();
            if(errc::again == err)
            {
                data = send_to_data_t{carray<const char>(x, n), move(ep)};
                async_proc->add(this, ::EPOLLOUT);
            }
            else
            {
                this->on_error(err);   
            }
        }
    }
    catch(...)
    {
        this->on_error(current_exception());
    }
}
//------------------------------------------------------------------------------
void epoll_socket::recv_from(char *x, size_t n) noexcept
{
    n_assert(!!async_proc);
    n_assert(sock.is_open());
    
    try
    {
        endpoint ep;
        expect<size_t, errc> r = sock.recv_from(ep, x, n);
        if(r.valid())
        {
            this->on_recv_from_completion(move(ep), r.get());
        }
        else
        {
            const errc err = r.error();
            if(errc::again == err)
            {
                data = recv_from_data_t{carray<char>(x, n)};
                async_proc->add(this, ::EPOLLIN);
            }
            else
            {
                this->on_error(err);   
            }
        }
    }
    catch(...)
    {
        this->on_error(current_exception());
    }
}
//------------------------------------------------------------------------------
void epoll_socket::finalize() noexcept
{
    n_assert(!!async_proc);
    n_assert(sock.is_open());
    
    try
    {
        switch(data.index())
        {
        case recv_data_index:
            {
                recv_data_t &dat
                    = variant_cast<recv_data_t>(data);
                
                expect<size_t, errc> r = sock.recv(
                    dat.buf.data(), dat.buf.size());
                if(r.valid())
                {
                    async_proc->remove(this);
                    const size_t n = r.get();
                    if(n == 0)
                    {
                        this->on_error(net::errc::connection_aborted);
                    }
                    else
                        this->on_recv_completion(r.get());
                }
                else
                {
                    const errc err = r.error();
                    if(errc::again == err)
                    {
                        async_proc->mod(this, EPOLLIN);
                    }
                    else
                    {
                        async_proc->remove(this);
                        this->on_error(err);
                    }
                }
            }
            break;
        case send_data_index:
            {
                send_data_t &dat
                    = variant_cast<send_data_t>(data);
                
                expect<size_t, errc> r = sock.send(
                    dat.buf.data(), dat.buf.size());
                if(r.valid())
                {
                    const size_t n = r.get();
                    dat.sent_bytes += n;
                    if(n == dat.buf.size())
                    {
                        async_proc->remove(this);
                        this->on_send_completion();
                    }
                    else
                    {
                        dat.buf.assign(dat.buf.begin()+n, dat.buf.end());
                        async_proc->mod(this, EPOLLOUT);
                    }
                }
                else
                {
                    const errc err = r.error();
                    if(errc::again == err)
                    {
                        async_proc->mod(this, EPOLLOUT);
                    }
                    else
                    {
                        async_proc->remove(this);
                        this->on_error(err);
                    }
                }
            }
            break;
        case connect_data_index:
            {
                connect_data_t &dat
                    = variant_cast<connect_data_t>(data);
                
                const errc err = sock.connect(dat.ep);
            
                if(errc::success == err)
                {
                    async_proc->remove(this);
                    this->on_connect_completion();
                }
                else if(errc::again == err)
                {
                    async_proc->mod(this, EPOLLIN | EPOLLOUT);
                }
                else
                {
                    async_proc->remove(this);
                    this->on_error(err);
                }
            }
            break;
        case accept_data_index:
            {
                expect<socket, errc> r = sock.accept();
                
                if(r.valid())
                {
                    async_proc->remove(this);
                    this->on_accept_completion(
                        epoll_socket(async_proc, r.get()));
                }
                else
                {
                    const errc err = r.error();
                    if(errc::again == err)
                    {
                        async_proc->mod(this, EPOLLIN);
                    }
                    else
                    {
                        async_proc->remove(this);
                        this->on_error(err);
                    }
                }
            }
            break;
        case recv_from_data_index:
            {
                recv_from_data_t &dat
                    = variant_cast<recv_from_data_t>(data);
                
                endpoint ep;
                expect<size_t, errc> r = sock.recv_from(
                    ep, dat.buf.data(), dat.buf.size());
                if(r.valid())
                {
                    async_proc->remove(this);
                    const size_t n = r.get();
                    if(n == 0)
                    {
                        this->on_error(net::errc::connection_aborted);
                    }
                    else
                        this->on_recv_from_completion(move(ep), r.get());
                }
                else
                {
                    const errc err = r.error();
                    if(errc::again == err)
                    {
                        async_proc->mod(this, EPOLLIN);
                    }
                    else
                    {
                        async_proc->remove(this);
                        this->on_error(err);
                    }
                }
            }
            break;
        case send_to_data_index:
            {
                send_to_data_t &dat
                    = variant_cast<send_to_data_t>(data);
                
                expect<size_t, errc> r = sock.send_to(
                    dat.ep, dat.buf.data(), dat.buf.size());
                if(r.valid())
                {
                    async_proc->remove(this);
                    this->on_send_to_completion(r.get());
                }
                else
                {
                    const errc err = r.error();
                    if(errc::again == err)
                    {
                        async_proc->mod(this, EPOLLOUT);
                    }
                    else
                    {
                        async_proc->remove(this);
                        this->on_error(err);
                    }
                }
            }
            break;
        default:
            n_throw(logic_error)
                << ei_msg_c("god dammit");
        }
    }
    catch(...)
    {
        async_proc->remove(this);
        this->on_error(current_exception());
    }
}

}}}} // namespaces

#endif
