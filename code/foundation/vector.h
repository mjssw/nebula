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
#ifndef NIC_DAFE7A9AC06BEA05_NIC
#define NIC_DAFE7A9AC06BEA05_NIC

#include "iterator.h"
#include "assert.h"
#include "enable_if.h"
#include "exception/exception.h"
#include "tuple.h"
#include "memory.h"
#include "declval.h"
#include "minmax.h"
#include "hash.h"

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
/** Similar to the std::vector<...> template.
 * */
template <class T, class Allocator = memory::allocator<T>>
class vector
{        
public:
    using allocator_type = Allocator;
    
public:
    using value_type = typename memory::allocator_value<allocator_type>::type;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    
    /** @internal iterator == pointer is required. */
    using iterator = pointer;
    /** @internal const_iterator == const_pointer is required. */
    using const_iterator = const_pointer;
    using reverse_iterator = 
        nebula::foundation::iterator::reverse_iterator<iterator, vector>;
    using const_reverse_iterator = 
        nebula::foundation::iterator::reverse_iterator<const_iterator, vector>;
    
    inline vector()
    noexcept(is_nothrow_default_constructible<allocator_type>::value)
    : beg_(pointer()), end_(pointer()), fin_(pointer())
    {}
    
    inline vector(const vector &other)
    : beg_(pointer()), end_(pointer()), fin_(pointer()),
    alloc(memory::socc(other.alloc))
    {
        if(!other.empty())
        {
            beg_ = memory::allocate(alloc, other.size());
            try {
                copy_construct_delete_(
                    other.begin(), other.end(), beg_, other.size());
            } catch(...) {
                beg_ = pointer();
                throw;
            }
            
            end_ = beg_ + other.size();
            fin_ = end_;
        }
    }
    template <class A>
    inline vector(const vector &other, A &&alloc_)
    : beg_(pointer()), end_(pointer()), fin_(pointer()),
    alloc(foundation::forward<A>(alloc_))
    {
        if(!other.empty())
        {
            beg_ = memory::allocate(alloc, other.size());
            try {
                copy_construct_delete_(
                    other.begin(), other.end(), beg_, other.size());
            } catch(...) {
                beg_ = pointer();
                throw;
            }
            
            end_ = beg_ + other.size();
            fin_ = end_;
        }
    }
    inline vector(vector &other)
    : vector(static_cast<const vector &>(other))
    {}
    
    inline vector(vector &&other) noexcept
    : beg_(other.beg_), 
    end_(other.end_),
    fin_(other.fin_), 
    alloc(foundation::move(other.alloc))
    {
        other.invalidate();
    }
    template <class A, 
        bool flag = memory::is_always_equal<allocator_type>::value,
        _enable_if_c<flag>* = nullptr>
    inline vector(vector &&other, A &&alloc_) noexcept
    : beg_(other.beg_),
    end_(other.end_),
    fin_(other.fin_),
    alloc(foundation::forward<A>(alloc_))
    {
        other.invalidate();
    }
    template <class A, 
        bool flag = memory::is_always_equal<allocator_type>::value,
        _disable_if_c<flag>* = nullptr>
    inline vector(vector &&other, A &&alloc_)
    : beg_(pointer()), end_(pointer()), fin_(pointer()),
    alloc(foundation::forward<A>(alloc_))
    {
        if(alloc == other.alloc)
        {
            beg_ = other.beg_;
            end_ = other.end_;
            fin_ = other.end_;
            other.invalidate();
        }
        else
        {
            if(other.size())
            {
                beg_ = memory::allocate(alloc, other.size());
                size_type i = 0;
                try {
                    for( ; i < other.size(); ++i)
                        memory::construct(alloc, beg_ + i, 
                            foundation::move_if_noexcept(other[i]));
                } catch(...) {
                    delete_range_(beg_, beg_+i, other.size());
                    beg_ = pointer();
                    throw;
                }
                end_ = beg_ + other.size();
                fin_ = end_;
            }
        }
    }
    
    template <class T_, class A>
    inline vector(const size_type n, const T_ &x, A &&alloc_)
    : beg_(pointer()), end_(pointer()), fin_(pointer()),
    alloc(foundation::forward<A>(alloc_))
    {
        this->resize(n, x);
    }
    template <class T_>
    inline vector(const size_type n, const T_ &x)
    : beg_(pointer()), end_(pointer()), fin_(pointer())
    {
        this->resize(n, x);
    }
    
    inline explicit vector(const allocator_type &alloc_)
    : beg_(pointer()), end_(pointer()), fin_(pointer()), alloc(alloc_)
    {}
    inline explicit vector(allocator_type &&alloc_)
    : beg_(pointer()), 
    end_(pointer()), 
    fin_(pointer()),
    alloc(foundation::move(alloc_))
    {}
    
    template <class I>
    inline vector(I first, I last)
    : beg_(pointer()), end_(pointer()), fin_(pointer())
    {
        this->construct_from_range_(first, last);
    }
    template <class I, class A>
    inline vector(I first, I last, A &&alloc_)
    : beg_(pointer()), end_(pointer()), fin_(pointer()),
    alloc(foundation::forward<A>(alloc_))
    {
        this->construct_from_range_(first, last);
    }
    
