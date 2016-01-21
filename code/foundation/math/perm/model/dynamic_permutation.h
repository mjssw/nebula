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
#ifndef NIC_7F1C294E8BCBE915_NIC
#define NIC_7F1C294E8BCBE915_NIC

#include "../traits.h"
#include "../../../dynamic_array.h"

namespace nebula { namespace foundation { namespace math { namespace perm {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <size_t N, class Allocator = memory::allocator<size_t>>
class dynamic_permutation
{
    n_static_assert(N > 0, "");
    
public:
    using allocator_type = Allocator;
    
    dynamic_permutation() = default;
    dynamic_permutation(dynamic_permutation &) = default;
    dynamic_permutation(const dynamic_permutation &) = default;
    dynamic_permutation(dynamic_permutation &&) = default;
    
    template <class A>
    inline dynamic_permutation(const dynamic_permutation &other, A &&alc)
    : v(other.v, foundation::forward<A>(alc))
    {}
    template <class A>
    inline dynamic_permutation(dynamic_permutation &&other, A &&alc)
    : v(foundation::move(other.v), foundation::forward<A>(alc))
    {}
    
    template <class ... X>
    inline dynamic_permutation(X && ... x)
    : dynamic_permutation({foundation::forward<X>(x)...})
    {}
    inline dynamic_permutation(std::initializer_list<size_t> lst)
    : v(lst)
    {}
    template <class A>
    inline dynamic_permutation(std::initializer_list<size_t> lst, A &&alc)
    : v(lst, foundation::forward<A>(alc))
    {}
    
    dynamic_permutation &operator = (const dynamic_permutation&) = default;
    dynamic_permutation &operator = (dynamic_permutation &&) = default;
    
    inline void swap(dynamic_permutation &other) noexcept {
        v.swap(other);
    }
    
    inline size_t &operator [] (const size_t n) noexcept {
        return v[n];
    }
    inline const size_t &operator [] (const size_t n) const noexcept {
        return v[n];
    }
    
    inline bool operator == (const dynamic_permutation &other) const noexcept {
        return v == other;
    }
    inline bool operator != (const dynamic_permutation &other) const noexcept {
        return v != other;
    }
    
    template <class Other>
    inline dynamic_permutation operator * (const Other &other)
    {
        dynamic_permutation r;
        for(size_t i = 0; i < N; ++i)
            r[i] = v[other[i]];
        return r;
    }
    
private:
    dynamic_array<size_t, N, allocator_type> v;
};

//------------------------------------------------------------------------------
template <size_t N>
struct size<dynamic_permutation<N>> : public meta::size_t_<N> {};

/** @} */

}}}} // namespaces

#endif // NIC_7F1C294E8BCBE915_NIC

