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
#ifndef NIC_2A90BD8FAFD3D503_NIC
#define NIC_2A90BD8FAFD3D503_NIC

#include "memory.h"
#include "type_traits.h"
#include "enable_if.h"
#include "swap.h"
#include "move.h"
#include "iterator.h"
#include "scope_exit.h"

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <class T, class Allocator = memory::allocator<T>>
class list
{
    struct node_base
    {
        inline node_base() noexcept
        : prv(this), nxt(this)
        {}
        
        inline node_base(const node_base &other) noexcept {
            if(other.prv == &other)
            {
                prv = nxt = this;
            }
            else
            {
                prv = other.prv;
                nxt = other.nxt;
                prv->nxt = this;
                nxt->prv = this;
            }
        }
        
        inline node_base(node_base *p, node_base *n) noexcept
        : prv(p), nxt(n)
        {}
        
        inline node_base &operator = (const node_base &other) noexcept {
            
            if(other.prv == &other)
            {
                prv = nxt = this;
            }
            else
            {
                prv = other.prv;
                nxt = other.nxt;
                prv->nxt = this;
                nxt->prv = this;
            }
            
            return *this;
        }
        
        node_base *prv;
        node_base *nxt;
    };
    
    struct node : public node_base
    {
        template <class ... X>
        inline node(node_base *p, node_base *n, X && ... x)
        : node_base(p, n), val(foundation::forward<X>(x)...)
        {}
        
        T val;
    };
    
    template <class X>
    using iter_value = meta::_if<
        is_const<X>,
        const T,
        T>;
    
    template <class NodePtr>
    struct iterator_impl 
    : public iterator::iterator_facade<
        iterator_impl<NodePtr>,
        iter_value<NodePtr>,
        iterator::bidirectional_traversal_tag,
        iterator::lvalue_iterator_tag,
        iter_value<NodePtr> &,
        iter_value<NodePtr> *,
        ptrdiff_t
    >
    {
    public:
        inline iterator_impl() noexcept
        : i(nullptr)
        {}
        inline iterator_impl(NodePtr i_) noexcept
        : i(i_)
        {}
        iterator_impl(iterator_impl &) = default;
        iterator_impl(const iterator_impl &) = default;
        iterator_impl(iterator_impl &&) = default;
        
        template <class J>
        inline iterator_impl(const iterator_impl<J> &other) noexcept
        : i(other.get())
        {}
        template <class J>
        inline iterator_impl(iterator_impl<J> &&other) noexcept
        : i(other.get())
        {}
        
        iterator_impl &operator = (const iterator_impl &) = default;
        iterator_impl &operator = (iterator_impl &&) = default;
        
        template <class J>
        inline iterator_impl &operator = (
            const iterator_impl<J> &other) noexcept
        {
            i = other.get();
            return *this;
        }
        template <class J>
        inline iterator_impl &operator = (iterator_impl<J> &&other) noexcept
        {
            i = other.get();
            return *this;
        }
        
        inline iter_value<NodePtr> &dereference() const
        {
            return *const_cast<iter_value<NodePtr> *>(
                &static_cast<const node *>(i)->val);
        }
        
        inline void increment() noexcept
        {
            i = i->nxt;
        }
        inline void decrement() noexcept
        {
            i = i->prv;
        }
        
        inline bool equal(const iterator_impl &other) const noexcept
        {
            return i == other.i;
        }
        
        inline const NodePtr get() const noexcept { return i; }
        inline NodePtr get() noexcept { return i; }
        
    private:
        NodePtr i;
    };
    
    using internal_allocator_type 
        = typename memory::rebind<Allocator, node>::type;
    
public:
    using allocator_type = Allocator;
    using value_type = typename memory::allocator_value<allocator_type>::type;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    
    using iterator = iterator_impl<node_base *>;
    using const_iterator = iterator_impl<const node_base *>;
    using reverse_iterator = foundation::iterator::reverse_iterator<iterator>;
    using const_reverse_iterator 
        = foundation::iterator::reverse_iterator<const_iterator>;
    
    list()
    : size_(0)
    {}
    inline list(list &other)
    : alloc(memory::socc(other.alloc)),
    size_(0)
    {
        try {
            this->insert(begin(), other.begin(), other.end());
        } catch(...) {
            this->reset();
            throw;
        } 
    }
    inline list(const list &other)
    : alloc(memory::socc(other.alloc)),
    size_(0)
    {
        try {
            this->insert(begin(), other.begin(), other.end());
        } catch(...) {
            this->reset();
            throw;
        }       
    }
    inline list(list &&other)
    : alloc(foundation::move(other.alloc)), size_(other.size())
    {
        this->fin = other.fin;
        other.invalidate();
    }
    
