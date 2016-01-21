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
#ifndef NIC_309F48068301E05B_NIC
#define NIC_309F48068301E05B_NIC

#include "dynamic_array.h"
#include "bitset.h"

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <
    size_t BitCount,
    class T = N_BITSET_DEFAULT_TYPE,
    class Allocator = memory::allocator<T>>
class dynamic_bitset
{
    n_static_assert(is_unsigned<T>::value,
        "T must be an unsigned integer.");
    n_static_assert(
        n_arg(is_same<T, memory::_allocator_value<Allocator>>::value),
        "Allocator's value type must be the same as T.");

private:
    inline static constexpr size_t storage_type_bits() noexcept {
        return sizeof(T) * n_char_bit;
    }
    inline static constexpr size_t storage_size() noexcept {
        return BitCount % storage_type_bits() == 0
            ? BitCount / storage_type_bits()
            : BitCount / storage_type_bits() + 1;
    }
    using storage_type = T;
    struct make_inverse_tag {};

public:
    using allocator_type = Allocator;
    using size_type = size_t;
    using value_type = bool;
    using difference_type = ptrdiff_t;

private:
    class reference_impl
    {
    private:
        inline reference_impl(storage_type &blk, const storage_type bt) noexcept
        : _block(blk), _bit(bt)
        {}

    public:
        inline reference_impl &operator |= (const bool x) noexcept {
            if(x)
                _block |= _bit;
            return *this;
        }
        inline reference_impl &operator &= (const bool x) noexcept {
            if(!x)
                _block &= ~_bit;
            return *this;
        }
        inline reference_impl &operator ^= (const bool x) noexcept {
            if(x)
                _block ^= _bit;
            return *this;
        }
        
        inline operator bool () const noexcept {
            return (_block & _bit) != 0;
        }
        inline bool operator ~ () const noexcept {
            return !static_cast<bool>(*this);
        }

        inline reference_impl &operator = (const bool x) noexcept {
            if(x)
                *this |= x;
            else
                *this &= x;
            return *this;
        }
        inline reference_impl &operator = (const reference_impl &x) noexcept {
            return *this = static_cast<bool>(x);
        }

        void operator & () = delete;

    private:
        storage_type &_block;
        storage_type _bit;
        
        friend class dynamic_bitset;
    };

public:
    typedef reference_impl reference;
    typedef const bool const_reference;

public:
    inline dynamic_bitset() noexcept
    {
        v.back() = storage_type();
    }
    dynamic_bitset(dynamic_bitset &) = default;
    dynamic_bitset(const dynamic_bitset &) = default;
    dynamic_bitset(dynamic_bitset &&) = default;
    
    template <class Alloc>
    inline dynamic_bitset(const dynamic_bitset &other, Alloc &&alc)
    : v(other.v, foundation::forward<Alloc>(alc))
    {}
    template <class Alloc>
    inline dynamic_bitset(dynamic_bitset &&other, Alloc &&alc)
    : v(move(other.v), foundation::forward<Alloc>(alc))
    {}
    
    inline dynamic_bitset(const storage_type x)
    {
        v.front() = x;
        foundation::iterator::fill(v.begin()+1, v.end(), storage_type());
    }
    template <class Alloc>
    inline dynamic_bitset(const storage_type x, Alloc &&alc)
    : v(foundation::forward<Alloc>(alc))
    {
        v.front() = x;
        foundation::iterator::fill(v.begin()+1, v.end(), storage_type());
    }
    
    inline dynamic_bitset(const allocator_type &alc)
    : v(alc)
    {
        v.back() = storage_type();
    }
    inline dynamic_bitset(allocator_type &&alc)
    : v(foundation::move(alc))
    {
        v.back() = storage_type();
    }
    
    dynamic_bitset &operator = (const dynamic_bitset &) = default;
    dynamic_bitset &operator = (dynamic_bitset &&) = default;
    
    inline void swap(dynamic_bitset &other) noexcept
    {
        v.swap(other.v);
    }
    
    inline size_t size() const noexcept {
        return BitCount;
    }
    inline bool empty() const noexcept {
        return this->size() == 0;
    }

    inline dynamic_bitset &set(const size_t n) noexcept
    {
        const size_t i = n / storage_type_bits();
        const storage_type bit = static_cast<storage_type>(1)
            << (n % storage_type_bits());
        
        v[i] |= bit;

        return *this;
    }
    inline dynamic_bitset &set() noexcept
    {
        range::fill(v, static_cast<storage_type>(1));
        v.back() = bitset_detail::mask_n<BitCount>(v.back());
        return *this;
    }
    
    inline dynamic_bitset &reset() noexcept
    {
        range::fill(v, storage_type());
        return *this;
    }
    inline dynamic_bitset &reset(const size_t n) noexcept
    {
        const size_t i = n / storage_type_bits();
        const storage_type bit = static_cast<storage_type>(1)
            << (n % storage_type_bits());

        v[i] &= ~bit;

        return *this;
    }

