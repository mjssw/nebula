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
#ifndef NIC_6BF9891D75DCE367_NIC
#define NIC_6BF9891D75DCE367_NIC

// Provide this here even though it is not directly neede by this file.
#include "../utils/tag.h"

namespace nebula { namespace foundation { namespace io {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
/** We can read from the stream. */
struct in_tag {};
/** A peekable stream, i.e. we can read a single character without advancing
 * the stream position.
 * */
struct peek_tag {};
/** The ability to put a character back into the stream after it has been
 * exctracted using get(). */
struct unget_tag {};
/** The stream is writable. */
struct out_tag {};
/** The stream can be flushed, i.e. data written to the stream is forwarded
 * to the actual device and thus emptying the stream's internal buffers. 
 * If this succeeds it is guaranteed that the data has been written to
 * the underlying device. 
 * */
struct flush_tag {};
/** The stream does not perform buffering, i.e. any data written to the stream
 * is directly forwarded to the underlying device.
 * */
struct direct_tag {};
/** Written data can be made available to be read from the stream after
 * synchronizing the input/output facilities. Direct streams support this
 * intrinsically.
 * */
struct sync_tag {};
/** When resetting the reading position of the stream the input position
 * updates to the exact same location, and vice versa (most filestreams).
 * */
struct shared_seq_tag {};

struct in_seek_cur_tag {};
struct in_seek_beg_tag {};
struct in_seek_end_tag {};

struct out_seek_cur_tag {};
struct out_seek_beg_tag {};
struct out_seek_end_tag {};

//------------------------------------------------------------------------------
// Below types are for convenience - combining several tags.
//------------------------------------------------------------------------------
struct in_seek_tag : in_seek_cur_tag, in_seek_beg_tag, in_seek_end_tag {};
struct out_seek_tag : out_seek_cur_tag, out_seek_beg_tag, out_seek_end_tag {};

struct seek_cur_tag : in_seek_cur_tag, out_seek_cur_tag {};
struct seek_beg_tag : in_seek_beg_tag, out_seek_beg_tag {};
struct seek_end_tag : in_seek_end_tag, out_seek_end_tag {};

struct seek_tag : seek_cur_tag, seek_beg_tag, seek_end_tag {};

/** @} */

}}} // namespaces

#endif // NIC_6BF9891D75DCE367_NIC
