#pragma once

#include "../../../utils/utils.h"

namespace solutions
{
    class Day8Solution final : public utils::SolutionTemplate<long long>
    {
    public:
        Day8Solution(): SolutionTemplate(2024, 8) {}

        static constexpr long long EXPECTED_TEST_A{14};
        static constexpr long long EXPECTED_SOLUTION_A{329};
        static constexpr long long EXPECTED_TEST_B{34};
        static constexpr long long EXPECTED_SOLUTION_B{1190};

        long long solve_part_a(utils::InputReader input_reader) override;
        long long solve_part_b(utils::InputReader input_reader) override;
    };

}
