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
#ifndef NIC_65DC8CC3B933E493_NIC
#define NIC_65DC8CC3B933E493_NIC

#include "traits.h"
#include "../defs.h"
#include "../enable_if.h"

namespace nebula { namespace foundation { namespace range {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class T>
struct begin_impl
{
    template <class R>
    inline static 
    typename range_iterator<typename remove_reference<R>::type>::type 
    apply(R &&r) noexcept
    {
        n_static_assert(noexcept(r.begin()), "Must not throw");
        return r.begin();
    }
};
//------------------------------------------------------------------------------
/** @return An iterator to the first element of the range.
 * @attention Must be noexcept. */
template <class T>
inline typename range_iterator<typename remove_reference<T>::type>::type
begin(T &&r) noexcept
{
    n_static_assert(
        noexcept(begin_impl<typename decay<T>::type>::apply(r)),
        "Must not throw");
    return begin_impl<typename decay<T>::type>::apply(r);
}
//------------------------------------------------------------------------------
template <class T>
struct end_impl
{
    template <class R>
    inline static 
    typename range_iterator<typename remove_reference<R>::type>::type 
    apply(R &&r) noexcept
    {
        n_static_assert(noexcept(r.end()), "Must not throw");
        return r.end();
    }
};
//------------------------------------------------------------------------------
/** @return An iterator one past the last element of the range.
 * @attention Must be noexcept. */
template <class T>
inline typename range_iterator<typename remove_reference<T>::type>::type 
end(T &&r) noexcept
{
    n_static_assert(
        noexcept(end_impl<typename decay<T>::type>::apply(r)),
        "Must not throw");
    return end_impl<typename decay<T>::type>::apply(r);
}
//------------------------------------------------------------------------------
template <class T>
struct rbegin_impl
{
    template <class R>
    inline static 
    typename range_reverse_iterator<typename remove_reference<R>::type>::type
    apply(R &&r) noexcept
    {
        n_static_assert(noexcept(r.rbegin()), "Must not throw");
        return r.rbegin();
    }
};
//------------------------------------------------------------------------------
/** Reverse begin().
 * @see nebula::foundation::range::begin */
template <class T>
inline typename range_reverse_iterator<typename remove_reference<T>::type>::type
rbegin(T &&r) noexcept
{
    n_static_assert(
        noexcept(rbegin_impl<typename decay<T>::type>::apply(r)), 
        "Must not throw");
    return rbegin_impl<typename decay<T>::type>::apply(r);
}
//------------------------------------------------------------------------------
template <class T>
struct rend_impl
{
    template <class R>
    inline static 
    typename range_reverse_iterator<typename remove_reference<R>::type>::type 
    apply(R &&r) noexcept
    {
        n_static_assert(noexcept(r.rend()), "Must not throw");
        return r.rend();
    }
};
//------------------------------------------------------------------------------
/** Reverse end().
 * @see nebula::foundation::range::end */
template <class T>
inline typename range_reverse_iterator<typename remove_reference<T>::type>::type 
rend(T &&r) noexcept
{
    n_static_assert(
        noexcept(rend_impl<typename decay<T>::type>::apply(r)), 
        "Must not throw");
    return rend_impl<typename decay<T>::type>::apply(r);
}
//------------------------------------------------------------------------------
template <class T>
struct front_impl
{
    template <class R>
    inline static 
    typename range_reference<typename remove_reference<R>::type>::type 
    apply(R &&r) noexcept
    {
        n_static_assert(noexcept(range::begin(r)), "Must not throw");
        return *range::begin(r);
    }
};
//------------------------------------------------------------------------------
/** @return Returns a reference to the first element of the range.
 * @attention Must be noexcept. */
template <class T>
inline typename range_reference<typename remove_reference<T>::type>::type
front(T &&r) noexcept
{
    n_static_assert(
        noexcept(front_impl<typename decay<T>::type>::apply(r)),
        "Must not throw");
    return front_impl<typename decay<T>::type>::apply(r);
}
//------------------------------------------------------------------------------
template <class T>
struct back_impl
{
    n_static_assert(n_arg(_is_same<_range_traversal<T>,
        random_access_traversal_tag>::value),
        "Random access range required.");
    
