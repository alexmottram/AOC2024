#pragma clang diagnostic ignored "-Woverloaded-shift-op-parentheses"
#include "../../doctest.h"
#include "../../utils/utils.h"
#include "all_solutions.h"

int YEAR {2023};

TEST_SUITE_BEGIN("AOC 2023");

TEST_CASE("AOC 2023 Day 1 tests.")
{
    utils::InputReader test_data {1, YEAR, true};
    auto part_a_test = solutions::day_1_part_a(test_data);
    CHECK(part_a_test==209);

    auto part_b_test = solutions::day_1_part_b(test_data);
    CHECK(part_b_test==281);
}

TEST_CASE("AOC 2023 Day 1 2023.")
{
    utils::InputReader input_data {1, YEAR, false};
    auto part_a_solution = solutions::day_1_part_a(input_data);
    std::cout << "Solution for day 1 part a: " << part_a_solution << std::endl;
    CHECK(part_a_solution==55029);

    auto part_b_solution = solutions::day_1_part_b(input_data);
    std::cout << "Solution for day 1 part b: " << part_b_solution << std::endl;
    CHECK(part_b_solution==55686);
}

TEST_CASE("AOC 2023 Day 2 tests.")
{
    utils::InputReader test_data {2, YEAR, true};
    auto part_a_test = solutions::day_2_part_a(test_data);
    CHECK(part_a_test==8);

    auto part_b_test = solutions::day_2_part_b(test_data);
    CHECK(part_b_test==2286);
}

TEST_CASE("AOC 2023 Day 2 2023.")
{
    utils::InputReader input_data {2, YEAR, false};
    auto part_a_solution = solutions::day_2_part_a(input_data);
    std::cout << "Solution for day 1 part a: " << part_a_solution << std::endl;
    CHECK(part_a_solution==2600);

    auto part_b_solution = solutions::day_2_part_b(input_data);
    std::cout << "Solution for day 1 part b: " << part_b_solution << std::endl;
    CHECK(part_b_solution==86036);
}

TEST_CASE("AOC 2023 Day 22 tests.")
{
    utils::InputReader test_data {22, YEAR, true};
    auto part_a_test = solutions::day_22_part_a(test_data);
    CHECK(part_a_test==5);
}

TEST_CASE("AOC 2023 Day 22 2023.")
{
    utils::InputReader input_data {22, YEAR, false};
    auto part_a_test = solutions::day_22_part_a(input_data);
    CHECK(part_a_test==5);
}

TEST_SUITE_END;