#pragma clang diagnostic ignored "-Woverloaded-shift-op-parentheses"

#include "../doctest.h"
#include "../utils/utils.h"

TEST_SUITE_BEGIN("Solution tools test suite.");

class MySolution final : public utils::SolutionTemplate<int> {
public:
	MySolution() : SolutionTemplate(
			2050,
			100,
			25,
			50,
			42,
			84) {
	}

	int solve_part_a(const utils::InputReader &input_reader) override { return 25; }

	int solve_part_b(const utils::InputReader &input_reader) override { return 42; }
};

TEST_CASE("Implementing of solution class.")
{
	SUBCASE("Test properties of solution template" + 1001) {
		MySolution my_sol{};
		auto part_a_val = my_sol.solution_part_a(true);
		auto part_b_val = my_sol.solution_part_b(true);
		CHECK(part_a_val == 25);
		CHECK(part_b_val == 42);
	}

}

TEST_SUITE_END;
