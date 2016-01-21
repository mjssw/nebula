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
#ifndef NIC_9E446E69500F8B14_NIC
#define NIC_9E446E69500F8B14_NIC

#include "../type_traits.h"
#include "../ratio.h"
#include "../meta.h"
#include "../declval.h"
#include "../math.h"
#include "../format.h"
#include "../enable_if.h"

namespace nebula { namespace foundation { namespace chrono {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class T, class P>
class duration;
//------------------------------------------------------------------------------
namespace chrono_detail {
//------------------------------------------------------------------------------
template <class D0, class D1>
struct common_duration {
    using type = duration<
        typename common_type<
            typename D0::value_type,
            typename D1::value_type,
            intmax_t>::type,
        typename ratio_gcd<
            typename D0::period, 
            typename D1::period>::type>;
};
//------------------------------------------------------------------------------
template <class To, class From, class P, bool N1, bool D1>
struct duration_caster;

template <class To, class From, class P>
struct duration_caster<To, From, P, true, true>
{
    inline static constexpr To apply(const From &x) {
        return To(static_cast<typename To::value_type>(x.count()));
    }
};

template <class To, class From, class P>
struct duration_caster<To, From, P, true, false>
{
    inline static constexpr To apply(const From &x) {
        using CT = typename common_type<
            typename To::value_type,
            typename From::value_type,
            intmax_t>::type;
        return To(
            static_cast<typename To::value_type>(
                static_cast<CT>(x.count()) / static_cast<CT>(P::den)
            )
        );
    }
};

template <class To, class From, class P>
struct duration_caster<To, From, P, false, true>
{
    inline static constexpr To apply(const From &x) {
        using CT = typename common_type<
            typename To::value_type,
            typename From::value_type,
            intmax_t>::type;
        return To(
            static_cast<typename To::value_type>(
                static_cast<CT>(x.count()) * static_cast<CT>(P::num)
            )
        );
    }
};

template <class To, class From, class P>
struct duration_caster<To, From, P, false, false>
{
    inline static constexpr To apply(const From &x) {
        using CT = typename common_type<
            typename To::value_type,
            typename From::value_type,
            intmax_t>::type;
        return To(
            static_cast<typename To::value_type>(
                static_cast<CT>(x.count())
                / static_cast<CT>(P::den)
                * static_cast<CT>(P::num)
            )
        );
    }
};
//------------------------------------------------------------------------------
} // chrono_detail
//------------------------------------------------------------------------------
template <class To, class T, class P>
inline constexpr To duration_cast(const duration<T, P> &x)
{
    using Div = typename ratio_div<P, typename To::period>::type;
    return chrono_detail::duration_caster<
        To,
        duration<T, P>,
        Div,
        Div::num == 1,
        Div::den == 1
    >::apply(x);
}
//------------------------------------------------------------------------------
/** This is the main class responsible for holding and managing time values.
 * 
 * It is primarily designed to work on machine types like int or float, rather
 * than any 'bignum' types. This is to keep this library simple, although this
 * class provides some functionality so that it is more usefull. For example
 * arithmetic operators and comparison operators have been overloaded. As of
 * now arithmetic operators do not work with difference duration types, but
 * comparison operators do. You can convert between different duration types
 * using construction or assignment, thereby the held time is converted between
 * units. For example microseconds to milliseconds. Depending on the data type
 * where the time is actually stored you have to expect truncation or loss of
 * precission in the conversion process.
 * */
template <class T, class P = ratio<1,1>>
class duration
{
public:
    using value_type = T;
    using period = P;
    
    duration() = default;
    duration(duration &) = default;
    duration(const duration &) = default;
    duration(duration &&) = default;
    
    inline duration(const value_type &x)
    : v(x)
    {}
    
    template <class T_, class P_>
    inline duration(const duration<T_, P_> &other)
    : duration(chrono::duration_cast<duration<T,P>>(other))
    {}
    
    duration &operator = (const duration &) = default;
    duration &operator = (duration &&) = default;
    
    template <class T_, class P_>
    inline duration &operator = (const duration<T_, P_> &other)
    {
        *this = duration<T, P>(chrono::duration_cast<duration<T,P>>(other));
        return *this;
    }
    
    inline const value_type &count() const noexcept {
        return v;
    }
    
    inline static duration zero() {
        return duration(value_type(0));
    }
    inline static duration max() {
        return duration(value_type(math::maximum<value_type>()));
    }
    inline static duration min() {
        return duration(value_type(math::minimum<value_type>()));
    }
    
