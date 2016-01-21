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
#ifndef NIC_F9D4EA9F1D461429_NIC
#define NIC_F9D4EA9F1D461429_NIC

#include "detail/map_index.h"

#include "../../../array.h"

namespace nebula { namespace foundation { namespace math { namespace vec {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <class T, size_t ... N>
struct vector
{
    vector() = default;
    vector(vector &) = default;
    vector(const vector &) = default;
    vector(vector &&) = default;
    
    template <class ... X>
    inline vector(X && ... x)
    : v{foundation::forward<X>(x)...}
    {}
    
    vector &operator = (const vector&) = default;
    vector &operator = (vector &&) = default;

    inline T &operator [] (const size_t i) & noexcept {
        return v[i];
    }
    inline T operator [] (const size_t i) && noexcept {
        return foundation::move(v[i]);
    }
    inline const T &operator [] (const size_t i) const & noexcept {
        return v[i];
    }
    
    template <class ... X>
    inline T &operator [] (const tuple<X...> &t) & noexcept {
        return this->operator [] (
            vec_indexer_detail::map_index<_layout<vector>>(t));
    }
    template <class ... X>
    inline T operator [] (const tuple<X...> &t) && noexcept {
        return move(*this)[
            vec_indexer_detail::map_index<_layout<vector>>(t)];
    }
    template <class ... X>
    inline const T &operator [] (const tuple<X...> &t) const & noexcept {
        return this->operator [] (
            vec_indexer_detail::map_index<_layout<vector>>(t));
    }
    
    template <class ... I>
    inline T &operator () (const I ... i) & noexcept
    {
        return this->operator [] (make_tuple(i...));
    }
    template <class ... I>
    inline T operator () (const I ... i) && noexcept
    {
        return move(*this)[make_tuple(i...)];
    }
    template <class ... I>
    inline const T &operator () (const I ... i) const & noexcept
    {
        return this->operator [] (make_tuple(i...));
    }
    
    template <class Other,
        _enable_if<is_lvalue_reference<Other>>* = nullptr>
    inline vector operator + (Other &&other) const &
    {
        vector r;
        for(size_t i = 0; i < vec::_size<vector>::value; ++i)
        {
            r[i] = v[i] + other.v[i];
        }
        return r;
    }
    template <class Other,
        _disable_if<is_lvalue_reference<Other>>* = nullptr>
    inline vector operator + (Other &&other) &
    {
        for(size_t i = 0; i < vec::_size<vector>::value; ++i)
        {
            other.v[i] += v[i];
        }
        return move(other);
    }
    template <class Other>
    inline vector operator + (const Other &other) &&
    {
        for(size_t i = 0; i < vec::_size<vector>::value; ++i)
        {
            v[i] += other.v[i];
        }
        return move(*this);
    }
    
    template <class Other,
        _enable_if<is_lvalue_reference<Other>>* = nullptr>
    inline vector operator - (Other &&other) const &
    {
        vector r;
        for(size_t i = 0; i < vec::_size<vector>::value; ++i)
        {
            r[i] = v[i] - other.v[i];
        }
        return r;
    }
    template <class Other,
        _disable_if<is_lvalue_reference<Other>>* = nullptr>
    inline vector operator - (Other &&other) &
    {
        for(size_t i = 0; i < vec::_size<vector>::value; ++i)
        {
            other.v[i] -= v[i];
        }
        return move(other);
    }
    template <class Other>
    inline vector operator - (const Other &other) &&
    {
        for(size_t i = 0; i < vec::_size<vector>::value; ++i)
        {
            v[i] -= other.v[i];
        }
        return move(*this);
    }
    
    inline vector operator - () &
    {
        return *this * T(-1);
    }
    inline vector operator - () &&
    {
        return move(*this) * T(-1);
    }
    
    template <class S>
    inline vector operator * (const S &n) const &
    {
        vector r;
        for(size_t i = 0; i < vec::_size<vector>::value; ++i)
        {
            r[i] = v[i] * n;
        }
        return r;
    }
    template <class S>
    inline vector operator * (const S &n) &&
    {
        for(size_t i = 0; i < vec::_size<vector>::value; ++i)
        {
            v[i] *= n;
        }
        return move(*this);
    }
    
    template <class S>
    inline vector operator / (S &&n) const &
    {
        return *this * (ctraits::_value<S>(1) / foundation::forward<S>(n));
    }
    template <class S>
    inline vector operator / (S &&n) &&
    {
        return move(*this)
            * (ctraits::_value<S>(1) / foundation::forward<S>(n));
    }
    
private:
    array<T, meta::_mul<meta::size_t_<N>...>::value> v;
};

//------------------------------------------------------------------------------
template <class T, size_t ... N>
struct scalar_value<vector<T,N...>>
{
    using type = T;
};
//------------------------------------------------------------------------------
template <class T, size_t ... N>
struct layout<vector<T,N...>>
{
    using type = meta::seq<meta::size_t_<N>...>;
};
//------------------------------------------------------------------------------
namespace vector_detail
{
//------------------------------------------------------------------------------
template <class T, class ... SizeT>
struct resized_vector
{
    using type = vector<T, SizeT::type::value ...>;
};

} // vector_detail
//------------------------------------------------------------------------------
template <class T, size_t ... N, class Layout>
class resize<vector<T,N...>, Layout>
{
    using Seq = typename Layout::type;
    using Seq2 = meta::_push_front<Seq, T>;
    using Fin = meta::_expand<vector_detail::resized_vector, Seq2>;
    
public:
    using type = typename Fin::type;
};
//------------------------------------------------------------------------------
template <class T, size_t ... N, class NewT>
struct rebind<vector<T,N...>, NewT>
{
    using type = vector<NewT, N...>;
};

/** @} */

}}}} // namespaces

#endif // NIC_F9D4EA9F1D461429_NIC

