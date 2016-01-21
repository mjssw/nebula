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
#include "message.h"
#include "../utils/demangle_type_info_name.h"

namespace nebula { namespace foundation {
//------------------------------------------------------------------------------
string diagnostic_information(const exception &e)
{
    io::msink<string> ss;
    const string s = exception_detail::message(e);
    if(e.name())
    {
        fmt::fwrite(ss,
            "== (", 
            fmt::hex(reinterpret_cast<uintptr_t>(
                static_cast<const exception_detail::exception_base *>(&e))),
            ") EXCEPTION: ",
            demangle_type_info_name(e.name()));
    }
    else
    {
        fmt::fwrite(ss,
            "== (", 
            fmt::hex(reinterpret_cast<uintptr_t>(
                static_cast<const exception_detail::exception_base *>(&e))),
            ") EXCEPTION: ",
            demangle_type_info_name(typeid(e).name()));
    }
    if(e.file())
    {
        fmt::fwrite(
            ss,
            fmt::endl,
            "origin: ",
            e.file(),
            '[',
            e.line(),
            ']');
    }
    if(e.func())
    {
        fmt::fwrite(
            ss,
            fmt::endl,
            "function: ",
            e.func());
    }
    if(e.message())
    {
        fmt::fwrite(
            ss,
            fmt::endl,
            e.message());
    }
    const std::exception * se = dynamic_cast<const std::exception *>(&e);
    if(se)
    {
        fmt::fwrite(
            ss,
            fmt::endl,
            "std::exception::what: ",
            se->what());
    }
    if(!s.empty())
        fmt::fwrite(ss, fmt::endl);
    return foundation::move(ss.container().append(s));
}

//------------------------------------------------------------------------------
string diagnostic_information(exception_ptr e)
{
    try
    {
        foundation::rethrow_exception(e);
    }
    catch(const exception &x)
    {
        return diagnostic_information(x);
    }
    catch(const std::exception &x)
    {
        return fmt::to_string(
            "== (", 
            fmt::hex(reinterpret_cast<uintptr_t>(
                static_cast<const std::exception *>(&x))),
            ") STD-EXCEPTION: ",
            demangle_type_info_name(typeid(x).name()),
            fmt::endl,
            "std::exception::what: ", x.what());
    }
    catch(...)
    {
        return "== UNKNOWN-EXCEPTION";
    }
}

}} // namespaces
