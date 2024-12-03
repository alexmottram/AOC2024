#pragma clang diagnostic ignored "-Woverloaded-shift-op-parentheses"

#include "../../doctest.h"
#include "../../utils/utils.h"
#include "all_solutions.h"

int YEAR{2024};
int TEST_DAY{3};

TEST_SUITE_BEGIN("AOC 2024");

TEST_CASE("AOC 2024 Day 3 part A tests.")
{
    constexpr bool is_test{true};
    const utils::InputReader data{TEST_DAY, YEAR, is_test};
    auto part_a = solutions::day_3_part_a(data);
    utils::print_solution_part("A", TEST_DAY, is_test, part_a);
    CHECK(part_a==solutions::DAY_3_PART_A_TEST);
}


TEST_CASE("AOC 2024 Day 3 part B tests.")
{
    constexpr bool is_test{true};
    const utils::InputReader data{TEST_DAY, YEAR, is_test};
    auto part_b = solutions::day_3_part_b(data);
    utils::print_solution_part("B", TEST_DAY, is_test, part_b);
    CHECK(part_b==solutions::DAY_3_PART_B_TEST);
}

TEST_CASE("AOC 2024 Day 3 part A solution.")
{
    constexpr bool is_test{false};
    const utils::InputReader data{TEST_DAY, YEAR, is_test};
    auto part_a = solutions::day_3_part_a(data);
    utils::print_solution_part("A", TEST_DAY, is_test, part_a);
    CHECK(part_a==solutions::DAY_3_PART_A_SOLUTION);
}

TEST_CASE("AOC 2024 Day 3 part B solution.")
{
    constexpr bool is_test{false};
    const utils::InputReader data{TEST_DAY, YEAR, is_test};
    auto part_b = solutions::day_3_part_b(data);
    utils::print_solution_part("B", TEST_DAY, is_test, part_b);
    CHECK(part_b==solutions::DAY_3_PART_B_SOLUTION);
}

TEST_SUITE_END;