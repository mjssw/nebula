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
#ifndef NIC_B2C7A2E17FE0831B_NIC
#define NIC_B2C7A2E17FE0831B_NIC

#include "digit_codec.h"
#include "../exception.h"
#include "../str.h"
#include "../string.h"
#include "../cstring.h"

namespace nebula { namespace foundation { namespace fmt {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <class T>
struct to_integer_impl
{
    template <class D>
    inline static T apply(
        const char *beg, const char *end, const unsigned base)
    {    
        const char *x = beg;
        
        const bool neg = 
            is_unsigned<T>::value ? false : (*x == '-');

        if(neg) {
            ++x;
            if(x == end)
                n_throw(runtime_error) << ei_msg_c("Invalid format");
        }
        
        T res = D::decode(*x++);
        for( ; x < end; ++x)
        {
            res *= T(base);
            res += T(D::decode(*x));
        }
        
        return neg ? T(-1)*res : res;
    }
};

//------------------------------------------------------------------------------
template <class T, class D = fmt::digit_codec>
inline T to_integer(
    const char *beg, const char *end,
    const unsigned base = 10)
{
    if(base > D::size::value)
        n_throw(out_of_range);
    if(beg == end)
        n_throw(logic_error);
    
    return to_integer_impl<T>::template apply<D>(beg, end, base);
}
//------------------------------------------------------------------------------
template <class T, class D = fmt::digit_codec>
inline T to_integer(
    const char *str,
    const unsigned base = 10)
{
    if(base > D::size::value)
        n_throw(out_of_range);
    if(foundation::strlen(str) == 0)
        n_throw(logic_error);
    
    return to_integer_impl<T>::template apply<D>(
        str, str + foundation::strlen(str), base);
}
//------------------------------------------------------------------------------
template <class T, class D = fmt::digit_codec, class X, class Y>
inline T to_integer(
    const basic_string<char, X, Y> &str,
    const unsigned base = 10)
{
    if(base > D::size::value)
        n_throw(out_of_range);
    if(str.empty())
        n_throw(logic_error);
    
    return to_integer_impl<T>::template apply<D>(str.begin(), str.end(), base);
}
//------------------------------------------------------------------------------
template <class T, class D = fmt::digit_codec, class X>
inline T to_integer(
    const basic_cstring<char, X> &str,
    const unsigned base = 10)
{
    if(base > D::size::value)
        n_throw(out_of_range);
    if(str.empty())
        n_throw(logic_error);
    
    return to_integer_impl<T>::template apply<D>(str.begin(), str.end(), base);
}
//------------------------------------------------------------------------------
template <class T, class D = fmt::digit_codec, class X>
inline T to_integer(
    const basic_cstring<const char, X> &str,
    const unsigned base = 10)
{
    if(base > D::size::value)
        n_throw(out_of_range);
    if(str.empty())
        n_throw(logic_error);
    
    return to_integer_impl<T>::template apply<D>(str.begin(), str.end(), base);
}

/** @} */

}}} // namespaces

#endif // NIC_B2C7A2E17FE0831B_NIC