    template <class T_>
    inline vector(std::initializer_list<T_> ilist)
    : beg_(pointer()), end_(pointer()), fin_(pointer())
    {
        if(ilist.size())
        {
            beg_ = memory::allocate(alloc, ilist.size());
            size_type i = 0;
            try {
                for( ; i < ilist.size(); ++i)
                    memory::construct(alloc, beg_ + i, *(ilist.begin() + i));
            } catch(...) {
                delete_range_(beg_, beg_ + i, ilist.size());
                beg_ = pointer();
                throw;
            }
            end_ = fin_ = beg_ + ilist.size();
        }
    }
    template <class T_, class A>
    inline vector(std::initializer_list<T_> ilist, A &&alloc_)
    : beg_(pointer()), end_(pointer()), fin_(pointer()),
    alloc(foundation::forward<A>(alloc_))
    {
        if(ilist.size())
        {
            beg_ = memory::allocate(alloc, ilist.size());
            size_type i = 0;
            try {
                for( ; i < ilist.size(); ++i)
                    memory::construct(alloc, beg_ + i, *(ilist.begin() + i));
            } catch(...) {
                delete_range_(beg_, beg_ + i, ilist.size());
                beg_ = pointer();
                throw;
            }
            end_ = fin_ = beg_ + ilist.size();
        }
    }
    
    /** @see adopt() 
     * */
    inline vector(pointer beg_p, pointer end_p, pointer fin_p)
    : beg_(beg_p), end_(end_p), fin_(fin_p)
    {}
    /** @see adopt() 
     * */
    template <class Allocator_>
    inline vector(pointer beg_p, pointer end_p, pointer fin_p,
        Allocator_ &&alc)
    : beg_(beg_p), end_(end_p), fin_(fin_p), 
    alloc(foundation::forward<Allocator_>(alc))
    {}
    /** @see adopt() 
     * */
    inline vector(tuple<pointer, pointer, pointer> x)
    : beg_(foundation::get<0>(x)), 
    end_(foundation::get<1>(x)), 
    fin_(foundation::get<2>(x))
    {}
    /** @see adopt() 
     * */
    template <class Allocator_>
    inline vector(tuple<pointer, pointer, pointer> x, Allocator_ &&alc)
    : beg_(foundation::get<0>(x)), 
    end_(foundation::get<1>(x)), 
    fin_(foundation::get<2>(x)),
    alloc(foundation::forward<Allocator_>(alc))
    {}
    
    inline ~vector() noexcept { 
        if(beg_)
        {
            delete_range_(beg_, end_, capacity());
            // Protection from multiple destructor calls.
            invalidate();
        }
    }
    
    inline vector &operator = (const vector &other)
    {
        if(this != &other)
        {
            if(memory::pocca<allocator_type>::value)
            {
                this->assign_alc_(
                    other.begin(),
                    other.end(),
                    other.get_allocator());
            }
            else
                this->assign(other.begin(), other.end());
        }
        return *this;
    }    
    inline vector &operator = (vector &&other) noexcept
    {
        n_assert(this != &other);
        
        reset();
        alloc = foundation::move(other.alloc);
        beg_ = other.beg_;
        end_ = other.end_;
        fin_ = other.fin_;
        other.invalidate();
        
        return *this;
    }
    
    template <class T_>
    inline vector &operator = (std::initializer_list<T_> ilist)
    {
        assign(ilist);
        return *this;
    }
    
    /** Swap the underlying array.
     * @note Invalidates all iterators and references.
     * */
    inline void swap(vector &other) noexcept
    {        
        foundation::swap(alloc, other.alloc);
        foundation::swap(beg_, other.beg_);
        foundation::swap(end_, other.end_);
        foundation::swap(fin_, other.fin_);
    }
    
    template <class T_>
    void assign(std::initializer_list<T_> ilist)
    {
        this->assign(ilist.begin(), ilist.end());
    }
    template <class I>
    inline void assign(I first, I last)
    {
        const size_type n = foundation::iterator::distance(first, last);
        
        if(n == 0) {
            reset();
            return;
        }
        else if(n <= capacity())
        {
            if(n <= size())
            {
                foundation::iterator::copy(first, last, beg_);
                destroy_range_(beg_+n, end_, alloc);
            }
            else
            {
                for(pointer i = beg_; i < end_; ++i)
                    *i = *first++;
                copy_construct_(first, last, end_);
            }
            
            end_ = beg_ + n;
        }
        else
        {
            pointer new_v = create_from_range_(first, last);
            this->reset();
            beg_ = new_v;
            end_ = fin_ = new_v + n;
        }
    }
    
    template <class T_,
        bool Cond = noexcept(declval<value_type>() = declval<T_>()),
        _disable_if_c<Cond>* = nullptr>
    void assign(const size_type &n, const T_ &x)
    {
        if(n == 0) {
            reset();
            return;
        }
        pointer new_v = memory::allocate(alloc, n);
        pointer i = new_v;
        try {
            for( ; i < new_v + n; ++i)
                memory::construct(alloc, i, x);
        } catch(...) {
            delete_range_(new_v, i, n);
            throw;
        }
        reset();
        beg_ = new_v;
        end_ = fin_ = new_v + n;
    }
    template <class T_,
        bool Cond = noexcept(declval<value_type>() = declval<T_>()),
        _enable_if_c<Cond>* = nullptr>
    void assign(const size_type &n, const T_ &x)
    {
        if(n == 0) {
            reset();
            return;
        }
        else if(n <= capacity())
        {
            if(n < size())
            {
                foundation::iterator::fill(beg_, beg_+n, x);
                destroy_range_(beg_+n, beg_+size(), alloc);
            }
            else
            {
                for(size_type i = 0; i < size(); ++i)
                    beg_[1] = x;
                for(size_type i = size(); i < n; ++i)
                    memory::construct(alloc, beg_+i, x);
            }
            
            end_ = beg_+n;
        }
        else
        {
            pointer new_v = memory::allocate(alloc, n);
            pointer i = new_v;
            try {
                for( ; i < new_v + n; ++i)
                    memory::construct(alloc, i, x);
            } catch(...) {
                delete_range_(new_v, i, n);
                throw;
            }
            reset();
            beg_ = new_v;
            end_ = fin_ = new_v + n;
        }
    }
    
