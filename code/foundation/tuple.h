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
#ifndef NIC_82B23FA2D2AD2294_NIC
#define NIC_82B23FA2D2AD2294_NIC

#include "swap.h"
#include "get.h"
#include "meta.h"
#include "move.h"
#include "enable_if.h"
#include "call_traits.h"
#include "utils/unpack.h"

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <class ... T> class tuple;
//------------------------------------------------------------------------------
namespace tuple_detail {
//------------------------------------------------------------------------------
struct assign_ {
    template <class T0, class T1>
    inline void operator () (T0 &t0, T1 &&t1) {
        t0 = foundation::forward<T1>(t1);
    }
};
//------------------------------------------------------------------------------
template <class I, class T>
struct holder
{    
    using type = T;
    T value;
};
//------------------------------------------------------------------------------
template <class ... T>
using gen_index_seq = 
meta::_for_each<
    meta::seq<T...>,
    n_bind(meta::push_back_<
        meta::_1, meta::size_<meta::_1>>),
    meta::seq<>
>;
//------------------------------------------------------------------------------
template <class IndexSeq>
struct do_for_each_;
template <class ... I>
struct do_for_each_<meta::seq<I...>>
{
    template <class Tpl, class J>
    using ElemType = typename Tpl::template tuple_element<J::type::value>::type;
        
    template <class F, class T0, class T1>
    inline static void apply(T0 && t0, T1 && t1, F && f)
    {        
        n_unpack(
            f(t0.template get<I::type::value>(),
                foundation::forward<T1>(t1)
                .template _priv_forw<I::type::value>())
        );
    }
};
//------------------------------------------------------------------------------
template <class IndexSeq, class ... T>
struct base;

template <class ... I, class ... T>
struct base<meta::seq<I...>, T...>
: holder<I, T>...
{
protected:
    template <size_t N>
    using holder_element = meta::nth_<
        meta::size_t_<N>, 
        tuple_detail::holder<meta::size_t_<N>, T>...
    >;
    
public:
    template <size_t N>
    using tuple_element = typename holder_element<N>::type;
   
    /** @todo Can be made private with friend decl - need to come back to this
     * when Im not procrastinating - lis. 
     * */
    template <size_t N>
    inline 
    typename remove_reference<typename tuple_element<N>::type>::type &
    _priv_forw() const & noexcept {
        return static_cast<
            typename holder_element<N>::type *
        >(const_cast<base *>(this))->value;
    }
    template <size_t N>
    inline typename tuple_element<N>::type &&_priv_forw() const && noexcept {
        return foundation::forward<typename tuple_element<N>::type>(
            static_cast<
                typename holder_element<N>::type *
            >(const_cast<base *>(this))->value
        );
    }
    
public:
    constexpr base() = default;
    constexpr base(base &) = default;
    constexpr base(const base &) = default;
    constexpr base(base &&) = default;
    
    template <class ... T_>
    inline constexpr base(T_ && ... t)
    : tuple_detail::holder<I, T>{foundation::forward<T_>(t)}...
    {}
    
    template <class ... T_,
        class Cond = meta::_and<is_convertible<T_, T>...>,
        typename enable_if<Cond>::type* = nullptr>
    inline base(tuple<T_...> &other)
    : tuple_detail::holder<I, T>{
        other._priv_forw<I::type::value>()}...
    {} 
    template <class ... T_,
        class Cond = meta::_and<is_convertible<T_, T>...>,
        typename enable_if<Cond>::type* = nullptr>
    inline base(const tuple<T_...> &other)
    : tuple_detail::holder<I, T>{
        other._priv_forw<I::type::value>()}...
    {} 
    template <class ... T_,
        class Cond = meta::_and<is_convertible<T_, T>...>,
        typename enable_if<Cond>::type* = nullptr>
    inline base(tuple<T_...> &&other)
    : tuple_detail::holder<I, T>{
        foundation::move(other)._priv_forw<I::type::value>()}...
    {} 
    
    base &operator = (base &) = default;
    base &operator = (const base &) = default;
    base &operator = (base &&) = default;
    
    template <size_t N>
    inline auto &get() noexcept {
        return static_cast<
            typename holder_element<N>::type *
        >(this)->value;
    }
    template <size_t N>
    inline constexpr const auto &get() const noexcept {
        return static_cast<
            const typename holder_element<N>::type *
        >(this)->value;
    }
};

} // tuple_detail

