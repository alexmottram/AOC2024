#pragma clang diagnostic ignored "-Woverloaded-shift-op-parentheses"

#include "../../doctest.h"
#include "../../utils/utils.h"
#include "all_solutions.h"

int YEAR{2024};

TEST_SUITE_BEGIN("AOC 2024");

template<typename solution_type>
void print_part_a_solution(int day, bool is_test, solution_type solution)
{
    std::cout << "Solution for day " << day << " part a ";
    if (is_test) {
        std::cout << "for test data: ";
    }
    else {
        std::cout << "for real data: ";
    }
    std::cout << solution << std::endl;
}

template<typename solution_type>
void print_part_b_solution(int day, bool is_test, solution_type solution)
{
    std::cout << "Solution for day " << day << " part b ";
    if (is_test) {
        std::cout << "for test data: ";
    }
    else {
        std::cout << "for real data: ";
    }
    std::cout << solution << std::endl;
}

TEST_CASE("AOC 2024 Day 1 tests.")
{
    int day{1};
    bool is_test{true};
    utils::InputReader data{day, YEAR, is_test};
    auto part_a = solutions::day_1_part_a(data);
    print_part_a_solution(day, is_test, part_a);
    CHECK(part_a==209);

    auto part_b = solutions::day_1_part_b(data);
    print_part_b_solution(day, is_test, part_b);
    CHECK(part_b==281);
}

TEST_CASE("AOC 2024 Day 1 solution.")
{
    int day{1};
    bool is_test{false};
    utils::InputReader data{day, YEAR, is_test};
    auto part_a = solutions::day_1_part_a(data);
    print_part_a_solution(day, is_test, part_a);
    CHECK(part_a==55029);

    auto part_b = solutions::day_1_part_b(data);
    print_part_b_solution(day, is_test, part_b);
    CHECK(part_b==55686);
}

TEST_SUITE_END;