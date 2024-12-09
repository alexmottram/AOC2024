#pragma once

#include "../../utils/utils.h"

namespace solutions
{
    class DayXSolution final : public utils::SolutionTemplate<long long>
    {
    public:
        DayXSolution(): SolutionTemplate(
            2024,
            0,
            1,
            1,
            1,
            1
            ) {}

        long long solve_part_a(const utils::InputReader& input_reader) override;
        long long solve_part_b(const utils::InputReader& input_reader) override;
    };

}
