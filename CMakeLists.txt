cmake_minimum_required(VERSION 3.25)
project(AOC-Utils)

set(utils
    utils/utils.h
    utils/std_extensions.h
    utils/precompile_header.cpp utils/precompile_header.h
    utils/string_tools.cpp utils/string_tools.h
    utils/maths_tools.cpp utils/maths_tools.h
    utils/vector_tools.cpp utils/vector_tools.h
    utils/array_template.cpp utils/array_template.h
    utils/array_template.h
    )

set(unittests
    doctest.h doctest.cpp
    utils_tests/maths_tools_tests.cpp
    utils_tests/vector_tools_tests.cpp
    utils_tests/string_tools_tests.cpp
    utils_tests/array_template_tests.cpp
    utils_tests/array_template_iterator_tests.cpp
)

set(CMAKE_CXX_STANDARD 20)
add_executable(AOC-Utils main.cpp "${utils}")
add_executable(AOC-Utils-Tests "${utils}" "${unittests}")
