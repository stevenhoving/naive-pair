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

#include "naive-pair-default-src.h"
#include <type_traits>

template<class KeyType, class ValueType>
pair_default_src<KeyType, ValueType>::pair_default_src() noexcept = default;

template<class KeyType, class ValueType>
pair_default_src<KeyType, ValueType>::~pair_default_src() noexcept = default;

template<class KeyType, class ValueType>
pair_default_src<KeyType, ValueType>::pair_default_src(KeyType key, ValueType value) noexcept
    : first(key)
    , second(value)
{
}

template<class KeyType, class ValueType>
pair_default_src<KeyType, ValueType>::pair_default_src(KeyType &&key, ValueType &&value) noexcept
    : first(std::forward<KeyType>(key))
    , second(std::forward<ValueType>(value))
{
}

template<class KeyType, class ValueType>
pair_default_src<KeyType, ValueType>::pair_default_src(const pair_default_src &pair_default_src) noexcept = default;

template<class KeyType, class ValueType>
pair_default_src<KeyType, ValueType> & pair_default_src<KeyType, ValueType>::operator = (const pair_default_src &pair_default_src) noexcept = default;

template<class KeyType, class ValueType>
pair_default_src<KeyType, ValueType>::pair_default_src(pair_default_src &&pair_default_src) noexcept = default;

template<class KeyType, class ValueType>
pair_default_src<KeyType, ValueType> &pair_default_src<KeyType, ValueType>::operator = (pair_default_src &&pair_default_src) noexcept = default;

// Explicit template instantiations
template struct pair_default_src<short, short>;
template struct pair_default_src<int, int>;
template struct pair_default_src<float, float>;
template struct pair_default_src<double, double>;