//------------------------------------------------------------------------------
/**
 * */
template <class ... T>
struct tuple
: public tuple_detail::base<tuple_detail::gen_index_seq<T...>, T...>
{
private:
    using base_type = tuple_detail::base<
        tuple_detail::gen_index_seq<T...>, 
        T...>;
    
public:
    using tuple_size = integral_constant<size_t, sizeof ... (T)>;
    
    constexpr tuple() = default;
    constexpr tuple(tuple &) = default;
    constexpr tuple(const tuple &) = default;
    constexpr tuple(tuple &&) = default;
    
    tuple &operator = (tuple &) = default;
    tuple &operator = (const tuple &) = default;
    tuple &operator = (tuple &&) = default;
    
    using tuple_detail::base<tuple_detail::gen_index_seq<T...>, T...>::base;
    
    template <class ... T_>
    inline tuple &operator = (const tuple<T_...> &other_) {
        tuple<T_...> &other = const_cast<tuple<T_...>&>(other_);
        tuple_detail::do_for_each_<
            tuple_detail::gen_index_seq<T...>
        >::apply(
            *this, 
            other, 
            tuple_detail::assign_()
        );
        return *this;
    }
    template <class ... T_>
    inline tuple &operator = (tuple<T_...> &&other_) {
        tuple<T_...> &other = const_cast<tuple<T_...>&>(other_);
        tuple_detail::do_for_each_<
            tuple_detail::gen_index_seq<T...>
        >::apply(
            *this, 
            foundation::move(other), 
            tuple_detail::assign_()
        );
        return *this;
    }
    
    template <class ... T_>
    inline void swap(tuple<T_...> &other)
    {
        tuple_detail::do_for_each_<
            tuple_detail::gen_index_seq<T...>
        >::apply(
            *this, 
            other, 
            [] (auto &lhs, auto &rhs) 
            {
                foundation::swap(lhs, rhs);
            }
        );
    }
    
    template <class ... T_>
    inline bool operator == (const tuple<T_...> &other) const
    {
        bool res = true;
        tuple_detail::do_for_each_<
            tuple_detail::gen_index_seq<T...>
        >::apply(
            *this, 
            other, 
            [&] (const auto &lhs, const auto &rhs )
            {
                res = res && (lhs == rhs);
            }
        );
        return res;
    }
    template <class ... T_>
    inline bool operator != (const tuple<T_...> &other) const
    {
        return *this != other;
    }
    
    template <class ... T_>
    inline bool operator < (const tuple<T_...> &other) const
    {
        bool res = true;
        tuple_detail::do_for_each_<
            tuple_detail::gen_index_seq<T...>
        >::apply(
            *this, 
            other, 
            [&] (const auto &lhs, const auto &rhs) 
            {
                res = res && (lhs < rhs);
            }
        );
        return res;
    }
    template <class ... T_>
    inline bool operator <= (const tuple<T_...> &other) const
    {
        bool res = true;
        tuple_detail::do_for_each_<
            tuple_detail::gen_index_seq<T...>
        >::apply(
            *this, 
            other, 
            [&] (const auto &lhs, const auto &rhs) 
            {
                res = res && (lhs <= rhs);
            }
        );
        return res;
    }
    template <class ... T_>
    inline bool operator > (const tuple<T_...> &other) const
    {
        bool res = true;
        tuple_detail::do_for_each_<
            tuple_detail::gen_index_seq<T...>
        >::apply(
            *this, 
            other, 
            [&] (const auto &lhs, const auto &rhs) 
            {
                res = res && (lhs > rhs);
            }
        );
        return res;
    }
    template <class ... T_>
    inline bool operator >= (const tuple<T_...> &other) const
    {
        bool res = true;
        tuple_detail::do_for_each_<
            tuple_detail::gen_index_seq<T...>
        >::apply(
            *this, 
            other, 
            [&] (const auto &lhs, const auto &rhs) 
            {
                res = res && (lhs >= rhs);
            }
        );
        return res;
    }
};

