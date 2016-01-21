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
#ifndef NIC_BE143CCD92805ED7_NIC
#define NIC_BE143CCD92805ED7_NIC

#include "formatter_base.h"

#include "../../io.h"
#include "../../format.h"
#include "../../chrono.h"

namespace nebula { namespace foundation { namespace qlog { namespace formatter {
//------------------------------------------------------------------------------
template <class Duration = chrono::nanoseconds>
class prepend_all final : public formatter_base
{
public:
    inline prepend_all()
    : beg_(chrono::monotonic_clock::now())
    {}
    
    inline void operator () (level lvl, string &str)
    {        
        str = fmt::to_string(
            "[ ",
            qlog::to_cstr(lvl),
            " | ",
            chrono::duration_cast<Duration>(
                chrono::monotonic_clock::now() - beg_),
            " ] ",
            str);
    }
    
private:
    typename chrono::clock_duration<chrono::monotonic_clock>::type beg_;
};

}}}} // namespaces

#endif // NIC_BE143CCD92805ED7_NIC