    /** Take ownership of a dynamically allocated array.
     * Any resources held thus far will be released.
     * @param beg_p Pointer to the beginning of a memory chunk.
     * @param end_p Points to one past the last, constructed element.
     * I.e. [beg_p, end_p) are the only elements that need to be destroy()
     * by the allocator. beg_p == end_p is valid.
     * @param fin_p A pointer such that [beg_p, fin_p) spans the whole
     * range of the allocated memory. fin_p > beg_p is required.
     * @warning The memory pointed to by beg_p must have been allocated
     * with an allocator that compares equal to container's allocator.
     * @throw nothing
     * */
    inline void adopt(pointer beg_p, pointer end_p, pointer fin_p)
    {
        this->reset();
        beg_ = beg_p;
        end_ = end_p;
        fin_ = fin_p;
    }
    /** Same as adopt(pointer, pointer, pointer), except that this
     * version takes an allocator as well, to control the new sequence.
     * @throw nothing
     * */
    template <class Allocator_>
    inline void adopt(
        pointer beg_p,
        pointer end_p, 
        pointer fin_p,
        Allocator_ &&alc)
    {
        this->reset();
        alloc = foundation::forward<Allocator_>(alc);
        beg_ = beg_p;
        end_ = end_p;
        fin_ = fin_p;
    }
    
    inline void adopt(const tuple<pointer, pointer, pointer> &t)
    {
        this->reset();
        beg_ = foundation::get<0>(t);
        end_ = foundation::get<1>(t);
        fin_ = foundation::get<2>(t);
    }
    template <class Allocator_>
    inline void 
    adopt(const tuple<pointer, pointer, pointer> &t, Allocator_ &&alc)
    {
        this->reset();
        alloc = foundation::forward<Allocator_>(alc);
        beg_ = foundation::get<0>(t);
        end_ = foundation::get<1>(t);
        fin_ = foundation::get<2>(t);
    }
    
    /** Transfers ownership of the internal resources.
     * The resources must be managed by the internal allocator.
     * @throw noexcept
     * @see get_alloc().
     * */
    inline tuple<pointer, pointer, pointer> dismiss() noexcept
    {
        const tuple<pointer, pointer, pointer> res = 
            tuple<pointer, pointer, pointer>(beg_, end_, fin_);
        invalidate();
        return res;
    }
    
    /** Forces a move-assignment as if pocma is true. */
    inline vector &force_move(vector &&other) noexcept
    {
        n_assert(this != &other);
        
        reset();
        alloc = foundation::move(other.alloc);
        beg_ = other.beg_;
        end_ = other.end_;
        fin_ = other.fin_;
        other.invalidate();
        
        return *this;
    }
    /** Forces a swap as if pocs is true. */
    inline void force_swap(vector &other) noexcept
    {
        foundation::swap(alloc, other.alloc);
        foundation::swap(beg_, other.beg_);
        foundation::swap(end_, other.end_);
        foundation::swap(fin_, other.fin_);
    }
    
    inline const_reference operator [] (const size_type &i) const {
        return beg_[i];
    }
    inline reference operator [] (const size_type &i) {
        return beg_[i];
    }
    inline const_reference at(const size_type &i) const {
        if(i >= size())
            n_throw(out_of_range);
        return beg_[i];
    }
    inline reference at(const size_type &i) {
        if(i >= size())
            n_throw(out_of_range);
        return beg_[i];
    }
    
    inline pointer data() noexcept { 
        return beg_; 
    }
    inline const_pointer data() const noexcept { 
        return beg_;
    }
    
    inline iterator begin() noexcept {
        return iterator(beg_);
    }
    inline const_iterator begin() const noexcept {
        return iterator(beg_);
    }
    inline const_iterator cbegin() const noexcept {
        return iterator(beg_);
    }
    inline iterator end() noexcept {
        return iterator(end_);
    }
    inline const_iterator end() const noexcept {
        return iterator(end_);
    }
    inline const_iterator cend() const noexcept {
        return iterator(end_);
    }
    
    inline reverse_iterator rbegin() noexcept {
        return reverse_iterator(end());
    }
    inline const_reverse_iterator rbegin() const noexcept {
        return const_reverse_iterator(end());
    }
    inline const_reverse_iterator crbegin() const noexcept {
        return const_reverse_iterator(cend());
    }
    inline reverse_iterator rend() noexcept {
        return reverse_iterator(begin());
    }
    inline const_reverse_iterator rend() const noexcept {
        return const_reverse_iterator(begin());
    }
    inline const_reverse_iterator crend() const noexcept {
        return const_reverse_iterator(cbegin());
    }
    
    inline reference front() {
        return *beg_;
    }
    inline const_reference front() const {
        return *beg_;
    }
    inline reference back() {
        return *(end_ - 1);
    }
    inline const_reference back() const {
        return *(end_ - 1);
    }
    
