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
#ifndef NIC_9261D1DF0545AD82_NIC
#define NIC_9261D1DF0545AD82_NIC

#include "../config.h"
#ifdef N_NET_posix_socket

#include "posix_ep_conv.h"
#include "posix_socket_option.h"
#include "../defs.h"
#include "../error.h"
#include "../../dll_interface.h"
#include "../../swap.h"
#include "../../system_error.h"
#include "../../io/defs.h"
#include "../../expect.h"

namespace nebula { namespace foundation { namespace net { namespace posix {
/** @ingroup Foundation
 * @{
 */  
//------------------------------------------------------------------------------
class n_foundation_dll socket
{
public:
    using handle = int;
    
    inline socket() noexcept
    : h(-1)
    {}
    template <class ... Options>
    inline socket(
        const net::address_family fam_,
        const net::socket_category cat_,
        const protocol_type proto_,
        const Options & ... opts)
    : h(-1)
    {
        this->open(fam_, cat_, proto_);
        this->set_option(opts ...);
    }
    /** Take ownership of a native socket handle. 
     * @throw nothing
     * */
    inline socket(const int h_) noexcept
    : h(h_)
    {}
    
    socket(socket &) = delete;
    socket(const socket &) = delete;
    /** @throw nothing */
    inline socket(socket &&other) noexcept
    : h(other.h)
    {
        other.h = -1;
    }
    
    inline ~socket() noexcept {
        this->close();
    }
    
    socket &operator = (const socket &) = delete;
    /** @throw nothing */
    inline socket &operator = (socket &&other) noexcept {
        h = other.h;
        other.h = -1;
        return *this;
    }
    
    /** @throw nothing */
    inline void swap(socket &other) noexcept {
        foundation::swap(h, other.h);
    }
    
    /** Create a new socket.
     * */
    template <class ... Options>
    inline void open(const net::address_family fam,
        const net::socket_category cat,
        const protocol_type proto,
        const Options & ... opts)
    {
        this->open_(fam, cat, proto);
        try {
            this->set_option(opts ...);
        } catch(...) {
            this->close();
            throw;
        }
    }
    /** Calls ::close().
     * @throw nothing
     * */
    void close() noexcept;
    /** Check if the socket is open.
     * @throw nothing
     * */
    inline bool is_open() const noexcept {
        return h != -1;
    }

    /** Calls ::connect().
     * @return Either success or an error code.
     * @note List of possible error codes:
     *      again
     *      timedout
     *      address_in_use
     *      connection_refused
     *      network_unreachable
     * */
    errc connect(const endpoint &);
    /** Calls ::shutdown().
     * @throw nothing
     * */
    void shutdown(const channel) noexcept;

    /** Calls ::listen().
     * @return Either success or an error code.
     * @note List of possible error codes:
     *      address_in_use
     * */
    errc listen(const size_t backlog);
    /** Calls ::bind().
     * @return Either success or an error code.
     * @note List of possible error codes:
     *      address_in_use
     * */
    errc bind(const endpoint &);    
    /** Calls ::accept().
     * @return Either a new socket or an error code.
     * @note List of possible error codes:
     *      again
     *      address_in_use
     *      connection_aborted
     *      timedout
     * */
    expect<socket, errc> accept(endpoint &);
    /** @see socket::accept(endpoint &)
     * */
    expect<socket, errc> accept();
    
    /** @returns The address the socket is bound to.
     * */
    endpoint bound_endpoint() const;
    /** @returns The address of the peer connected to the socket.
     * */
    endpoint peer_endpoint() const;
    
    /** Calls ::send().
     * @return Either the result or an error code.
     * @note List of possible error codes:
     *      again
     *      connection_reset
     * */
    expect<size_t, errc> send(const char *ptr, const size_t n);
    /** Calls ::recv().
     * @return Either the result or an error code.
     * @note List of possible error codes:
     *      again
     *      connection_reset
     * */
    expect<size_t, errc> recv(char *ptr, const size_t n);
    
    /** Calls ::send_to().
     * @return Either the result or an error code.
     * @note List of possible error codes:
     *      again
     *      connection_reset
     * */
    expect<size_t, errc> send_to(
        const endpoint &ep, 
        const char *ptr, 
        const size_t n);
    /** Calls ::recv_from().
     * @return Either the result or an error code.
     * @note List of possible error codes:
     *      again
     *      connection_reset
     * */
    expect<size_t, errc> recv_from(
        endpoint &ep,
        char *ptr, 
        const size_t n);
    
    /** @return The posix fd
     * @attention Only valid if is_open().
     * @throw nothing
     * */
    inline int native_handle() const noexcept {
        return h;
    }
    /** Give ownership of the internal socket handle.
     * After a call to this function you have to treat the instance as if 
     * move() has been called on it.
     * @return posix socket fd
     * @attention Only valid if is_open().
     * @throw nothing
     * */
    inline int dismiss() noexcept {
        const int tmp = h;
        h = -1;
        return tmp;
    }
    /** Take ownership of a native socket handle.
     * If is_open() then close() will be called first.
     * @throw nothing
     * */
    inline void adopt(int native_h) noexcept
    {
        close();
        h = native_h;
    }
    
    /** Set an arbitrary number of options.
     * */
    template <class Option0, class ... Option>
    inline void set_option(const Option0 &opt0, const Option & ... opts)
    {
        this->set_option_(opt0);
        this->set_option(opts...);
    }
    /// Dummy function doing nothing.
    inline void set_option() noexcept {}
    
    /** Query an option.
     * */
    template <class Option>
    inline Option get_option() const
    {
        Option opt;
        this->get_option_(opt);
        return opt;
    }
    
private:
    void open_(const net::address_family fam,
        const net::socket_category cat,
        const protocol_type proto);
        
    bool blocking() const;
    void blocking(const bool x);
        
    void get_opt_(int level, int name, void *ptr, size_t &len) const;
    void set_opt_(int level, int name, const void *ptr, size_t len);
    
    template <int Opt>
    inline void set_option_(const sol_socket_option<bool, Opt> x)
    {
        const int val = x.value ? 1 : 0;
        this->set_opt_(SOL_SOCKET, Opt, &val, sizeof(int));
    }
    inline void set_option_(const socket_option::blocking &x)
    {
        this->blocking(x.value);
    }
    
    template <int Opt>
    inline void get_option_(sol_socket_option<bool, Opt> &x) const
    {
        int val;
        size_t n = sizeof(val);
        this->get_opt_(SOL_SOCKET, Opt, &val, n);
        if(n != sizeof(val))
            n_throw(network_error) << ei_msg_c("Invalid option size.");
        x.value = val;
    }
    inline void get_option_(socket_option::blocking &x) const
    {
        x.value = this->blocking();
    }
    
    int h;
};

/** @} */    

}}}} // namespaces

#endif // N_NET_posix_socket

#endif // NIC_9261D1DF0545AD82_NIC
