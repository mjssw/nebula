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
#ifndef NIC_C7957E76D3E2F8F3_NIC
#define NIC_C7957E76D3E2F8F3_NIC

#include "system_error.h"
#include "move.h"

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
/** Thrown by expect<...>::get() if an error is set. */
struct unexpected : public virtual runtime_error {};

//------------------------------------------------------------------------------
template <class T, class Error>
class expect
{
    n_static_assert(!system::is_error_condition_enum<T>::value, 
        "T must not satisfy is_error_condition_enum");
    n_static_assert(system::is_error_condition_enum<Error>::value,
        "Error must satisfy is_error_condition_enum");
    
public:
    using value_type = T;
    using error_type = Error;
    
    template <class X,
        typename enable_if<
        system::is_error_condition_enum<X>>::type* = nullptr>
    inline expect(const X x) noexcept
    : good(false), e(x)
    {}
    template <class X,
        typename disable_if<
        system::is_error_condition_enum<X>>::type* = nullptr>
    inline expect(X &&x)
    : good(true), v(foundation::forward<X>(x))
    {}
    
    inline expect(expect<T, Error> &other)
    : good(other.good)
    {
        if(other.good)
            new (&v) T(other.v);
        else
            new (&e) Error(other.e);
    }
    inline expect(const expect<T, Error> &other)
    : good(other.good)
    {
        if(other.good)
            new (&v) T(other.v);
        else
            new (&e) Error(other.e);
    }
    inline expect(expect<T, Error> &&other)
    : good(other.good)
    {
        if(other.good)
            new (&v) T(foundation::move(other.v));
        else
            new (&e) Error(other.e);
    }
    
    /** @attention May throw if ~T() does. */
    inline ~expect()
    {        
        if(good)
            v.~T();
        else
            e.~Error();
    }
    
    /* No sane way to impl assignments or a swap. */
    inline expect<T, Error> &operator = (
        const expect<T, Error> &other) = delete;
    inline expect<T, Error> &operator = (expect<T, Error> &&other) = delete;
    
    /** @return true if everything worked out without an error. */
    inline bool valid() const noexcept {
        return good;
    }
    
    /** @attention May only be called once.
     * @return The stored value if valid().
     * @throw unexpected If !valid().
     * @throw unknown If throwing unexptected failed (maybe out of mem, etc.).
     * */
    inline T get()
    {
        if(good)
            return foundation::move(v);
        else
            n_throw(unexpected)
            << system::ei_error_condition(e);
    }
    
    /** @return The stored error object if valid(), otherwise
     * a default constructed error_condition.
     * @throw nothing
     * */
    inline Error error() const noexcept
    {
        return !valid() ? e : Error();
    }
    
private:
    bool good;
    union
    {
        T v;
        Error e;
    };
};

/** @} */

}} // namespaces

#endif // NIC_C7957E76D3E2F8F3_NIC