    inline size_type size() const noexcept {
        return end_ - beg_;
    }
    inline size_type capacity() const noexcept {
        return fin_ - beg_;
    }
    inline bool empty() const noexcept {
        return begin() == end();
    }
    inline size_type max_size() const noexcept {
        return memory::max_size(alloc);
    }
    
    /** Allocate a chunk of memory that can hold at least n elements, in order
     * to avoid frequent allocations.
     * @param n The new capacity of the vector.
     * @note Strong exception guarantee if value_type is either copyable or
     * nothrow move-constructible or size() == 0,
     * otherwise basic exception guarantee.
     * @note Invalidates all iterators and references if n > capacity().
     * */
    inline void reserve(const size_type &n) 
    {
        if(n <= capacity())
            return;
        else if(capacity())
        {
            pointer new_v = memory::reallocate(alloc, beg_, capacity(), n);
            if(new_v != beg_)
            {
                const size_type delta = size();
                move_construct_if_noexcept_delete_(
                    beg_, end_, new_v, n);
                delete_range_(beg_, end_, capacity());
                beg_ = new_v;
                end_ = beg_ + delta;
                fin_ = beg_ + n;
            }
            else
                fin_ = beg_ + n;
        }
        else
        {
            beg_ = memory::allocate(alloc, n);
            end_ = beg_;
            fin_ = beg_ + n;
        }
    }
    /** Resizes the vector. 
     * @details Suppose the old size is m and we want to resize
     * to n. If n < m, then all elements [n, m) are destructed, if n > m,
     * then n-m new elements are added as if by calling emplace_back(x...)
     * n-m times. The case n == m is a noop.
     * @param n The new size.
     * @param x Parameter list to construct new objects of type value_type.
     * @note Will not throw if n <= size().
     * @note Same exception guarantee as reserve().
     * @note Invalidates all iterators and references if n > capacity(),
     * otherwise just end().
     * @warning 
     * */ 
    template <class ... X>
    inline void resize(const size_type &n, X && ... x)
    {
        if(n > size())
        {
            const size_t delta = n - size();
            if(n > capacity())
                reserve(req_buf_size_grow(delta));
            // If this throws the capacity will remain changed, but thats ok.
            construct_range_destroy_(end_, end_ + delta, x ...);
            end_ = end_ + delta;
        }
        else if(n < size())
        {
            // This branch can handle n == 0.
            destroy_range_(beg_ + n, end_);
            end_ = beg_ + n;
        }
        // else size() == n requires no action
    }
    /** Reduces the capacity() to size(), so we don't waste space.
     * @note Same exception guarantee as reserve().
     * @note Invalidates all iterators and references
     * if size() < capacity().
     * */ 
    inline void shrink_to_fit()
    {
        const size_type s = size();
        if(s == 0)
            reset();
        else if(s < capacity())
        {
            pointer new_v = memory::reallocate(alloc, beg_, capacity(), s);
            if(new_v != beg_)
            {
                move_construct_if_noexcept_delete_(
                    beg_, end_, new_v, s);
                delete_range_(beg_, end_, capacity());
                beg_ = new_v;
                end_ = beg_ + s;
            }
            fin_ = end_;
        }
    }
    
    /** Construct a new 'tail' element.
     * @param x Parameter list to construct an element with.
     * @return Iterator to the created element.
     * @note Same exception guarantee as reserve().
     * @note Invalidates all iterators and references if the new size is greater
     * than the capacity, otherwise just the past-the-end iterator.
     * */ 
    template <class ... X>
    inline void emplace_back(X && ... x)
    {
        if(size() == capacity())
            reserve(req_buf_size_grow(1));
        memory::construct(alloc,
            end_++, 
            foundation::forward<X>(x)...);
    }
    /** Construct an a new element at position pos.
     * @param pos The position to construct the new element.
     * @param x Parameter list to construct an element with.
     * @return Iterator to the created element.
     * @note Strong exception guarantee if value_type is nothrow movable,
     * otherwise just basic exception guarantee.
     * @note Invalidates all iterators and references if the new size is greater
     * than the capacity, otherwise just the [pos, end()) iterators.
     * */
    template <class ... X>
    inline iterator emplace(const_iterator pos, X && ... x)
    {        
        pointer p = to_ptr(pos);
        
        if(p == end_) {
            emplace_back(foundation::forward<X>(x)...);
            return end()-1;
        }
        
        const difference_type p_offset = p - beg_;
        
        if(size() == capacity())
        {
            const size_type new_s = size() + 1;
            const size_type ncapacity = req_buf_size_grow(1);
            pointer new_v = memory::reallocate(
                alloc, beg_, capacity(), ncapacity);
            if(new_v != beg_)
            {
                move_construct_if_noexcept_delete_(
                    beg_, p, new_v, ncapacity);
                try {
                    move_construct_if_noexcept_(
                        p, end_, new_v + (p_offset + 1));
                } catch(...) {
                    destroy_range_(new_v, new_v + p_offset);
                    memory::deallocate(alloc, new_v, ncapacity);
                    throw;
                }
                try {
                    memory::construct(
                        alloc,
                        new_v + p_offset, 
                        foundation::forward<X>(x)...);
                } catch(...) {
                    destroy_range_(new_v, new_v + p_offset - 1);
                    destroy_range_(new_v + p_offset + 1, new_v + new_s);
                    memory::deallocate(alloc, new_v, ncapacity);
                    throw;
                }
                this->reset();
                end_ = new_v + new_s;
                fin_ = new_v + ncapacity;
                beg_ = new_v;
                return begin() + p_offset;
            }
            else
                fin_ = beg_ + ncapacity;
        }
        
        memory::construct(
            alloc, 
            end_,
            foundation::move_if_noexcept(*(end()-1)));
        
        try {
            foundation::iterator::move(
                rbegin() + 1, 
                rend() - p_offset,
                rbegin());
            memory::construct(alloc,
                p, 
                foundation::forward<X>(x)...);
        } catch(...) {
            // We only destroy the element at end(),
            // so we don't leak.
            memory::destroy(alloc, end_);
            throw;
        }
        end_++;
        return iterator(p);
    }
    /** Works like emplace(begin(), ...). */
    template <class ... X>
    inline void emplace_front(X && ... x)
    {
        if(empty())
            emplace_back(foundation::forward<X>(x)...);
        else
            emplace(begin(), foundation::forward<X>(x)...);
    }
    
