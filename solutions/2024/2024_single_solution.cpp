#pragma clang diagnostic ignored "-Woverloaded-shift-op-parentheses"

#include "../../doctest.h"
#include "../../utils/utils.h"
#include "all_solutions.h"

typedef solutions::Day1Solution CurrentSolution;

TEST_SUITE_BEGIN("AOC 2024 Single Solution Suite");

TEST_CASE_TEMPLATE("AOC 2024 part A tests template: ", T, CurrentSolution)
{
    T solution = T();
    SUBCASE("Test solution for part A")
    {
        CHECK(solution.solution_part_a(true)==solution.EXPECTED_TEST_A);
    }
    SUBCASE("Actual solution for part A")
    {
        CHECK(solution.solution_part_a(false)==solution.EXPECTED_SOLUTION_A);
    }
    SUBCASE("Test solution for part B")
    {
        CHECK(solution.solution_part_b(true)==solution.EXPECTED_TEST_B);
    }
    SUBCASE("Actual solution for part B")
    {
        CHECK(solution.solution_part_b(false)==solution.EXPECTED_SOLUTION_B);
    }
}

TEST_SUITE_END;
