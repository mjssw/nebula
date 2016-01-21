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
#include "console.h"

#include "../../async.h"
#include "../../io.h"

namespace nebula { namespace foundation { namespace qlog { namespace sink {
//------------------------------------------------------------------------------
class console_ final : public sink_base
{
public:
    inline void operator () (level lvl, const string &s)
    {
        async::lock(mtx);
        n_scoped_unlock(mtx);
        if(lvl < level::warning) {
            io::write(io::cerr, s.data(), s.size());
            io::put(io::cerr, '\n');
        }
        else {
            io::write(io::cout, s.data(), s.size());
            io::put(io::cout, '\n');
        }
    }
    inline void flush()
    {
        async::lock(mtx);
        n_scoped_unlock(mtx);
        io::flush(io::cout);
    }
    
private:
    async::mutex mtx;
};

//------------------------------------------------------------------------------
intrusive_ptr<sink_base> con;
//------------------------------------------------------------------------------
void init_console()
{
    if(con)
        n_throw(logic_error)
        << ei_msg_c("init_console() has already been called.");
    con = new console_();
}
//------------------------------------------------------------------------------
intrusive_ptr<sink_base> console()
{
    if(con)
        return con;
    n_throw(logic_error)
        << ei_msg_c("Call init_console() first!");
}

}}}} // namespaces