    template <class R>
    inline static 
    typename range_reference<typename remove_reference<R>::type>::type 
    apply(R &&r) noexcept
    {
        n_static_assert(noexcept(range::end(r)), "Must not throw");
        return *(range::end(r)-1);
    }
};
//------------------------------------------------------------------------------
/** @return Returns a reference to the last element of the range. The range
 * must be bidirectional to be applicable.
 * @attention Must be noexcept. */
template <class T>
inline typename range_reference<typename remove_reference<T>::type>::type
back(T &&r) noexcept
{
    n_static_assert(
        noexcept(back_impl<typename decay<T>::type>::apply(r)),
        "Must not throw");
    return back_impl<typename decay<T>::type>::apply(r);
}
//------------------------------------------------------------------------------
template <class T>
struct empty_impl
{
    inline static bool apply(const T &r) noexcept
    {
        return range::begin(r) == range::end(r);
    }
};
//------------------------------------------------------------------------------
/** A range is empty only if begin(r) == end(r).
 * @attention Must be noexcept. */
template <class T>
inline bool empty(const T &r) noexcept
{
    n_static_assert(noexcept(empty_impl<T>::apply(r)), "Must not throw");
    return empty_impl<T>::apply(r);
}
//------------------------------------------------------------------------------
template <class T>
struct distance_impl
{
    inline static typename range_difference<T>::type apply(const T &r) noexcept
    {
        return ins_::distance(range::begin(r), range::end(r));
    }
};
//------------------------------------------------------------------------------
/** @return the Distance of end(r) - begin(r).
 * @attention Must be noexcept. */
template <class T>
inline typename range_difference<T>::type distance(const T &r) noexcept
{
    n_static_assert(noexcept(distance_impl<T>::apply(r)), "Must not throw");
    return distance_impl<T>::apply(r);
}
//------------------------------------------------------------------------------
namespace range_detail {
template <class T>
struct _has_size_method
{
private:
    typedef char yes[1];
    typedef char no[2];

    template <class X>
    static yes &test( decltype(&X::size) );

    template <class>
    static no &test(...);

public:
    static const bool value = sizeof(test<T>(0)) == sizeof(yes);
};
//------------------------------------------------------------------------------
/** So we know if the range provides a size() method. */
template <class T>
struct has_size_method :
    public integral_constant<bool, _has_size_method<T>::value> {};
}// range_detail
//------------------------------------------------------------------------------
/** Makes use of a member function size() if available, otherwise distance() is
 * applied as a fallback. */
template <class T>
struct size_impl
{
    template <class X = T,
        typename enable_if<range_detail::has_size_method<X>, int>::type = 0>
    inline static typename range_size<T>::type apply(const T &r) noexcept
    {
        n_static_assert(noexcept(r.size()), "Must not throw");
        return r.size();
    }
    template <class X = T,
        typename disable_if<range_detail::has_size_method<X>, int>::type = 0>
    inline static typename range_size<T>::type apply(const T &r) noexcept
    {
        return range::distance(r);
    }
};
//------------------------------------------------------------------------------
/** @return The size of the range, i.e. distance(r) for most applications.
 * @attention Must be noexcept. */
template <class T>
inline typename range_size<T>::type size(const T &r) noexcept
{
    n_static_assert(noexcept(size_impl<T>::apply(r)), "Must not throw");
    return size_impl<T>::apply(r);
}
//------------------------------------------------------------------------------
template <class T>
struct data_impl
{
    template <class R>
    inline static 
    typename range_pointer<typename remove_reference<R>::type>::type 
    apply(R &&r) noexcept
    {
        n_static_assert(noexcept(r.data()), "Must not throw");
        return r.data();
    }
};
//------------------------------------------------------------------------------
/** @return A pointer to the stored array.
 * @attention Must be noexcept. */
template <class T>
inline typename range_pointer<typename remove_reference<T>::type>::type
data(T &&r) noexcept
{
    n_static_assert(
        noexcept(data_impl<typename decay<T>::type>::apply(r)),
        "Must not throw");
    return data_impl<typename decay<T>::type>::apply(r);
}

/** @} */

}}} // namespaces

#endif // NIC_65DC8CC3B933E493_NIC
