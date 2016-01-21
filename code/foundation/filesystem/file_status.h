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
#ifndef NIC_2A620803F0F8666F_NIC
#define NIC_2A620803F0F8666F_NIC

#include "path.h"
#include "types.h"
#include "../dll_interface.h"

namespace nebula { namespace foundation { namespace filesystem {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
/** Represents the status of a file. This class is copy/move able.
 * @attention Do not call any member functions, instead use free functions to
 * query file properties, because this class is subject to change.
 * */
class n_foundation_dll file_status
{
public:    
    inline file_status()
    {}
    inline file_status(
        const file_type ft_,
        const size_t s_,
        const file_permission_type p_,
        const file_time_type &at_,
        const file_time_type &mt_,
        const file_time_type &ct_) noexcept
    : ftype_(ft_),
    size_(s_),
    perm_(p_),
    atime_(at_),
    mtime_(mt_),
    ctime_(ct_)
    {}
    
    file_status(file_status &) = default;
    file_status(const file_status &) = default;
    file_status(file_status &&) = default;
    
    file_status &operator = (const file_status &) = default;
    file_status &operator = (file_status &&) = default;
    
    inline void size(const size_t n) noexcept { 
        size_ = n;
    }
    inline void type(const file_type x) noexcept {
        ftype_ = x;
    }
    inline void last_access(const file_time_type &x) noexcept {
        atime_ = x; 
    }
    inline void last_modification(const file_time_type &x) noexcept {
        mtime_ = x; 
    }
    inline void last_status_change(const file_time_type &x) noexcept {
        ctime_ = x; 
    }
    inline void permissions(file_permission_type x) noexcept {
        perm_ = x;
    }
    
    inline size_t size() const noexcept { return size_; }
    inline file_type type() const noexcept { return ftype_; }
    inline file_time_type last_access() const noexcept {
        return atime_;
    }
    inline file_time_type last_modification() const noexcept { 
        return mtime_; 
    }
    inline file_time_type last_status_change() const noexcept {
        return ctime_;
    }
    inline file_permission_type permissions() const noexcept {
        return perm_;
    }
    
private:
    file_type ftype_;
    size_t size_;
    file_permission_type perm_;
    file_time_type atime_;
    file_time_type mtime_;
    file_time_type ctime_;
};

//------------------------------------------------------------------------------
extern file_status n_foundation_dll status(const path &p);

//------------------------------------------------------------------------------
extern string n_foundation_dll pretty_permissions(const file_status &fs);
//------------------------------------------------------------------------------
inline file_permission_type permissions(const file_status &fs) {
    return fs.permissions();
}
//------------------------------------------------------------------------------
inline bool test_permissions(
    const file_status &fs, 
    const file_permission_type x) 
{
    return (fs.permissions() & x) == x;
}

//------------------------------------------------------------------------------
inline file_time_type last_access(const file_status &fs) {
    return fs.last_access();
}
//------------------------------------------------------------------------------
inline file_time_type last_modification(const file_status &fs) {
    return fs.last_modification();
}
//------------------------------------------------------------------------------
inline file_time_type last_status_change(const file_status &fs) {
    return fs.last_status_change();
}

//------------------------------------------------------------------------------
template <class D>
inline D last_access(const file_status &fs) {
    return chrono::duration_cast<D>(fs.last_access());
}
//------------------------------------------------------------------------------
template <class D>
inline D last_modification(const file_status &fs) {
    return chrono::duration_cast<D>(fs.last_modification());
}
//------------------------------------------------------------------------------
template <class D>
inline D last_status_change(const file_status &fs) {
    return chrono::duration_cast<D>(fs.last_status_change());
}

//------------------------------------------------------------------------------
inline size_t size(const file_status &fs) {
    return fs.size();
}

//------------------------------------------------------------------------------
inline file_type type(const file_status &fs) {
    return fs.type();
}
//------------------------------------------------------------------------------
inline bool is_directory(const file_status &fs) {
    return fs.type() == file_type::directory;
}
//------------------------------------------------------------------------------
inline bool is_regular(const file_status &fs) {
    return fs.type() == file_type::regular;
}
//------------------------------------------------------------------------------
inline bool is_symlink(const file_status &fs) {
    return fs.type() == file_type::symlink;
}
//------------------------------------------------------------------------------
inline bool is_fifo(const file_status &fs) {
    return fs.type() == file_type::fifo;
}
//------------------------------------------------------------------------------
inline bool is_socket(const file_status &fs) {
    return fs.type() == file_type::socket;
}
//------------------------------------------------------------------------------
inline bool is_block(const file_status &fs) {
    return fs.type() == file_type::block;
}
//------------------------------------------------------------------------------
inline bool is_unknown(const file_status &fs) {
    return fs.type() == file_type::unknown;
}

/** @} */

}}}

#endif // NIC_2A620803F0F8666F_NIC