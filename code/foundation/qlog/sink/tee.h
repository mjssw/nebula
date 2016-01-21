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
#ifndef NIC_6624349DD11D446D_NIC
#define NIC_6624349DD11D446D_NIC

#include "sink_base.h"

#include "../../vector.h"

namespace nebula { namespace foundation { namespace qlog { namespace sink {
//------------------------------------------------------------------------------
class tee : public sink_base
{
public:
    template <class ... Sinks>
    inline tee(Sinks && ... s)
    {
        n_static_assert(sizeof ... (s) > 0, "");
        sinks.reserve(sizeof ... (s));
        n_unpack(sinks.emplace_back(foundation::forward<Sinks>(s)));
    }    
    
    inline void operator () (level lvl, const string &s)
    {
        for(auto &x : sinks)
            x->operator () (lvl, s);
    }
    inline void flush()
    {
        for(auto &x : sinks)
            x->flush();
    }

private:
    vector<intrusive_ptr<sink_base>> sinks;
};

}}}} // namespaces

#endif // NIC_6624349DD11D446D_NIC
