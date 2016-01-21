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
#ifndef NIC_4F7878B88E2A90AF_NIC
#define NIC_4F7878B88E2A90AF_NIC

#include "detail/ei_container.h"
#include <exception>
#include <new> // std::bad_alloc

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <class ... E>
struct combined_exception : public virtual E ... {};

//------------------------------------------------------------------------------
/** Like ei_msg but stores the string in a const char * pointer. This way
 * we can avoid memory allocation for the string. */
using ei_msg_c = error_info<struct msg_c_, const char *>;

//------------------------------------------------------------------------------
namespace exception_detail {
//------------------------------------------------------------------------------
template <class EI>
struct get_helper {
    template <class X>
    inline static EI *apply(X *x) noexcept {
        return x->eic.template get<EI>();
    }
    template <class X>
    inline static const EI *apply(const X *x) noexcept {
        return x->eic.template get<EI>();
    }
};
template <>
struct get_helper<ei_msg_c> {
    template <class X>
    inline static ei_msg_c *apply(X *x) noexcept {
        if(x->msg_.value())
            return &x->msg_;
        return nullptr;
    }
    template <class X>
    inline static const ei_msg_c *apply(const X *x) noexcept {
        if(x->msg_.value())
            return &x->msg_;
        return nullptr;
    }
};
//------------------------------------------------------------------------------
class n_foundation_dll exception_base : public virtual std::exception
{
public:
    inline exception_base() noexcept
    : name_(nullptr),
    file_(nullptr),
    func_(nullptr),
    msg_(nullptr),
    line_(0)
    {}
    exception_base(exception_base &) = default;
    exception_base(const exception_base &) = default;
    exception_base(exception_base &&) = default;
    
    exception_base &operator = (const exception_base &) = default;
    exception_base &operator = (exception_base &&) = default;
    
    template <class EI>
    inline EI *get() noexcept
    {
        return get_helper<EI>::apply(this);
    }
    template <class EI>
    inline const EI *get() const noexcept
    {
        return get_helper<EI>::apply(this);
    }
    
    inline const char *name() const noexcept {
        return name_;
    }
    inline const char *file() const noexcept {
        return file_;
    }
    inline const char *func() const noexcept {
        return func_;
    }
    inline const char *message() const noexcept {
        return msg_.value();
    }
    inline size_t line() const noexcept {
        return line_;
    }
    
    template <class Exc, class Tag, class T>
    inline friend const Exc &operator << (
        const Exc &e, const error_info<Tag, T> &ei)
    {
        e.eic.push(ei);
        return e;
    }
    template <class Exc>
    inline friend const Exc &operator << (
        const Exc &e, const ei_msg_c &ei) noexcept
    {
        e.msg_ = ei;
        return e;
    }
    /** Alias for operator << (ei_msg_c(str)).
     * */
    template <class Exc>
    inline friend const Exc &operator << (
        const Exc &e, const char *str) noexcept
    {
        e.msg_ = ei_msg_c(str);
        return e;
    }
    
private:
    mutable const char *name_;
    mutable const char *file_;
    mutable const char *func_;
    mutable ei_msg_c msg_;
    size_t line_;
    mutable ei_container eic;
    
    template <class E>
    friend E create_exception(
        const char *fl,
        const char *fnc,
        const size_t l) noexcept;
    
    template <class First, class Second, class ... Rest>
    friend combined_exception<First, Second, Rest...> create_exception(
        const char *fl,
        const char *fnc,
        const size_t l) noexcept;
        
    template <class EI>
    friend struct get_helper;
        
    friend string message(
        const exception_base &e);
};

//------------------------------------------------------------------------------
template <class E>
inline E create_exception(
    const char *fl,
    const char *fnc,
    const size_t l) noexcept
{
    E e;
    e.name_ = typeid(E).name();
    e.file_ = fl;
    e.func_ = fnc;
    e.line_ = l;
    return e;
}
//------------------------------------------------------------------------------
template <class First, class Second, class ... Rest>
inline combined_exception<First, Second, Rest...> create_exception(
    const char *fl,
    const char *fnc,
    const size_t l) noexcept
{
    combined_exception<First, Second, Rest...> e;
    e.name_ = typeid(e).name();
    e.file_ = fl;
    e.func_ = fnc;
    e.line_ = l;
    return e;
}
//------------------------------------------------------------------------------
extern string n_foundation_dll message(const exception_base &e);

//------------------------------------------------------------------------------
} // exception_detail
//------------------------------------------------------------------------------
using std::exception_ptr;
using std::rethrow_exception;
using std::current_exception;
using std::make_exception_ptr;

//------------------------------------------------------------------------------
struct exception : 
    public virtual exception_detail::exception_base
    {};    
//------------------------------------------------------------------------------
/** Thrown if something went wrong at runtime. */
class runtime_error :
    public virtual exception 
    {};
//------------------------------------------------------------------------------
/** Thrown if something, which could have been detected at compile time,
 *  went wrong.
 * */
class logic_error :
    public virtual exception 
    {};
//------------------------------------------------------------------------------
/** Bad type casting operation. */
class bad_cast :
    public virtual runtime_error,
    public virtual std::bad_cast
    {};
//------------------------------------------------------------------------------
/** Thrown when a memory allocation failed. */
class bad_alloc :
    public virtual runtime_error,
    public virtual std::bad_alloc
    {};
//------------------------------------------------------------------------------
/** Thrown when an index is out of range. */
class out_of_range : 
    public virtual runtime_error
    {};
//------------------------------------------------------------------------------
/** Exception for underflow errors. */
class underflow_error :
    public virtual runtime_error
    {};
//------------------------------------------------------------------------------
/** Exception for overflow errors. */
class overflow_error : 
    public virtual runtime_error
    {};
//------------------------------------------------------------------------------
/** Thrown if an operation was not able to find something.
 * Like if an entry in a map like object is missing.
 * Or a file is not where it is expected to be. */
class item_not_found : 
    public virtual runtime_error
    {};
//------------------------------------------------------------------------------
/** A file can't be found. */
class file_not_found : 
    public virtual item_not_found 
    {};

//------------------------------------------------------------------------------
/** To encapsulate an exception. */
using ei_exc = error_info<struct nested_exception_, exception_ptr>;

//------------------------------------------------------------------------------
template <class EI>
inline const EI *get_error_info(const exception &e) noexcept
{
    return e.get<EI>();
}
//------------------------------------------------------------------------------
template <class EI>
inline EI *get_error_info(exception &e) noexcept
{
    return e.get<EI>();
}

//------------------------------------------------------------------------------
/** @def n_throw
 *  Used to throw exceptions derived from nebula::foundation::exception.
 *  Do not use throw directly.
 *  Example:
 *  @code
 *      n_throw(runtime_error) << ei_msg("This is an example.");
 *  @endcode
 * */
#ifdef N_EXCEPTIONS_STORE_FUNCTION_NAME
#   define n_throw(...)\
        throw ::nebula::foundation::exception_detail::create_exception<\
            __VA_ARGS__>(__FILE__, n_current_function, __LINE__)
#else
#   define n_throw(...)\
        throw ::nebula::foundation::exception_detail::create_exception<\
            __VA_ARGS__>(__FILE__, nullptr, __LINE__)
#endif // N_EXCEPTIONS_STORE_FUNCTION_NAME

/** @} */

}} // namespaces


#endif // NIC_4F7878B88E2A90AF_NIC