    /** Alias for emplace_back().
     * @param pos The position to construct the new element.
     * @param x Object to construct an element with.
     * @return Iterator to the created element.
     * @see emplace_back()
     * */
    template <class X>
    inline void push_back(X &&x) {
        this->emplace_back(foundation::forward<X>(x));
    }
    /** Alias for emplace().
     * @param pos The position to construct the new element.
     * @param x Object to construct an element with.
     * @return Iterator to the created element.
     * @see emplace()
     * */
    template <class X>
    inline iterator insert(const_iterator pos, X &&x) {
        return this->emplace(pos, foundation::forward<X>(x));
    }
    /** Insert the range [first, last) at pos.
     * @param pos Must be in the range [begin(), end()].
     * @note first == last is allowed, the function returns right away.
     * @note Strong exception guarantee only if inserting at end().
     * @note Invalidates all iterators and references if the new size is greater
     * than the capacity, otherwise just the [pos, end()) iterators.
     * */
    template <class I,
        _enable_if<foundation::iterator::is_iterator<I>>* = nullptr>
    inline iterator insert(const_iterator pos, I first, I last)
    {
        if(pos == cend()) {
            const difference_type d = pos-cbegin();
            this->append(first, last);
            return begin()+d;
        }
        
        const size_type n = foundation::iterator::distance(first, last);
        if(n == 0)
            return iterator(to_ptr(pos));
        
        pointer p = to_ptr(pos);
        const size_type new_s = size() + n;
        
        if(new_s > capacity())
        {
            const difference_type p_offset = p - beg_;
            const size_type ncapacity = req_buf_size_grow(n);
            pointer new_v = memory::reallocate(
                alloc, beg_, capacity(), ncapacity);
            if(new_v != beg_)
            {
                // First we move the existing data and leave a gap
                // for the range to be inserted.
                // move/copy [beg_, p) -> [new_v, new_v + p_offset)
                // move/copy [p, end_) -> [new_p + (p_offset + n), ...)
                
                move_construct_if_noexcept_delete_(
                    beg_, p, new_v, ncapacity);
                try {
                    move_construct_if_noexcept_(
                        p, end_, new_v + (p_offset + n));
                } catch(...) {
                    destroy_range_(new_v, new_v + p_offset);
                    memory::deallocate(alloc, new_v, ncapacity);
                    throw;
                }
                
                // Place the new data in the gap.
                
                pointer k = new_v + p_offset;
                try {
                    copy_construct_(
                        first, last, new_v + p_offset);
                } catch(...) {
                    destroy_range_(new_v, new_v + p_offset);
                    destroy_range_(new_v + p_offset + n, new_v + new_s);
                    memory::deallocate(alloc, new_v, ncapacity);
                    throw;
                }
                
                // Delete old data.
                
                this->reset();
                
                // Everything worked fine, update internals.
                
                end_ = new_v + new_s;
                beg_ = new_v;
                fin_ = beg_ + ncapacity;
                return iterator(beg_ + p_offset);
            }
            else
                fin_ = beg_ + ncapacity; // realloc worked -> fall through.
        }
                    
        if(p+n >= end_)
        {
            using IsPOD = meta::_and<
                is_pointer<I>,
                is_pod<value_type>,
                is_same<value_type,
                    typename foundation::iterator::iterator_value<I>::type>>;
                
            move_construct_if_noexcept_(p, end_, p+n);
            
            if(IsPOD::value)
            {
                foundation::iterator::copy_n(first, end_-p, p);
                foundation::iterator::copy(
                    foundation::iterator::advanced(first, end_-p),
                    last,
                    end_);
            }
            else
            {
                pointer q = p;
                try {
                    while(q < end_)
                        *q++ = *first++;
                    while(q < p+n)
                        memory::construct(alloc, q++, *first++);
                } catch(...) {
                    destroy_range_(p+n, p+2*n);
                    destroy_range_(end_, q);
                    throw;
                }
            }
        }
        else
        {
            const size_type m = end_ - (p+n);
            move_construct_if_noexcept_(p+m, end_, end_);
            foundation::iterator::move(p, p+m, p+n);
            foundation::iterator::copy(first, last, p);
        }
        
        end_ += n;
        return iterator(p);
    }
    
