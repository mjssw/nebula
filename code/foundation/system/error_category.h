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
#ifndef NIC_D626FD1575A6C3AC_NIC
#define NIC_D626FD1575A6C3AC_NIC

#include "../dll_interface.h"
#include "../string.h"
#include "../ops.h"
#include "errval.h"

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{
 */
namespace system {
//------------------------------------------------------------------------------
/* Forward decl. needed here. */
class error_code;
class error_condition;
//------------------------------------------------------------------------------
/** */
class n_foundation_dll error_category
{
public:
    inline error_category() noexcept {}
    inline virtual ~error_category() noexcept
    {}

    error_category(const error_category &) = delete;
    error_category &operator = (const error_category &) = delete;

    virtual const char *name() const noexcept = 0;
    virtual string message(errval_t ev) const = 0;
    virtual error_condition default_error_condition(errval_t e) const noexcept;
    virtual bool equivalent(
        errval_t code, const error_condition &condition) const noexcept;
    virtual bool equivalent(
        const error_code &code, errval_t condition) const noexcept;

    inline bool operator == (const error_category &rhs) const noexcept {
        return this == &rhs;
    }
    inline bool operator != (const error_category &rhs) const noexcept {
        return this != &rhs;
    }
    inline bool operator < (const error_category &rhs) const noexcept {
        return less<const error_category *>()(this, &rhs);
    }
};

//------------------------------------------------------------------------------
/** */
extern const error_category & n_foundation_dll generic_category() noexcept;
//------------------------------------------------------------------------------
/** */
extern const error_category & n_foundation_dll system_category() noexcept;

} // system
/** @} */
}} // namespaces

#endif // NIC_D626FD1575A6C3AC_NIC