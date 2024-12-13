#include "day_13.h"

namespace solutions {
	ClawMachine::ClawMachine(std::vector<std::string> str_vec, long long prize_addition) {
		auto button_a = str_vec.at(0);
		auto button_b = str_vec.at(1);
		auto prize = str_vec.at(2);

		auto a_x_and_y_strs = utils::split_string(
				utils::split_string(button_a, ":").at(1),
				",", true

		);

		auto b_x_and_y_strs = utils::split_string(
				utils::split_string(button_b, ":").at(1),
				",", true

		);

		auto prize_x_y_strs = utils::split_string(
				utils::split_string(prize, ":").at(1),
				",", true

		);

		auto a_x_str = a_x_and_y_strs.at(0);
		auto a_x_num = utils::string_to_type<long long>(a_x_str.substr(2, a_x_str.size() - 2));
		auto a_y_str = a_x_and_y_strs.at(1);
		auto a_y_num = utils::string_to_type<long long>(a_y_str.substr(2, a_y_str.size() - 2));

		auto b_x_str = b_x_and_y_strs.at(0);
		auto b_x_num = utils::string_to_type<long long>(b_x_str.substr(2, b_x_str.size() - 2));
		auto b_y_str = b_x_and_y_strs.at(1);
		auto b_y_num = utils::string_to_type<long long>(b_y_str.substr(2, b_y_str.size() - 2));

		auto prize_x_str = prize_x_y_strs.at(0);
		auto prize_x_num = utils::string_to_type<long long>(prize_x_str.substr(2, prize_x_str.size() - 2));
		auto prize_y_str = prize_x_y_strs.at(1);
		auto prize_y_num = utils::string_to_type<long long>(prize_y_str.substr(2, prize_y_str.size() - 2));

		a_x = a_x_num;
		a_y = a_y_num;
		b_x = b_x_num;
		b_y = b_y_num;
		prize_x = prize_x_num + prize_addition;
		prize_y = prize_y_num + prize_addition;
	}

	std::pair<long long, long long> ClawMachine::get_button_presses() {
		long long press_a = ((prize_x * b_y) - (prize_y * b_x)) / ((a_x * b_y) - (a_y * b_x));
		long long press_b = ((prize_x * a_y) - (prize_y * a_x)) / ((b_x * a_y) - (b_y * a_x));
		if (check_button_presses(press_a, press_b)) {
			return {press_a, press_b};
		} else {
			return {0, 0};
		}
	}

	long long ClawMachine::get_token_cost() {
		auto button_presses = get_button_presses();
		return (button_presses.first * 3) + (button_presses.second * 1);
	}

	bool ClawMachine::check_button_presses(long long int a, long long int b) {
		return (((a * a_x + b * b_x) == prize_x) and ((a * a_y + b * b_y) == prize_y));
	}


	std::vector<ClawMachine> get_claw_machines(const utils::InputReader &input_reader, long long prize_addition) {
		std::vector<ClawMachine> claw_machines{};
		std::vector<std::string> current_data{};

		for (auto line: input_reader.string_vector()) {
			if (line.empty()) {
				claw_machines.emplace_back(current_data, prize_addition);
				current_data = {};
			} else {
				current_data.push_back(line);
			}
		}
		claw_machines.emplace_back(current_data, prize_addition);
		std::cout << "Found " << claw_machines.size() << " claw machines." << std::endl;
		return claw_machines;
	}

	long long Day13Solution::solve_part_a(const utils::InputReader &input_reader) {
		auto claw_machines = get_claw_machines(input_reader, 0);
		long long total_token_cost{0};
		for (auto claw_machine: claw_machines) {
			auto curr_token_cost = claw_machine.get_token_cost();
			total_token_cost += curr_token_cost;
			std::cout << claw_machine << std::endl;
			std::cout << "Solution for claw machine is: "
			          << claw_machine.get_button_presses() << " with token cost: "
			          << curr_token_cost << std::endl;

		}
		return total_token_cost;
	}

	long long Day13Solution::solve_part_b(const utils::InputReader &input_reader) {
		auto claw_machines = get_claw_machines(input_reader, 10000000000000);
		long long total_token_cost{0};
		for (auto claw_machine: claw_machines) {
			auto curr_token_cost = claw_machine.get_token_cost();
			total_token_cost += curr_token_cost;
			std::cout << claw_machine << std::endl;
			std::cout << "Solution for claw machine is: "
			          << claw_machine.get_button_presses() << " with token cost: "
			          << curr_token_cost << std::endl;
		}
		return total_token_cost;
	}

}