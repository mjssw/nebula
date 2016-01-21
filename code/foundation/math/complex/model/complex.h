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
#ifndef NIC_555C3C17CD7787FB_NIC
#define NIC_555C3C17CD7787FB_NIC

#include "../common.h"
#include "../../vec/traits.h"
#include "../../vec/model/detail/map_index.h"
#include "../../../array.h"

namespace nebula { namespace foundation { namespace math {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <class T>
struct complex
{    
public:
    complex() = default;
    complex(complex &) = default;
    complex(const complex &) = default;
    complex(complex &&) = default;
    
    template <class X>
    inline complex(X && x)
    : v{foundation::forward<X>(x), T(0)}
    {}
    template <class X, class Y>
    inline complex(X && x, Y &&y)
    : v{foundation::forward<X>(x), foundation::forward<Y>(y)}
    {}
    
    complex &operator = (const complex&) = default;
    complex &operator = (complex &&) = default;

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
            vec::vec_indexer_detail::map_index<vec::_layout<complex>>(t));
    }
    template <class ... X>
    inline T operator [] (const tuple<X...> &t) && noexcept {
        return move(*this)[
            vec::vec_indexer_detail::map_index<vec::_layout<complex>>(t)];
    }
    template <class ... X>
    inline const T &operator [] (const tuple<X...> &t) const & noexcept {
        return this->operator [] (
            vec::vec_indexer_detail::map_index<vec::_layout<complex>>(t));
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
    inline complex operator + (Other &&other) const &
    {
        return complex(
            v[0] + other.v[0],
            v[1] + other.v[1]);
    }
    template <class Other,
        _disable_if<is_lvalue_reference<Other>>* = nullptr>
    inline complex operator + (Other &&other) &
    {
        other.v[0] += v[0];
        other.v[1] += v[1];
        return move(other);
    }
    template <class Other>
    inline complex operator + (const Other &other) &&
    {
        v[0] += other.v[0];
        v[1] += other.v[1];
        return move(*this);
    }
    
    template <class Other>
    inline complex &operator += (const Other &other)
    {
        *this = move(*this) + other;
        return *this;
    }
    
    inline complex operator + () &
    {
        return *this;
    }
    inline complex operator + () &&
    {
        return move(*this);
    }
    
    template <class Other,
        _enable_if<is_lvalue_reference<Other>>* = nullptr>
    inline complex operator - (Other &&other) const &
    {
        return complex(
            v[0] - other.v[0],
            v[1] - other.v[1]);
    }
    template <class Other,
        _disable_if<is_lvalue_reference<Other>>* = nullptr>
    inline complex operator - (Other &&other) &
    {
        other.v[0] -= v[0];
        other.v[1] -= v[1];
        return move(other);
    }
    template <class Other>
    inline complex operator - (const Other &other) &&
    {
        v[0] -= other.v[0];
        v[1] -= other.v[1];
        return move(*this);
    }
    
    template <class Other>
    inline complex &operator -= (const Other &other)
    {
        *this = move(*this) - other;
        return *this;
    }
    
    inline complex operator - () &
    {
        return *this * T(-1);
    }
    inline complex operator - () &&
    {
        return move(*this) * T(-1);
    }
    
    template <class S>
    inline complex operator * (S &&x) const &
    {
        complex res;
        res[0] = v[0] * x;
        res[1] = v[1] * foundation::forward<S>(x);
        return res;
    }
    template <class S>
    inline complex operator * (S &&x) &&
    {
        v[0] *= x;
        v[1] *= foundation::forward<S>(x);
        return move(*this);
    }
    
    template <class S>
    inline complex operator * (complex<S> &other) const &
    {
        return complex(
            v[0] * other[0] - v[1] * other[1],
            v[0] * other[1] + v[1] * other[0]);
    }
    template <class S>
    inline complex operator * (const complex<S> &other) const &
    {
        return complex(
            v[0] * other[0] - v[1] * other[1],
            v[0] * other[1] + v[1] * other[0]);
    }
    template <class S>
    inline complex operator * (complex<S> &&other) const &
    {
        return move(other) * *this;
    }
    template <class S>
    inline complex operator * (complex<S> &other) &&
    {
        T tmp = v[0] * other[0] - v[1] * other[1];
        v[1] = v[0] * other[1] + v[1] * other[0];
        v[0] = move(tmp);
        return move(*this);
    }
    template <class S>
    inline complex operator * (const complex<S> &other) &&
    {
        T tmp = v[0] * other[0] - v[1] * other[1];
        v[1] = v[0] * other[1] + v[1] * other[0];
        v[0] = move(tmp);
        return move(*this);
    }
    template <class S>
    inline complex operator * (complex<S> &&other) &&
    {
        T tmp = v[0] * other[0] - v[1] * other[1];
        v[1] = v[0] * other[1] + v[1] * other[0];
        v[0] = move(tmp);
        return move(*this);
    }
    
    template <class Other>
    inline complex &operator *= (Other &&other)
    {
        *this = move(*this) * foundation::forward<Other>(other);
        return *this;
    }
    
    template <class S>
    inline complex operator / (S &&n) const &
    {
        return *this * (T(1) / foundation::forward<S>(n));
    }
    template <class S>
    inline complex operator / (S &&n) &&
    {
        return move(*this) * (T(1) / foundation::forward<S>(n));
    }
    
    template <class S>
    inline complex operator / (complex<S> &other) const &
    {
        S d = other[0]*other[0] + other[1]*other[1];
        return *this * complex(other[0]/d, -other[1]/d);
    }
    template <class S>
    inline complex operator / (const complex<S> &other) const &
    {
        S d = other[0]*other[0] + other[1]*other[1];
        return *this * complex(other[0]/d, -other[1]/d);
    }
    template <class S>
    inline complex operator / (complex<S> &&other) const &
    {
        S d = other[0]*other[0] + other[1]*other[1];
        other[0] /= d;
        other[1] /= -d;
        return *this * move(other);
    }
    template <class S>
    inline complex operator / (complex<S> &other) &&
    {
        S d = other[0]*other[0] + other[1]*other[1];
        return move(*this) * complex(other[0]/d, -other[1]/d);
    }
    template <class S>
    inline complex operator / (const complex<S> &other) &&
    {
        S d = other[0]*other[0] + other[1]*other[1];
        return move(*this) * complex(other[0]/d, -other[1]/d);
    }
    template <class S>
    inline complex operator / (complex<S> &&other) &&
    {
        S d = other[0]*other[0] + other[1]*other[1];
        other[0] /= d;
        other[1] /= -d;
        return move(*this) * move(other);
    }
    
    template <class Other>
    inline complex &operator /= (Other &&other)
    {
        *this = move(*this) / foundation::forward<Other>(other);
        return *this;
    }
    
    template <class S>
    inline bool operator == (const complex<S> &other) const
    {
        return v == other.v;
    }
    template <class S>
    inline bool operator != (const complex<S> &other) const
    {
        return v != other.v;
    }
    
    template <class Stream>
    inline void operator () (Stream &s, fmt::fout_tag) const
    {
        fmt::fwrite(s, v[0], " + ", v[1], 'i');
    }
    
private:
    array<T, 2> v;
};

namespace vec {
//------------------------------------------------------------------------------
template <class T>
struct scalar_value<complex<T>>
{
    using type = T;
};
//------------------------------------------------------------------------------
template <class T>
struct layout<complex<T>>
{
    using type = meta::seq<meta::size_t_<2>>;
};
//------------------------------------------------------------------------------
template <class T, class NewT>
struct rebind<complex<T>, NewT>
{
    using type = complex<NewT>;
};

} // vec

//------------------------------------------------------------------------------
template <class T>
struct abs_impl<complex<T>>
{
    inline static T apply(const complex<T> &c)
    {
        return math::sqrt(c[0]*c[0] + c[1]*c[1]);
    }
};

/** @} */

}}} // namespaces

#endif // NIC_555C3C17CD7787FB_NIC

