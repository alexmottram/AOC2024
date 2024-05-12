#pragma clang diagnostic ignored "-Woverloaded-shift-op-parentheses"
#include "../doctest.h"
#include "../utils/utils.h"
#include "solutions/all_solutions.h"
std::filesystem::path EXAMPLE_PATH = std::filesystem::path("C:\\Users\\alexa\\OneDrive\\Code\\AOC-Utils\\aoc_2023_examples");
TEST_SUITE_BEGIN("AOC 2023");

TEST_CASE("AOC 2023 Day 1 tests.")
{
    utils::InputReader test_data {1, true, EXAMPLE_PATH};
    auto part_a_test = solutions::day_1_part_a(test_data);
    CHECK(part_a_test==209);

    auto part_b_test = solutions::day_1_part_b(test_data);
    CHECK(part_b_test==281);
}

TEST_CASE("AOC 2023 Day 1 solutions.")
{
    utils::InputReader input_data {1, false, EXAMPLE_PATH};
    auto part_a_solution = solutions::day_1_part_a(input_data);
    std::cout << "Solution for day 1 part a: " << part_a_solution << std::endl;
    CHECK(part_a_solution==55029);

    auto part_b_solution = solutions::day_1_part_b(input_data);
    std::cout << "Solution for day 1 part b: " << part_b_solution << std::endl;
    CHECK(part_b_solution==55686);
}

TEST_CASE("AOC 2023 Day 2 tests.")
{
    utils::InputReader test_data {2, true, EXAMPLE_PATH};
    auto part_a_test = solutions::day_2_part_a(test_data);
    CHECK(part_a_test==8);

    auto part_b_test = solutions::day_2_part_b(test_data);
    CHECK(part_b_test==2286);
}

TEST_CASE("AOC 2023 Day 2 solutions.")
{
    utils::InputReader input_data {2, false, EXAMPLE_PATH};
    auto part_a_solution = solutions::day_2_part_a(input_data);
    std::cout << "Solution for day 1 part a: " << part_a_solution << std::endl;
    CHECK(part_a_solution==2600);

    auto part_b_solution = solutions::day_2_part_b(input_data);
    std::cout << "Solution for day 1 part b: " << part_b_solution << std::endl;
    CHECK(part_b_solution==86036);
}

TEST_CASE("AOC 2023 Day 22 tests.")
{
    utils::InputReader test_data {22, true, EXAMPLE_PATH};
    auto part_a_test = solutions::day_22_part_a(test_data);
    CHECK(part_a_test==5);
}

TEST_CASE("AOC 2023 Day 22 solutions.")
{
    utils::InputReader input_data {22, false, EXAMPLE_PATH};
    auto part_a_test = solutions::day_22_part_a(input_data);
    CHECK(part_a_test==5);
}

TEST_SUITE_END;