    /** Insert n copies of e into the vector at position pos.
     * @param pos The position to construct the new element.
     * @param x Parameter list to construct an element with.
     * @note Strong exception guarantee only if inserting at end().
     * @note Invalidates all iterators and references if the new size is greater
     * than the capacity, otherwise just the [pos, end()) iterators.
     * */
    template <class X>
    inline iterator insert(const_iterator pos, const size_type n, const X &e)
    {
        if(n == 0)
            return iterator(to_ptr(pos));
        
        pointer p = to_ptr(pos);
        const size_type new_s = size() + n;
        
        if(new_s > capacity())
        {
            const difference_type p_offset = p - beg_;
            const size_type ncapacity = req_buf_size_grow(n);
            pointer new_v = memory::reallocate(
                alloc, beg_, capacity(), ncapacity);
            if(new_v != beg_)
            {
                // First we move the existing data and leave a gap
                // for the range to be inserted.
                // move/copy [beg_, p) -> [new_v, new_v + p_offset)
                // move/copy [p, end_) -> [new_p + (p_offset + n), ...)
                
                move_construct_if_noexcept_delete_(
                    beg_, p, new_v, ncapacity);
                try {
                    move_construct_if_noexcept_(
                        p, end_, new_v + (p_offset + n));
                } catch(...) {
                    destroy_range_(new_v, new_v + p_offset);
                    memory::deallocate(alloc, new_v, ncapacity);
                    throw;
                }
                
                // Place the new data in the gap
                
                try {
                    pointer new_p = new_v + p_offset;
                    construct_range_destroy_(new_p, new_p + n, e);
                } catch(...) {
                    destroy_range_(new_v, new_v + p_offset);
                    destroy_range_(new_v + p_offset + n, new_v + new_s);
                    memory::deallocate(alloc, new_v, ncapacity);
                    throw;
                }
                
                // Delete old data.
                
                delete_range_(beg_, end_, capacity());
                
                // Everything worked fine, update internals.
                
                end_ = new_v + new_s;
                beg_ = new_v;
                fin_ = beg_ + ncapacity;
                return iterator(beg_ + p_offset);
            }
            else
                fin_ = beg_ + ncapacity; // realloc worked -> fall through.
        }
        
        // Make a gab for the new data.
        // Move [p, end_) -> [p+n, ...)
        
        if(p+n >= end_)
        {
            move_construct_if_noexcept_(p, end_, p+n);
            pointer q = p;
            try {
                while(q < end_)
                    *q++ = e;
                while(q < p+n)
                    memory::construct(alloc, q++, e);
            } catch(...) {
                destroy_range_(p+n, p+2*n);
                destroy_range_(end_, q);
                throw;
            }
        }
        else
        {
            const size_type m = end_ - (p+n);
            move_construct_if_noexcept_(p+m, end_, end_);
            foundation::iterator::move(p, p+m, p+n);
            foundation::iterator::fill(p, p+n, e);
        }
        
        end_ += n;
        return iterator(p);
    }
    
    /** Basically this is v.insert(v.end(), first, last).
     * */
    template <class I,
        _enable_if<foundation::iterator::is_iterator<I>>* = nullptr>
    inline vector &append(I first, I last)
    {
        const size_type n = foundation::iterator::distance(first, last);
        if(n == 0)
            return *this;
            
        if(size() + n >= capacity())
        {        
            const size_type ncapacity = req_buf_size_grow(n);
            const size_type new_s = size() + n;
            pointer new_v = memory::reallocate(
                alloc, beg_, capacity(), ncapacity);
                
            if(new_v != beg_)
            {
                move_construct_if_noexcept_delete_(
                    beg_, end_, new_v, ncapacity);
                    
                try {
                    copy_construct_(first, last, new_v + size());
                } catch(...) {
                    destroy_range_(new_v, new_v + size());
                    memory::deallocate(alloc, new_v, ncapacity);
                    throw;
                }
                
                reset();
                
                end_ = new_v + new_s;
                beg_ = new_v;
                fin_ = new_v + ncapacity;
                
                return *this;
            }
            else
                fin_ = beg_ + ncapacity;
        }
        
        copy_construct_(first, last, end_);
        end_ += n;
        return *this;
    }
    inline vector &append(const_pointer x, const size_type n) {
        return this->append(x, x+n);
    }
    inline vector &append(const vector &other) {
        return this->append(other.begin(), other.end());
    }
    inline vector &append(vector &&other) {
        if(empty())
            *this = foundation::move(other);
        else
            this->append(other);
        return *this;
    }
    template <class T_>
    inline vector &append(std::initializer_list<T_> ilist) {
        return this->append(ilist.begin(), ilist.end());
    }
    
    /** Erase the last element in the range.
     * @param i The element to erase.
     * @return Iterator to the element following the erased one.
     * @throw nothing
     * @note Invalidates the past-the-end iterator and the iterator
     * to the last element.
     * */
    inline void pop_back() noexcept {
        memory::destroy(alloc, --end_);
    }
    /** Alias for erase(begin()).
     * */
    inline void pop_front() noexcept {
        this->erase(begin());
    }
    
