#pragma clang diagnostic ignored "-Woverloaded-shift-op-parentheses"
#include "../doctest.h"
#include "solutions/days_1_to_5/day_1.h"

TEST_SUITE_BEGIN("Solving AOC 2023 problems.");

TEST_CASE("AOC 2023 Day 1.")
{

    auto part_a_test = solutions::day_1_part_a();
    CHECK(part_a_test==142);
    auto part_a_solution = solutions::day_1_part_a();
    std::cout << "Solution for day 1 part a: " << part_a_solution << std::endl;
    CHECK(part_a_solution==55029);

    auto part_b_test = solutions::day_1_part_b();
    CHECK(part_b_test==281);
    auto part_b_solution = solutions::day_1_part_b();
    std::cout << "Solution for day 1 part b: " << part_b_solution << std::endl;
    CHECK(part_b_solution==55686);
}

TEST_SUITE_END;