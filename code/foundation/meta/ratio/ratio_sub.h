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
#ifndef NIC_27429DCBB0C9B65C_NIC
#define NIC_27429DCBB0C9B65C_NIC

#include "ratio_add.h"
#include "ratio_mul.h"

namespace nebula { namespace foundation { namespace meta {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
template <class First, class ... T>
struct ratio_sub_
{
private:
    template <class A, class B>
    struct F {
        using type = typename meta_detail::ratio_add_2_<
            A, 
            typename ratio_mul_<B, ratio<-1,1>>::type>::type;
    };
    
public:
    using type = _for_each<
        seq<T...>,
        F,
        First>;
};

template <class ... T>
using _ratio_sub = typename ratio_sub_<T...>::type;

/** @} */

}}} // namespaces

#endif // NIC_27429DCBB0C9B65C_NIC