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
#ifndef NIC_5B8C6C5D85FA6A73_NIC
#define NIC_5B8C6C5D85FA6A73_NIC

#include "for_each.h"

namespace nebula { namespace foundation { namespace meta {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
template <class Seq, template <class ...> class F>
struct transform_
{
private:
    using EmptySeq = _clear<Seq>;
    
    template <class A, class B>
    using Func = push_back_<
            A,
            typename F<B>::type>;
        
public:
    using type = _for_each<
        Seq,
        Func,
        EmptySeq>;
};

/** @} */

}}} // namespaces

#endif // NIC_5B8C6C5D85FA6A73_NIC