#pragma clang diagnostic ignored "-Woverloaded-shift-op-parentheses"

#include "../../doctest.h"
#include "../../utils/utils.h"
#include "all_solutions.h"

TEST_SUITE_BEGIN("AOC 2024");

solutions::Day8Solution solution{};

TEST_CASE("AOC 2024 part A tests.")
{
    CHECK(solution.solution_part_a(true)==solution.EXPECTED_TEST_A);
}

TEST_CASE("AOC 2024 part A solution.")
{
    CHECK(solution.solution_part_a(false)==solution.EXPECTED_SOLUTION_A);
}

TEST_CASE("AOC 2024 part B tests.")
{
    CHECK(solution.solution_part_b(true)==solution.EXPECTED_TEST_B);
}

TEST_CASE("AOC 2024 part B solution.")
{
    CHECK(solution.solution_part_b(false)==solution.EXPECTED_SOLUTION_B);
}

TEST_SUITE_END;