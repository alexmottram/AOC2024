#pragma once

#include "../../../utils/utils.h"
#include "../common_header.h"

namespace solutions
{
	typedef utils::Array2D<char> FactoryMap;
	typedef utils::Vec2D<long long> LlVec2D;
	typedef std::vector<char> RobotMoves;

    class Day15Solution final : public utils::SolutionTemplate<long long>
    {
    public:
        Day15Solution(): SolutionTemplate(
            2024,
            15,
            10092,
            1514353,
            9021,
            1533076
            ) {}

        long long solve_part_a(const utils::InputReader& input_reader) override;
        long long solve_part_b(const utils::InputReader& input_reader) override;
    };

}
