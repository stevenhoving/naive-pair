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

/* To do:
 * 1. For now we always assume that KeyType and ValueType are noexcept types. Add a constrain for
 *    that.
 */
template<class KeyType, class ValueType>
struct naive_pair
{
    using first_type = KeyType;
    using second_type = ValueType;

    constexpr naive_pair() noexcept = default;
    ~naive_pair() noexcept = default;

    /* Questions:
     * 1. Is this a constructor that assumes that KeyType and ValueType are move constructible?
     * 2. Should I add a constrain for that? And add a constructor that uses KeyType and ValueType
     *    const ref when this constrain is not met?
     */
    constexpr naive_pair(KeyType key, ValueType value) noexcept
        : first(std::move(key))
        , second(std::move(value))
    {
    }

    /* Questions:
     * 1. Is this the correct way to create a rvalue constructor for this class?
     */
    template<class T1, class T2>
    constexpr naive_pair(T1 &&key, T2 &&value) noexcept
        : first(std::forward<T1>(key))
        , second(std::forward<T2>(value))
    {}

    constexpr naive_pair(const naive_pair &pair) noexcept
        : first(pair.first)
        , second(pair.second)
    {
    }

    constexpr naive_pair &operator = (const naive_pair &pair) noexcept
    {
        first = pair.first;
        second = pair.second;
        return *this;
    }

    /* Questions:
     * 1. Should I use std::exchange here for when both KeyType and ValueType are move
     *    constructible? (add a constrain for that)
     *
     */
    constexpr naive_pair(naive_pair &&pair) noexcept
        : first(std::forward<KeyType>(pair.first))
        , second(std::forward<ValueType>(pair.second))
    {
    }

    /* See question for the move constructor.
     */
    constexpr naive_pair &operator = (naive_pair &&pair) noexcept
    {
        first = std::move(pair.first);
        second = std::move(pair.second);
        return *this;
    }

    KeyType first;
    ValueType second;
};
