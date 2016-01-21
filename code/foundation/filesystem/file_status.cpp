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
#include "file_status.h"

namespace nebula { namespace foundation { namespace filesystem {
//------------------------------------------------------------------------------
const char *to_cstr(file_type t) noexcept
{
    switch(t)
    {
    case file_type::regular:
        return "regular";
    case file_type::directory:
        return "directory";
    case file_type::symlink:
        return "symlink";
    case file_type::block:
        return "block";
    case file_type::fifo:
        return "fifo";
    case file_type::socket:
        return "socket";
    case file_type::character_device:
        return "character_device";
    default:
        return "unknown";
    }
}
//------------------------------------------------------------------------------
string pretty_permissions(const file_status &fs)
{
    string s;    
    s.reserve(9);
    
    const file_permission_type mode = fs.permissions();
    
    if((mode & permissions_unknown) == permissions_unknown)
        return "---------";
    
    // user permission
    if((mode & user_read) == user_read)
        s += 'r';
    else 
        s += '-';
    
    if((mode & user_write) == user_write) 
        s += 'w';
    else 
        s += '-';
    
    if((mode & user_execute) == user_execute) 
        s += 'x';
    else
        s += '-';
    
    // group permission
    if((mode & group_read) == group_read) 
        s += 'r';
    else 
        s += '-';
    
    if((mode & group_write) == group_write)
        s += 'w';
    else
        s += '-';
    
    if((mode & group_execute) == group_execute) 
        s += 'x';
    else 
        s += '-';
    
    // other permission
    if((mode & other_read) == other_read) 
        s += 'r';
    else 
        s += '-';
    
    if((mode & other_write) == other_write) 
        s += 'w';
    else s += '-';
    
    if((mode & other_execute) == other_execute)
        s += 'x';
    else
        s += '-';
    
    return s;
}

}}}
