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
/** @file enum_utils.h
 * This file contains a collection of simple converters from an error
 * enumeration to a simple static cstr. Extra file because this is
 * a huge ugly pile of generated code.
 * */
#ifndef NIC_90B955A50D8A58B4_NIC
#define NIC_90B955A50D8A58B4_NIC

#include "errc.h"

namespace nebula { namespace foundation {

/** @ingroup Foundation
 * @{
 * */
namespace system { namespace detail {
//------------------------------------------------------------------------------
/** @ingroup Foundation
 * @internal Simple function to form a basic message from an errc input.
 * We use this function for two reasons. First std::strerror() isn't thread
 * safe and second, the supplied error message does not need to be userfriendly,
 * but instead just be a hint for the programmer.
 */
inline const char *to_cstr(const errc e) noexcept {
    switch(e)
    {
    case errc::success: return "errc::success";
    case errc::unknown: return "errc::unknown";
    case errc::address_family_not_supported: return "errc::address_family_not_supported";
    case errc::address_in_use: return "errc::address_in_use";
    case errc::address_not_available: return "errc::address_not_available";
    case errc::already_connected: return "errc::already_connected";
    case errc::argument_list_too_long: return "errc::argument_list_too_long";
    case errc::argument_out_of_domain: return "errc::argument_out_of_domain";
    case errc::bad_address: return "errc::bad_address";
    case errc::bad_file_descriptor: return "errc::bad_file_descriptor";
    case errc::bad_message: return "errc::bad_message";
    case errc::broken_pipe: return "errc::broken_pipe";
    case errc::connection_aborted: return "errc::connection_aborted";
    case errc::connection_already_in_progress: return "errc::connection_already_in_progress";
    case errc::connection_refused: return "errc::connection_refused";
    case errc::connection_reset: return "errc::connection_reset";
    case errc::cross_device_link: return "errc::cross_device_link";
    case errc::destination_address_required: return "errc::destination_address_required";
    case errc::device_or_resource_busy: return "errc::device_or_resource_busy";
    case errc::directory_not_empty: return "errc::directory_not_empty";
    case errc::executable_format_error: return "errc::executable_format_error";
    case errc::file_exists: return "errc::file_exists";
    case errc::file_too_large: return "errc::file_too_large";
    case errc::filename_too_long: return "errc::filename_too_long";
    case errc::function_not_supported: return "errc::function_not_supported";
    case errc::host_unreachable: return "errc::host_unreachable";
    case errc::identifier_removed: return "errc::identifier_removed";
    case errc::illegal_byte_sequence: return "errc::illegal_byte_sequence";
    case errc::inappropriate_io_control_operation: return "errc::inappropriate_io_control_operation";
    case errc::interrupted: return "errc::interrupted";
    case errc::invalid_argument: return "errc::invalid_argument";
    case errc::invalid_seek: return "errc::invalid_seek";
    case errc::io_error: return "errc::io_error";
    case errc::is_a_directory: return "errc::is_a_directory";
    case errc::message_size: return "errc::message_size";
    case errc::network_down: return "errc::network_down";
    case errc::network_reset: return "errc::network_reset";
    case errc::network_unreachable: return "errc::network_unreachable";
    case errc::no_buffer_space: return "errc::no_buffer_space";
    case errc::no_child_process: return "errc::no_child_process";
    case errc::no_link: return "errc::no_link";
    case errc::no_lock_available: return "errc::no_lock_available";
    case errc::no_message: return "errc::no_message";
    case errc::no_message_available: return "errc::no_message_available";
    case errc::no_protocol_option: return "errc::no_protocol_option";
    case errc::no_space_on_device: return "errc::no_space_on_device";
    case errc::no_stream_resources: return "errc::no_stream_resources";
    case errc::no_such_device: return "errc::no_such_device";
    case errc::no_such_device_or_address: return "errc::no_such_device_or_address";
    case errc::no_such_file_or_directory: return "errc::no_such_file_or_directory";
    case errc::no_such_process: return "errc::no_such_process";
    case errc::not_a_directory: return "errc::not_a_directory";
    case errc::not_a_socket: return "errc::not_a_socket";
    case errc::not_a_stream: return "errc::not_a_stream";
    case errc::not_connected: return "errc::not_connected";
    case errc::not_enough_memory: return "errc::not_enough_memory";
    case errc::not_supported: return "errc::not_supported";
    case errc::operation_canceled: return "errc::operation_canceled";
    case errc::operation_in_progress: return "errc::operation_in_progress";
    case errc::operation_not_permitted: return "errc::operation_not_permitted";
#    ifndef N_OS_LINUX // Colliding values
    case errc::operation_not_supported: return "errc::operation_not_supported";
#    endif
    case errc::operation_would_block: return "errc::operation_would_block";
    case errc::owner_dead: return "errc::owner_dead";
    case errc::permission_denied: return "errc::permission_denied";
    case errc::protocol_error: return "errc::protocol_error";
    case errc::protocol_not_supported: return "errc::protocol_not_supported";
    case errc::read_only_file_system: return "errc::read_only_file_system";
    case errc::resource_deadlock_would_occur: return "errc::resource_deadlock_would_occur";
#    ifndef N_OS_LINUX // Colliding values
    case errc::resource_unavailable_try_again: return "errc::resource_unavailable_try_again";
#    endif
    case errc::result_out_of_range: return "errc::result_out_of_range";
    case errc::state_not_recoverable: return "errc::state_not_recoverable";
    case errc::stream_timeout: return "errc::stream_timeout";
    case errc::text_file_busy: return "errc::text_file_busy";
    case errc::timed_out: return "errc::timed_out";
    case errc::too_many_files_open: return "errc::too_many_files_open";
    case errc::too_many_files_open_in_system: return "errc::too_many_files_open_in_system";
    case errc::too_many_links: return "errc::too_many_links";
    case errc::too_many_symbolic_link_levels: return "errc::too_many_symbolic_link_levels";
    case errc::value_too_large: return "errc::value_too_large";
    case errc::wrong_protocol_type: return "errc::wrong_protocol_type";
    default: return "errc::?";
    }
}
//------------------------------------------------------------------------------
inline errc to_errc(const errval_t e) noexcept {
    switch(e)
    {
    case static_cast<errval_t>(errc::success): return errc::success;
    // case static_cast<errval_t>(errc::unknown): return errc::unknown;
    case static_cast<errval_t>(errc::address_family_not_supported): return errc::address_family_not_supported;
    case static_cast<errval_t>(errc::address_in_use): return errc::address_in_use;
    case static_cast<errval_t>(errc::address_not_available): return errc::address_not_available;
    case static_cast<errval_t>(errc::already_connected): return errc::already_connected;
    case static_cast<errval_t>(errc::argument_list_too_long): return errc::argument_list_too_long;
    case static_cast<errval_t>(errc::argument_out_of_domain): return errc::argument_out_of_domain;
    case static_cast<errval_t>(errc::bad_address): return errc::bad_address;
    case static_cast<errval_t>(errc::bad_file_descriptor): return errc::bad_file_descriptor;
    case static_cast<errval_t>(errc::bad_message): return errc::bad_message;
    case static_cast<errval_t>(errc::broken_pipe): return errc::broken_pipe;
    case static_cast<errval_t>(errc::connection_aborted): return errc::connection_aborted;
    case static_cast<errval_t>(errc::connection_already_in_progress): return errc::connection_already_in_progress;
    case static_cast<errval_t>(errc::connection_refused): return errc::connection_refused;
    case static_cast<errval_t>(errc::connection_reset): return errc::connection_reset;
    case static_cast<errval_t>(errc::cross_device_link): return errc::cross_device_link;
    case static_cast<errval_t>(errc::destination_address_required): return errc::destination_address_required;
    case static_cast<errval_t>(errc::device_or_resource_busy): return errc::device_or_resource_busy;
    case static_cast<errval_t>(errc::directory_not_empty): return errc::directory_not_empty;
    case static_cast<errval_t>(errc::executable_format_error): return errc::executable_format_error;
    case static_cast<errval_t>(errc::file_exists): return errc::file_exists;
    case static_cast<errval_t>(errc::file_too_large): return errc::file_too_large;
    case static_cast<errval_t>(errc::filename_too_long): return errc::filename_too_long;
    case static_cast<errval_t>(errc::function_not_supported): return errc::function_not_supported;
    case static_cast<errval_t>(errc::host_unreachable): return errc::host_unreachable;
    case static_cast<errval_t>(errc::identifier_removed): return errc::identifier_removed;
    case static_cast<errval_t>(errc::illegal_byte_sequence): return errc::illegal_byte_sequence;
    case static_cast<errval_t>(errc::inappropriate_io_control_operation): return errc::inappropriate_io_control_operation;
    case static_cast<errval_t>(errc::interrupted): return errc::interrupted;
    case static_cast<errval_t>(errc::invalid_argument): return errc::invalid_argument;
    case static_cast<errval_t>(errc::invalid_seek): return errc::invalid_seek;
    case static_cast<errval_t>(errc::io_error): return errc::io_error;
    case static_cast<errval_t>(errc::is_a_directory): return errc::is_a_directory;
    case static_cast<errval_t>(errc::message_size): return errc::message_size;
    case static_cast<errval_t>(errc::network_down): return errc::network_down;
    case static_cast<errval_t>(errc::network_reset): return errc::network_reset;
    case static_cast<errval_t>(errc::network_unreachable): return errc::network_unreachable;
    case static_cast<errval_t>(errc::no_buffer_space): return errc::no_buffer_space;
    case static_cast<errval_t>(errc::no_child_process): return errc::no_child_process;
    case static_cast<errval_t>(errc::no_link): return errc::no_link;
    case static_cast<errval_t>(errc::no_lock_available): return errc::no_lock_available;
    case static_cast<errval_t>(errc::no_message): return errc::no_message;
    case static_cast<errval_t>(errc::no_message_available): return errc::no_message_available;
    case static_cast<errval_t>(errc::no_protocol_option): return errc::no_protocol_option;
    case static_cast<errval_t>(errc::no_space_on_device): return errc::no_space_on_device;
    case static_cast<errval_t>(errc::no_stream_resources): return errc::no_stream_resources;
    case static_cast<errval_t>(errc::no_such_device): return errc::no_such_device;
    case static_cast<errval_t>(errc::no_such_device_or_address): return errc::no_such_device_or_address;
    case static_cast<errval_t>(errc::no_such_file_or_directory): return errc::no_such_file_or_directory;
    case static_cast<errval_t>(errc::no_such_process): return errc::no_such_process;
    case static_cast<errval_t>(errc::not_a_directory): return errc::not_a_directory;
    case static_cast<errval_t>(errc::not_a_socket): return errc::not_a_socket;
    case static_cast<errval_t>(errc::not_a_stream): return errc::not_a_stream;
    case static_cast<errval_t>(errc::not_connected): return errc::not_connected;
    case static_cast<errval_t>(errc::not_enough_memory): return errc::not_enough_memory;
    case static_cast<errval_t>(errc::not_supported): return errc::not_supported;
    case static_cast<errval_t>(errc::operation_canceled): return errc::operation_canceled;
    case static_cast<errval_t>(errc::operation_in_progress): return errc::operation_in_progress;
    case static_cast<errval_t>(errc::operation_not_permitted): return errc::operation_not_permitted;
#   ifndef N_OS_LINUX // Colliding values
    case static_cast<errval_t>(errc::operation_not_supported): return errc::operation_not_supported;
#   endif
    case static_cast<errval_t>(errc::operation_would_block): return errc::operation_would_block;
    case static_cast<errval_t>(errc::owner_dead): return errc::owner_dead;
    case static_cast<errval_t>(errc::permission_denied): return errc::permission_denied;
    case static_cast<errval_t>(errc::protocol_error): return errc::protocol_error;
    case static_cast<errval_t>(errc::protocol_not_supported): return errc::protocol_not_supported;
    case static_cast<errval_t>(errc::read_only_file_system): return errc::read_only_file_system;
    case static_cast<errval_t>(errc::resource_deadlock_would_occur): return errc::resource_deadlock_would_occur;
#   ifndef N_OS_LINUX // Colliding values
    case static_cast<errval_t>(errc::resource_unavailable_try_again): return errc::resource_unavailable_try_again;
#   endif
    case static_cast<errval_t>(errc::result_out_of_range): return errc::result_out_of_range;
    case static_cast<errval_t>(errc::state_not_recoverable): return errc::state_not_recoverable;
    case static_cast<errval_t>(errc::stream_timeout): return errc::stream_timeout;
    case static_cast<errval_t>(errc::text_file_busy): return errc::text_file_busy;
    case static_cast<errval_t>(errc::timed_out): return errc::timed_out;
    case static_cast<errval_t>(errc::too_many_files_open): return errc::too_many_files_open;
    case static_cast<errval_t>(errc::too_many_files_open_in_system): return errc::too_many_files_open_in_system;
    case static_cast<errval_t>(errc::too_many_links): return errc::too_many_links;
    case static_cast<errval_t>(errc::too_many_symbolic_link_levels): return errc::too_many_symbolic_link_levels;
    case static_cast<errval_t>(errc::value_too_large): return errc::value_too_large;
    case static_cast<errval_t>(errc::wrong_protocol_type): return errc::wrong_protocol_type;
    default: return errc::unknown;
    }
}

} // detail

//------------------------------------------------------------------------------

/* Below is some compile time checking to ensure that the 'unknown' error value isn't already in use. */

n_static_assert(errc::success != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::address_family_not_supported != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::address_in_use != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::address_not_available != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::already_connected != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::argument_list_too_long != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::argument_out_of_domain != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::bad_address != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::bad_file_descriptor != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::bad_message != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::broken_pipe != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::connection_aborted != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::connection_already_in_progress != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::connection_refused != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::connection_reset != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::cross_device_link != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::destination_address_required != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::device_or_resource_busy != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::directory_not_empty != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::executable_format_error != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::file_exists != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::file_too_large != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::filename_too_long != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::function_not_supported != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::host_unreachable != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::identifier_removed != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::illegal_byte_sequence != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::inappropriate_io_control_operation != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::interrupted != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::invalid_argument != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::invalid_seek != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::io_error != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::is_a_directory != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::message_size != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::network_down != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::network_reset != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::network_unreachable != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::no_buffer_space != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::no_child_process != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::no_link != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::no_lock_available != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::no_message != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::no_message_available != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::no_protocol_option != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::no_space_on_device != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::no_stream_resources != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::no_such_device != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::no_such_device_or_address != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::no_such_file_or_directory != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::no_such_process != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::not_a_directory != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::not_a_socket != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::not_a_stream != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::not_connected != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::not_enough_memory != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::not_supported != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::operation_canceled != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::operation_in_progress != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::operation_not_permitted != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::operation_not_supported != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::operation_would_block != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::owner_dead != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::permission_denied != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::protocol_error != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::protocol_not_supported != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::read_only_file_system != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::resource_deadlock_would_occur != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::resource_unavailable_try_again != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::result_out_of_range != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::state_not_recoverable != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::stream_timeout != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::text_file_busy != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::timed_out != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::too_many_files_open != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::too_many_files_open_in_system != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::too_many_links != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::too_many_symbolic_link_levels != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::value_too_large != errc::unknown, "errc::unkown maps to an actual error code.");
n_static_assert(errc::wrong_protocol_type != errc::unknown, "errc::unkown maps to an actual error code.");

} // system

/** @} */

}} // namespaces

#endif // NIC_90B955A50D8A58B4_NIC