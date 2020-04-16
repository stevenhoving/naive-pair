/**
 * Copyright (c) 2019 - 2020 Steven Hoving
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include <type_traits>

template<class KeyType, class ValueType>
struct pair_default
{
    using first_type = KeyType;
    using second_type = ValueType;

    constexpr pair_default() noexcept = default;
    ~pair_default() noexcept = default;

    constexpr pair_default(KeyType key, ValueType value) noexcept
        : first(key)
        , second(value)
    {
    }

    constexpr pair_default(KeyType &&key, ValueType &&value) noexcept
        : first(std::forward<KeyType>(key))
        , second(std::forward<ValueType>(value))
    {
    }

    constexpr pair_default(const pair_default &pair_default) noexcept = default;
    constexpr pair_default &operator = (const pair_default &pair_default) noexcept = default;
    constexpr pair_default(pair_default &&pair_default) noexcept = default;
    constexpr pair_default &operator = (pair_default &&pair_default) noexcept = default;

    first_type first;
    second_type second;
};

static_assert(std::is_trivially_constructible_v<pair_default<int, int>>);
static_assert(std::is_trivially_move_constructible_v<pair_default<int, int>>);
static_assert(std::is_trivially_copy_constructible_v<pair_default<int, int>>);
static_assert(std::is_trivially_default_constructible_v<pair_default<int, int>>);