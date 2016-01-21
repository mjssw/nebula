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
#ifndef NIC_A13554ECBE29B217_NIC
#define NIC_A13554ECBE29B217_NIC

#include "../config.h"

#ifdef N_API_WINDOWS

#include "errc.h"

#include <winerror.h>

namespace nebula { namespace foundation { namespace system {
/** @ingroup Foundation
 * @{
 * */
namespace detail {
//------------------------------------------------------------------------------
/** This function is responsible for mapping a windows specific error to 
 * standard error list errc. If there is no correspondance of the error code
 * in question this function returns errc::unknown. This function can be 
 * modified to add more windows errors to the decode table.
 * @note If you enter new error translations please make sure to keep the
 * alphabetic order.
 * @return Valid errc if the windows error was translated successfully, 
 * otherwise errc::unknown.
 * @throw nothing
 * @todo Any idea how to automatically generate a decoding table?
 * */
inline errc map_windows_error(const errval_t e) noexcept
{
    switch(e)
    {
    /* ---------------------------------------------------------------------- */
    /* ERROR_ */
    /* ---------------------------------------------------------------------- */
    case ERROR_ACCESS_DENIED: return errc::permission_denied;
    case ERROR_ALREADY_EXISTS: return errc::file_exists;
    case ERROR_BAD_UNIT: return errc::no_such_device;
    case ERROR_BUFFER_OVERFLOW: return  errc::filename_too_long;
    case ERROR_BUSY: return errc::device_or_resource_busy;
    case ERROR_BUSY_DRIVE: return errc::device_or_resource_busy;
    case ERROR_CANNOT_MAKE: return errc::permission_denied;
    case ERROR_CANTOPEN: return errc::io_error;
    case ERROR_CANTREAD: return errc::io_error;
    case ERROR_CANTWRITE: return errc::io_error;
    case ERROR_CURRENT_DIRECTORY: return errc::permission_denied;
    case ERROR_DEV_NOT_EXIST: return errc::no_such_device;
    case ERROR_DEVICE_IN_USE: return errc::device_or_resource_busy;
    case ERROR_DIR_NOT_EMPTY: return errc::directory_not_empty;
    case ERROR_DIRECTORY: return errc::invalid_argument;
    case ERROR_DISK_FULL: return errc::no_space_on_device;
    case ERROR_FILE_EXISTS: return errc::file_exists;
    case ERROR_FILE_NOT_FOUND: return errc::no_such_file_or_directory;
    case ERROR_HANDLE_DISK_FULL: return errc::no_space_on_device;
    case ERROR_INVALID_ACCESS: return errc::permission_denied;
    case ERROR_INVALID_DRIVE: return errc::no_such_device;
    case ERROR_INVALID_FUNCTION: return errc::function_not_supported;
    case ERROR_INVALID_HANDLE: return errc::invalid_argument;
    case ERROR_INVALID_NAME: return errc::invalid_argument;
    case ERROR_LOCK_VIOLATION: return errc::no_lock_available;
    case ERROR_LOCKED: return errc::no_lock_available;
    case ERROR_NEGATIVE_SEEK: return errc::invalid_argument;
    case ERROR_NOACCESS: return errc::permission_denied;
    case ERROR_NOT_ENOUGH_MEMORY: return errc::not_enough_memory;
    case ERROR_NOT_READY: return errc::resource_unavailable_try_again;
    case ERROR_NOT_SAME_DEVICE: return errc::cross_device_link;
    case ERROR_OPEN_FAILED: return errc::io_error;
    case ERROR_OPEN_FILES: return errc::device_or_resource_busy;
    case ERROR_OPERATION_ABORTED: return errc::operation_canceled;
    case ERROR_OUTOFMEMORY: return errc::not_enough_memory;
    case ERROR_PATH_NOT_FOUND: return errc::no_such_file_or_directory;
    case ERROR_READ_FAULT: return errc::io_error;
    case ERROR_RETRY: return errc::resource_unavailable_try_again;
    case ERROR_SEEK: return errc::io_error;
    case ERROR_SHARING_VIOLATION: return errc::permission_denied;
    case ERROR_TOO_MANY_OPEN_FILES: return errc::too_many_files_open;
    case ERROR_WRITE_FAULT: return errc::io_error;
    case ERROR_WRITE_PROTECT: return errc::permission_denied;

    /* ---------------------------------------------------------------------- */
    /* WSAE */
    /* ---------------------------------------------------------------------- */
    case WSAEACCES: return errc::permission_denied;
    case WSAEADDRINUSE: return errc::address_in_use;
    case WSAEADDRNOTAVAIL: return errc::address_not_available;
    case WSAEAFNOSUPPORT: return errc::address_family_not_supported;
    case WSAEALREADY: return errc::connection_already_in_progress;
    case WSAEBADF: return errc::bad_file_descriptor;
    case WSAECONNABORTED: return errc::connection_aborted;
    case WSAECONNREFUSED: return errc::connection_refused;
    case WSAECONNRESET: return errc::connection_reset;
    case WSAEDESTADDRREQ: return errc::destination_address_required;
    case WSAEFAULT: return errc::bad_address;
    case WSAEHOSTUNREACH: return errc::host_unreachable;
    case WSAEINPROGRESS: return errc::operation_in_progress;
    case WSAEINTR: return errc::interrupted;
    case WSAEINVAL: return errc::invalid_argument;
    case WSAEISCONN: return errc::already_connected;
    case WSAEMFILE: return errc::too_many_files_open;
    case WSAEMSGSIZE: return errc::message_size;
    case WSAENAMETOOLONG: return errc::filename_too_long;
    case WSAENETDOWN: return errc::network_down;
    case WSAENETRESET: return errc::network_reset;
    case WSAENETUNREACH: return errc::network_unreachable;
    case WSAENOBUFS: return errc::no_buffer_space;
    case WSAENOPROTOOPT: return errc::no_protocol_option;
    case WSAENOTCONN: return errc::not_connected;
    case WSAENOTSOCK: return errc::not_a_socket;
    case WSAEOPNOTSUPP: return errc::operation_not_supported;
    case WSAEPROTONOSUPPORT: return errc::protocol_not_supported;
    case WSAEPROTOTYPE: return errc::wrong_protocol_type;
    case WSAETIMEDOUT: return errc::timed_out;
    case WSAEWOULDBLOCK: return errc::operation_would_block;
    }

    /* Couldn't map the error. */
    return errc::unknown;
}

} // detail

/** @} */

}}} // namespaces

#endif // N_API_WINDOWS

#endif // NIC_A13554ECBE29B217_NIC