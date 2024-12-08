#pragma once

#include "../../../utils/utils.h"

namespace solutions
{
    class Day6Solution final : public utils::SolutionTemplate<long long>
    {
    public:
        Day6Solution(): SolutionTemplate(2024, 6) {}

        static constexpr long long EXPECTED_TEST_A{41};
        static constexpr long long EXPECTED_SOLUTION_A{5331};
        static constexpr long long EXPECTED_TEST_B{6};
        static constexpr long long EXPECTED_SOLUTION_B{1812};

        long long solve_part_a(utils::InputReader input_reader) override;
        long long solve_part_b(utils::InputReader input_reader) override;
    };
}
