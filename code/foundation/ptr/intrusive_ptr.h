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
#ifndef NIC_5E6EB16BACDC4E01_NIC
#define NIC_5E6EB16BACDC4E01_NIC

#include "../swap.h"
#include "../async/atomic.h"
#include "../assert.h"
#include "../dll_interface.h"
#include "../defs.h"

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{ 
 * */
//------------------------------------------------------------------------------
template <class T>
struct intrusive_ptr_acquire_impl
{
    inline static void apply(T *x) {
        x->intrusive_ptr_acquire(x);
    }
};
//------------------------------------------------------------------------------
template <class T>
inline void intrusive_ptr_acquire(T *x) {
    intrusive_ptr_acquire_impl<T>::apply(x);
}
//------------------------------------------------------------------------------
template <class T>
struct intrusive_ptr_release_impl
{
    inline static void apply(T *x) {
        x->intrusive_ptr_release(x);
    }
};
//------------------------------------------------------------------------------
template <class T>
inline void intrusive_ptr_release(T *x) {
    intrusive_ptr_release_impl<T>::apply(x);
}

//------------------------------------------------------------------------------
/** Simple intrusive smart pointer implementation.
 * @attention intrusive_ptr_release() must not throw.
 * @attention Destructor ~T() must not throw.
 * */
template <class T>
class intrusive_ptr
{
public:
    inline constexpr intrusive_ptr() noexcept
    : p(nullptr)
    {}
    
    inline constexpr intrusive_ptr(std::nullptr_t) noexcept
    : p(nullptr)
    {}
    
    intrusive_ptr(intrusive_ptr &x)
    : p(x.p)
    {
        if(p)
            foundation::intrusive_ptr_acquire(p);
    }
    intrusive_ptr(const intrusive_ptr &x)
    : p(x.p)
    {
        if(p)
            foundation::intrusive_ptr_acquire(p);
    }
    intrusive_ptr(intrusive_ptr &&x) noexcept
    : p(x.p)
    {
        x.p = nullptr;
    }
    template <class S>
    intrusive_ptr(intrusive_ptr<S> &x)
    : p(static_cast<T*>(x.p))
    {
        if(p)
            foundation::intrusive_ptr_acquire(p);
    }
    template <class S>
    intrusive_ptr(const intrusive_ptr<S> &x)
    : p(static_cast<T*>(x.p))
    {
        if(p)
            foundation::intrusive_ptr_acquire(p);
    }
    template <class S>
    intrusive_ptr(intrusive_ptr<S> &&x) noexcept
    : p(static_cast<T*>(x.p))
    {
        x.p = nullptr;
    }
    
    template <class S>
    inline intrusive_ptr(S *p_) noexcept
    : p(static_cast<T*>(p_))
    {
        if(p)
            foundation::intrusive_ptr_acquire(p);
    }

    inline ~intrusive_ptr()
    {
        reset();
    }
    
    inline intrusive_ptr &operator = (intrusive_ptr &x) {
        reset(x.p);
        return *this;
    }
    inline intrusive_ptr &operator = (const intrusive_ptr &x) {
        reset(x.p);
        return *this;
    }
    inline intrusive_ptr &operator = (intrusive_ptr &&x) noexcept {
        if(p)
            this->release_(p);
        p = x.p;
        x.p = nullptr;
        return *this;
    }
    
    template <class S>
    inline intrusive_ptr &operator = (intrusive_ptr<S> &x) {
        reset(static_cast<T*>(x.p));
        return *this;
    }
    template <class S>
    inline intrusive_ptr &operator = (const intrusive_ptr<S> &x) {
        reset(static_cast<T*>(x.p));
        return *this;
    }
    template <class S>
    inline intrusive_ptr &operator = (intrusive_ptr<S> &&x) noexcept {
        if(p)
            this->release_(p);
        p = static_cast<T*>(x.p);
        x.p = nullptr;
        return *this;
    }
    
    template <class S>
    inline intrusive_ptr &operator = (S *x) {
        reset(static_cast<T*>(x));
        return *this;
    }
    
    inline intrusive_ptr &operator = (std::nullptr_t) {
        reset();
        return *this;
    }
    
    inline T *operator -> () const noexcept {
        n_assert(p);
        return p;
    }
    inline T &operator * () const noexcept {
        n_assert(p);
        return *p;
    }
    
    inline void reset(T *x) {
        if(x)
            intrusive_ptr_acquire(x);
        if(p)
            this->release_(p);
        p = x;
    }
    inline void reset() noexcept {
        if(p) {
            this->release_(p);
            p = nullptr;
        }
    }
    
    inline T &ref() const noexcept {
        n_assert(p);
        return *p;
    }
    inline T *ptr() const noexcept {
        return p;
    }
    
    inline T *dismiss() noexcept {
        T *res = p;
        p = nullptr;
        return res;
    }
    
    inline void swap(intrusive_ptr &x) noexcept {
        foundation::swap(p, x.p);
    }
    
    inline constexpr operator bool() const noexcept {
        return p != nullptr;
    }
    
    template <class S>
    inline constexpr bool operator == (const intrusive_ptr<S> &x) const noexcept
    {
        return p == x.p;
    }
    template <class S>
    inline constexpr bool operator != (const intrusive_ptr<S> &x) const noexcept
    {
        return p != x.p;
    }
    template <class S>
    inline constexpr bool operator < (const intrusive_ptr<S> &x) const noexcept
    {
        return p < x.p;
    }
    template <class S>
    inline constexpr bool operator <= (const intrusive_ptr<S> &x) const noexcept
    {
        return p <= x.p;
    }
    template <class S>
    inline constexpr bool operator > (const intrusive_ptr<S> &x) const noexcept
    {
        return p > x.p;
    }
    template <class S>
    inline constexpr bool operator >= (const intrusive_ptr<S> &x) const noexcept
    {
        return p >= x.p;
    }
    
    template <class S>
    inline constexpr bool operator == (const S *x) const noexcept {
        return p == x;
    }
    template <class S>
    inline constexpr bool operator != (const S *x) const noexcept {
        return p != x;
    }
    template <class S>
    inline constexpr bool operator < (const S *x) const noexcept {
        return p < x;
    }
    template <class S>
    inline constexpr bool operator <= (const S *x) const noexcept {
        return p <= x;
    }
    template <class S>
    inline constexpr bool operator > (const S *x) const noexcept {
        return p > x;
    }
    template <class S>
    inline constexpr bool operator >= (const S *x) const noexcept {
        return p >= x;
    }
    
private:
    inline void release_(T *p) noexcept
    {
        foundation::intrusive_ptr_release(p);
    }
    
    T *p;
    
    template <class S>
    friend class intrusive_ptr;
};

//------------------------------------------------------------------------------
/** This class provides reference counting in a thread safe manner. */
class n_foundation_dll ref_counted
{
public:
    inline ref_counted() noexcept : _rcount(0) {}
    inline ref_counted(ref_counted &) noexcept : _rcount(0) {}
    inline ref_counted(const ref_counted &) noexcept : _rcount(0) {}
    inline ref_counted(ref_counted &&) noexcept : _rcount(0) {}
    inline virtual ~ref_counted() noexcept { n_assert(_rcount == 0); }
    
    ref_counted &operator = (const ref_counted &) noexcept {
        return *this;
    }
    ref_counted &operator = (ref_counted &&) noexcept {
        return *this;
    }

    template <class T>
    inline void intrusive_ptr_acquire(T *) noexcept {
        async::atomic_fetch_add(&_rcount, size_t(1));
    }
    template <class T>
    inline void intrusive_ptr_release(T *ptr) noexcept {
        if(async::atomic_fetch_sub(&_rcount, size_t(1)) == 1)
            delete ptr;
    }

private:
    async::atomic_size_t _rcount;
};
//------------------------------------------------------------------------------
/** Single threaded version of ref_counted. */
class n_foundation_dll ref_counted_st
{
public:
    inline ref_counted_st() noexcept : _rcount(0) {}
    inline ref_counted_st(ref_counted_st &) noexcept : _rcount(0) {}
    inline ref_counted_st(const ref_counted_st &) noexcept : _rcount(0) {}
    inline ref_counted_st(ref_counted_st &&) noexcept : _rcount(0) {}
    inline virtual ~ref_counted_st() noexcept { n_assert(_rcount == 0); }
    
    ref_counted_st &operator = (const ref_counted_st &) noexcept {
        return *this;
    }
    ref_counted_st &operator = (ref_counted_st &&) noexcept {
        return *this;
    }
    
    template <class T>
    inline void intrusive_ptr_acquire(T *) noexcept {
        _rcount++;
    }
    template <class T>
    inline void intrusive_ptr_release(T *ptr) noexcept {
        if(--_rcount == 0)
            delete ptr;
    }

private:
    size_t _rcount;
};

/** @} */

}} // namespaces

#endif // NIC_5E6EB16BACDC4E01_NIC
