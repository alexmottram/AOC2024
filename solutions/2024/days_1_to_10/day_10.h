#pragma once

#include "../../../utils/utils.h"

namespace solutions
{
    class Day10Solution final : public utils::SolutionTemplate<long long>
    {
    public:
        Day10Solution(): SolutionTemplate(
            2024,
            10,
            36,
            811,
            81,
            1
            ) {}

        long long solve_part_a(const utils::InputReader& input_reader) override;
        long long solve_part_b(const utils::InputReader& input_reader) override;
    };

}
