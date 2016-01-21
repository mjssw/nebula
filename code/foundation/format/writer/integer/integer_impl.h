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
#ifndef NIC_D723934BD06B2F42_NIC
#define NIC_D723934BD06B2F42_NIC

#include "../../tags.h"
#include "../../../io.h"
#include "../../../math/traits/digits.h"
#include "../../../math/traits/is_integer.h"
#include "../../../math/exact_cast.h"
#include "../../../defs.h"
#include "../../../assert.h"
#include "../../../array.h"
#include "../../../range.h"
#include "../../../str.h"
#include "../../../exception.h"

namespace nebula { namespace foundation { namespace fmt {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
namespace integer_detail {
//------------------------------------------------------------------------------
template <class T, class D>
struct pod_integer_writer_
{
    template <class S>
    inline void operator () (S &sink, fout_tag) const
    {                
        using array_t = array<char, math::digits<T>::type::value>;
        array_t buf;
        
        typename array_t::iterator i = buf.begin();    
        
        auto calc_digits = [&](
            /* Unsigned types are usually faster to process. */
            typename make_unsigned<T>::type x_)
        {
            do 
            {
                const T r = x_ % base;
                x_ /= base;
                *i++ = D::encode(r);
            }
            while(x_ > T(0));
        };
        
        if(is_unsigned<T>::value)
        {
            calc_digits(x);
        }
        else
        {
            if(x < T(0))
            {
                calc_digits(x * T(-1));
                *i++ = '-';
            }
            else
            {
                calc_digits(x);
            }
        }
        
        const size_t n = static_cast<size_t>(i - range::begin(buf));
        for(const char c : buf | range::sliced(0, n) | range::reversed)
        {
            io::put(sink, c);
        }
    }
    
    T x;
    typename make_unsigned<T>::type base;
};

} // integer_detail

/** @} */

}}} // namespaces

#endif // NIC_D723934BD06B2F42_NIC