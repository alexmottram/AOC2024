#pragma once

#include "../../../utils/utils.h"

namespace solutions
{
    class Day6Solution final : public utils::SolutionTemplate<long long>
    {
    public:
        Day6Solution(): SolutionTemplate(
            2024,
            6,
            41,
            5331,
            6,
            1812
        )
        {
        }

        long long solve_part_a(const utils::InputReader& input_reader) override;
        long long solve_part_b(const utils::InputReader& input_reader) override;
    };
}
