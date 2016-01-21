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
#ifndef NIC_A5857E4765F10D26_NIC
#define NIC_A5857E4765F10D26_NIC

#include "exception/exception.h"
#include "system/errc.h"
#include "system/error_code.h"
#include "exception/message.h"

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{
 */
namespace system {
//------------------------------------------------------------------------------
/** Error in the low level system (operating system, system specific low level
 * C/C++ api).
 * */
class system_error : public virtual runtime_error {};

//------------------------------------------------------------------------------
/** Used to store error_code objects. */
typedef error_info<
    struct _error_code_tag,
    ::nebula::foundation::system::error_code> ei_error_code;
//------------------------------------------------------------------------------
/** Used to store error_condition objects. */
typedef error_info<
    struct _error_condition_tag, 
    ::nebula::foundation::system::error_condition> ei_error_condition;

//------------------------------------------------------------------------------
extern error_code n_foundation_dll errno_code() noexcept;
extern error_condition n_foundation_dll errno_condition() noexcept;
extern ei_error_code n_foundation_dll ei_errno_code() noexcept;
extern ei_error_condition n_foundation_dll ei_errno_condition() noexcept;

} // system

/** @} */

}} // namespaces

namespace nebula { namespace foundation { namespace fmt {
//------------------------------------------------------------------------------
template <>
struct fwrite_impl<system::errc>
{
    template <class Sink>
    inline static void apply (Sink &sink, const system::errc e)
    {
        fmt::fwrite(sink, system::error_condition(e));
    }
};

}}} // namespaces

#endif // NIC_A5857E4765F10D26_NIC