    /** Erase a single element.
     * @param i The element to erase.
     * @return Iterator to the element following the erased one.
     * @note Nothrow if value_type provides a nothrow move-assignemnt
     * operator, otherwise basic exception guarantee.
     * @note Invalidates the iterators [i, end()).
     * */
    inline iterator erase(const_iterator i)
    {
        foundation::iterator::move(i+1, cend(), to_ptr(i));
        memory::destroy(alloc, --end_);
        return iterator(to_ptr(i));
    }
    /** Erase a range of elements.
     * @param first Iterator to the first element to erase.
     * @param last Iterator to the element past the last one to erase.
     * @return Iterator to the element following the erased element, which
     * can be end().
     * @note Nothrow if value_type provides a nothrow move-assignemnt
     * operator, otherwise basic exception guarantee.
     * @note Invalidates the iterators [first, end()).
     * */
    inline iterator erase(const_iterator first, const_iterator last)
    {
        foundation::iterator::move(last, cend(), to_ptr(first));
        pointer new_end_ = end_ - foundation::iterator::distance(first, last);
        destroy_range_(new_end_, end_);
        end_ = new_end_;
        return iterator(to_ptr(first));
    }
   
    /** Destroys all elements and sets the size to 0, the capacity will
     * remain unchanged.
     * @throw nothing
     * @note Invalidates all iterators but begin().
     * */
    inline void clear() noexcept {
        if(!empty())
        {
            destroy_range_(beg_, end_);
            end_ = beg_;
        }
    }
    /** clear() the vector and free all associated resources.
     * @throw nothing
     * @note Invalidates all iterators.
     * */
    inline void reset() noexcept {
        if(beg_)
        {
            destroy_range_(beg_, end_);
            memory::deallocate(alloc, beg_, capacity());
            invalidate();
        }
    }
    
    /** Get a copy of the allocator.
     * */
    inline allocator_type get_allocator() const {
        return alloc;
    }
    
private:
    inline size_type req_buf_size_grow(const size_type &n) noexcept {
        return capacity() == 0 ? n : (capacity() + n) * size_type(2);
    }
    
    inline pointer to_ptr(iterator i) const noexcept {
        return i;
    }
    inline const_pointer to_cptr(iterator i) const noexcept {
        return i;
    }
    inline pointer to_ptr(const_iterator i) const noexcept {
        return const_cast<pointer>(i);
    }
    inline const_pointer to_cptr(const_iterator i) const noexcept {
        return i;
    }
    
    inline void internal_move_(vector &&other) noexcept
    {
        this->beg_ = other.beg_;
        this->end_ = other.end_;
        this->fin_ = other.fin_;
        this->alloc = other.alloc;
        other.invalidate();
    }
    
    template <class P, class A>
    inline void 
    delete_range_(P first, const P last, size_type capcty, A &alc) noexcept
    {
        destroy_range_(first, last, alc);
        memory::deallocate(alc, first, capcty); 
    }
    template <class P>
    inline void delete_range_(P first, const P last, size_type capcty) noexcept
    {
        destroy_range_(first, last);
        memory::deallocate(alloc, first, capcty); 
    }
    template <class P, class A>
    inline void destroy_range_(P first, const P last, A &alc) noexcept
    {
        while(first < last)
            memory::destroy(alc, first++);
    }
    template <class P>
    inline void destroy_range_(P first, const P last) noexcept
    {
        while(first < last)
            memory::destroy(alloc, first++);
    }
    
    template <class P, class ... X>
    inline void 
    construct_range_destroy_(P first, const P last, X && ... x)
    {
        pointer i = first;
        try {
            while(i < last)
                memory::construct(alloc, i++, std::forward<X>(x)...);
        } catch(...) {
            destroy_range_(first, i);
            throw;
        }
    }
    
    template <class P, class Q>
    using test_pod_copy = meta::_and<
        is_pointer<P>,
        is_pointer<Q>,
        is_pod<value_type>,
        is_same<value_type,
            typename foundation::iterator::iterator_value<P>::type>>;
    
    template <class P, class Q,
        class Cond = test_pod_copy<P, Q>,
        _enable_if<Cond>* = nullptr>
    inline void copy_construct_(
        P first, const P last, Q first2)
    {
        foundation::iterator::copy(first, last, first2);
    }
    template <class P, class Q,
        class Cond = test_pod_copy<P, Q>,
        _disable_if<Cond>* = nullptr>
    inline void copy_construct_(
        P first, const P last, Q first2)
    {
        pointer i = first2;
        try {
            while(first != last)
            {
                memory::construct(
                    alloc,
                    i++,
                    *first++);
            }
        } catch(...) {
            destroy_range_(first2, i);
            throw;
        }
    }
    
    template <class P, class Q>
    inline void copy_construct_delete_(
        P first, 
        const P last, 
        Q first2, 
        const size_type capcty)
    {
        copy_construct_delete_(first, last, first2, capcty, alloc);
    }
    template <class P, class Q, class Alloc,
        class Cond = test_pod_copy<P, Q>,
        _enable_if<Cond>* = nullptr>
    inline void copy_construct_delete_(
        P first, 
        const P last, 
        Q first2, 
        const size_type capcty,
        Alloc &alc)
    {
        foundation::iterator::copy(first, last, first2);
    }
    template <class P, class Q, class Alloc,
        class Cond = test_pod_copy<P, Q>,
        _disable_if<Cond>* = nullptr>
    inline void copy_construct_delete_(
        P first, 
        const P last, 
        Q first2, 
        const size_type capcty,
        Alloc &alc)
    {
        pointer i = first2;
        try {
            while(first < last)
            {
                memory::construct(
                    alc,
                    i++,
                    *first++);
            }
        } catch(...) {
            delete_range_(first2, i, capcty, alc);
            throw;
        }
    }
    
