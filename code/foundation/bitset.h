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
#ifndef NIC_7F4D2F3EC393AF4D_NIC
#define NIC_7F4D2F3EC393AF4D_NIC

#include "array.h"
#include "range.h"
#include "math/limits.h"

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{
 */
#define N_BITSET_DEFAULT_TYPE unsigned long long

namespace bitset_detail {
//------------------------------------------------------------------------------
template <size_t N, class StorageType,
    size_t N_ = N % (sizeof(StorageType)*n_char_bit)>
inline static constexpr StorageType mask_n(const StorageType x) noexcept {
    return N_
        ? x & ~((~static_cast<StorageType>(0)) << N_)
        : x;
}

} // bitset_detail

//------------------------------------------------------------------------------
template <
    size_t BitCount,
    class T = N_BITSET_DEFAULT_TYPE>
class bitset
{
    n_static_assert(BitCount > 0, "");
    n_static_assert(is_unsigned<T>::value,
        "T must be an unsigned integer.");

private:
    using storage_type = T;
    inline static constexpr size_t storage_type_bits() noexcept {
        return sizeof(T) * n_char_bit;
    }
    inline static constexpr size_t storage_size() noexcept {
        return BitCount % storage_type_bits() == 0
            ? BitCount / storage_type_bits()
            : BitCount / storage_type_bits() + 1;
    }
    struct make_inverse_tag {};

public:
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
        
        friend class bitset;
    };

public:
    typedef reference_impl reference;
    typedef const bool const_reference;

public:
    inline bitset() noexcept
    {
        v.back() = storage_type();
    }
    bitset(bitset &) = default;
    bitset(const bitset &) = default;
    bitset(bitset &&) = default;
    
    inline bitset(const storage_type x)
    {
        v.front() = x;
        foundation::iterator::fill(v.begin()+1, v.end(), storage_type());
    }
    
    bitset &operator = (const bitset &) = default;
    bitset &operator = (bitset &&) = default;
    
    inline void swap(bitset &other) noexcept
    {
        for(size_t i = 0; i < storage_size(); ++i)
            foundation::swap(v[i], other.v[i]);
    }
    
    inline size_t size() const noexcept {
        return BitCount;
    }
    
    inline bitset &set(const size_t n) noexcept
    {
        const size_t i = n / storage_type_bits();
        const storage_type bit = static_cast<storage_type>(1)
            << (n % storage_type_bits());
        
        v[i] |= bit;

        return *this;
    }
    inline bitset &set() noexcept
    {
        range::fill(v, static_cast<storage_type>(1));
        v.back() = bitset_detail::mask_n<BitCount>(v.back());
        return *this;
    }
    
    inline bitset &reset() noexcept
    {
        range::fill(v, storage_type());
        return *this;
    }
    inline bitset &reset(const size_t n) noexcept
    {
        const size_t i = n / storage_type_bits();
        const storage_type bit = static_cast<storage_type>(1)
            << (n % storage_type_bits());

        v[i] &= ~bit;

        return *this;
    }

    inline bitset &flip(const size_t n) noexcept
    {
        const size_t i = n / storage_type_bits();
        const storage_type bit = static_cast<storage_type>(1)
            << (n % storage_type_bits());

        v[i] ^= bit;

        return *this;
    }
    inline bitset &flip() noexcept
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
    
    inline bitset operator ~ () const
    {
        return bitset(*this, make_inverse_tag());
    }
    
    inline bitset &operator &= (const bitset &rhs) noexcept
    {
        for(size_t i = 0; i < storage_size(); ++i)
            v[i] &= rhs.v[i];

        return *this;
    }
    inline friend bitset operator & (
        const bitset &lhs, const bitset &rhs) noexcept
    {
        bitset res;
        for(size_t i = 0; i < res.storage_size(); ++i)
            res.v[i] = lhs.v[i] & rhs.v[i];        
        return res;
    }
    
    inline bitset &operator |= (const bitset &rhs) noexcept
    {
        for(size_t i = 0; i < storage_size(); ++i)
            v[i] |= rhs.v[i];

        return *this;
    }
    inline friend bitset operator | (
        const bitset &lhs, const bitset &rhs) noexcept
    {
        bitset res;
        for(size_t i = 0; i < res.storage_size(); ++i)
            res.v[i] = lhs.v[i] | rhs.v[i];        
        return res;
    }
    
    inline bitset &operator ^= (const bitset &rhs) noexcept
    {
        for(size_t i = 0; i < storage_size(); ++i)
            v[i] ^= rhs.v[i];

        return *this;
    }
    inline friend bitset operator ^ (
        const bitset &lhs, const bitset &rhs) noexcept
    {
        bitset res;
        for(size_t i = 0; i < res.storage_size(); ++i)
            res.v[i] = lhs.v[i] ^ rhs.v[i];        
        return res;
    }
    
    inline bitset &operator <<= (const size_t &n) noexcept
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
    inline friend bitset operator << (
        const bitset &lhs, const size_t n) noexcept
    {
        bitset res(lhs);
        res <<= n;
        return res;
    }
    
    inline bitset &operator >>= (const size_t &n) noexcept
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
    inline friend bitset operator >> (
        const bitset &lhs, const size_t n) noexcept
    {
        bitset res(lhs);
        res >>= n;
        return res;
    }

    inline bool operator == (const bitset &rhs) const noexcept
    {
        for(size_t i = 0; i < storage_size(); ++i)
            if(v[i] != rhs.v[i])
                return false;

        return true;
    }
    inline bool operator != (const bitset &rhs) const noexcept
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

private:
    inline bitset(const bitset &other, make_inverse_tag)
    {
        for(size_t i = 0; i < storage_size(); ++i)
            v[i] = ~other.v[i];
        v.back() = bitset_detail::mask_n<BitCount>(v.back());
    }
    
    array<storage_type, storage_size()> v;
};

/** @} */

}} // namespaces
 
#endif // NIC_7F4D2F3EC393AF4D_NIC
