#pragma once

#include "../../../utils/utils.h"
#include "../common_header.h"

namespace solutions {

	class Day16Solution final : public utils::SolutionTemplate<long long> {
	public:
		Day16Solution() : SolutionTemplate(
				2024,
				16,
				11048,
				102488,
				64,
				559
		) {}

		long long solve_part_a(const utils::InputReader &input_reader) override;

		long long solve_part_b(const utils::InputReader &input_reader) override;
	};


	struct MazeLocation {
		char map_char{'.'};
		long long from_above{-1};
		long long from_below{-1};
		long long from_left{-1};
		long long from_right{-1};

		MazeLocation(char map_char_in) :
				map_char(map_char_in),
				from_above(-1),
				from_below(-1),
				from_left(-1),
				from_right(-1) {
		}

		long long minimum_score() const {
			std::set<long long> all_values{};
			if (from_above != -1) {
				all_values.insert(from_above);
			}
			if (from_below != -1) {
				all_values.insert(from_below);
			}
			if (from_left != -1) {
				all_values.insert(from_left);
			}
			if (from_right != -1) {
				all_values.insert(from_right);
			}
			if (all_values.empty()) {
				return -1;
			}
			return *std::min_element(all_values.begin(), all_values.end());
		}

		long long get_value(char direction) const {
			switch (direction) {
				case '^':
					return from_below;
				case 'v':
					return from_above;
				case '>':
					return from_left;
				case '<':
					return from_right;
				default:
					throw std::runtime_error("Invalid direction character.");
			}
		}

		long long shortest_distance_to_next_destination(char next_destination) const {
			char anticlockwise{'.'};
			char clockwise{'.'};
			char reverse{'.'};
			char straight{next_destination};
			switch (next_destination) {
				case '^':
					anticlockwise = '<';
					clockwise = '>';
					reverse = 'v';
					break;
				case 'v':
					anticlockwise = '>';
					clockwise = '<';
					reverse = '^';
					break;
				case '>':
					anticlockwise = '^';
					clockwise = 'v';
					reverse = '<';
					break;
				case '<':
					anticlockwise = 'v';
					clockwise = '^';
					reverse = '>';
					break;
				default:
					throw std::runtime_error("Invalid direction character.");
			}
			auto anticlockwise_value = get_value(anticlockwise);
			auto clockwise_value = get_value(clockwise);
			auto straight_value = get_value(straight);
			auto reverse_value = get_value(reverse);

			std::set<long long> all_values{};

			if (anticlockwise_value != -1) {
				all_values.insert(1001 + anticlockwise_value);
			}
			if (clockwise_value != -1) {
				all_values.insert(1001 + clockwise_value);
			}
			if (reverse_value != -1) {
				all_values.insert(2001 + reverse_value);
			}
			if (straight_value != -1) {
				all_values.insert(1 + straight_value);
			}

			return *std::min_element(all_values.begin(), all_values.end());
		}

		void set_value(char direction, long long distance) {
			switch (direction) {
				case '^':
					from_below = distance;
					break;
				case 'v':
					from_above = distance;
					break;
				case '>':
					from_left = distance;
					break;
				case '<':
					from_right = distance;
					break;
				default:
					throw std::runtime_error("Invalid direction character.");
			}
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

		friend bool operator==(const MazeLocation &ml_a, const MazeLocation &ml_b) {
			return ml_a.map_char == ml_b.map_char;
		}

		friend bool operator<(const MazeLocation &ml_a, const MazeLocation &ml_b) {
			return ml_a.map_char < ml_b.map_char;
		}
	};

	typedef utils::Array2D<MazeLocation> ReindeerMaze;

}
