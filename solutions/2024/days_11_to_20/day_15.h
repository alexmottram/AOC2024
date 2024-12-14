#pragma once

#include "../../../utils/utils.h"

namespace solutions
{
    class Day15Solution final : public utils::SolutionTemplate<long long>
    {
    public:
        Day15Solution(): SolutionTemplate(
            2024,
            15,
            1,
            1,
            1,
            1
            ) {}

        long long solve_part_a(const utils::InputReader& input_reader) override;
        long long solve_part_b(const utils::InputReader& input_reader) override;
    };

}
