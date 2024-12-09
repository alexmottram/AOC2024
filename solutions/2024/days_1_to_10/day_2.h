#pragma once

#include "../../../utils/utils.h"

namespace solutions{
    class Day2Solution final : public utils::SolutionTemplate<long long>
    {
    public:
        Day2Solution(): SolutionTemplate(
            2024,
            2,
            2,
            534,
            4,
            577
            ) {}

        long long solve_part_a(const utils::InputReader& input_reader) override;
        long long solve_part_b(const utils::InputReader& input_reader) override;
    };
}