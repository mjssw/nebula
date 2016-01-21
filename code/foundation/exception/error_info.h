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
#ifndef NIC_3D90C8D7B3BCCCD4_NIC
#define NIC_3D90C8D7B3BCCCD4_NIC

#include "../move.h"
#include "../fwd.h"
#include <typeinfo>

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
namespace exception_detail {
//------------------------------------------------------------------------------
struct error_info_base
{
    inline virtual ~error_info_base() {}
    
    virtual size_t type_size() const noexcept = 0;
    virtual const char *type_name() const noexcept = 0;
    virtual string message() const = 0;
    
private:
    virtual error_info_base *clone() const = 0;
    
    friend class ei_container;
};
//------------------------------------------------------------------------------
} // exception_detail
//------------------------------------------------------------------------------
template <class Tag, class T>
class error_info : public exception_detail::error_info_base
{
public:
    using value_type = T;
    using tag = Tag;
    
    error_info() = default;
    error_info(error_info &) = default;
    error_info(const error_info &) = default;
    error_info(error_info &&) = default;
    
    template <class ... X>
    inline error_info(X && ... x)
    : v(foundation::forward<X>(x)...)
    {}
    
    error_info &operator = (error_info &) = default;
    error_info &operator = (const error_info &) = default;
    error_info &operator = (error_info &&) = default;
    
    inline value_type &value() noexcept { return v; }
    inline const value_type &value() const noexcept { return v; }
    
    inline size_t type_size() const noexcept {
        return sizeof(error_info);
    }
    inline const char *type_name() const noexcept {
        return typeid(error_info).name();
    }
    /** @internal Defined in message.h */
    string message() const;

private:
    inline exception_detail::error_info_base *clone() const
    {
        return new error_info(v);
    }

    value_type v;
};

/** @} */

}} // namespaces

#endif // NIC_3D90C8D7B3BCCCD4_NIC
