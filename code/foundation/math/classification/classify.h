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
#ifndef NIC_80DB0148DC4C99D2_NIC
#define NIC_80DB0148DC4C99D2_NIC

#include "../traits.h"
#include "../../defs.h"
#include <cmath>

namespace nebula { namespace foundation { namespace math {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
enum class f_state
{
    zero,
    subnormal,
    normal,
    infinite,
    NaN,
    unknowen
};
//------------------------------------------------------------------------------
inline const char *to_cstr(const f_state s) noexcept {
    switch(s){
        case f_state::zero: return "zero";
        case f_state::subnormal: return "subnormal";
        case f_state::normal: return "normal";
        case f_state::infinite: return "infinite";
        case f_state::NaN: return "NaN";
        case f_state::unknowen: return "unknowen";
    }
}
//------------------------------------------------------------------------------
template <class T>
struct classify_impl
{
    inline static f_state apply(const T &x)
    {
        switch(std::fpclassify(x)) {
        case FP_NAN:
            return f_state::NaN;
        case FP_SUBNORMAL:
            return f_state::subnormal;
        case FP_NORMAL:
            return f_state::normal;
        case FP_INFINITE:
            return f_state::infinite;
        case FP_ZERO:
            return f_state::zero;
        default:
            return f_state::unknowen;
        }
    }
};
//------------------------------------------------------------------------------
template <class T>
inline f_state classify(const T &x) {
    n_static_assert(
        !is_integer<T>::type::value,
        "Floating point type required.");
    return classify_impl<T>::apply(x);
}

/** @} */

}}} // namespaces

#endif // NIC_80DB0148DC4C99D2_NIC