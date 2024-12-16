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
    utils/solution_tools.cpp utils/solution_tools.h
    )

set(utils_unittests
    doctest.h doctest.cpp
    utils_tests/maths_tools_tests.cpp
    utils_tests/vector_tools_tests.cpp
    utils_tests/string_tools_tests.cpp
    utils_tests/array_template_tests.cpp
    utils_tests/array_template_iterator_tests.cpp
    utils_tests/array_template_node_iterator_tests.cpp
    utils_tests/solution_tools_tests.cpp)

set(solutions
    solutions/2024/all_solutions.h
        solutions/2024/day_x.cpp
        solutions/2024/day_x.h
        solutions/2024/days_1_to_10/day_1.cpp
        solutions/2024/days_1_to_10/day_1.h
        solutions/2024/days_1_to_10/day_2.cpp
        solutions/2024/days_1_to_10/day_2.h
        solutions/2024/days_1_to_10/day_3.cpp
        solutions/2024/days_1_to_10/day_3.h
        solutions/2024/days_1_to_10/day_4.cpp
        solutions/2024/days_1_to_10/day_4.h
        solutions/2024/days_1_to_10/day_5.cpp
        solutions/2024/days_1_to_10/day_5.h
        solutions/2024/days_1_to_10/day_6.cpp
        solutions/2024/days_1_to_10/day_6.h
        solutions/2024/days_1_to_10/day_7.cpp
        solutions/2024/days_1_to_10/day_7.h
        solutions/2024/days_1_to_10/day_8.cpp
        solutions/2024/days_1_to_10/day_8.h
        solutions/2024/days_1_to_10/day_9.cpp
        solutions/2024/days_1_to_10/day_9.h
        solutions/2024/days_1_to_10/day_10.cpp
        solutions/2024/days_1_to_10/day_10.h
        solutions/2024/days_11_to_20/day_11.cpp
        solutions/2024/days_11_to_20/day_11.h
        solutions/2024/days_11_to_20/day_12.cpp
        solutions/2024/days_11_to_20/day_12.h
        solutions/2024/days_11_to_20/day_13.cpp
        solutions/2024/days_11_to_20/day_13.h
        solutions/2024/days_11_to_20/day_14.cpp
        solutions/2024/days_11_to_20/day_14.h
        solutions/2024/days_11_to_20/day_15.cpp
        solutions/2024/days_11_to_20/day_15.h
        solutions/2024/days_11_to_20/day_16.cpp
        solutions/2024/days_11_to_20/day_16.h
        solutions/2024/days_11_to_20/day_17.cpp
        solutions/2024/days_11_to_20/day_17.h
        solutions/2024/days_11_to_20/day_18.cpp
        solutions/2024/days_11_to_20/day_18.h
        solutions/2024/days_11_to_20/day_19.cpp
        solutions/2024/days_11_to_20/day_19.h
        solutions/2024/days_11_to_20/day_20.cpp
        solutions/2024/days_11_to_20/day_20.h
)

set(all_solution_tests
    doctest.h doctest.cpp
    solutions/2024/2024_solution_tests.cpp
        solutions/2024/common_header.h)

set(single_days_solution_tests
    doctest.h doctest.cpp
    solutions/2024/2024_single_solution.cpp
    )

set(CMAKE_CXX_STANDARD 20)
add_executable(AOC-Utils main.cpp "${utils}")
add_executable(AOC-Utils-Tests "${utils}" "${utils_unittests}")
add_executable(AOC-2024-All-Solutions "${utils}" "${solutions}" "${all_solution_tests}")
add_executable(AOC-2024-Single-Solutions "${utils}" "${solutions}" "${single_days_solution_tests}")
