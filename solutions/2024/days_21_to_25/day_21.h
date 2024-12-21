#pragma once

#include "../../../utils/utils.h"
#include "../common_header.h"

namespace solutions {
	typedef std::pair<char, char> PairChar;
	typedef std::set<std::vector<char>> SetVectorChar;

	class Day21Solution final : public utils::SolutionTemplate<long long> {
	public:
		Day21Solution() : SolutionTemplate(
				2024,
				21,
				126384,
				182844,
				154115708116294,
				226179529377982
		) {}

		long long solve_part_a(const utils::InputReader &input_reader) override;

		long long solve_part_b(const utils::InputReader &input_reader) override;
	};

	class KeyPad {
	public:
		KeyPad(const std::string &label, const CharArray &buttons) :
				label(label), buttons(buttons) {
			loc = buttons.const_find_unique('A').vector();
			calculate_all_moves();
		}

		void calculate_all_moves();

		SetVectorChar valid_instructions_between_locations(SizeTVec2D start, SizeTVec2D end);

		SetVectorChar shortest_routes_between_buttons(PairChar start_end_pair);

		std::set<PairChar> all_valid_pairs() {
			std::set<PairChar> set_of_pairs;
			std::transform(
					move_options.begin(), move_options.end(),
					std::inserter(set_of_pairs, set_of_pairs.end()),
					[](auto pair) { return pair.first; }
			);
			return set_of_pairs;
		}

		SetVectorChar routes_between_locations(PairChar start_end_pair) {
			return move_options[start_end_pair];
		}

		friend std::ostream &operator<<(std::ostream &os, const KeyPad &kp) {
			os << "KeyPad(label=" << kp.label << " current_loc=" << kp.loc
			   << "\n" << kp.buttons << ")\n";
			for (auto [k, v]: kp.move_options) {
				os << "Moves for: " << k << " are: " << v << "\n";
			}
			return os;
		}

	private:
		std::string label;
		CharArray buttons;
		SizeTVec2D loc;
		std::map<PairChar, SetVectorChar> move_options{};
	};

}
