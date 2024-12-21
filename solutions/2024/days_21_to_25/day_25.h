#pragma once

#include "../../../utils/utils.h"
#include "../common_header.h"

namespace solutions
{
    class Day25Solution final : public utils::SolutionTemplate<long long>
    {
    public:
        Day25Solution(): SolutionTemplate(
            2024,
            25,
            1,
            1,
            1,
            1
            ) {}

        long long solve_part_a(const utils::InputReader& input_reader) override;
        long long solve_part_b(const utils::InputReader& input_reader) override;
    };

}
