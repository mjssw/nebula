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
#ifndef NIC_6198FF1D881E7A86_NIC
#define NIC_6198FF1D881E7A86_NIC

#include "tags.h"

namespace nebula { namespace foundation { namespace io {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class Stream>
struct stream_size {
    typedef typename Stream::stream_size type;
};
//------------------------------------------------------------------------------
template <class Stream>
struct stream_offset {
    typedef typename Stream::stream_offset type;
};
//------------------------------------------------------------------------------
template <class Stream>
struct stream_position {
    typedef typename Stream::stream_position type;
};
//------------------------------------------------------------------------------
template <class Stream>
struct stream_category {
    typedef typename Stream::stream_category type;
};

//------------------------------------------------------------------------------
n_meta_alias(stream_size);
n_meta_alias(stream_offset);
n_meta_alias(stream_position);
n_meta_alias(stream_category);

//------------------------------------------------------------------------------
/* Below are simple query metafunctions for the stream_category, 
 * which must not be specialized! */
//------------------------------------------------------------------------------
template <class Stream>
struct has_read
: public has_tag<
    typename stream_category<Stream>::type,
    in_tag>
{};
//------------------------------------------------------------------------------
template <class Stream>
struct has_write
: public has_tag<
    typename stream_category<Stream>::type,
    out_tag>
{};
//------------------------------------------------------------------------------
template <class Stream>
struct has_put
: public has_write<Stream>
{};
//------------------------------------------------------------------------------
template <class Stream>
struct has_unget
: public has_tag<
    typename stream_category<Stream>::type,
    unget_tag>
{};
//------------------------------------------------------------------------------
template <class Stream>
struct has_peek
: public has_tag<
    typename stream_category<Stream>::type,
    peek_tag>
{};
//------------------------------------------------------------------------------
template <class Stream>
struct has_flush
: public has_tag<
    typename stream_category<Stream>::type,
    flush_tag>
{};
//------------------------------------------------------------------------------
template <class Stream>
struct is_direct
: public has_tag<
    typename stream_category<Stream>::type,
    direct_tag>
{};
//------------------------------------------------------------------------------
template <class Stream>
struct has_sync
: public has_tag<
    typename stream_category<Stream>::type,
    sync_tag>
{};
//------------------------------------------------------------------------------
template <class Stream>
struct has_shared_seeking
: public has_tag<
    typename stream_category<Stream>::type,
    shared_seq_tag>
{};
//------------------------------------------------------------------------------
template <class Stream>
struct has_seekg_beg
: public has_tag<
    typename stream_category<Stream>::type,
    in_seek_beg_tag>
{};
//------------------------------------------------------------------------------
template <class Stream>
struct has_seekg_cur
: public has_tag<
    typename stream_category<Stream>::type,
    in_seek_cur_tag>
{};
//------------------------------------------------------------------------------
template <class Stream>
struct has_seekg_end
: public has_tag<
    typename stream_category<Stream>::type,
    in_seek_end_tag>
{};
//------------------------------------------------------------------------------
template <class Stream>
struct has_seekp_beg
: public has_tag<
    typename stream_category<Stream>::type,
    out_seek_beg_tag>
{};
//------------------------------------------------------------------------------
template <class Stream>
struct has_seekp_cur
: public has_tag<
    typename stream_category<Stream>::type,
    out_seek_cur_tag>
{};
//------------------------------------------------------------------------------
template <class Stream>
struct has_seekp_end
: public has_tag<
    typename stream_category<Stream>::type,
    out_seek_end_tag>
{};

/** @} */

}}} // namespaces

#endif // NIC_6198FF1D881E7A86_NIC
