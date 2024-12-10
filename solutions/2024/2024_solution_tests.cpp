#pragma clang diagnostic ignored "-Woverloaded-shift-op-parentheses"

#include "../../doctest.h"
#include "../../utils/utils.h"
#include "all_solutions.h"

TEST_SUITE_BEGIN("AOC 2024 All Solution Suite");

TEST_CASE_TEMPLATE_DEFINE("AOC 2024 part A tests template: ", T, STANDARD_TEST_CASE)
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

TEST_CASE_TEMPLATE_INVOKE(STANDARD_TEST_CASE, solutions::Day1Solution);
TEST_CASE_TEMPLATE_INVOKE(STANDARD_TEST_CASE, solutions::Day2Solution);
//TEST_CASE_TEMPLATE_INVOKE(STANDARD_TEST_CASE, solutions::Day3Solution);
//TEST_CASE_TEMPLATE_INVOKE(STANDARD_TEST_CASE, solutions::Day4Solution);
//TEST_CASE_TEMPLATE_INVOKE(STANDARD_TEST_CASE, solutions::Day5Solution);
TEST_CASE_TEMPLATE_INVOKE(STANDARD_TEST_CASE, solutions::Day6Solution);
TEST_CASE_TEMPLATE_INVOKE(STANDARD_TEST_CASE, solutions::Day7Solution);
TEST_CASE_TEMPLATE_INVOKE(STANDARD_TEST_CASE, solutions::Day8Solution);
TEST_CASE_TEMPLATE_INVOKE(STANDARD_TEST_CASE, solutions::Day9Solution);
TEST_CASE_TEMPLATE_INVOKE(STANDARD_TEST_CASE, solutions::Day10Solution);

TEST_SUITE_END;