    template <class AL>
    inline list(const list &other, AL &&new_alloc)
    : alloc(foundation::move(new_alloc)),
    size_(0)
    {
        try {
            this->insert(begin(), other.begin(), other.end());
        } catch(...) {
            this->reset();
            throw;
        }       
    }
    
    template <class Iter, class AL>
    inline list(Iter first, Iter last, AL &&new_alloc)
    : alloc(foundation::move(new_alloc)), size_(0)
    {
        this->assign(first, last);   
    }
    template <class Iter>
    inline list(Iter first, Iter last)
    : size_(0)
    {
        this->assign(first, last);   
    }
    
    inline ~list() noexcept
    {
        this->reset();
    }
    
    template <class T_, class AL>
    inline list(std::initializer_list<T_> ilist, AL &&new_alloc)
    : list(ilist.begin(), ilist.end(), foundation::forward<AL>(new_alloc))
    {}
    template <class T_>
    inline list(std::initializer_list<T_> ilist)
    : list(ilist.begin(), ilist.end())
    {}
    
    template <class Cond = memory::pocca<internal_allocator_type>,
        typename enable_if<Cond>::type* = nullptr>
    inline list &operator = (list &other)
    {
        return this->assign(other.begin(), other.end(), other.alloc);
    }
    template <class Cond = memory::pocca<internal_allocator_type>,
        typename disable_if<Cond>::type* = nullptr>
    inline list &operator = (list &other)
    {
        return this->assign(other.begin(), other.end());
    }
    template <class Cond = memory::pocca<internal_allocator_type>,
        typename enable_if<Cond>::type* = nullptr>
    inline list &operator = (const list &other)
    {
        return this->assign(other.begin(), other.end(), other.alloc);
    }
    template <class Cond = memory::pocca<internal_allocator_type>,
        typename disable_if<Cond>::type* = nullptr>
    inline list &operator = (const list &other)
    {
        return this->assign(other.begin(), other.end());
    }
    
    inline list &operator = (list &&other) noexcept
    {
        reset();
        alloc = foundation::move(other.alloc);
        fin = other.fin;
        size_ = other.size();
        other.invalidate();
        return *this;
    }
    
    template <class T_>
    inline list &operator = (std::initializer_list<T_> ilist) {
        return this->assign(ilist);
    }
    
    inline void swap(list &other) noexcept
    {
        foundation::swap(alloc, other.alloc);
        foundation::swap(size_, other.size_);
        foundation::swap(fin, other.fin);
    }
    
    template <class Iter>
    inline list &assign(Iter f, Iter l)
    {
        if(f == l)
            reset();
        else if(!empty())
        {            
            Iter f_ = f;
            iterator k = begin();
            
            while(k != end() && f_ != l)
                *k++ = *f_++;
            
            if(f_ != l)
            {
                 this->insert_range_alloc_(end_(), f_, l, size_, alloc);
            }
            else
            {
                this->erase(k, end());
            }
        }
        else
        {
            this->insert_range_alloc_(end_(), f, l, size_, alloc);
        }
        
        return *this;
    }
    template <class Iter, class AL>
    inline list &assign(Iter f, Iter l, AL &&alc)
    {        
        if(f == l) {
            reset();
            alloc = foundation::forward<AL>(alc);
        }
        else if(alloc == alc && !empty())
        {            
            Iter f_ = f;
            iterator k = begin();
            
            while(k != end() && f_ != l)
                *k++ = *f_++;
            
            internal_allocator_type tmp_alc = foundation::forward<AL>(alc);
            
            if(f_ != l)
            {
                 this->insert_range_alloc_(end_(), f_, l, size_, tmp_alc);
            }
            else
            {
                this->erase(k, end());
            }
            
            alloc = foundation::move(tmp_alc);
        }
        else
        {
            internal_allocator_type tmp_alc = foundation::forward<AL>(alc);
            node_base tmp;
            size_type s = 0;
            this->insert_range_alloc_(&tmp, f, l, s, tmp_alc);
            reset_(end_());
            size_ = s;
            fin = tmp;
            alloc = foundation::move(tmp_alc);
        }
        
        return *this;
    }
    
    template <class T_>
    inline list &assign(std::initializer_list<T_> ilist)
    {        
        return this->assign(ilist.begin(), ilist.end());
    }
    template <class T_, class AL>
    inline list &assign(std::initializer_list<T_> ilist, AL &&alc)
    {        
        return this->assign(ilist.begin(), ilist.end(), alc);
    }
    
    template <class T_ = value_type>
    inline void resize(const size_type n, const T_ &x = T_())
    {
        if(n > size())
        {
            while(n > size())
                emplace_back(x);
        }
        else if (n == size()) ;
        else
        {
            while(n < size())
                pop_back();
        }
    }
    
