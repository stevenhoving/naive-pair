/**
 * Copyright (c) 2019 Steven Hoving
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


/**
 * Inspired by https://www.reddit.com/r/cpp/comments/ar4ghs/stdpair_disappointing_performance/
 */

#pragma once

template<class KeyType, class ValueType>
struct Pair
{
    using first_type = KeyType;
    using second_type = ValueType;

    constexpr Pair() noexcept = default;
    ~Pair() noexcept = default;

    //constexpr Pair(const KeyType &key, const ValueType &value) noexcept
    //    : first(key)
    //    , second(value)
    //{}

    constexpr Pair(KeyType key, ValueType value) noexcept
        : first(std::move(key))
        , second(std::move(value))
    {}

    template<class T1, class T2>
    constexpr Pair(T1&& key, T2&& value) noexcept
        : first(std::forward<T1>(key))
        , second(std::forward<T2>(value))
    {}

    // copy
    constexpr Pair(const Pair<KeyType, ValueType>& pair) noexcept = default;
    //constexpr Pair(const Pair<KeyType, ValueType>& pair) noexcept
    //    : first(pair.first)
    //    , second(pair.second)
    //{}

    // copy assignment
    constexpr Pair<KeyType, ValueType> &operator = (const Pair<KeyType, ValueType>& pair) noexcept = default;
    //constexpr Pair<KeyType, ValueType> &operator = (const Pair<KeyType, ValueType>& pair) noexcept
    //{
    //    first = pair.first;
    //    second = pair.second;
    //    return *this;
    //}

    // move
    constexpr Pair(Pair<KeyType, ValueType>&& pair) noexcept = default;
    //constexpr Pair(Pair<KeyType, ValueType>&& pair) noexcept
    //    : first(std::forward<KeyType>(pair.first))
    //    , second(std::forward<ValueType>(pair.second))
    //{
    //}

    // move assignment
    constexpr Pair<KeyType, ValueType>& operator = (Pair<KeyType, ValueType>&& pair) noexcept = default;
    //constexpr Pair<KeyType, ValueType>& operator = (Pair<KeyType, ValueType>&& pair) noexcept
    //{
    //    first = std::move(pair.first);
    //    second = std::move(pair.second);
    //    return *this;
    //}

    KeyType first;
    ValueType second;
};

static_assert(std::is_trivially_copyable_v<Pair<int, int>>);
