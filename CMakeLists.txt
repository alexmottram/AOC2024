cmake_minimum_required(VERSION 3.25)
project(AOC-Utils)

set(utils
    utils/utils.h
    utils/std_extensions.h
    utils/precompile_header.cpp utils/precompile_header.h
    utils/string_tools.cpp utils/string_tools.h
    utils/maths_tools.cpp utils/maths_tools.h
    utils/vector_2d.h
    utils/vector_3d.h
    utils/input_reader.cpp utils/input_reader.h
    utils/array_node_wrapper.h
    utils/array_iterators.h
    utils/array_template.h
#    utils/solution.h
    )

set(utils_unittests
    doctest.h doctest.cpp
    utils_tests/maths_tools_tests.cpp
    utils_tests/vector_tools_tests.cpp
    utils_tests/string_tools_tests.cpp
    utils_tests/array_template_tests.cpp
    utils_tests/array_template_iterator_tests.cpp
    utils_tests/array_template_node_iterator_tests.cpp)

set(solutions
    solutions/2024/all_solutions.h
    solutions/2024/days_1_to_5/day_1.cpp
    solutions/2024/days_1_to_5/day_1.h
    solutions/2024/days_1_to_5/day_2.cpp
    solutions/2024/days_1_to_5/day_2.h
    solutions/2024/day_x.h
    solutions/2024/day_x.cpp
)

set(solution_tests
    doctest.h doctest.cpp
    solutions/2024/2024_solution_tests.cpp
    )

set(CMAKE_CXX_STANDARD 20)
add_executable(AOC-Utils main.cpp "${utils}")
add_executable(AOC-Utils-Tests "${utils}" "${utils_unittests}")
add_executable(AOC-2024-Solutions "${utils}" "${solutions}" "${solution_tests}")
