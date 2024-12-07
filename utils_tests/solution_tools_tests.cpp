#pragma clang diagnostic ignored "-Woverloaded-shift-op-parentheses"
#include "../doctest.h"
#include "../utils/utils.h"

TEST_SUITE_BEGIN("Solution tools test suite.");

class MySolution final : public utils::SolutionTemplate<int>
{
public:
    MySolution(): SolutionTemplate(2024, 6)
    {
    }

    int solve_part_a(utils::InputReader input_reader) override { return 6; }
    int solve_part_b(utils::InputReader input_reader) override { return 2024; }
};

TEST_CASE("Implementing of solution class.")
{
    SUBCASE("Test properties of solution template")
    {
        MySolution my_sol{};
        auto part_a_val = my_sol.solution_part_a(true);
        auto part_b_val = my_sol.solution_part_b(true);
        CHECK(part_a_val == 6);
        CHECK(part_b_val == 2024);
    }
}

TEST_SUITE_END;
