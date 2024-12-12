#pragma once

#include "../../../utils/utils.h"

namespace solutions
{
    class Day12Solution final : public utils::SolutionTemplate<long long>
    {
    public:
        Day12Solution(): SolutionTemplate(
            2024,
            12,
            1930,
            1421958,
            1206,
            885394
            ) {}

        long long solve_part_a(const utils::InputReader& input_reader) override;
        long long solve_part_b(const utils::InputReader& input_reader) override;
    };

}