    template <class P, class Q,
        class Cond = test_pod_copy<P, Q>,
        _enable_if<Cond>* = nullptr>
    inline void
    move_construct_if_noexcept_(
        P first, P last, Q first2)
    {
        foundation::iterator::copy(first, last, first2);
    }
    template <class P, class Q,
        class Cond = test_pod_copy<P, Q>,
        _disable_if<Cond>* = nullptr>
    inline void
    move_construct_if_noexcept_(
        P first, P last, Q first2)
    {
        pointer i = first2;
        try {
            while(first < last)
            {
                memory::construct(
                    alloc,
                    i++,
                    foundation::move_if_noexcept(*first++));
            }
        } catch(...) {
            destroy_range_(first2, i);
            throw;
        }
    }
    
    template <class P, class Q,
        class Cond = test_pod_copy<P, Q>,
        _enable_if<Cond>* = nullptr>
    inline void move_construct_if_noexcept_delete_(
        P first, 
        const P last,
        Q first2,
        const size_type capcty)
    {
        foundation::iterator::copy(first, last, first2);
    }
    template <class P, class Q,
        class Cond = test_pod_copy<P, Q>,
        _disable_if<Cond>* = nullptr>
    inline void move_construct_if_noexcept_delete_(
        P first, 
        const P last,
        Q first2,
        const size_type capcty)
    {
        pointer i = first2;
        try {
            while(first < last)
                memory::construct(
                    alloc,
                    i++,
                    foundation::move_if_noexcept(*first++));
        } catch(...) {
            delete_range_(first2, i, capcty);
            throw;
        }
    }
    
    template <class I>
    inline void construct_from_range_(I first, I last)
    {
        const size_type n = foundation::iterator::distance(first, last);
        beg_ = memory::allocate(alloc, n);
        copy_construct_delete_(first, last, beg_, n);        
        end_ = fin_ = beg_ + n;
    }
    
    template <class I>
    inline pointer create_from_range_(I first, I last)
    {
        return create_from_range_(first, last, alloc);
    }
    template <class I, class Alloc>
    inline pointer create_from_range_(I first, I last, Alloc &alc)
    {
        const size_type n = foundation::iterator::distance(first, last);
        
        n_assert(n > 0);
        
        pointer new_v = memory::allocate(alc, n);
        copy_construct_delete_(first, last, new_v, n, alc);
        
        return new_v;
    }

    template <class I, class Alloc>
    inline void assign_alc_(I first, I last, Alloc &&alc)
    {
        const size_type n = foundation::iterator::distance(first, last);
        
        if(n == 0) {
            reset();
            this->alloc = foundation::forward<Alloc>(alc);
            return;
        }
        else if(n <= capacity() && alloc == alc)
        {
            if(n <= size())
            {
                foundation::iterator::copy(first, last, beg_);
                destroy_range_(beg_+n, end_, alloc);
            }
            else
            {
                for(pointer i = beg_; i < end_; ++i)
                    *i = *first++;
                copy_construct_(first, last, end_);
            }
            
            end_ = beg_ + n;
            alloc = foundation::forward<Alloc>(alc);
        }
        else
        {
            pointer new_v = create_from_range_(first, last, alc);
            this->reset();
            beg_ = new_v;
            end_ = fin_ = new_v + n;
            alloc = foundation::forward<Alloc>(alc);
        }
    }
    
    inline void invalidate() noexcept {
        beg_ = end_ = fin_ = pointer();
    }

    pointer beg_, end_, fin_;
    allocator_type alloc;
    
    template <class, class, class>
    friend class basic_string;
};

//==============================================================================
template <class T, class A>
inline bool operator == (const vector<T, A> &lhs, const vector<T, A> &rhs)
{
    return foundation::iterator::equal(
        lhs.begin(), lhs.end(),
        rhs.begin(), rhs.end());
}
//------------------------------------------------------------------------------
template <class T, class A>
inline bool operator != (const vector<T, A> &lhs, const vector<T, A> &rhs)
{
    return !(lhs == rhs);
}
//------------------------------------------------------------------------------
template <class T, class A>
inline bool operator < (const vector<T, A> &lhs, const vector<T, A> &rhs)
{
    return foundation::iterator::lexicographical_compare(
        lhs.begin(), lhs.end(),
        rhs.begin(), rhs.end(),
        less<T>());
}
//------------------------------------------------------------------------------
template <class T, class A>
inline bool operator <= (const vector<T, A> &lhs, const vector<T, A> &rhs)
{
    return foundation::iterator::lexicographical_compare(
        lhs.begin(), lhs.end(),
        rhs.begin(), rhs.end(),
        less_equal<T>());
}
//------------------------------------------------------------------------------
template <class T, class A>
inline bool operator > (const vector<T, A> &lhs, const vector<T, A> &rhs)
{
    return foundation::iterator::lexicographical_compare(
        lhs.begin(), lhs.end(),
        rhs.begin(), rhs.end(),
        greater<T>());
}
//------------------------------------------------------------------------------
template <class T, class A>
inline bool operator >= (const vector<T, A> &lhs, const vector<T, A> &rhs)
{
    return foundation::iterator::lexicographical_compare(
        lhs.begin(), lhs.end(),
        rhs.begin(), rhs.end(),
        greater_equal<T>());
}

//==============================================================================
template <class T, class A>
struct hash<vector<T, A>>
{
    using result_type = size_t;
    inline size_t operator () (const vector<T, A> &x) const noexcept
    {
        return hash_detail::hash_blob(x.data(), x.size());
    }
};

/** @} */

}} // namespaces

#endif // NIC_DAFE7A9AC06BEA05_NIC
