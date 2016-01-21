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
#ifndef NIC_200A34102EFC8709_NIC
#define NIC_200A34102EFC8709_NIC

#include "exception.h"
#include "move.h"
#include "swap.h"
#include "meta.h"
#include "type_traits.h"

#include <cstddef> // alignas

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{ 
 * */
//------------------------------------------------------------------------------
struct bad_variant_cast : public virtual bad_cast {};

//------------------------------------------------------------------------------
template <class ... T>
class variant
{
private:
    using this_type = variant<T...>;
    
    template <class X>
    struct sizeof_ : public meta::size_t_<sizeof(X)> {};
    template <class X>
    struct alignof_ : public meta::size_t_<alignof(X)> {};
    
    template <class X>
    using Type = meta::_at<X, meta::size_t_<0>>;
    template <class X>
    using Index = meta::_at<X, meta::size_t_<1>>;
    template <class X>
    using Type_ = meta::at_<X, meta::size_t_<0>>;
    template <class X>
    using Index_ = meta::at_<X, meta::size_t_<1>>;
    
    using TypeSeq = meta::_for_each<
        meta::seq<T...>,
        n_bind(meta::push_back_<
            meta::protect<meta::_1>,
            meta::seq<meta::protect<meta::_2>,
                meta::size_<meta::protect<meta::_1>>>>),
        meta::seq<>>;
    using BufSize = 
        meta::_for_each<
            TypeSeq,
            n_bind(
                meta::if_<
                    meta::greater_<
                        sizeof_<
                            Type_<meta::protect<meta::_2>>>,
                        meta::_1>,
                    sizeof_<Type_<meta::protect<meta::_2>>>,
                    meta::_1>),
            meta::size_t_<0>>;
    using BufAlignment = 
        meta::_for_each<
            TypeSeq,
            n_bind(
                meta::if_<
                    meta::greater_<
                        alignof_<
                            Type_<meta::protect<meta::_2>>>,
                        meta::_1>,
                    alignof_<Type_<meta::protect<meta::_2>>>,
                    meta::_1>),
            meta::size_t_<0>>;
            
    template <class X>
    struct SearchType_
    {
        using type = meta::_for_each<
            TypeSeq,
            n_bind(
                meta::if_<
                    is_same<
                        Type_<meta::protect<meta::_2>>,
                        meta::protect<X>>,
                    meta::protect<meta::_2>,
                    meta::protect<meta::_1>>),
            void>;
    };
    template <class X>
    using SearchType = typename SearchType_<X>::type;
    
    struct backend_base
    {
        virtual ~backend_base() noexcept {}
        
        virtual void copy_construct(variant &, const variant &) = 0;
        virtual void move_construct(variant &, variant &) = 0;
        virtual void destruct(variant &) = 0;
        virtual void copy_assign(variant &, const variant &) = 0;
        virtual void move_assign(variant &, variant &) = 0;
        virtual void swap(variant &, variant &) = 0; 
    };
     
    template <class X>       
    struct backend : public backend_base
    {
        inline void copy_construct(variant &a, const variant &b)
        {
            new (a.buf) X(b.template cast_<X>());
            new (a.backend_storage) backend<X>();
        }
        inline void move_construct(variant &a, variant &b)
        {
            new (a.buf) X(foundation::move(b.template cast_<X>()));
            new (a.backend_storage) backend<X>();
        }
        
        inline void destruct(variant &v)
        {
            v.template cast_<X>().~X();
        }
        
        inline void copy_assign(variant &a, const variant &b)
        {
            a.template cast_<X>() = b.template cast_<X>();
        }
        inline void move_assign(variant &a, variant &b)
        {
            a.template cast_<X>() = 
                foundation::move(b.template cast_<X>());
        }
        
        inline void swap(variant &a, variant &b)
        {
            foundation::swap(
                a.template cast_<X>(),
                b.template cast_<X>());
        }
    };

public:    
    template <class X>
    inline variant(X &&x)
    : index_(-1)
    {
        this->make(foundation::forward<X>(x));      
    }
    
    inline variant()
    : index_(-1)
    {}
    inline variant(variant &other)
    : index_(-1)
    {
        if(!other.empty())
        {
            other.be()->copy_construct(*this, other);
            index_ = other.index_;
        }
    }
    inline variant(const variant &other)
    : index_(-1)
    {
        if(!other.empty())
        {
            other.be()->copy_construct(*this, other);
            index_ = other.index_;
        }
    }
    inline variant(variant &&other)
    : index_(-1)
    {
        if(!other.empty())
        {
            other.be()->move_construct(*this, other);
            index_ = other.index_;
        }
    }
    
    inline ~variant()
    {
        this->clear();
    }
    
    inline variant &operator = (variant &other)
    {
        return this->operator = (static_cast<const variant &>(other));
    }
    inline variant &operator = (const variant &other)
    {
        if(empty())
        {
            other.be()->copy_construct(*this, other);
            index_ = other.index_;
        }
        else
        {   
            if(index_ == other.index_)
            {
                be()->copy_assign(*this, other);
            }
            else
            {
                if(other.empty())
                {
                    this->clear();
                    return *this;
                }
                else
                {
                    this->clear();
                    other.be()->copy_construct(*this, other);
                    index_=other.index_;
                }
            }
        }
        return *this;
    }
    inline variant &operator = (variant &&other)
    {
        if(empty())
        {
            other.be()->move_construct(*this, other);
            index_ = other.index_;
        }
        else
        {   
            if(index_ == other.index_)
            {
                be()->move_assign(*this, other);
            }
            else
            {
                if(other.empty())
                {
                    this->clear();
                    return *this;
                }
                else
                {
                    this->clear();
                    other.be()->move_construct(*this, other);
                    index_=other.index_;
                }
            }
        }
        return *this;
    }
    
    template <class X>
    inline variant &operator = (X &&x)
    {
        make(forward<X>(x));
        return *this;
    }
    
    inline void swap(variant &other)
    {        
        if(!empty())
        {
            if(!other.empty())
            {
                if(index_ == other.index_)
                    be()->swap(*this, other);
                else
                    foundation::swap(*this, other);
            }
            else
            {
                other = foundation::move(*this);
                clear();
            }
        }
        else
        {
            if(!other.empty())
            {
                *this = foundation::move(other);
                other.clear();
            }
        }
    }
    
    inline bool empty() const noexcept {
        return index_ == -1;
    }
    inline size_t index() const noexcept {
        return index_;
    }
    
    inline void clear()
    {
        if(!empty()) {
            be()->destruct(*this);
            index_ = -1;
        }
    }
    
private:
    inline backend_base *be() const noexcept
    {
        return const_cast<backend_base *>(
            static_cast<const backend_base *>(
            static_cast<const void *>(backend_storage)));
    }
    
    template <class X>
    inline X &cast_() noexcept
    {
        return *static_cast<X *>(static_cast<void *>(buf));
    }
    template <class X>
    inline const X &cast_() const noexcept
    {
        return *static_cast<const X *>(static_cast<const void *>(buf));
    }
    template <class X>
    inline X &cast()
    {
        using Found = SearchType<X>;
        if(Index<Found>::value != index_)
            n_throw(bad_variant_cast);
        return this->template cast_<X>();
    }
    template <class X>
    inline const X &cast() const
    {
        using Found = SearchType<X>;
        if(Index<Found>::value != index_)
            n_throw(bad_variant_cast);
        return this->template cast_<X>();
    }
    
    template <class X>
    inline void make(X &&x)
    {
        using StrippedX = typename ctraits::value<X>::type;
        using Found = SearchType<StrippedX>;
        n_static_assert(
            n_arg(is_same<Type<Found>, StrippedX>::value),
            "Unknown Type");
        if(Index<Found>::value == index_)
        {
            this->template cast_<StrippedX>() = foundation::forward<X>(x);
        }
        else
        {
            this->clear();
            new (buf) Type<Found>(foundation::forward<X>(x));
            new (backend_storage) backend<Type<Found>>();
            index_ = static_cast<int>(Index<Found>::value);
        }
    }

    int index_;
    struct alignas(backend<int>)
    {
        char backend_storage[sizeof(backend_base)];
    };  
    struct alignas(BufAlignment::value)
    {
        char buf[BufSize::value];
    };
    
    template <class X, class ... Q>
    friend X &variant_cast(variant<Q...> &);
    template <class X, class ... Q>
    friend const X &variant_cast(const variant<Q...> &);
    template <class X, class ... Q>
    friend X variant_cast(variant<Q...> &&);
};

//------------------------------------------------------------------------------
template <class X, class ... T>
inline X &variant_cast(variant<T...> &v)
{
    return v.template cast<X>();
}
//------------------------------------------------------------------------------
template <class X, class ... T>
inline const X &variant_cast(const variant<T...> &v)
{
    return v.template cast<X>();
}
//------------------------------------------------------------------------------
template <class X, class ... T>
inline X variant_cast(variant<T...> &&v)
{
    return foundation::move(v.template cast<X>());
}

/** @} */

}} // namespaces

#endif // NIC_200A34102EFC8709_NIC
