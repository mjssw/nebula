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
#ifndef NIC_9E2DCB41AA78AF59_NIC
#define NIC_9E2DCB41AA78AF59_NIC

#include "distance.h"
#include "../../swap.h"

/* Heap datastructure
 * -----------------------------------------------------------------------------
 * Graphical representation
 * -----------------------------------------------------------------------------
 *    graph    | depth
 * -------------------
 *      A      | 0
 *   B     C   | 1
 * D   E F   G | 2
 * 
 * -----------------------------------------------------------------------------
 * Flat, array-like, representation
 * -----------------------------------------------------------------------------
 * A | B | C | D | E | F | G
 * -------------------------
 * 0 | 1 | 2 | 3 | 4 | 5 | 6
 * 
 * -----------------------------------------------------------------------------
 * Formulas
 * -----------------------------------------------------------------------------
 * -] left child of n-th node: 2(n + 1) - 1
 * -] right child of n-th node: 2(n + 1)
 * -] parent of n-th node: floor((n-1) / 2)
 * -] maximum index of a node with leafs if the heap has n nodes: (n - 2) / 2.
 * */
namespace nebula { namespace foundation { namespace iterator {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
namespace iterator_detail {
//------------------------------------------------------------------------------
template <class N>
inline N parent_index(const N &n) noexcept
{
    return (n - 1) / 2;
}
//------------------------------------------------------------------------------
template <class N>
inline N right_child_index(const N &n) noexcept
{
    return 2 * (n + 1);
}
//------------------------------------------------------------------------------
template <class N>
inline N max_leafed_subheap_index(const N &n) noexcept
{
    return (n - 2) / 2;
}
//------------------------------------------------------------------------------
/** Calculate the upper bound of the largest range, beginning at @e first, that 
 * is a maximal heap.
 * @param f Binary comparison function.
 * @return The last iterator X for which range [first, X) is a maximal heap. 
 * @note This function does not throw if f does not either.
 * */
template <class I, class F>
inline I is_heap_until_(I first, I last, F &&f)
{
    if(iterator::distance(first, last) < 2)
        return last;
    I p = first;
    I c = p + 1;
    while(true)
    {
        if(f(*p, *c))
            return c;
        c++;
        if(c == last)
            return last;
        else if(f(*p, *c))
            return c;
        p++;
        c++;
        if(c == last)
            return last;
    }
}
//------------------------------------------------------------------------------
/** Insert an element into the heap.
 * @param root Iterator pointing to the first element in our range.
 * @param i Index of the element to be added.
 * @param top The element index where we have to terminate the search, i.e.
 * this marks the root of the subtree the algorithm will look at.
 * @param v The element to be inserted, which has position i in the range.
 * @param f Binary comparison function!
 * @note This function does not throw if both f and the move assignment of
 * the actual values do not throw - otherwise there is no exception guarantee.
 * @note root + i must be an already constructed(!) object,
 * the actual value doesn't matter, we just need to copy/move assign to it.
 * */
template<class I, class F>
void push_heap_(
    I root, 
    typename iterator_difference<I>::type i, 
    const typename iterator_difference<I>::type &top, 
    const typename iterator_value<I>::type v, 
    F &&f)
{
    using D = typename iterator_difference<I>::type;
    // parent index
    D p = parent_index(i);
    // Short circuit boolean evaluation saves us from evaluating *(root+p) if
    // i == 0 and thus p < 0.
    while(i > top && f(*(root + p), v))
    {
        // replace element.
        *(root + i) = foundation::move(*(root + p));
        // move up
        i = p;
        // find new parent
        p = parent_index(i);
    }
    // we are done
    *(root + i) = foundation::move(v);
}
//------------------------------------------------------------------------------
/** This algorithm looks at a sub-heap with root r and maximizes it.
 * @param base Iterator pointing to the first element in our range.
 * @param n The size of the total heap.
 * @param r The element index marking the root of the sub-heap.
 * @param f Binary comparison function.
 * @note This function does not throw if both f and the move assignment of
 * the actual values do not throw - otherwise there is no exception guarantee.
 * */
template<typename I, typename F>
void adjust_heap(I base, 
    const typename iterator_difference<I>::type &n, 
    typename iterator_difference<I>::type r,
    F &&f)
{
    using D = typename iterator_difference<I>::type;
    // Move the element at r to a safe place until we re-insert it at the end.
    typename iterator_value<I>::type old_root = foundation::move(*(base + r));
    const D top = r; // keep track.
    D r_child = r;
    // while there are 2 leaf nodes attached.
    while(r_child < (n - 1) / 2)
    {
        r_child = right_child_index(r_child);
        if(f(*(base + r_child), *(base + (r_child -1))))
            r_child--;
        *(base + r) = foundation::move(*(base + r_child));
        r = r_child;
    }
    // In case there is a sub-heap with just 1 leaf.
    if((n & 1) == 0 && r_child == max_leafed_subheap_index(n))
    {
        r_child = right_child_index(r_child);
        *(base + r) = foundation::move(*(base + (r_child - 1)));
        r = r_child - 1;
    }
    // Finally we need to insert the element which initially was at index r.
    push_heap_(base, r, top, foundation::move(old_root), f);
}
//------------------------------------------------------------------------------
/** Take a range [first, last) and turn it into a heap using the binary
 * comparator f.
 * @param f Binary comparison function.
 * @note This function does not throw if both f and the move assignment of
 * the actual values do not throw - otherwise there is no exception guarantee.
 * */
template <class I, class F>
inline void make_heap_(I first, I last, F &&f)
{
    using D = typename iterator_difference<I>::type;
    // Only one element, bail out.
    if(last - first < 2)
        return;
    // The heap size.
    const D n = iterator::distance(first, last);
    // The biggest index of our range where the element is not
    // a trivial heap (ie. it has still child nodes).
    D r = max_leafed_subheap_index(n);
    while(true) {
        iterator_detail::adjust_heap(first, n, r, f);
        if(!r) // we are done, no nodes left.
            return;
        r--; // simply go down to the next node.
    }
}
//------------------------------------------------------------------------------
} // iterator_detail
//------------------------------------------------------------------------------
template <class I>
struct make_heap_impl
{
    template <class F_>
    inline static void apply(I first, I last, F_ &&f)
    {
        iterator_detail::make_heap_(first, last, f);
    }
};
//------------------------------------------------------------------------------
/** Take a range [first, last) and turn it into a heap using the binary
 * comparator f.
 * @param f Binary comparison function, which must not throw.
 * @note Move assignment of values must not throw.
 * @throw nothing
 * */
template <class I, class F>
inline void make_heap(I first, I last, F &&f)
{
    make_heap_impl<I>::apply(first, last, f);
}

//------------------------------------------------------------------------------
template <class I>
struct push_heap_impl
{
    template <class F>
    inline static void apply(I first, I last, F &&f)
    {
        iterator_detail::push_heap_(first, 
            iterator::distance(first, last) - 1,
            0, foundation::move(*(last - 1)), f);
    }
};
//------------------------------------------------------------------------------
/** Insert an element, positioned at (last-1), into the heap, using the binary
 * comparator f.
 * @param f Binary comparision operator, which must not throw.
 * @note Move assignment of values must not throw.
 * @throw nothing
 * */
//------------------------------------------------------------------------------
template <class I, class F>
inline void push_heap(I first, I last, F &&f)
{
    push_heap_impl<I>::apply(first, last, f);
}
//------------------------------------------------------------------------------
template <class I>
struct pop_heap_impl
{
    template <class F>
    inline static void apply(I first, I last, F &&f)
    {
        using D = typename iterator_difference<I>::type;
        const D delta = iterator::distance(first, last);
        if(delta < 2)
            return;
        foundation::swap(*first, *(last-1));
        iterator_detail::adjust_heap(first, delta-1, 0, f);
    }
};
//------------------------------------------------------------------------------
/** Swaps the elements *first and *(last-1) and makes the range [first, last-1)
 * a heap.
 * @param f Binary comparision operator, which must not throw.
 * @note Move assignment of values must not throw.
 * @throw nothing
 * */
//------------------------------------------------------------------------------
template <class I, class F>
inline void pop_heap(I first, I last, F &&f)
{
    pop_heap_impl<I>::apply(first, last, f);
}
//------------------------------------------------------------------------------
template <class I>
struct is_heap_until_impl
{
    template <class F>
    inline static I apply(I first, I last, F &&f)
    {
        return iterator_detail::is_heap_until_(first, last, f);
    }
};
//------------------------------------------------------------------------------
/** Calculate the upper bound of the largest range beginning at first that is 
 * a maximal heap.
 * @param f Binary comparison function, which must not throw.
 * @return The last iterator X for which range [first, X) is a maximal heap. 
 * @throw nothing
 * */
//------------------------------------------------------------------------------
template <class I, class F>
inline I is_heap_until(I first, I last, F &&f)
{
    return is_heap_until_impl<I>::apply(first, last, f);
}
//------------------------------------------------------------------------------
template <class I>
struct is_heap_impl
{
    template <class F>
    inline static bool apply(I first, I last, F &&f)
    {
        return iterator_detail::is_heap_until_(first, last, f) == last;
    }
};
//------------------------------------------------------------------------------
/** Calculate the upper bound of the largest range beginning at first that is 
 * a maximal heap.
 * @param f Binary comparison function, which must not throw.
 * @return The last iterator X for which range [first, X) is a maximal heap. 
 * @throw nothing
 * */
//------------------------------------------------------------------------------
template <class I, class F>
inline bool is_heap(I first, I last, F &&f)
{
    return is_heap_impl<I>::apply(first, last, f);
}
//------------------------------------------------------------------------------
template <class I>
struct sort_heap_impl
{
    template <class F>
    inline static void apply(I first, I last, F &&f)
    {
        for( ; iterator::distance(first, last) > 1; --last)
            iterator::pop_heap(first, last, f);
    }
};
//------------------------------------------------------------------------------
/** Sorts a maximal heap using a binary comparision function.
 * @param f Binary comparison function, which must not throw.
 * @throw nothing
 * */
//------------------------------------------------------------------------------
template <class I, class F>
inline void sort_heap(I first, I last, F &&f)
{
    sort_heap_impl<I>::apply(first, last, f);
}

/** @} */

}}} // namespaces

#endif // NIC_9E2DCB41AA78AF59_NIC
