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
#include "syslog.h"
#include "../../exception.h"

#ifdef N_HEADER_UNISTD_H

#include <syslog.h>

namespace nebula { namespace foundation { namespace qlog { namespace sink {
//------------------------------------------------------------------------------
class syslog_ final : public sink_base
{
public:    
    inline void operator () (level lvl, const string &s)
    {
        int pri;
        
        switch(lvl)
        {
        case level::fatal:      pri = LOG_EMERG; break;
        case level::alert:      pri = LOG_ALERT; break;
        case level::critical:   pri = LOG_CRIT; break;
        case level::error:      pri = LOG_ERR; break;
        case level::warning:    pri = LOG_WARNING; break;
        case level::notice:     pri = LOG_NOTICE; break;
        case level::info:       pri = LOG_INFO; break;
        case level::debug:      pri = LOG_DEBUG; break;
        default:                pri = LOG_DEBUG; break;
        }
        
        ::syslog(pri, "%s", s.c_str());
    }
};

//------------------------------------------------------------------------------
string sl_ident;
intrusive_ptr<sink_base> sl_instance;
//------------------------------------------------------------------------------
void init_syslog(const string &s)
{
    if(sl_instance)
        n_throw(logic_error) 
        << ei_msg_c("init_syslog() has already been called.");
    
    sl_ident = s;
    ::openlog(
        sl_ident.empty() ? nullptr : sl_ident.c_str(),
        LOG_PID,
        LOG_USER);
    sl_instance = new syslog_();
}
//------------------------------------------------------------------------------
intrusive_ptr<sink_base> syslog()
{
    if(sl_instance)
        return sl_instance;
    n_throw(logic_error)
        << ei_msg_c("Call init_syslog() first!");
}

}}}} // namespaces

#else
#   error "Implement Me!"
#endif
