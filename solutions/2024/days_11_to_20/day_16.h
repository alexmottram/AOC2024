#pragma once

#include "../../../utils/utils.h"
#include "../common_header.h"

namespace solutions {

	class Day16Solution final : public utils::SolutionTemplate<long long> {
	public:
		Day16Solution() : SolutionTemplate(
				2024,
				16,
				1,
				1,
				1,
				1
		) {}

		long long solve_part_a(const utils::InputReader &input_reader) override;

		long long solve_part_b(const utils::InputReader &input_reader) override;
	};


	struct MazeLocation {
		char map_char{'.'};
		long long from_above{0};
		long long from_below{0};
		long long from_left{0};
		long long from_right{0};

		MazeLocation(char map_char_in) :
				map_char(map_char_in),
				from_above(0),
				from_below(0),
				from_left(0),
				from_right(0) {
		}

		long long minimum_score(){
			return std::min(std::min(from_above, from_below), std::min(from_left, from_right));
		}

		friend std::ostream &operator<<(std::ostream &os, const MazeLocation &ml) {
			os << "Loc(char=" << ml.map_char
			   << ", v=" << ml.from_above
			   << ", ^=" << ml.from_below
			   << ", >=" << ml.from_left
			   << ", <=" << ml.from_right
			   << ")";
			return os;
		}

	};

	typedef utils::Array2D<MazeLocation> ReindeerMaze;

}
