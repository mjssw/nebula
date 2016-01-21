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
#ifndef NIC_4C570DA27E215C11_NIC
#define NIC_4C570DA27E215C11_NIC

#include "placeholder.h"
#include "../seq/seq.h"
#include "../seq/at.h"
#include "../seq/push_back.h"
#include "../seq/pop_front.h"
#include "../seq/front.h"
#include "../algo_fwd.h"
#include "../if.h"
#include "../lazy.h"

namespace nebula { namespace foundation { namespace meta {
/** @ingroup Foundation
 * @{ 
 */

//------------------------------------------------------------------------------
namespace bind_detail {
//------------------------------------------------------------------------------
template <class T>
struct is_template : false_ {};

template <template <class ... X> class T, class ... X>
struct is_template<T<X...>> : true_ {};

//------------------------------------------------------------------------------
template <class T>
struct make_parameter_list_
{
    using type = seq<void>; 
};
template <template <class ...> class F, class ... Params>
struct make_parameter_list_<F<Params...>>
{
    using type = seq<Params...>; 
};
//------------------------------------------------------------------------------
template <class Tree, class Expression>
struct make_tree_
{
    using type = void;
};

template <class Tree, template <class ...> class Expr, class ... Parms>
struct make_tree_<Tree, Expr<Parms...>>
{
    using Expression = Expr<Parms...>;
    using params = typename make_parameter_list_<Expression>::type;
    
    template <class Seq_, class X>
    struct F 
    {
        using type = _push_back<Seq_, typename make_tree_<seq<X>, X>::type>;
    };
    
    using node = seq<Expression>;
    using type = _for_each<params, F, node>;
};
//------------------------------------------------------------------------------
template <class Expression>
struct parse_
{
    using tree = seq<>;
    using type = typename make_tree_<tree, Expression>::type;
};

template <class Expr, class Params>
struct rebind_ {};
template <
    template <class ...> class Expr,
    class ... Params, 
    class ... OldParams>
struct rebind_<Expr<OldParams...>, seq<Params...>>
{
    using type = Expr<Params...>;
};
//------------------------------------------------------------------------------
template <class T>
struct placeholder_index_ : public size_t_<0> {};

template <size_t N>
struct placeholder_index_<placeholder<N>> : public size_t_<N> {};
//------------------------------------------------------------------------------
/** @internal In case we have an empty parameter sequence, we just return void.
 * Just so we can compile.
 * */
template <class Seq, class Index>
struct my_at_ : public at_<Seq, Index> {};

template <class Index>
struct my_at_<seq<>, Index>  {
    using type = void;
};
//------------------------------------------------------------------------------
template <class Node, class ParamSeq>
struct assemble_
{
    using Expr = _front<Node>;
    using OldParams = typename make_parameter_list_<Expr>::type;
    using NewParams = _pop_front<Node>;
    
    template <class S, class T>
    struct F {
        // The corresponding parameter - this is only relevant if NParam is
        // a template expression, otherwise it won't be used.
        using NParam = _at<NewParams, _size<S>>;
        
        // If we encounter a placeholder, we need to exchange it with one of
        // the provided template parameters in ParamSeq.
        // Note: if ParamSeq is empty then is_placeholder is always false.
        using new_T = _if<is_placeholder<T>,
            typename my_at_<ParamSeq, placeholder_index_<T>>::type,
            T>;
        
        // Simply add the new type if it isn't a template expression, otherwise
        // recurse down into the graph until we find a non template expression.
        using type = 
        _if<
            is_template<T>,
            _push_back<S, typename assemble_<NParam, ParamSeq>::type >,
            _push_back<S, new_T>
        >;
    };

    // Remove the outter seq<> wrapper and replace it with the actual
    // expression. For example seq<int, float> ---> expr<int, float>.
    using type = typename rebind_<Expr, _for_each<OldParams, F, seq<>>>::type;
};

template <class ParamSeq>
struct assemble_<void, ParamSeq>
{
    using type = void; // Never called, just to avoid a compilation error.
};
//------------------------------------------------------------------------------
} // bind_detail
//------------------------------------------------------------------------------
/** This meta function generates new templates (can also be done at function 
 * scope).
 * @todo I need to clean up and comment some code here. - lis
 * */
template <class Expression>
struct bind_
{
private:    
    using parse_result = typename bind_detail::parse_<lazy<Expression>>::type;
    
public:
    template <class ... Params>
    using type = typename bind_detail::assemble_<
        parse_result, seq<Params...>>::type;
};

//------------------------------------------------------------------------------
#define n_bind(...) ::nebula::foundation::meta::bind_<__VA_ARGS__>::template type

/** @} */

}}} // namespaces

#endif // NIC_4C570DA27E215C11_NIC