//------------------------------------------------------------------------------
template <class ... T>
inline constexpr tuple<typename decay<T>::type...> make_tuple(T && ... t) {
    return tuple<T &&...>(foundation::forward<T>(t)...);
}
//------------------------------------------------------------------------------
template <class ... T>
inline constexpr tuple<T&&...> forward_as_tuple(T && ... t) noexcept {
    return tuple<T&&...>(foundation::forward<T>(t)...);
}

//------------------------------------------------------------------------------
struct ignore_t
{
    template <class T>
    inline ignore_t &operator = (const T &) noexcept { return *this; }
};

n_unused_variable(static ignore_t, ignore);

//------------------------------------------------------------------------------
template <class ... T>
inline constexpr tuple<T&...> tie(T & ... t) noexcept {
    return tuple<T&...>(t...);
}

//------------------------------------------------------------------------------
template <size_t N, class T>
struct tuple_element {
    using type = typename T::template tuple_element<N>::type;
};

//------------------------------------------------------------------------------
template <class T>
struct tuple_size : public T::tuple_size {};

//------------------------------------------------------------------------------
template <class Tuple>
struct tuple_indices_
{
    using type = meta::_expand<tuple_detail::gen_index_seq, Tuple>;
};

template <class Tuple>
using tuple_indices = tuple_indices_<Tuple>;

template <class Tuple>
using _tuple_indices = typename tuple_indices_<Tuple>::type;

//------------------------------------------------------------------------------
namespace tuple_detail {
//------------------------------------------------------------------------------
template <class ... T>
struct tuple_merge_result
{
    using type = meta::_expand<tuple,
        meta::_merge<meta::seq<>, meta::_expand<meta::seq, T>...>>;
};
//------------------------------------------------------------------------------
template <class Result, size_t N, class Indices, class ... T>
struct tuple_merger;

template <class Result, size_t N, class ... I, class ... Tuples>
struct tuple_merger<Result, N, meta::seq<I...>, meta::seq<Tuples...>>
{
    template <class Tuple, class ... T_>
    inline static Result apply(
        Tuple &&tpl,
        T_ && ... t)
    {
        using Seq = meta::_pop_front<meta::seq<Tuples...>>;
        return 
        tuple_merger<
            Result, 
            N+1,
            _tuple_indices<meta::_front<Seq>>,
            Seq
        >::apply(
            foundation::move(tpl),
            foundation::forward<T_>(t)...,
            foundation::forward<
                Tuple
            >(tpl)
                .template _priv_forw<N>()
                .template _priv_forw<I::type::value>()...);
    }
};
template <class Result, size_t N, class ... I, class Last>
struct tuple_merger<Result, N, meta::seq<I...>, meta::seq<Last>>
{
    template <class Tuple, class ... T_>
    inline static Result apply(
        Tuple &&tpl,
        T_ && ... t)
    {
        return Result(
            foundation::forward<T_>(t)...,
            foundation::forward<
                Tuple
            >(tpl)
                .template _priv_forw<N>()
                .template _priv_forw<I::type::value>()...
        );
    }
};

} // tuple_detail

//------------------------------------------------------------------------------
template <class First, class ... Rest>
inline typename tuple_detail::tuple_merge_result<
    typename ctraits::value<First>::type,
    typename ctraits::value<Rest>::type...>::type
merge_tuple(First &&f, Rest && ... r)
{
    using Res = typename tuple_detail::tuple_merge_result<
        typename ctraits::value<First>::type,
        typename ctraits::value<Rest>::type...>::type;
    
    return tuple_detail::tuple_merger<
        Res,
        0,
        _tuple_indices<typename ctraits::value<First>::type>,
        meta::seq<
            typename ctraits::value<First>::type,
            typename ctraits::value<Rest>::type...>
    >::apply(
        foundation::forward_as_tuple(
            foundation::forward<First>(f),
            foundation::forward<Rest>(r)...)                         
    );
}

