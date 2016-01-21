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
#ifndef NIC_313C1671BC53B212_NIC
#define NIC_313C1671BC53B212_NIC

#include "../exception/exception.h"
#include "../type_traits.h"
#include "../enable_if.h"
#include "../assert.h"

namespace nebula { namespace foundation { namespace memory {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
/** The default general purpose allocator template. This allocator might hold a
 * state.
 * */
template <class T>
struct allocator
{
    using value_type = T;
    using is_always_equal = true_type;
    
    template <class X>
    struct rebind {
        using type = allocator<X>;
    };
    
    allocator() = default;
    allocator(allocator &) = default;
    allocator(const allocator &) = default;
    allocator(allocator &&) = default;
    template <class X>
    constexpr allocator(allocator<X>) {}
    
    allocator &operator = (const allocator &) = default;
    allocator &operator = (allocator &&) = default;
    
    inline T* allocate(const size_t n, const T * = nullptr) {
        n_assert(n > 0);
        
        T *ptr = static_cast<T*>(
            ::operator new [] (n * sizeof(T), std::nothrow_t()));
        if(n_expect(!ptr, false))
            throw bad_alloc();
        return ptr;
    }
    inline T* reallocate(T *ptr, const size_t old_size, const size_t new_size) {
        n_assert(new_size > 0);
        n_assert(old_size > 0);
        n_assert(ptr);
        
        return allocate(new_size);
    }
    inline void deallocate(T *ptr, const size_t n) noexcept {
        n_assert(ptr);
        n_assert(n > 0);
        
        ::operator delete [] (
            static_cast<void *>(ptr),
            std::nothrow_t());
    } 
    
    template <class ... Args, class T_ = T,
        _disable_if_c<is_pod<T_>::value 
            && (sizeof ... (Args) < 2)>* = nullptr>
    inline void construct(T *ptr, Args && ... args) {
        n_assert(ptr);
        
        ::new (ptr) T(foundation::forward<Args>(args)...);
    }
    /** @internal
     * Placement new is testing for nullptr,
     * thus generating at least two extra instructions (test, je).
     * This pretty much fucks algorithms (like copying) hard, since
     * the compiler can't do it's optimization magic.
     * Therefore we provide a specialized construct() version for
     * POD types, which simply bit-copies (POD = Trivial type).
     * For small types this boils down to a simple mov instruction.
     * Now the compiler optimization can kick in and we get a HUGE
     * performance gain (~400%).
     * libstdc++ suffers from the same issue, hence why std::vector<>
     * is terribly slow with POD types like char in contrast to 
     * std::string which avoids placement new.
     * */
    template <class T_ = T,
        _enable_if<is_pod<T_>>* = nullptr>
    inline void construct(T *ptr, const T x) noexcept {
        n_assert(ptr);
        
        *ptr = x;
    }
    template <class T_ = T,
        _enable_if<is_pod<T_>>* = nullptr>
    inline void construct(T *ptr) noexcept { n_assert(ptr); }
    
    inline void destroy(T *ptr) {
        n_assert(ptr);
        
        ptr->~T();
    }
    
    template <class X>
    inline bool operator == (const allocator<X> &) const noexcept {
        return true;
    }
    template <class X>
    inline bool operator != (const allocator<X> &) const noexcept {
        return false;
    }
};

/** @} */

}}} // namespaces

#endif // NIC_313C1671BC53B212_NIC
