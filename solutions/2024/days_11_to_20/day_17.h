#pragma once

#include "../../../utils/utils.h"

namespace solutions
{
    class Day17Solution final : public utils::SolutionTemplate<long long>
    {
    public:
        Day17Solution(): SolutionTemplate(
            2024,
            17,
            1,
            1,
            1,
            1
            ) {}

        long long solve_part_a(const utils::InputReader& input_reader) override;
        long long solve_part_b(const utils::InputReader& input_reader) override;
    };

}
