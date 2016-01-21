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
#ifndef NIC_85D2B18EDEAC3793_NIC
#define NIC_85D2B18EDEAC3793_NIC

#include "../gcd.h"
#include "../sign.h"
#include "../../defs.h"

namespace nebula { namespace foundation { namespace meta {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
template <intmax_t N, intmax_t D = 1>
struct ratio
{
private:
    using GCD_ = _gcd<intmax_t_<N>, intmax_t_<D>>;
    
public:
    n_static_assert(D != 0, "Division by zero.");
    
    using type = ratio<N, D>;
    
    constexpr static intmax_t num = 
        N 
        * _sign<intmax_t_<D>>::value 
        / GCD_::value;
        
    constexpr static intmax_t den = 
        _abs<intmax_t_<D>>::value 
        / GCD_::value;
};

template <intmax_t N, intmax_t D>
constexpr intmax_t ratio<N, D>::num;

template <intmax_t N, intmax_t D>
constexpr intmax_t ratio<N, D>::den;

//------------------------------------------------------------------------------
using atto =    ratio<1, 1000000000000000000>;
using femto =   ratio<1, 1000000000000000>;
using pico =    ratio<1, 1000000000000>;
using nano =    ratio<1, 1000000000>;
using micro =   ratio<1, 1000000>;
using milli =   ratio<1, 1000>;
using centi =   ratio<1, 100>;
using deci =    ratio<1, 10>;

using deca =    ratio<10, 1>;
using hecto =   ratio<100, 1>;
using kilo =    ratio<1000, 1>;
using mega =    ratio<1000000, 1>;
using giga =    ratio<1000000000, 1>;
using tera =    ratio<1000000000000, 1>;
using peta =    ratio<1000000000000000, 1>;
using exa =     ratio<1000000000000000000, 1>;

/** @} */

}}} // namespaces

#endif // NIC_85D2B18EDEAC3793_NIC