# Copyright (c) 2019 - 2020 Steven Hoving
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

cmake_minimum_required(VERSION 3.13)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

project(naive-pair)

include(CTest)
enable_testing()

if(NOT DEFINED MSVC OR MSVC_VERSION LESS 1916)
  message(FATAL_ERROR "naive-pair currently only builds with visual studio 2017 15.9 or higher for now.")
endif()

set(CMAKE_CXX_STANDARD 17)

#add_compile_options(/WX) # treat warnings as errors.
add_compile_options(/permissive-) # vs conformance mode.
add_compile_options(/Zc:rvalueCast)
add_compile_options(/Zc:ternary)
add_compile_options(/Zc:referenceBinding)
add_compile_options(/Oi) # Enable intrinsic functions
add_compile_options(/Ot) # Favor fast code
add_compile_options(/GL) # Whole program optimalisation

###############################################################################

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

###############################################################################

add_subdirectory(dep)

add_library(naive-pair STATIC
    include/naive-pair/naive-pair.h
    include/naive-pair/naive-pair-default.h
    include/naive-pair/naive-pair-pod.h
    include/naive-pair/naive-pair-default-src.cpp
    include/naive-pair/naive-pair-default-src.h
    include/naive-pair/naive-pair-default-empty-base.h
)

target_include_directories(naive-pair
  INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

add_subdirectory(benchmark)
