/* Copyright(c) 2018 Steven Hoving
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files(the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions :
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <benchmark/benchmark.h>
#include <yuvconvert.h>

#include <vector>
#include <string>
#include <tuple>

//std::pair

//template<typename T>
//using container = std::vector<T>;

template<typename T>
using container = std::basic_string<T>;

template<class KeyType, class ValueType>
struct Pair
{
    using first_type = KeyType;
    using second_type = ValueType;

    constexpr Pair() = default;
    ~Pair() noexcept = default;

    constexpr Pair(KeyType key, ValueType value) noexcept
        //: first(std::move(key))
        //, second(std::move(value))

        : first(key)
        , second(value)
    {}

    template<class T1, class T2>
    constexpr Pair(T1&& key, T2&& value) noexcept
        : first(std::forward<T1>(key))
        , second(std::forward<T2>(value))
    {}

    // copy
    constexpr Pair(const Pair<KeyType, ValueType>& pair) noexcept
        : first(pair.first)
        , second(pair.second)
    {}

    // copy assignment
    constexpr Pair<KeyType, ValueType> &operator = (const Pair<KeyType, ValueType>& pair) noexcept
    {
        first = pair.first;
        second = pair.second;
        return *this;
    }

    // move
    constexpr Pair(Pair<KeyType, ValueType>&& pair) noexcept
        : first(std::forward<KeyType>(pair.first))
        , second(std::forward<ValueType>(pair.second))
    {
    }

    // move assignment
    constexpr Pair<KeyType, ValueType>& operator = (Pair<KeyType, ValueType>&& pair) noexcept
    {
        first = std::move(pair.first);
        second = std::move(pair.second);
        return *this;
    }

    KeyType first;
    ValueType second;
};

template<typename T>
container<T> min(int a)
{
    container<T> result;
    ::benchmark::DoNotOptimize(result);
    result.reserve(a);
    for (int i = 0; i < a; ++i)
        //result.emplace_back(i, i);
        result.push_back({i, i});
    ::benchmark::ClobberMemory();
    return result;
}

class pair_fixture : public ::benchmark::Fixture
{
public:
    void SetUp(const ::benchmark::State& state)
    {
    }

    void TearDown(const ::benchmark::State& state)
    {
    }
};

//BENCHMARK_DEFINE_F(pair_fixture, std_pair)(benchmark::State& st)
//{
//    const auto count = static_cast<int>(st.range(0));
//    for (auto _ : st) {
//        const auto result = min<std::pair<int, int>>(count);
//        ::benchmark::ClobberMemory();
//    }
//}
//
//BENCHMARK_REGISTER_F(pair_fixture, std_pair)
//    ->RangeMultiplier(2)
//    ->Range(1, 4096);

BENCHMARK_DEFINE_F(pair_fixture, std_tuple)(benchmark::State& st)
{
    const auto count = static_cast<int>(st.range(0));
    for (auto _ : st) {
        const auto result = min<std::tuple<int, int>>(count);
        ::benchmark::ClobberMemory();
    }
}

BENCHMARK_REGISTER_F(pair_fixture, std_tuple)
    //->RangeMultiplier(2)
    ->Range(1, 4096);

BENCHMARK_DEFINE_F(pair_fixture, custom_pair)(benchmark::State& st)
{
    const auto count = static_cast<int>(st.range(0));
    for (auto _ : st) {
        const auto result = min<Pair<int, int>>(count);
        ::benchmark::ClobberMemory();
    }
}

BENCHMARK_REGISTER_F(pair_fixture, custom_pair)
    //->RangeMultiplier(2)
    ->Range(1, 4096);

