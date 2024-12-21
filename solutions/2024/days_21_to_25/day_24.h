#pragma once

#include "../../../utils/utils.h"
#include "../common_header.h"

namespace solutions
{
    class Day24Solution final : public utils::SolutionTemplate<long long>
    {
    public:
        Day24Solution(): SolutionTemplate(
            2024,
            24,
            1,
            1,
            1,
            1
            ) {}

        long long solve_part_a(const utils::InputReader& input_reader) override;
        long long solve_part_b(const utils::InputReader& input_reader) override;
    };

}