    inline dynamic_bitset &flip(const size_t n) noexcept
    {
        const size_t i = n / storage_type_bits();
        const storage_type bit = static_cast<storage_type>(1)
            << (n % storage_type_bits());

        v[i] ^= bit;

        return *this;
    }
    inline dynamic_bitset &flip() noexcept
    {
        const storage_type _a = math::maximum<storage_type>();
        for(size_t i = 0; i < storage_size(); ++i)
            v[i] ^= _a;
        v.back() = bitset_detail::mask_n<BitCount>(v.back());
        return *this;
    }

    inline bool all() const noexcept
    {   
        const storage_type _a = math::maximum<storage_type>();
        for(size_t i = 0; i < storage_size(); ++i)
            if(!(v[i] & _a))
                return false;
        return true;
    }
    inline bool any() const noexcept
    {
        const storage_type _a = math::maximum<storage_type>();
        for(size_t i = 0; i < storage_size(); ++i)
            if(v[i] | _a)
                return true;
        return false;
    }
    inline bool none() const noexcept
    {
        const storage_type _a = math::maximum<storage_type>();
        for(size_t i = 0; i < storage_size(); ++i)
            if(v[i] | _a)
                return false;
        return true;
    }

    inline reference operator [] (const size_t n) noexcept
    {
        const size_t i = n / storage_type_bits();
        return reference(v[i],
            static_cast<storage_type>(1) << (n % storage_type_bits()));
    }
    inline bool operator [] (const size_t n) const noexcept
    {
        const size_t i = n / storage_type_bits();
        return v[i] & ((static_cast<storage_type>(1)
            << (n % storage_type_bits())));
    }
    
    inline bool test(const size_t n) const noexcept
    {
        if(n >= BitCount)
            n_throw(out_of_range);
        const size_t i = n / storage_type_bits();
        return v[i] & ((static_cast<storage_type>(1)
            << (n % storage_type_bits())));
    }

    inline dynamic_bitset operator ~ () &
    {
        return dynamic_bitset(*this, make_inverse_tag());
    }
    inline dynamic_bitset operator ~ () &&
    {
        for(size_t i = 0; i < storage_size(); ++i)
            v[i] = ~v[i];
        v.back() = bitset_detail::mask_n<BitCount>(v.back());
        return move(*this);
    }
    inline dynamic_bitset operator ~ () const &
    {
        return dynamic_bitset(*this, make_inverse_tag());
    }
    
    inline dynamic_bitset &operator &= (const dynamic_bitset &rhs) noexcept
    {
        for(size_t i = 0; i < storage_size(); ++i)
            v[i] &= rhs.v[i];

        return *this;
    }
    inline friend dynamic_bitset operator & (
        const dynamic_bitset &lhs, const dynamic_bitset &rhs)
    {
        dynamic_bitset res(lhs.size(), lhs.get_allocator());
        for(size_t i = 0; i < res.storage_size(); ++i)
            res.v[i] = lhs.v[i] & rhs.v[i];        
        return res;
    }
    inline friend dynamic_bitset operator & (
        dynamic_bitset &&lhs, const dynamic_bitset &rhs) noexcept
    {
        lhs &= rhs;       
        return move(lhs);
    }
    inline friend dynamic_bitset operator & (
        const dynamic_bitset &lhs, dynamic_bitset &&rhs) noexcept
    {
        rhs &= lhs;
        return move(rhs);
    }
    inline friend dynamic_bitset operator & (
        dynamic_bitset &&lhs, dynamic_bitset &&rhs) noexcept
    {
        lhs &= rhs;       
        return move(lhs);
    }
    
    inline dynamic_bitset &operator |= (const dynamic_bitset &rhs) noexcept
    {
        for(size_t i = 0; i < storage_size(); ++i)
            v[i] |= rhs.v[i];

        return *this;
    }
    inline friend dynamic_bitset operator | (
        const dynamic_bitset &lhs, const dynamic_bitset &rhs)
    {
        dynamic_bitset res(lhs.size(), lhs.get_allocator());
        for(size_t i = 0; i < res.storage_size(); ++i)
            res.v[i] = lhs.v[i] | rhs.v[i];        
        return res;
    }
    inline friend dynamic_bitset operator | (
        dynamic_bitset &&lhs, const dynamic_bitset &rhs) noexcept
    {
        lhs |= rhs;       
        return move(lhs);
    }
    inline friend dynamic_bitset operator | (
        const dynamic_bitset &lhs, dynamic_bitset &&rhs) noexcept
    {
        rhs |= lhs;
        return move(rhs);
    }
    inline friend dynamic_bitset operator | (
        dynamic_bitset &&lhs, dynamic_bitset &&rhs) noexcept
    {
        lhs |= rhs;       
        return move(lhs);
    }
    
