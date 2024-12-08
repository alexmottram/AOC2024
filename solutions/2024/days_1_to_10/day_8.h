#pragma once

#include "../../../utils/utils.h"

namespace solutions
{
    class Day8Solution final : public utils::SolutionTemplate<long long>
    {
    public:
        Day8Solution(): SolutionTemplate(
            2024,
            8,
            14,
            329,
            34,
            1190
            ) {}

        long long solve_part_a(const utils::InputReader& input_reader) override;
        long long solve_part_b(const utils::InputReader& input_reader) override;
    };

}