    inline iterator begin() noexcept {
        return iterator(end_()->nxt);
    }
    inline const_iterator begin() const noexcept {
        return const_iterator(end_()->nxt);
    }
    inline const_iterator cbegin() const noexcept {
        return const_iterator(end_()->nxt);
    }
    inline iterator end() noexcept {
        return iterator(end_());
    }
    inline const_iterator end() const noexcept {
        return const_iterator(end_());
    }
    inline const_iterator cend() const noexcept {
        return const_iterator(end_());
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
    
    inline reference front() noexcept {
        return *begin();
    }
    inline const_reference front() const noexcept {
        return *begin();
    }
    inline reference back() noexcept {
        return *--end();
    }
    inline const_reference back() const noexcept {
        return *--end();
    }
    
    template <class ... X>
    inline void emplace_back(X && ... x) {
        this->emplace_(end_(), size_, foundation::forward<X>(x)...);
    }
    inline void pop_back() noexcept {
        this->erase_(last_());
    }
    
    template <class ... X>
    inline void emplace_front(X && ... x) {
        this->emplace_(beg_(), size_, foundation::forward<X>(x)...);
    }
    inline void pop_front() noexcept {
        this->erase_(beg_());
    }
    
    template <class ... X>
    inline void push_back(X && ... x) {
        this->emplace_(end_(), size_, foundation::forward<X>(x)...);
    }
    template <class ... X>
    inline void push_front(X && ... x) {
        this->emplace_(beg_(), size_, foundation::forward<X>(x)...);
    }
    
    template <class ... X>
    inline iterator emplace(const_iterator pos, X && ... x)
    {
        node_base * const nb = const_cast<node_base *>(pos.get());
        this->emplace_(nb, size_, foundation::forward<X>(x)...);
        return iterator(nb->prv);
    }
    
    template <class I>
    inline iterator insert(const_iterator pos, I first, I last)
    {
        for(I i = first; i != last; ++i)
            this->emplace(pos, *i);
        return iterator(const_cast<node_base *>(pos.get()));
    }
    inline iterator insert(const_iterator pos, const list &other)
    {
        return this->insert(pos, other.begin(), other.end());
    }
    inline iterator insert(const_iterator pos, list &&other)
    {
        if(!other.empty())
        {
            if(other.alloc == this->alloc)
            {
                node_base * const p = const_cast<node_base *>(pos.get());
                
                node_base *b = p->prv;                
                b->nxt = other.beg_();
                other.beg_()->prv = b;
                
                p->prv = other.last_();
                other.last_()->nxt = p;
                
                size_ += other.size();
                other.invalidate();
                return iterator(p);
            }
            else
                return this->insert(pos, other.begin(), other.end());
        }
        
        node_base * const p = const_cast<node_base *>(pos.get());
        return iterator(p);
    }
    
    template <class I>
    inline list &append(I first, I last) {
        this->insert(end(), first, last);
        return *this;
    }
    template <class T_>
    inline list &append(std::initializer_list<T_> ilist) {
        this->insert(end(), ilist.begin(), ilist.end());
        return *this;
    }
    
    inline iterator erase(const_iterator pos)
    {
        node_base * const nb = const_cast<node_base *>(pos.get());
        node_base * const r = nb->nxt;
        this->erase_(nb);
        return iterator(r);
    }
    inline iterator erase(const_iterator first, const_iterator last)
    {
        node_base * const prv = first.get()->prv;
        node_base * const nxt = last.get()->prv->nxt;
        
        for(const_iterator i = first; i != last; )
        {
            const_iterator nxt = ++i;
            node * const nd = const_cast<node *>(
                static_cast<const node *>(i.get()));
            memory::destroy(alloc, nd);
            memory::deallocate(alloc, nd, 1);
            --size_;
            i = nxt;
        }
        
        prv->nxt = nxt;
        nxt->prv = prv;
        
        return iterator(const_cast<node_base *>(last.get()));
    }
    
    inline void reset() noexcept {
        if(!empty())
        {
            this->reset_();
            invalidate();
        }
    }
    inline void clear() noexcept {
        this->reset();
    }
    
    inline bool empty() const noexcept {
        return last_() == end_();
    }
    inline size_t size() const noexcept {
        return size_;
    }
    
    inline allocator_type get_allocator() const {
        return alloc;
    }
    
private:
    inline node_base *end_() noexcept {
        return &fin;
    }
    inline const node_base *end_() const noexcept {
        return &fin;
    }
    inline node_base *beg_() noexcept {
        return end_()->nxt;
    }
    inline node_base *last_() noexcept {
        return end_()->prv;
    }
    inline const node_base *last_() const noexcept {
        return end_()->prv;
    }
    
    template <class ... X>
    inline void emplace_(node_base *pos, size_type &s, X && ... x)
    {
        n_assert(pos);
        
        emplace_alloc_(pos, alloc, s, foundation::forward<X>(x)...);
    }
    template <class ... X>
    inline void emplace_alloc_(
        node_base *pos,
        internal_allocator_type &alc,
        size_type &s,
        X && ... x)
    {
        n_assert(pos);
        
        node *nd = memory::allocate(alc, 1);
        try {
            memory::construct(
                alc,
                nd,
                pos->prv,
                pos,
                foundation::forward<X>(x)...);
        }
        catch(...) {
            memory::deallocate(alc, nd, 1);
            throw;
        }
        
        pos->prv->nxt = nd;
        pos->prv = nd;
        
        ++s;
    }
    
    template <class Iter>
    inline void insert_range_alloc_(
        node_base * const pos, 
        Iter f,
        Iter l,
        size_type &s,
        internal_allocator_type &alc)
    {
        node_base *p = pos->prv;
        try {
            while(f != l) {
                emplace_alloc_(pos, alc, s, *f++);
            }
        } catch(...) {
            this->erase_alloc_(p, pos, s, alc);
            throw;
        }
    }
    template <class Iter>
    inline void move_insert_range_alloc_(
        node_base * const pos, 
        Iter f,
        Iter l,
        size_type &s,
        internal_allocator_type &alc)
    {
        node_base *p = pos->prv;
        try {
            while(f != l) {
                emplace_alloc_(pos, alc, s, foundation::move(*f++));
            }
        } catch(...) {
            this->erase_alloc_(p, pos, s, alc);
            throw;
        }
    }
    
    inline void erase_(node_base *pos) noexcept {
        n_assert(pos);
        n_assert(pos != end_());
        
        pos->prv->nxt = pos->nxt;
        pos->nxt->prv = pos->prv;
        
        node *nd = static_cast<node *>(pos);
        memory::destroy(alloc, nd);
        memory::deallocate(alloc, nd, 1);
        
        --size_;
    }
    inline iterator erase_alloc_(
        node_base *first, 
        node_base *last,
        size_type &s,
        internal_allocator_type &alc)
    {
        node_base * const prv = first->prv;
        
        for(node_base *i = first; i != last; i = i->nxt)
        {
            node *nd = static_cast<node*>(i);
            memory::destroy(alc, nd);
            memory::deallocate(alc, nd, 1);
            --s;
        }
        
        prv->nxt = last;
        last->prv = prv;
        
        return iterator(last);
    }
    
    inline void reset_(internal_allocator_type &alc) noexcept
    {
        for(node_base *i = beg_(); i != end_(); )
        {
            node * const nd = static_cast<node *>(i);
            node_base *nxt = i->nxt;
            memory::destroy(alc, nd);
            memory::deallocate(alc, nd, 1);
            i = nxt;
        }
    }
    inline void reset_() noexcept
    {
        reset_(alloc);
    }
    
    inline void invalidate() noexcept {
        end_()->prv = end_();
        end_()->nxt = end_();
        size_ = 0;
    }
    
    internal_allocator_type alloc;
    node_base fin;
    size_type size_;
};

//==============================================================================
template <class T, class A>
inline bool operator == (const list<T, A> &lhs, const list<T, A> &rhs)
{
    return foundation::iterator::equal(
        lhs.begin(), lhs.end(),
        rhs.begin(), rhs.end());
}
//------------------------------------------------------------------------------
template <class T, class A>
inline bool operator != (const list<T, A> &lhs, const list<T, A> &rhs)
{
    return !(lhs == rhs);
}
//------------------------------------------------------------------------------
template <class T, class A>
inline bool operator < (const list<T, A> &lhs, const list<T, A> &rhs)
{
    return foundation::iterator::lexicographical_compare(
        lhs.begin(), lhs.end(),
        rhs.begin(), rhs.end(),
        less<T>());
}
//------------------------------------------------------------------------------
template <class T, class A>
inline bool operator <= (const list<T, A> &lhs, const list<T, A> &rhs)
{
    return foundation::iterator::lexicographical_compare(
        lhs.begin(), lhs.end(),
        rhs.begin(), rhs.end(),
        less_equal<T>());
}
//------------------------------------------------------------------------------
template <class T, class A>
inline bool operator > (const list<T, A> &lhs, const list<T, A> &rhs)
{
    return foundation::iterator::lexicographical_compare(
        lhs.begin(), lhs.end(),
        rhs.begin(), rhs.end(),
        greater<T>());
}
//------------------------------------------------------------------------------
template <class T, class A>
inline bool operator >= (const list<T, A> &lhs, const list<T, A> &rhs)
{
    return foundation::iterator::lexicographical_compare(
        lhs.begin(), lhs.end(),
        rhs.begin(), rhs.end(),
        greater_equal<T>());
}

/** @} */

}} // namespaces

#endif // NIC_2A90BD8FAFD3D503_NIC