    inline duration &operator += (const duration &other) {
        v += other.v;
        return *this;
    }
    inline duration &operator -= (const duration &other) {
        v += other.v;
        return *this;
    }
    inline duration &operator *= (const duration &other) {
        v += other.v;
        return *this;
    }
    inline duration &operator /= (const duration &other) {
        v += other.v;
        return *this;
    }
    template <class Cond = math::is_integer<value_type>,
        typename enable_if<Cond>::type* = nullptr>
    inline duration &operator %= (const duration &other) {
        v %= other.v;
        return *this;
    }
    template <class Cond = math::is_integer<value_type>,
        typename enable_if<Cond>::type* = nullptr>
    inline duration &operator ++ () {
        ++v;
        return *this;
    }
    template <class Cond = math::is_integer<value_type>,
        typename enable_if<Cond>::type* = nullptr>
    inline duration operator ++ (int) {
        return duration(v+1);
    }
    template <class Cond = math::is_integer<value_type>,
        typename enable_if<Cond>::type* = nullptr>
    inline duration &operator -- () {
        --v;
        return *this;
    }
    template <class Cond = math::is_integer<value_type>,
        typename enable_if<Cond>::type* = nullptr>
    inline duration operator -- (int) {
        return duration(v-1);
    }
    inline duration operator + () const {
        return *this;
    }
    inline duration operator - () const {
        return duration(-v);
    }
    
    inline duration operator + (const duration &other) const {
        return duration(v + other.v);
    }
    inline duration operator - (const duration &other) const {
        return duration(v - other.v);
    }
    inline duration operator * (const duration &other) const {
        return duration(v * other.v);
    }
    inline duration operator / (const duration &other) const {
        return duration(v / other.v);
    }
    template <class Cond = math::is_integer<value_type>,
        typename enable_if<Cond>::type* = nullptr>
    inline duration operator % (const duration &other) const {
        return duration(v % other.v);
    }
    
    inline bool operator < (const duration &other) const {
        return this->count() < other.count();
    }
    template <class T_, class P_>
    inline bool operator < (const duration<T_, P_> &other) const {
        using CD = typename chrono_detail::common_duration<
            duration<T, P>,
            duration<T_, P_>
        >::type;
        
        return CD(*this).count() < CD(other).count();
    }
    inline bool operator <= (const duration &other) const {
        return this->count() <= other.count();
    }
    template <class T_, class P_>
    inline bool operator <= (const duration<T_, P_> &other) const {
        using CD = typename chrono_detail::common_duration<
            duration<T, P>,
            duration<T_, P_>
        >::type;
        
        return CD(*this).count() <= CD(other).count();
    }
    inline bool operator > (const duration &other) const {
        return this->count() > other.count();
    }
    template <class T_, class P_>
    inline bool operator > (const duration<T_, P_> &other) const {
        using CD = typename chrono_detail::common_duration<
            duration<T, P>,
            duration<T_, P_>
        >::type;
        
        return CD(*this).count() > CD(other).count();
    }
    inline bool operator >= (const duration &other) const {
        return this->count() >= other.count();
    }
    template <class T_, class P_>
    inline bool operator >= (const duration<T_, P_> &other) const {
        using CD = typename chrono_detail::common_duration<
            duration<T, P>,
            duration<T_, P_>
        >::type;
        
        return CD(*this).count() >= CD(other).count();
    }
    
    inline bool operator == (const duration &other) const {
        return this->count() == other.count();
    }
    template <class T_, class P_>
    inline bool operator == (const duration<T_, P_> &other) const {
        using CD = typename chrono_detail::common_duration<
            duration<T, P>,
            duration<T_, P_>
        >::type;
        
        return CD(*this).count() == CD(other).count();
    }
    inline bool operator != (const duration &other) const {
        return this->count() != other.count();
    }
    template <class T_, class P_>
    inline bool operator != (const duration<T_, P_> &other) const {
        using CD = typename chrono_detail::common_duration<
            duration<T, P>,
            duration<T_, P_>
        >::type;
        
        return CD(*this).count() != CD(other).count();
    }
    
    template <class Other>
    inline Other cast() const {
        return chrono::duration_cast<Other>(*this);
    }
    
    template <class Sink>
    inline void operator () (Sink &sink, fmt::fout_tag) const
    {
        fmt::fwrite(sink, v);
    }
    
private:    
    value_type v;
};

//------------------------------------------------------------------------------
using nanoseconds =     duration<intmax_t, nano>;
using microseconds =    duration<intmax_t, micro>;
using milliseconds =    duration<intmax_t, milli>;
using centiseconds =    duration<intmax_t, centi>;
using deciseconds =     duration<intmax_t, deci>;
using seconds =         duration<intmax_t, ratio<1, 1>>;
using minutes =         duration<intmax_t, ratio<60, 1>>;
using hours =           duration<intmax_t, ratio<60*60, 1>>;
using days =            duration<intmax_t, ratio<60*60*24, 1>>;

/** @} */

}}} // namespaces

#endif // NIC_9E446E69500F8B14_NIC
