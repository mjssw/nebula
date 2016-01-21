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
#ifdef N_FILESYSTEM_posix_stat

#include "../file_status.h"
#include "../exception.h"

#define _FILE_OFFSET_BITS 64
#include <sys/stat.h>

namespace nebula { namespace foundation { namespace filesystem {
//------------------------------------------------------------------------------
file_status status(const path &p)
{
    struct stat s;
    const int r = ::stat(p.c_str(), &s);
    
    if(r != 0)
    {
         n_throw(system::system_error)
            << ei_msg_c("stat() failed.")
            << ei_path(p)
            << system::ei_error_code(system::error_code(
                errno, system::system_category()));
    }
    
    file_status fs;
    
    {
        if(S_ISREG(s.st_mode))
        {
            fs.type(file_type::regular);
        }
        else if(S_ISDIR(s.st_mode))
        {
            fs.type(file_type::directory);
        }
        else if(S_ISBLK(s.st_mode))
        {
            fs.type(file_type::block);
        }
        else if(S_ISFIFO(s.st_mode))
        {
            fs.type(file_type::fifo);
        }
        else if(S_ISLNK(s.st_mode))
        {
            fs.type(file_type::symlink);
        }
        else if(S_ISSOCK(s.st_mode))
        {
            fs.type(file_type::socket);
        }
        else if(S_ISCHR(s.st_mode))
        {
            fs.type(file_type::character_device);
        }
        else
            fs.type(file_type::unknown);
    }
    
    n_static_assert(sizeof(s.st_size) == sizeof(long), "");
    fs.size(static_cast<long>(s.st_size));
    
    fs.last_access(
        chrono::to_duration<file_time_type>(s.st_atim));
    fs.last_modification(
        chrono::to_duration<file_time_type>(s.st_mtim));
    fs.last_status_change(
        chrono::to_duration<file_time_type>(s.st_ctim));
    
    fs.permissions(s.st_mode & 0777);
    
    return fs;
}

}}} // namespaces

#endif // N_FILESYSTEM_posix_stat
