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
#ifndef NIC_4F20E395CCD194C0_NIC
#define NIC_4F20E395CCD194C0_NIC

#include "sink_base.h"

#include "../../async.h"
#include "../../io.h"

namespace nebula { namespace foundation { namespace qlog { namespace sink {
//------------------------------------------------------------------------------
class file final : public sink_base
{
public:
    inline file(const string &fname, const bool trunc = false)
    : f(fname, trunc)
    {}
    
    inline void operator () (level lvl, const string &s)
    {
        async::lock(mtx);
        n_scoped_unlock(mtx);
        io::write(f, s.data(), s.size());
        io::put(f, '\n');
    }
    inline void flush()
    {
        async::lock(mtx);
        n_scoped_unlock(mtx);
        io::flush(f);
    }
    
private:
    async::mutex mtx;
    io::ofstream_ate f;
};

}}}} // namespaces

#endif // NIC_4F20E395CCD194C0_NIC