//------------------------------------------------------------------------------
namespace tuple_detail {
//------------------------------------------------------------------------------
template <class Tuple, size_t ... N>
struct reorder_tuple_ {};

template <class ... T, size_t ... N>
struct reorder_tuple_<tuple<T...>, N...>
{
    using result_type = tuple<
        typename tuple_element<N, tuple<T...>>::type...>;
       
    inline static constexpr result_type apply(tuple<T...> &tpl)
    {        
        return result_type(foundation::get<N>(tpl)...);
    }
    inline static constexpr result_type apply(const tuple<T...> &tpl)
    {        
        return result_type(foundation::get<N>(tpl)...);
    }
    inline static constexpr auto apply(tuple<T...> &&tpl)
    {        
        return forward_as_tuple(
            foundation::forward<
                typename tuple_element<N, tuple<T...>>::type>(
                    foundation::get<N>(tpl))...);
    }
};

} // tuple_detail

//------------------------------------------------------------------------------
template <size_t ... N, class Tuple>
inline constexpr auto reorder_tuple(Tuple &&t)
{
    return tuple_detail::reorder_tuple_<
        typename decay<Tuple>::type,
        N...>::apply(
            foundation::forward<Tuple>(t));
}

//------------------------------------------------------------------------------
namespace tuple_detail {
//------------------------------------------------------------------------------
template <class T, class I>
struct tuple_expander {};

//------------------------------------------------------------------------------
template <class ... T, class ... I>
struct tuple_expander<tuple<T...>, meta::seq<I...>>
{
    template <class F>
    inline static auto apply(F &&f, const tuple<T...> &t)
    {
        return f(
            foundation::get<I::value>(t)...);
    }
    template <class F>
    inline static auto apply(F &&f, tuple<T...> &t)
    {
        return f(
            foundation::get<I::value>(t)...);
    }
    template <class F>
    inline static auto apply(F &&f, tuple<T...> &&t)
    {
        return f(
            foundation::forward<T>(foundation::get<I::value>(t))...);
    }
};

} // tuple_detail

//------------------------------------------------------------------------------
template <class F, class ... T>
inline auto expand_tuple(F &&f, const tuple<T...> &t)
{
    using tuple_t = tuple<T...>;
    return tuple_detail::tuple_expander<
        tuple_t,
        tuple_detail::gen_index_seq<T...>>::apply(f, t);
}
//------------------------------------------------------------------------------
template <class F, class ... T>
inline auto expand_tuple(F &&f, tuple<T...> &t)
{
    using tuple_t = tuple<T...>;
    return tuple_detail::tuple_expander<
        tuple_t,
        tuple_detail::gen_index_seq<T...>>::apply(f, t);
}
//------------------------------------------------------------------------------
template <class F, class ... T>
inline auto expand_tuple(F &&f, tuple<T...> &&t)
{
    using tuple_t = tuple<T...>;
    return tuple_detail::tuple_expander<
        tuple_t,
        tuple_detail::gen_index_seq<T...>>::apply(f, foundation::move(t));
}

namespace tuple_detail {
//------------------------------------------------------------------------------
template <class F>
struct tuple_for_each_helper
{
    template <class First, class Second, class ... Rest>
    inline void operator () (First &&first, Second &&second, Rest && ... rest)
    {
        if(!f(foundation::forward<First>(first)))
            return;
        this->operator () (foundation::forward<Second>(second),
            foundation::forward<Rest>(rest)...);
    }
    template <class T>
    inline void operator () (T &&t) {
        f(foundation::forward<T>(t));
    }
    
    ctraits::_ref<F> f;
};

} // tuple_detail

//------------------------------------------------------------------------------
template <class Tuple, class F>
inline void for_each(Tuple &&t, F &&f)
{
    expand_tuple(
        tuple_detail::tuple_for_each_helper<F>{f},
        foundation::forward<Tuple>(t));
}

/** @} */

}} // namespaces

#endif // NIC_82B23FA2D2AD2294_NIC
