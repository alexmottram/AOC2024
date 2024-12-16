#pragma once

#include "../../../utils/utils.h"

namespace solutions
{
	typedef utils::Array2D<long long> ToiletMap;
	typedef utils::Array2D<char> ToiletCharMap;
	typedef std::set<utils::Vec2D<size_t>> SetVec2D;
    class Day14Solution final : public utils::SolutionTemplate<long long>
    {
    public:
        Day14Solution(): SolutionTemplate(
            2024,
            14,
            12,
            230172768,
            70505,
            70505
            ) {}

        long long solve_part_a(const utils::InputReader& input_reader) override;
        long long solve_part_b(const utils::InputReader& input_reader) override;
    };

	struct ToiletRobot {
		utils::Vec2D<long long> start;
		utils::Vec2D<long long> position;
		utils::Vec2D<long long> velocity;

		ToiletRobot(std::string str_vec);

		utils::Vec2D<long long> move(long long moves, const ToiletMap& toilet_map);

		friend std::ostream &operator<<(std::ostream &os, const ToiletRobot &tr) {
			os << "ToiletRobot(position=" << tr.position << ", velocity=" << tr.velocity
				<<", start=" << tr.start << ")";
			return os;
		}

	};
}
