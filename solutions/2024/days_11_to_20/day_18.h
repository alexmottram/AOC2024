#pragma once

#include "../../../utils/utils.h"
#include "../common_header.h"

namespace solutions
{
    class Day18Solution final : public utils::SolutionTemplate<long long>
    {
    public:
        Day18Solution(): SolutionTemplate(
            2024,
            18,
            22,
            248,
            1,
            1
            ) {}

        long long solve_part_a(const utils::InputReader& input_reader) override;
        long long solve_part_b(const utils::InputReader& input_reader) override;
    };

}
