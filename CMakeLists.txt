cmake_minimum_required(VERSION 3.25)
project(AOC-Utils)

set(utils
    utils/utils.h
    utils/std_extensions.h
    utils/maths_tools.cpp utils/maths_tools.h
    utils/precompile_header.cpp utils/precompile_header.h
    utils/vector_tools.cpp utils/vector_tools.h
    )

set(unittests
    doctest.h doctest.cpp
    utils_tests/maths_tools_tests.cpp
    utils_tests/vector_tools_test.cpp
    )

set(CMAKE_CXX_STANDARD 20)
add_executable(AOC-Utils main.cpp "${utils}")
add_executable(AOC-Utils-Tests "${utils}" "${unittests}")
