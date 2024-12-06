#pragma clang diagnostic ignored "-Woverloaded-shift-op-parentheses"
#include "../doctest.h"
#include "../utils/utils.h"

TEST_SUITE_BEGIN("Solution tools test suite.");

class MySolution final : utils::SolutionTemplate<int>{
public:
    static constexpr int DAY {10};
    static constexpr int YEAR {2024};

    int solve_part_a(utils::InputReader input_reader) override {return DAY;}
    int solve_part_b(utils::InputReader input_reader) override {return YEAR;}
};

TEST_CASE("Implementing of solution class.")
{
    SUBCASE("Test properties of solution template")
    {
        MySolution my_sol{};
        auto part_a_val = my_sol.get_input_reader();
        CHECK(part_a_val == MySolution::DAY);
        CHECK(part_a_val == MySolution::YEAR);
    }
}

TEST_SUITE_END;
