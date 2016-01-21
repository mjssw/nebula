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
#ifndef NIC_301724A31BBE0418_NIC
#define NIC_301724A31BBE0418_NIC

#include "config.h"
#include "../chrono.h"

namespace nebula { namespace foundation { namespace filesystem {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
enum class file_type
{
    regular,
    directory,
    symlink,
    block,
    fifo,
    socket,
    character_device,
    unknown
};
//------------------------------------------------------------------------------
/** @internal Defined in file_status.cpp. */
extern const char * n_foundation_dll to_cstr(file_type) noexcept;

//------------------------------------------------------------------------------
using file_permission_type = unsigned;
//------------------------------------------------------------------------------
constexpr file_permission_type user_read = 0400;
constexpr file_permission_type user_write = 0200;
constexpr file_permission_type user_execute = 0100;

constexpr file_permission_type user_all = 0700;

constexpr file_permission_type group_read = 040;
constexpr file_permission_type group_write = 020;
constexpr file_permission_type group_execute = 010;

constexpr file_permission_type group_all = 070;

constexpr file_permission_type other_read = 04;
constexpr file_permission_type other_write = 02;
constexpr file_permission_type other_execute = 01;

constexpr file_permission_type other_all = 07;

constexpr file_permission_type all_all = 0777;

constexpr file_permission_type permissions_unknown = 1000;

//------------------------------------------------------------------------------
using file_time_type = chrono::nanoseconds;

/** @} */

}}}

#endif // NIC_301724A31BBE0418_NIC
