/*
 * Copyright (C) 2023 Geon Technologies, LLC
 *
 * This file is part of vrtgen.
 *
 * vrtgen is free software: you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * vrtgen is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses/.
 */

#pragma once

#include <concepts>
#include <bit>

#if defined(__APPLE__)
#include <libkern/OSByteOrder.h>
#define bswap_16(x) OSSwapInt16(x)
#define bswap_32(x) OSSwapInt32(x)
#define bswap_64(x) OSSwapInt64(x)
#elif defined(_WIN32)
#include <stdlib.h>
#define bswap_16(x) _byteswap_ushort(x)
#define bswap_32(x) _byteswap_ulong(x)
#define bswap_64(x) _byteswap_uint64(x)
#else
#include <byteswap.h>
#endif

namespace vrtgen::swap {

/**
 * @fn to_be
 * @brief Convert an integer value to big-endian byte order
 * @tparam T Integer type
 * @param value Integer value to be converted
 * @return Big-endian representation of value
 */
template <std::integral T>
inline constexpr T to_be(T value) noexcept
{
    if constexpr (std::endian::native == std::endian::little) {
        switch(sizeof(T)) {
            case 1: return value;
            case 2: return bswap_16(value);
            case 4: return bswap_32(value);
            case 8: return bswap_64(value);
            default: return value;
        }
    }
    return value;
}

/**
 * @fn from_be
 * @brief Convert an integer value from big-endian byte order to host byte order
 * @tparam T Integer type
 * @param value Integer value to be converted
 * @return Host byte order representation of value
 */
template <std::integral T>
inline constexpr T from_be(T value) noexcept
{
    if constexpr (std::endian::native == std::endian::little) {
        switch(sizeof(T)) {
            case 1: return value;
            case 2: return bswap_16(value);
            case 4: return bswap_32(value);
            case 8: return bswap_64(value);
            default: return value;
        }
    }
    return value;
}

} // end namespace vrtgen::swap
