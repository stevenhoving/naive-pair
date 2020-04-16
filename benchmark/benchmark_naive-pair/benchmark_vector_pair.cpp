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

#include "benchmark_fixture.h"
#include <naive-pair/naive-pair.h>
#include <naive-pair/naive-pair-default.h>
#include <naive-pair/naive-pair-default-src.h>
#include <naive-pair/naive-pair-pod.h>
#include <naive-pair/naive-pair-default-empty-base.h>
#include <naive-pair/naive-pair-default-compressed.h>
#include <vector>
#include <tuple>
#include <cstdint>


#define ENABLE_PRE_ALLOCATE 0

//using test_type = int64_t;
using test_type = int;
//using test_type = short;
//using test_type = char;

//std::_Compressed_pair

//using test_type = float;

template<typename T>
auto do_benchmark(int a)
{
    std::vector<T> result;
    ::benchmark::DoNotOptimize(result);

#if ENABLE_PRE_ALLOCATE
    result.reserve(a);
#endif

    for (int i = 0; i < a; ++i)
        result.emplace_back(
            i,
            i
        );

    ::benchmark::ClobberMemory();
    return result;
}

template<typename T>
auto do_pod_benchmark(int a)
{
    std::vector<T> result;
    ::benchmark::DoNotOptimize(result);

#if ENABLE_PRE_ALLOCATE
    result.reserve(a);
#endif
    for (int i = 0; i < a; ++i)
        result.emplace_back(T{
            static_cast<test_type>(i), static_cast<test_type>(i)
        });

    ::benchmark::ClobberMemory();
    return result;
}


#if 0
template<typename T>
std::vector<T> do_reference_benchmark(int a)
{
    std::vector<T> result;
    ::benchmark::DoNotOptimize(result);

#if ENABLE_PRE_ALLOCATE
    result.reserve(a);
#endif

    for (int i = 0; i < a; ++i)
        //result.emplace_back((static_cast<int64_t>(i) << 32) | i);
        result.emplace_back(static_cast<int64_t>(i));

    ::benchmark::ClobberMemory();
    return result;
}

#endif

struct vector_pair : pair_fixture {};

//BENCHMARK_DEFINE_F(pair_fixture, reference)(benchmark::State& st)
//{
//    const auto count = static_cast<int>(st.range(0));
//    for (auto _ : st) {
//        (void)_;
//        const auto result = min_reference<int64_t>(count);
//        ::benchmark::ClobberMemory();
//    }
//}
//

BENCHMARK_F(vector_pair, std_pair)(benchmark::State& st)
{
    const auto count = static_cast<int>(st.range(0));
    for (auto _ : st) {
        (void)_;
        const auto result = do_benchmark<std::pair<test_type, test_type>>(count);
        ::benchmark::ClobberMemory();
    }
}

BENCHMARK_F(vector_pair, std_tuple)(benchmark::State& st)
{
    const auto count = static_cast<int>(st.range(0));
    for (auto _ : st) {
        (void)_;
        const auto result = do_benchmark<std::tuple< test_type, test_type>>(count);
        ::benchmark::ClobberMemory();
    }
}

BENCHMARK_F(vector_pair, custom_pair)(benchmark::State& st)
{
    const auto count = static_cast<int>(st.range(0));
    for (auto _ : st) {
        (void)_;
        const auto result = do_benchmark<naive_pair<test_type, test_type>>(count);
        ::benchmark::ClobberMemory();
    }
}

BENCHMARK_F(vector_pair, custom_pair_default)(benchmark::State& st)
{
    const auto count = static_cast<int>(st.range(0));
    for (auto _ : st) {
        (void)_;
        const auto result = do_benchmark<pair_default< test_type, test_type>>(count);
        ::benchmark::ClobberMemory();
    }
}

BENCHMARK_F(vector_pair, custom_pair_default_src)(benchmark::State& st)
{
    const auto count = static_cast<int>(st.range(0));
    for (auto _ : st) {
        (void)_;
        const auto result = do_benchmark<pair_default_src<test_type, test_type>>(count);
        ::benchmark::ClobberMemory();
    }
}

BENCHMARK_F(vector_pair, custom_pair_default_empty_base)(benchmark::State& st)
{
    const auto count = static_cast<int>(st.range(0));
    for (auto _ : st) {
        (void)_;
        const auto result = do_benchmark<pair_default_empty_base<test_type, test_type>>(count);
        ::benchmark::ClobberMemory();
    }
}

BENCHMARK_F(vector_pair, custom_pair_pod)(benchmark::State& st)
{
    const auto count = static_cast<int>(st.range(0));
    for (auto _ : st) {
        (void)_;
        const auto result = do_pod_benchmark<pair_pod< test_type, test_type>>(count);
        ::benchmark::ClobberMemory();
    }
}
