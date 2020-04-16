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
#include <tuple>
#include "eastl-tuple.h"

template <typename T>
std::vector<T> min(int a)
{
    std::vector<T> result;
    ::benchmark::DoNotOptimize(result);
    for (int i = 0; i < a; ++i)
        result.emplace_back(i, i, i);
    ::benchmark::ClobberMemory();
    return result;
}

class tuple_fixture : public ::benchmark::Fixture
{
public:
    void SetUp(const ::benchmark::State &state)
    {
    }

    void TearDown(const ::benchmark::State &state)
    {
    }
};

BENCHMARK_DEFINE_F(tuple_fixture, std_tuple)(benchmark::State &st)
{
    const auto count = static_cast<int>(st.range(0));
    for (auto _ : st)
    {
        const auto result = min<std::tuple<int, int, int>>(count);
        ::benchmark::ClobberMemory();
    }
}

BENCHMARK_REGISTER_F(tuple_fixture, std_tuple)->Range(1, 4096);

BENCHMARK_DEFINE_F(tuple_fixture, custom_tuple)(benchmark::State &st)
{
    const auto count = static_cast<int>(st.range(0));
    for (auto _ : st)
    {
        const auto result = min<Tuple<int, int, int>>(count);
        ::benchmark::ClobberMemory();
    }
}

BENCHMARK_REGISTER_F(tuple_fixture, custom_tuple)->Range(1, 4096);
