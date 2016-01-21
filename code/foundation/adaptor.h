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
#ifndef NIC_9CFC33DAB78AD325_NIC
#define NIC_9CFC33DAB78AD325_NIC

#include "type_traits.h"

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{
 */
namespace adaptor_detail {
//------------------------------------------------------------------------------
template <class T>
struct is_adaptor_helper {
private:
    typedef char yes[1];
    typedef char no[2];
    template <class X>
    static yes &_test(typename X::adaptor_id_ *);
    template <class X>
    static no &_test(...);

public:
    constexpr static bool value = sizeof(_test<T>(0)) == sizeof(yes);
};
} // adaptor_detail
//------------------------------------------------------------------------------
template <class T>
struct is_adaptor : public integral_constant<
    bool,
    adaptor_detail::is_adaptor_helper<typename remove_const<T>::type>::value
>
{};
//------------------------------------------------------------------------------
/** */
template <class T, bool IsAdaptor = is_adaptor<T>::value>
class adaptor_base
{
public:    
    struct adaptor_id_ {};
    
    using adaptee_type = typename remove_const<T>::type;
    
    adaptor_base(adaptor_base &) = default;
    adaptor_base(const adaptor_base &) = default;
    adaptor_base(adaptor_base &&) = default;
    
    inline adaptor_base(T &x) noexcept
    : subj(&x)
    {}
    
    adaptor_base &operator = (const adaptor_base &rhs) = default;
    adaptor_base &operator = (adaptor_base &&rhs) = default;
    
    inline T &adaptee() noexcept {
        return *subj;
    }
    inline const T &adaptee() const noexcept {
        return *subj;
    }
    
private:
    T *subj;
};
//------------------------------------------------------------------------------
/** */
template <class T>
class adaptor_base<T, true>
{   
public:    
    struct adaptor_id_ {};
    
    using adaptee_type = typename remove_const<T>::type;
    
    adaptor_base(adaptor_base &) = default;
    adaptor_base(const adaptor_base &) = default;
    adaptor_base(adaptor_base &&) = default;
    
    inline adaptor_base(T &x)
    : subj(x)
    {}
    inline adaptor_base(typename remove_const<T>::type &&x)
    : subj(foundation::move(x))
    {}
    
    adaptor_base &operator = (const adaptor_base &rhs) = default;
    adaptor_base &operator = (adaptor_base &&rhs) = default;
    
    inline T &adaptee() noexcept {
        return subj;
    }
    inline const T &adaptee() const noexcept {
        return subj;
    }
    
private:
    adaptee_type subj;
};

/** @} */

}} // namespaces

#endif // NIC_9CFC33DAB78AD325_NIC