    inline dynamic_bitset &operator ^= (const dynamic_bitset &rhs) noexcept
    {
        for(size_t i = 0; i < storage_size(); ++i)
            v[i] ^= rhs.v[i];
        v.back() = bitset_detail::mask_n<BitCount>(v.back());
        return *this;
    }
    inline friend dynamic_bitset operator ^ (
        const dynamic_bitset &lhs, const dynamic_bitset &rhs)
    {
        dynamic_bitset res(lhs.size(), lhs.get_allocator());
        for(size_t i = 0; i < res.storage_size(); ++i)
            res.v[i] = lhs.v[i] ^ rhs.v[i];
        res.v.back() = bitset_detail::mask_n<BitCount>(res.v.back());       
        return res;
    }
    inline friend dynamic_bitset operator ^ (
        dynamic_bitset &&lhs, const dynamic_bitset &rhs) noexcept
    {
        lhs ^= rhs;       
        return move(lhs);
    }
    inline friend dynamic_bitset operator ^ (
        const dynamic_bitset &lhs, dynamic_bitset &&rhs) noexcept
    {
        rhs ^= lhs;
        return move(rhs);
    }
    inline friend dynamic_bitset operator ^ (
        dynamic_bitset &&lhs, dynamic_bitset &&rhs) noexcept
    {
        lhs ^= rhs;       
        return move(lhs);
    }
    
    inline dynamic_bitset &operator <<= (const size_t &n) noexcept
    {
        if(n >= size())
        {
            this->reset();
            return *this;
        }
        if(n == 0)
            return *this;

        const size_t border_idx = n / storage_type_bits();
        const size_t bit_idx = n % storage_type_bits();

        if(bit_idx != 0)
        {
            const size_t inv_bit_idx = storage_type_bits() - bit_idx;

            for(size_t i = storage_size()-1; i > border_idx; --i)
            {
                v[i] = (v[i-border_idx] << bit_idx)
                    | (v[i-border_idx-1] >> inv_bit_idx);
            }
            v[border_idx] = v[0] << bit_idx;
        }
        else
        {
            for(size_t i = storage_size()-1; i > border_idx; --i)
                v[i] = v[i-border_idx];
            v[border_idx] = v[0];
        }

        foundation::iterator::fill_n(
            v.begin(), border_idx, storage_type());
            
        v.back() = bitset_detail::mask_n<BitCount>(v.back());

        return *this;
    }
    inline friend dynamic_bitset operator << (
        const dynamic_bitset &lhs, const size_t n)
    {
        dynamic_bitset res(lhs);
        res <<= n;
        return res;
    }
    inline friend dynamic_bitset operator << (
        dynamic_bitset &&lhs, const size_t n) noexcept
    {
        dynamic_bitset res(move(lhs));
        res <<= n;
        return res;
    }
    
    inline dynamic_bitset &operator >>= (const size_t &n) noexcept
    {
        if(n >= size())
        {
            this->reset();
            return *this;
        }
        if(n == 0)
            return *this;

        const size_t border_idx = n / storage_type_bits();
        const size_t bit_idx = n % storage_type_bits();
        const size_t max_idx = storage_size() - border_idx - 1;

        if(bit_idx != 0)
        {
            const size_t inv_bit_idx = storage_type_bits() - bit_idx;

            for(size_t i = 0; i < max_idx; ++i)
            {
                v[i] = (v[i + border_idx] >> bit_idx)
                    | (v[i + border_idx + 1] << inv_bit_idx);
            }
            v[max_idx] = v[storage_size() - 1] >> bit_idx;
        }
        else
        {
            for(size_t i = 0; i <= max_idx; ++i)
                v[i] = v[i+border_idx];
        }

        foundation::iterator::fill_n(
            v.begin() + (storage_size() - border_idx),
            border_idx, storage_type());
            
        v.back() = bitset_detail::mask_n<BitCount>(v.back());

        return *this;
    }
    inline friend dynamic_bitset operator >> (
        const dynamic_bitset &lhs, const size_t n)
    {
        dynamic_bitset res(lhs);
        res >>= n;
        return res;
    }
    inline friend dynamic_bitset operator >> (
        dynamic_bitset &&lhs, const size_t n) noexcept
    {
        dynamic_bitset res(move(lhs));
        res >>= n;
        return res;
    }

    inline bool operator == (const dynamic_bitset &rhs) const noexcept
    {
        for(size_t i = 0; i < storage_size(); ++i)
            if(v[i] != rhs.v[i])
                return false;

        return true;
    }
    inline bool operator != (const dynamic_bitset &rhs) const noexcept
    {
        for(size_t i = 0; i < storage_size(); ++i)
            if(v[i] != rhs.v[i])
                return true;

        return false;
    }

    inline explicit operator storage_type() const noexcept
    {
        return v[0];
    }
    
    inline allocator_type get_allocator() const noexcept {
        return v.get_allocator();
    }

private:
    inline dynamic_bitset(const dynamic_bitset &other, make_inverse_tag)
    : v(other.get_allocator())
    {
        for(size_t i = 0; i < storage_size(); ++i)
            v[i] = ~other.v[i];
        v.back() = bitset_detail::mask_n<BitCount>(v.back());
    }

    dynamic_array<storage_type, storage_size(), allocator_type> v;
};

/** @} */

}} // namespaces
 
#endif // NIC_309F48068301E05B_NIC
