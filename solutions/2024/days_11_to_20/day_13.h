#pragma once

#include "../../../utils/utils.h"

namespace solutions {
	class Day13Solution final : public utils::SolutionTemplate<long long> {
	public:
		Day13Solution() : SolutionTemplate(
				2024,
				13,
				480,
				33481,
				875318608908,
				92572057880885
		) {}

		long long solve_part_a(const utils::InputReader &input_reader) override;

		long long solve_part_b(const utils::InputReader &input_reader) override;
	};

	struct ClawMachine {
		long long a_x{};
		long long a_y{};
		long long b_x{};
		long long b_y{};
		long long prize_x{};
		long long prize_y{};

		ClawMachine(std::vector<std::string> str_vec, long long prize_addition = 0);

		std::pair<long long, long long> get_button_presses();

		bool check_button_presses(long long a, long long b);

		long long get_token_cost();

		friend std::ostream &operator<<(std::ostream &os, const ClawMachine &cm) {
			os << "ClawMachine{ButtonA: x=" << cm.a_x << ",y=" << cm.a_y
			   << ", ButtonB: x=" << cm.b_x << ",y=" << cm.b_y
			   << ", PrizeLocation: x=" << cm.prize_x << ",y=" << cm.prize_y
			   << "}";
			return os;
		}

	};
}
