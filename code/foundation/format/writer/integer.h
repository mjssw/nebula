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
#ifndef NIC_A4B28AA9B1D6F027_NIC
#define NIC_A4B28AA9B1D6F027_NIC

#include "integer/integer_impl.h"
#include "../digit_codec.h"

namespace nebula { namespace foundation { namespace fmt {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <class T>
struct integer_impl
{    
private:
    using unsigned_type = typename make_unsigned<T>::type;
    
public:
    template <class D>
    inline static integer_detail::pod_integer_writer_<T, D>
    apply(const T x, const unsigned base)
    {
        n_static_assert(is_arithmetic<T>::type::value, "");
        n_static_assert(is_pod<T>::type::value, "");
        n_static_assert(math::is_integer<T>::type::value, "");
        
        math::require_exact_cast<unsigned_type>(base);
        
        return integer_detail::pod_integer_writer_<T, D>{
            x, unsigned_type(base)};
    }
};

//------------------------------------------------------------------------------
template <class D = digit_codec, class T>
inline auto integer(
    const T &x,
    const unsigned base = 10)
-> decltype(integer_impl<T>::template apply<D>(x, base))
{
    if(base > D::size::value)
        n_throw(out_of_range);
    
    return integer_impl<T>::template apply<D>(x, base);
}

/** @} */

}}} // namespaces

#endif // NIC_A4B28AA9B1D6F027_NIC