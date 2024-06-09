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
    solutions/2023/all_solutions.h
    solutions/2023/days_1_to_5/day_1.cpp
    solutions/2023/days_1_to_5/day_1.h
    solutions/2023/days_1_to_5/day_2.cpp
    solutions/2023/days_1_to_5/day_2.h
    solutions/2023/days_21_to_25/day_21.cpp
    solutions/2023/days_21_to_25/day_21.h
    solutions/2023/days_1_to_5/day_3.h solutions/2023/days_1_to_5/day_3.cpp solutions/2023/day_x.h solutions/2023/day_x.cpp)

set(solution_tests
    doctest.h doctest.cpp
    solutions/2023/2023_solution_tests.cpp
    )

set(CMAKE_CXX_STANDARD 20)
add_executable(AOC-Utils main.cpp "${utils}")
add_executable(AOC-Utils-Tests "${utils}" "${utils_unittests}")
add_executable(AOC-Example-Solutions "${utils}" "${solutions}" "${solution_tests}")
