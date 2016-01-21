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
#ifndef NIC_A3151707D8745F20_NIC
#define NIC_A3151707D8745F20_NIC

#include "../../type_traits.h"
#include <limits>

namespace nebula { namespace foundation { namespace math {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class T>
struct maximum_impl {};

//------------------------------------------------------------------------------
template <>
struct maximum_impl<char> {
    inline static constexpr char apply() noexcept {
        return std::numeric_limits<char>::max();
    }
};
template <>
struct maximum_impl<signed char> {
    inline static constexpr signed char apply() noexcept {
        return std::numeric_limits<signed char>::max();
    }
};
template <>
struct maximum_impl<unsigned char> {
    inline static constexpr unsigned char apply() noexcept {
        return std::numeric_limits<unsigned char>::max();
    }
};

//------------------------------------------------------------------------------
template <>
struct maximum_impl<short> {
    inline static constexpr short apply() noexcept {
        return std::numeric_limits<short>::max();
    }
};
template <>
struct maximum_impl<unsigned short> {
    inline static constexpr unsigned short apply() noexcept {
        return std::numeric_limits<unsigned short>::max();
    }
};

//------------------------------------------------------------------------------
template <>
struct maximum_impl<int> {
    inline static constexpr int apply() noexcept {
        return std::numeric_limits<int>::max();
    }
};
template <>
struct maximum_impl<unsigned int> {
    inline static constexpr unsigned int apply() noexcept {
        return std::numeric_limits<unsigned int>::max();
    }
};

//------------------------------------------------------------------------------
template <>
struct maximum_impl<long> {
    inline static constexpr long apply() noexcept {
        return std::numeric_limits<long>::max();
    }
};
template <>
struct maximum_impl<unsigned long> {
    inline static constexpr unsigned long apply() noexcept {
        return std::numeric_limits<unsigned long>::max();
    }
};

//------------------------------------------------------------------------------
template <>
struct maximum_impl<long long> {
    inline static constexpr long long apply() noexcept {
        return std::numeric_limits<long long>::max();
    }
};
template <>
struct maximum_impl<unsigned long long> {
    inline static constexpr unsigned long long apply() noexcept {
        return std::numeric_limits<unsigned long long>::max();
    }
};

//------------------------------------------------------------------------------
template <>
struct maximum_impl<float> {
    inline static constexpr float apply() noexcept {
        return std::numeric_limits<float>::max();
    }
};
//------------------------------------------------------------------------------
template <>
struct maximum_impl<double> {
    inline static constexpr double apply() noexcept {
        return std::numeric_limits<double>::max();
    }
};
//------------------------------------------------------------------------------
template <>
struct maximum_impl<long double> {
    inline static constexpr long double apply() noexcept {
        return std::numeric_limits<long double>::max();
    }
};

//------------------------------------------------------------------------------
template <>
struct maximum_impl<wchar_t> {
    inline static constexpr wchar_t apply() noexcept {
        return std::numeric_limits<wchar_t>::max();
    }
};
//------------------------------------------------------------------------------
template <>
struct maximum_impl<char16_t> {
    inline static constexpr char16_t apply() noexcept {
        return std::numeric_limits<char16_t>::max();
    }
};
//------------------------------------------------------------------------------
template <>
struct maximum_impl<char32_t> {
    inline static constexpr char32_t apply() noexcept {
        return std::numeric_limits<char32_t>::max();
    }
};

//------------------------------------------------------------------------------
template <class T>
inline constexpr auto maximum() noexcept
-> decltype(maximum_impl<T>::apply())
{
    return maximum_impl<T>::apply();
}

/** @} */

}}} // namespaces

#endif // NIC_A3151707D8745F20_NIC