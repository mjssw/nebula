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
#ifndef NIC_06D2105B025C4D89_NIC
#define NIC_06D2105B025C4D89_NIC

#include "sink_base.h"

#include "../../move.h"
#include "../../call_traits.h"

namespace nebula { namespace foundation { namespace qlog { namespace sink {
//------------------------------------------------------------------------------
template <class F>
class function final : public sink_base
{
public:
    template <class F_>
    inline function(F_ &&f)
    : func(foundation::forward<F_>(f))
    {}
    
    inline void operator () (level lvl, const string &s)
    {
        func(lvl, s);
    }
    
private:
    F func;
};
//------------------------------------------------------------------------------
template <class F>
inline intrusive_ptr<function<typename ctraits::value<F>::type>>
capture(F &&f)
{
    return new function<
        typename ctraits::value<F>::type>(foundation::forward<F>(f));
}

}}}} // namespaces

#endif // NIC_06D2105B025C4D89_NIC
