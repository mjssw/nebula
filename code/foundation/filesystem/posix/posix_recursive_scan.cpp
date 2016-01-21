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
#include "../config.h"
#ifdef N_FILESYSTEM_posix_nftw

#include "../path.h"
#include "../exception.h"
#include "../recursive_scan.h"
#include "../../scope_exit.h"
#include "../../function.h"
#include "../../math/limits.h"

#if _XOPEN_SOURCE < 500
#   error "nftw is missing."
#endif

#include <ftw.h>

namespace nebula { namespace foundation { namespace filesystem {
//------------------------------------------------------------------------------
exception_ptr g_exc_;
const recursive_scan_callback *g_f_;
size_t g_max_depth_ = math::maximum<size_t>();
//------------------------------------------------------------------------------
static int g_fn_(
    const char *fpath,
    const struct stat *sb,
    int typeflag,
    struct FTW *ftwbuf)
{
    #ifdef _GNU_SOURCE
    try {
        switch(typeflag)
        {
        case FTW_D:
        case FTW_F:
            if(size_t(ftwbuf->level) > g_max_depth_)
                return FTW_SKIP_SUBTREE;
            if(!(*g_f_)(fpath, ftwbuf->level))
                return FTW_STOP;
            break;            
        default: break; // shut up compiler
        }
    } catch(...) {
        try {
            g_exc_ = foundation::current_exception();
        } catch(...) {}
        return FTW_STOP;
    }
    return FTW_CONTINUE;
    #else
    try {
        switch(typeflag)
        {
        case FTW_D:
        case FTW_F:
            if(size_t(ftwbuf->level) > g_max_depth_)
                break;
            if(!(*g_f_)(fpath, ftwbuf->level))
                return -1;
            break;            
        default: break; // shut up compiler
        }
    } catch(...) {
        try {
            g_exc_ = foundation::current_exception();
        } catch(...) {}
        return -1;
    }
    return 0;
    #endif
}
//------------------------------------------------------------------------------
void recursive_scan(
    const path &p,
    const size_t max_depth,
    const recursive_scan_callback &f)
{
    n_scope_exit(&) {
        g_exc_ = nullptr;
        g_f_ = nullptr;
        g_max_depth_ = math::maximum<size_t>();
    };

    g_max_depth_ = max_depth;
    g_f_ = &f;
    
    errno = 0;
    #ifdef _GNU_SOURCE
    const int r = ::nftw(p.c_str(), g_fn_, 1000, FTW_PHYS | FTW_ACTIONRETVAL);
    #else
    const int r = ::nftw(p.c_str(), g_fn_, 1000, FTW_PHYS);
    #endif
    if(g_exc_)
        rethrow_exception(g_exc_);
    else if(r == -1)
    {
        if(errno != 0)
            n_throw(system::system_error)
                << ei_msg_c("nftw() failed.")
                << ei_path(p)
                << system::ei_error_code(system::error_code(
                    errno, system::system_category()));
    }
}
//------------------------------------------------------------------------------
void recursive_scan(
    const path &p, 
    const recursive_scan_callback &f)
{
    recursive_scan(p, math::maximum<size_t>(), f);
}

}}} // namespaces

#endif // N_FILESYSTEM_posix_stat
