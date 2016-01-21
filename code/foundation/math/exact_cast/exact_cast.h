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
#ifndef NIC_13EFCD785289DDBF_NIC
#define NIC_13EFCD785289DDBF_NIC

#include "../traits.h"
#include "../limits.h"
#include "../basic.h"
#include "../../exception/exception.h"
#include "../../call_traits.h"
#include "../../type_traits.h"
#include "../../meta.h"

namespace nebula { namespace foundation { namespace math {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
struct bad_exact_cast : public virtual bad_cast {};
//------------------------------------------------------------------------------
namespace exact_cast_detail {
//------------------------------------------------------------------------------
struct s_to_u_narrow {};
struct x_to_s_narrow {};
struct x_to_s_widen {};
struct s_to_u_widen {};
//------------------------------------------------------------------------------
template <class T, class S, class Tag>
struct exact_caster;

template <class T, class S>
struct exact_caster<T, S, x_to_s_widen>
{
    inline static bool apply(const S &s)
    {
        return true;
    }
};

template <class T, class S>
struct exact_caster<T, S, s_to_u_widen>
{
    inline static bool apply(const S &s)
    {
        return S(0) <= s;
    }
};

template <class T, class S>
struct exact_caster<T, S, s_to_u_narrow>
{
    inline static bool apply(const S &s)
    {
        const S mx = math::maximum<T>();
        if(S(0) <= s && s <= mx)
            return true;
        return false;
    }
};

template <class T, class S>
struct exact_caster<T, S, x_to_s_narrow>
{
    inline static bool apply(const S &s)
    {
        const S mx = math::maximum<T>();
        if(math::abs(s) <= mx)
            return true;
        return false;
    }
};

} // exact_cast_detail
//------------------------------------------------------------------------------
template <class Trg, class Src>
struct check_exact_cast_impl
{
    using caster_tag = meta::_if<
        meta::_less_equal<digits<Trg>, digits<Src>>,
        meta::_if<
            meta::_not<is_signed<Trg>>, 
            exact_cast_detail::s_to_u_narrow, 
            exact_cast_detail::x_to_s_narrow>,
        meta::_if<
            meta::_not<is_signed<Trg>>, 
            exact_cast_detail::s_to_u_widen, 
            exact_cast_detail::x_to_s_widen>>;
    
    inline static bool apply(const Src &s)
    {
        return exact_cast_detail::exact_caster<Trg, Src, caster_tag>::apply(s);
    }
};

//------------------------------------------------------------------------------
/** Returns true iff static_cast<Trg>(s) can represent the value stored in s.
 * @note Only applies to integral types.
 * @note Will not throw if Trg and Src are POD types.
 * */
template <class Trg, class Src>
inline bool check_exact_cast(const Src &s)
{
    n_static_assert(is_integer<Trg>::value, "");
    n_static_assert(is_integer<Src>::value, "");
    
    return check_exact_cast_impl<Trg, Src>::apply(s);
}
//------------------------------------------------------------------------------
/** Similar to check_exact_cast() but throws bad_exact_cast if
 * check_exact_cast() would return true. Otherwise this does nothing.
 * */
template <class Trg, class Src>
inline void require_exact_cast(const Src &s)
{
    n_static_assert(is_integer<Trg>::value, "");
    n_static_assert(is_integer<Src>::value, "");
    
    if(!math::check_exact_cast<Trg>(s))
        n_throw(bad_exact_cast);
}

/** @} */

}}} // namespaces

#endif // NIC_13EFCD785289DDBF_NIC
