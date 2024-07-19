#pragma clang diagnostic ignored "-Woverloaded-shift-op-parentheses"

#include "../../doctest.h"
#include "../../utils/utils.h"
#include "all_solutions.h"

int YEAR{2023};

TEST_SUITE_BEGIN("AOC 2023");

template<typename solution_type>
void print_part_a_solution(int day, bool is_test, solution_type solution)
{
    std::cout << "Solution for day " << 1 << " part a ";
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
    std::cout << "Solution for day " << 1 << " part b ";
    if (is_test) {
        std::cout << "for test data: ";
    }
    else {
        std::cout << "for real data: ";
    }
    std::cout << solution << std::endl;
}

TEST_CASE("AOC 2023 Day 1 tests.")
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

TEST_CASE("AOC 2023 Day 1 solution.")
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

TEST_CASE("AOC 2023 Day 2 tests.")
{
    int day{2};
    bool is_test{true};
    utils::InputReader data{day, YEAR, is_test};
    auto part_a = solutions::day_2_part_a(data);
    print_part_a_solution(day, is_test, part_a);
    CHECK(part_a==8);

    auto part_b = solutions::day_2_part_b(data);
    print_part_b_solution(day, is_test, part_b);
    CHECK(part_b==2286);
}

TEST_CASE("AOC 2023 Day 2 solution.")
{

    int day{2};
    bool is_test{false};
    utils::InputReader data{day, YEAR, is_test};
    auto part_a = solutions::day_2_part_a(data);
    print_part_a_solution(day, is_test, part_a);
    CHECK(part_a==2600);

    auto part_b = solutions::day_2_part_b(data);
    print_part_b_solution(day, is_test, part_b);
    CHECK(part_b==86036);
}

TEST_CASE("AOC 2023 Day 3 tests.")
{
    int day{3};
    bool is_test{true};
    utils::InputReader data{day, YEAR, is_test};
    auto part_a = solutions::day_3_part_a(data);
    print_part_a_solution(day, is_test, part_a);
    CHECK(part_a==4361);
//    auto part_b_test = solutions::day_3_part_b(test_data);
//    CHECK(part_b_test==2286);
}

TEST_CASE("AOC 2023 Day 3 solution.")
{
    int day{3};
    bool is_test{false};
    utils::InputReader data{day, YEAR, is_test};
    auto part_a = solutions::day_3_part_a(data);
    print_part_a_solution(day, is_test, part_a);
    CHECK(part_a==525181);

//    auto part_b_test = solutions::day_3_part_b(test_data);
//    CHECK(part_b_test==2286);
}

TEST_CASE("AOC 2023 Day 21 tests.")
{

    utils::InputReader test_data{21, YEAR, true};
    auto part_a_test = solutions::day_21_part_a(test_data, 6);
    CHECK(part_a_test==16);
}

TEST_CASE("AOC 2023 Day 21 2023.")
{
    utils::InputReader test_data{21, YEAR, false};
    auto part_a_test = solutions::day_21_part_a(test_data, 64);
    CHECK(part_a_test==3649);
}

TEST_SUITE_END;