#pragma once

#include "../../../utils/utils.h"

namespace solutions{
    class Day1Solution final : public utils::SolutionTemplate<long long>
    {
    public:
        Day1Solution(): SolutionTemplate(
            2024,
            1,
            11,
            1110981,
            31,
            24869388
            ) {}

        long long solve_part_a(const utils::InputReader& input_reader) override;
        long long solve_part_b(const utils::InputReader& input_reader) override;
    };
}