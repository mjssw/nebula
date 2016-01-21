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
#ifndef NIC_2FA25AA9B1DFA227_NIC
#define NIC_2FA25AA9B1DFA227_NIC

#include "real/real_impl.h"
#include "../config.h"

namespace nebula { namespace foundation { namespace fmt {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <class T>
struct real_impl
{    
public:
    template <class D>
    inline static real_impl_detail::real_writer_<T, D>
    apply(
        const T &x,
        const size_t prec,
        const math::rounding_style rounding,
        const bool scientific,
        const unsigned base)
    {
        n_static_assert(!math::is_integer<T>::type::value, "");
        
        return real_impl_detail::real_writer_<T, D>{
            x, base, prec, rounding, scientific ? 'e' : char(0), '.'};
    }
};

//------------------------------------------------------------------------------
template <class D = digit_codec, class T>
inline auto real(
    const T &x,
    const size_t prec = N_FORMAT_DEFAULT_PRECISION,
    const math::rounding_style rounding = N_FORMAT_DEFAULT_ROUNDING_STYLE,
    const bool scientific = true,
    const unsigned base = 10)
-> decltype(real_impl<T>::template apply<D>(
    x, prec, rounding, scientific, base))
{
    if(base > D::size::value)
        n_throw(out_of_range);
    
    return real_impl<T>::template apply<D>(
        x, prec, rounding, scientific, base);
}

/** @} */

}}} // namespaces

#endif // NIC_2FA25AA9B1DFA227_NIC