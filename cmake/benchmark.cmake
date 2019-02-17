# Copyright (c) 2012-2018 Robin Degen
#
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation
# files (the "Software"), to deal in the Software without
# restriction, including without limitation the rights to use,
# copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following
# conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
# OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.

if (NOT TARGET benchmark)
    message(FATAL_ERROR "Benchmark.cmake requires google benchmark included as submodule.")
endif ()

include(CMakeParseArguments)

function(add_benchmark_suite)
    cmake_parse_arguments(
        BENCHMARK_PARSED_ARGS
        "NO_BENCHMARK_MAIN"
        "TARGET;FOLDER"
        "SOURCES;LIBRARIES;INCLUDES;LABELS"
        ${ARGN}
    )

    if (NOT BENCHMARK_PARSED_ARGS_TARGET)
        message(FATAL_ERROR "No target name was given for benchmark.")
    endif ()

    if (NOT BENCHMARK_PARSED_ARGS_SOURCES)
        message(FATAL_ERROR "No sources were given for benchmark.")
    endif ()

    foreach(_src ${BENCHMARK_PARSED_ARGS_SOURCES})
        list (APPEND SRCS "${BENCHMARK_PARSED_ARGS_TARGET}/${_src}")
    endforeach()

    add_executable(${BENCHMARK_PARSED_ARGS_TARGET} ${SRCS})

    if (BENCHMARK_PARSED_ARGS_FOLDER)
        set_target_properties(
            ${BENCHMARK_PARSED_ARGS_TARGET} PROPERTIES
            FOLDER ${BENCHMARK_PARSED_ARGS_FOLDER}
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        )
    endif ()

    if (BENCHMARK_PARSED_ARGS_INCLUDES)
        target_include_directories(${BENCHMARK_PARSED_ARGS_TARGET} PRIVATE ${BENCHMARK_PARSED_ARGS_INCLUDES})
    endif ()

    target_link_libraries(
        ${BENCHMARK_PARSED_ARGS_TARGET}
        benchmark
    )

    if (NOT ${BENCHMARK_PARSED_ARGS_NO_BENCHMARK_MAIN})
        target_link_libraries(${BENCHMARK_PARSED_ARGS_TARGET} benchmark_main)
    endif ()

    if (BENCHMARK_PARSED_ARGS_LIBRARIES)
        target_link_libraries(
            ${BENCHMARK_PARSED_ARGS_TARGET}
            ${BENCHMARK_PARSED_ARGS_LIBRARIES}
        )
    endif ()
endfunction()
