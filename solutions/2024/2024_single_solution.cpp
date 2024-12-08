#pragma clang diagnostic ignored "-Woverloaded-shift-op-parentheses"

#include "../../doctest.h"
#include "../../utils/utils.h"
#include "all_solutions.h"

typedef solutions::Day8Solution CurrentSolution;

TEST_SUITE_BEGIN("AOC 2024 Single Solution Suite");

TEST_CASE_TEMPLATE("AOC 2024 part A tests template: ", T, CurrentSolution)
{
    T solution = T();
    CHECK(solution.solution_part_a(true)==solution.EXPECTED_TEST_A);
}

TEST_CASE_TEMPLATE("AOC 2024 part A solution template: ", T, CurrentSolution)
{
    T solution = T();
    CHECK(solution.solution_part_a(false)==solution.EXPECTED_SOLUTION_A);
}

TEST_CASE_TEMPLATE("AOC 2024 part B tests template: ", T, CurrentSolution)
{
    T solution = T();
    CHECK(solution.solution_part_b(true)==solution.EXPECTED_TEST_B);
}

TEST_CASE_TEMPLATE("AOC 2024 part B solution template: ", T, CurrentSolution)
{
    T solution = T();
    CHECK(solution.solution_part_b(false)==solution.EXPECTED_SOLUTION_B);
}

TEST_SUITE_END;
