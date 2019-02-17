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

#include <benchmark/benchmark.h>
#include <naive-pair/naive-pair.h>
#include <vector>
#include <string>
#include <tuple>
#include <cstdint>

#define ENABLE_BASIC_STRING 0

#if ENABLE_BASIC_STRING
  template<typename T>
  using container = std::basic_string<T>;
#else
  template<typename T>
  using container = std::vector<T>;
#endif // ENABLE_BASIC_STRING

template<typename T>
container<T> min_reference(int a)
{
    container<T> result;
    ::benchmark::DoNotOptimize(result);
    //result.reserve(a);
    for (int i = 0; i < a; ++i)
#if ENABLE_BASIC_STRING
        //result.push_back((static_cast<int64_t>(i) << 32) | i);
        result.push_back(static_cast<int64_t>(i));
#else
        //result.emplace_back((static_cast<int64_t>(i) << 32) | i);
        result.emplace_back(static_cast<int64_t>(i));
#endif
    ::benchmark::ClobberMemory();
    return result;
}

template<typename T>
container<T> min(int a)
{
    container<T> result;
    ::benchmark::DoNotOptimize(result);
    //result.reserve(a);
    for (int i = 0; i < a; ++i)
#if ENABLE_BASIC_STRING
        result.push_back({0, i});
#else
        result.emplace_back(0, i);
#endif
    ::benchmark::ClobberMemory();
    return result;
}

class pair_fixture : public ::benchmark::Fixture
{
public:
    pair_fixture()
    {
        //RangeMultiplier(2);
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
//    ->Range(1, 4096);

BENCHMARK_DEFINE_F(pair_fixture, reference)(benchmark::State& st)
{
    const auto count = static_cast<int>(st.range(0));
    for (auto _ : st) {
        const auto result = min_reference<int64_t>(count);
        ::benchmark::ClobberMemory();
    }
}

BENCHMARK_REGISTER_F(pair_fixture, reference)
    ->Range(1, 4096);

BENCHMARK_DEFINE_F(pair_fixture, std_tuple)(benchmark::State& st)
{
    const auto count = static_cast<int>(st.range(0));
    for (auto _ : st) {
        const auto result = min<std::tuple<int, int>>(count);
        ::benchmark::ClobberMemory();
    }
}

BENCHMARK_REGISTER_F(pair_fixture, std_tuple)
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
    ->Range(1, 4096);

