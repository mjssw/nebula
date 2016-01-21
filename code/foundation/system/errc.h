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
#ifndef NIC_BF119F0FCBD9722E_NIC
#define NIC_BF119F0FCBD9722E_NIC

#include "traits.h"
#include "error_code.h"

#include "../cerrno.h"

namespace nebula { namespace foundation {

/** @ingroup Foundation
 * @{
 * */

namespace system {
//------------------------------------------------------------------------------
enum class errc
{
    success                                         = noerr,
    unknown                                         = -1,
    address_family_not_supported                    = EAFNOSUPPORT,
    address_in_use                                  = EADDRINUSE,
    address_not_available                           = EADDRNOTAVAIL,
    already_connected                               = EISCONN,
    argument_list_too_long                          = E2BIG,
    argument_out_of_domain                          = EDOM,
    bad_address                                     = EFAULT,
    bad_file_descriptor                             = EBADF,
    bad_message                                     = EBADMSG,
    broken_pipe                                     = EPIPE,
    connection_aborted                              = ECONNABORTED,
    connection_already_in_progress                  = EALREADY,
    connection_refused                              = ECONNREFUSED,
    connection_reset                                = ECONNRESET,
    cross_device_link                               = EXDEV,
    destination_address_required                    = EDESTADDRREQ,
    device_or_resource_busy                         = EBUSY,
    directory_not_empty                             = ENOTEMPTY,
    executable_format_error                         = ENOEXEC,
    file_exists                                     = EEXIST,
    file_too_large                                  = EFBIG,
    filename_too_long                               = ENAMETOOLONG,
    function_not_supported                          = ENOSYS,
    host_unreachable                                = EHOSTUNREACH,
    identifier_removed                              = EIDRM,
    illegal_byte_sequence                           = EILSEQ,
    inappropriate_io_control_operation              = ENOTTY,
    interrupted                                     = EINTR,
    invalid_argument                                = EINVAL,
    invalid_seek                                    = ESPIPE,
    io_error                                        = EIO,
    is_a_directory                                  = EISDIR,
    message_size                                    = EMSGSIZE,
    network_down                                    = ENETDOWN,
    network_reset                                   = ENETRESET,
    network_unreachable                             = ENETUNREACH,
    no_buffer_space                                 = ENOBUFS,
    no_child_process                                = ECHILD,
    no_link                                         = ENOLINK,
    no_lock_available                               = ENOLCK,
    no_message                                      = ENOMSG,
    no_message_available                            = ENODATA,
    no_protocol_option                              = ENOPROTOOPT,
    no_space_on_device                              = ENOSPC,
    no_stream_resources                             = ENOSR,
    no_such_device                                  = ENODEV,
    no_such_device_or_address                       = ENXIO,
    no_such_file_or_directory                       = ENOENT,
    no_such_process                                 = ESRCH,
    not_a_directory                                 = ENOTDIR,
    not_a_socket                                    = ENOTSOCK,
    not_a_stream                                    = ENOSTR,
    not_connected                                   = ENOTCONN,
    not_enough_memory                               = ENOMEM,
    not_supported                                   = ENOTSUP,
    operation_canceled                              = ECANCELED,
    operation_in_progress                           = EINPROGRESS,
    operation_not_permitted                         = EPERM,
    operation_not_supported                         = EOPNOTSUPP,
    operation_would_block                           = EWOULDBLOCK,
    owner_dead                                      = EOWNERDEAD,
    permission_denied                               = EACCES,
    protocol_error                                  = EPROTO,
    protocol_not_supported                          = EPROTONOSUPPORT,
    read_only_file_system                           = EROFS,
    resource_deadlock_would_occur                   = EDEADLK,
    resource_unavailable_try_again                  = EAGAIN,
    result_out_of_range                             = ERANGE,
    state_not_recoverable                           = ENOTRECOVERABLE,
    stream_timeout                                  = ETIME,
    text_file_busy                                  = ETXTBSY,
    timed_out                                       = ETIMEDOUT,
    too_many_files_open                             = EMFILE,
    too_many_files_open_in_system                   = ENFILE,
    too_many_links                                  = EMLINK,
    too_many_symbolic_link_levels                   = ELOOP,
    value_too_large                                 = EOVERFLOW,
    wrong_protocol_type                             = EPROTOTYPE
};

} // system

}} // namespaces

n_register_error_code_enum(nebula::foundation::system::errc, nebula::foundation::system::generic_category());
n_register_error_condition_enum(nebula::foundation::system::errc, nebula::foundation::system::generic_category());

/** @} */

#endif // NIC_BF119F0FCBD9722E_NIC
