#include "day_21.h"

namespace solutions {
	utils::Array2D<char> PASSCODE_BUTTONS{
			{std::vector<char>{'7', '8', '9'},
			 {'4', '5', '6'},
			 {'1', '2', '3'},
			 {' ', '0', 'A'}
			}};
	utils::Array2D<char> DIRECTION_BUTTONS{
			{std::vector<char>{' ', '^', 'A'}, {'<', 'v', '>'}
			}};

	std::vector<char> shortest_in_set(SetVectorChar set_of_vector_chars) {
		SetVectorChar shortest_vecs;
		auto smallest_size = std::min_element(
				set_of_vector_chars.begin(),
				set_of_vector_chars.end(),
				[](auto i, auto j) { return i.size() < j.size(); }
		)->size();

		for (auto vector_char: set_of_vector_chars) {
			if (vector_char.size() == smallest_size) {
				shortest_vecs.insert(vector_char);
			}
		}
		auto return_vec = *(shortest_vecs.begin());
		return return_vec;
	}

	SetVectorChar KeyPad::valid_instructions_between_locations(SizeTVec2D start, SizeTVec2D end) {
		auto start_ll = static_cast<LlVec2D>(start);
		auto end_ll = static_cast<LlVec2D>(end);

		std::vector<std::vector<LlVec2D>> running_paths{{start_ll}};
		std::vector<std::vector<LlVec2D>> solved_paths{};

		while (!running_paths.empty()) {
			std::vector<std::vector<LlVec2D>> next_paths{};
			for (auto path: running_paths) {
				// If path is at end point add it to solved paths
				if (path.back() == end_ll) {
					solved_paths.push_back(path);
				}

				// Should we move on the x axis
				if (path.back().x != end.x) {
					if (path.back().x < end.x) {
						auto next_loc = path.back() + LlVec2D{1, 0};
						if (buttons.at(next_loc) != ' ') {
							auto continued_path = path;
							continued_path.push_back(next_loc);
							next_paths.push_back(continued_path);
						}
					} else if (path.back().x > end.x) {
						auto next_loc = path.back() + LlVec2D{-1, 0};
						if (buttons.at(next_loc) != ' ') {
							auto continued_path = path;
							continued_path.push_back(next_loc);
							next_paths.push_back(continued_path);
						}
					}
				}

				// Should we move on the y axis
				if (path.back().y != end.y) {
					if (path.back().y < end.y) {
						auto next_loc = path.back() + LlVec2D{0, 1};
						if (buttons.at(next_loc) != ' ') {
							auto continued_path = path;
							continued_path.push_back(next_loc);
							next_paths.push_back(continued_path);
						}
					} else if (path.back().y > end.y) {
						auto next_loc = path.back() + LlVec2D{0, -1};
						if (buttons.at(next_loc) != ' ') {
							auto continued_path = path;
							continued_path.push_back(next_loc);
							next_paths.push_back(continued_path);
						}
					}
				}
			}
			running_paths = next_paths;
		}


		// Turn vector arrays into list of character instructions
		SetVectorChar all_paths{};
		for (auto path: solved_paths) {
			std::vector<char> char_path{};

			for (auto i{1}; i < path.size(); i++) {
				auto first_vec = path.at(i - 1);
				auto second_vec = path.at(i);
				auto diff = second_vec - first_vec;
				if (diff.x == 0) {

					if (diff.y == 1) { char_path.push_back('v'); }
					else if (diff.y == -1) { char_path.push_back('^'); }
					else { throw std::runtime_error("Can only handle plus or minus 1 y."); }

				} else if (diff.y == 0) {

					if (diff.x == 1) { char_path.push_back('>'); }
					else if (diff.x == -1) { char_path.push_back('<'); }
					else { throw std::runtime_error("Can only handle plus or minus 1 x."); }

				} else {

					throw std::runtime_error("Both moves not valid.");
				}
			}
			all_paths.insert(char_path);
		}
		return all_paths;
	}


	void KeyPad::calculate_all_moves() {

		for (auto start_node: buttons.const_node_iter()) {
			for (auto end_node: buttons.const_node_iter()) {
				auto start_vec = start_node.vector();
				auto end_vec = end_node.vector();
				if (start_node.value != ' ' and end_node.value != ' ') {
//					std::cout << "Finding paths between: " << start_node << " and " << end_node << std::endl;
					auto valid_paths = valid_instructions_between_locations(start_vec, end_vec);
					move_options[{start_node.value, end_node.value}] = valid_paths;
				}
			}
		}
	}

	SetVectorChar KeyPad::shortest_routes_between_buttons(PairChar start_end_pair) {
		SetVectorChar shortest_routes;
		auto routes = move_options[start_end_pair];
		auto smallest_size = std::min_element(
				routes.begin(),
				routes.end(),
				[](auto i, auto j) { return i.size() < j.size(); }
		)->size();

		for (auto route: routes) {
			if (route.size() == smallest_size) {
				shortest_routes.insert(route);
			}
		}
		return shortest_routes;
	}


	std::map<PairChar, std::vector<char>> create_passcode_to_dkeypad_map(
			KeyPad passcode_keypad, KeyPad dkeypad, size_t num_keypads
	) {
		std::cout << "\nStarting map creation for directional keypad 2 to keypad 1." << std::endl;

		// Create map of directional keypad 2 to keypad 3 instructions

		std::map<PairChar, std::vector<char>> rolling_keypad_map{};

		for (auto start_end_pair: dkeypad.all_valid_pairs()) {
			std::cout << "Processing keyboard 1 instruction pair: " << start_end_pair << std::endl;
			SetVectorChar sets_of_dkeypad_1_instructions{};

			// Handle duplicate button presses
			if (start_end_pair.first == start_end_pair.second) {
				sets_of_dkeypad_1_instructions.insert({'A'});
			} else {
				auto sets_of_dkeypad_2_instructions = dkeypad.routes_between_locations(start_end_pair);

				for (const auto &instructions: sets_of_dkeypad_2_instructions) {
					auto instruction_copy = instructions;
					instruction_copy.push_back('A');
					sets_of_dkeypad_1_instructions.insert(instruction_copy);
				}
			}

			std::cout << "Valid 2 instructions on keyboard 3 are: " << sets_of_dkeypad_1_instructions << std::endl;
			rolling_keypad_map[start_end_pair] = shortest_in_set(sets_of_dkeypad_1_instructions);
		}

		for (auto dkeypad_num{2}; dkeypad_num <= num_keypads; dkeypad_num++) {


			std::cout << "\nStarting map creation for directional keypad "
			          << dkeypad_num << " to final keypad." << std::endl;

			std::map<PairChar, std::vector<char>> keypad_map_current;

			for (auto start_end_pair: dkeypad.all_valid_pairs()) {
				std::cout << "Processing keyboard " << dkeypad_num
				          << " instruction pair: " << start_end_pair << std::endl;
				SetVectorChar sets_of_dkeypad_3_instructions{};

				if (start_end_pair.first == start_end_pair.second) {
					sets_of_dkeypad_3_instructions.insert({'A'});
				} else {
					auto sets_of_dkeypad_1_instructions = dkeypad.routes_between_locations(start_end_pair);
					for (const auto &dkeypad_2_instructions: sets_of_dkeypad_1_instructions) {
						std::vector<char> dkeypad_2_instructions_copy{'A'};
						std::copy(
								dkeypad_2_instructions.begin(),
								dkeypad_2_instructions.end(),
								std::back_inserter(dkeypad_2_instructions_copy)
						);
						dkeypad_2_instructions_copy.push_back('A');
						std::vector<char> dkeypad_3_instructions{};
						for (auto i{1}; i < dkeypad_2_instructions_copy.size(); i++) {
							PairChar dkeypad_2_pair{dkeypad_2_instructions_copy.at(i - 1),
							                        dkeypad_2_instructions_copy.at(i)};
							auto curr_dkeypad_3_instructions = rolling_keypad_map[dkeypad_2_pair];
							std::copy(
									curr_dkeypad_3_instructions.begin(),
									curr_dkeypad_3_instructions.end(),
									std::back_inserter(dkeypad_3_instructions)
							);
						}
						sets_of_dkeypad_3_instructions.insert(dkeypad_3_instructions);
					}
				}
				auto shortest_instructions = shortest_in_set(sets_of_dkeypad_3_instructions);
//				std::cout << "Valid instructions on directional keyboard are: " << shortest_instructions << std::endl;
				keypad_map_current[start_end_pair] = shortest_instructions;
			}
			rolling_keypad_map = keypad_map_current;
		}
		std::cout << "\nStarting map creation for number keypad to first keypad." << std::endl;
		// Create map of directional keypad 1 to keypad 3 instructions
		std::map<PairChar, std::vector<char>> passcode_keypad_to_keypad_3_commands;

		for (auto start_end_pair: passcode_keypad.all_valid_pairs()) {
//			std::cout << "Processing passcode keypad instruction pair: " << start_end_pair << std::endl;
			SetVectorChar sets_of_dkeypad_3_instructions{};

			if (start_end_pair.first == start_end_pair.second) {
				sets_of_dkeypad_3_instructions.insert({'A'});
			} else {
				auto sets_of_pkeypad_instructions = passcode_keypad.routes_between_locations(start_end_pair);
				for (const auto &dkeypad_1_instructions: sets_of_pkeypad_instructions) {
					std::vector<char> dkeypad_1_instructions_copy{'A'};
					std::copy(
							dkeypad_1_instructions.begin(),
							dkeypad_1_instructions.end(),
							std::back_inserter(dkeypad_1_instructions_copy)
					);
					dkeypad_1_instructions_copy.push_back('A');
					std::vector<char> dkeypad_3_instructions{};
					for (auto i{1}; i < dkeypad_1_instructions_copy.size(); i++) {
						PairChar dkeypad_1_pair{dkeypad_1_instructions_copy.at(i - 1),
						                        dkeypad_1_instructions_copy.at(i)};
						auto curr_dkeypad_3_instructions = rolling_keypad_map[dkeypad_1_pair];
						std::copy(
								curr_dkeypad_3_instructions.begin(),
								curr_dkeypad_3_instructions.end(),
								std::back_inserter(dkeypad_3_instructions)
						);
					}
					sets_of_dkeypad_3_instructions.insert(dkeypad_3_instructions);
				}
			}
			auto shortest_key_strokes = shortest_in_set(sets_of_dkeypad_3_instructions);
//			std::cout << "Valid passcode instructions on keyboard 3 are: " << shortest_key_strokes << std::endl;
			passcode_keypad_to_keypad_3_commands[start_end_pair] = shortest_key_strokes;
		}
		std::cout << std::endl;
		return passcode_keypad_to_keypad_3_commands;
	}

	std::map<PairChar, long long> create_passcode_to_dkeypad_len(
			KeyPad passcode_keypad, KeyPad dkeypad, size_t num_keypads
	) {
		std::cout << "\nStarting map creation for directional keypad 2 to keypad 1." << std::endl;

		// Create map of directional keypad 2 to keypad 3 instructions

		std::map<PairChar, long long> rolling_keypad_map{};

		for (auto start_end_pair: dkeypad.all_valid_pairs()) {
			std::cout << "Processing keyboard 1 instruction pair: " << start_end_pair << std::endl;
			SetVectorChar sets_of_dkeypad_1_instructions{};

			// Handle duplicate button presses
			if (start_end_pair.first == start_end_pair.second) {
				sets_of_dkeypad_1_instructions.insert({'A'});
			} else {
				auto sets_of_dkeypad_2_instructions = dkeypad.routes_between_locations(start_end_pair);

				for (const auto &instructions: sets_of_dkeypad_2_instructions) {
					auto instruction_copy = instructions;
					instruction_copy.push_back('A');
					sets_of_dkeypad_1_instructions.insert(instruction_copy);
				}
			}

			std::cout << "Valid 2 instructions on keyboard 3 are: " << sets_of_dkeypad_1_instructions << std::endl;
			rolling_keypad_map[start_end_pair] = shortest_in_set(sets_of_dkeypad_1_instructions).size();
		}

		for (auto dkeypad_num{2}; dkeypad_num <= num_keypads; dkeypad_num++) {

			std::cout << "\nStarting map creation for directional keypad "
			          << dkeypad_num << " to final keypad." << std::endl;

			std::map<PairChar, long long> keypad_map_current;

			for (auto start_end_pair: dkeypad.all_valid_pairs()) {
				std::cout << "Processing keyboard " << dkeypad_num
				          << " instruction pair: " << start_end_pair << std::endl;
				std::set<long long> next_set_of_instruction_lengths{};

				if (start_end_pair.first == start_end_pair.second) {
					next_set_of_instruction_lengths.insert(1);
				} else {
					auto new_instructions = dkeypad.routes_between_locations(start_end_pair);
					for (const auto &new_instruction: new_instructions) {
						std::vector<char> new_instructions_with_capping{'A'};
						std::copy(
								new_instruction.begin(),
								new_instruction.end(),
								std::back_inserter(new_instructions_with_capping)
						);
						new_instructions_with_capping.push_back('A');
						long long new_instruction_length{};

						for (auto i{1}; i < new_instructions_with_capping.size(); i++) {
							PairChar lookup_pair{new_instructions_with_capping.at(i - 1),
							                     new_instructions_with_capping.at(i)};
							auto curr_instruction_length = rolling_keypad_map[lookup_pair];
							new_instruction_length += curr_instruction_length;
						}
						next_set_of_instruction_lengths.insert(new_instruction_length);
					}
				}
				auto shortest_instruction_length = *std::ranges::min_element(next_set_of_instruction_lengths);
				std::cout << "Shortest valid instructions on directional keyboard are: " << shortest_instruction_length
				          << std::endl;
				keypad_map_current[start_end_pair] = shortest_instruction_length;
			}
			rolling_keypad_map = keypad_map_current;
		}
		std::cout << "\nStarting map creation for number keypad to first keypad." << std::endl;
		// Create map of directional keypad 1 to keypad 3 instructions
		std::map<PairChar, long long> final_passcode_to_length;

		for (auto start_end_pair: passcode_keypad.all_valid_pairs()) {
			std::cout << "Processing passcode keyboard instruction pair: " << start_end_pair << std::endl;
			std::set<long long> next_set_of_instruction_lengths{};

			if (start_end_pair.first == start_end_pair.second) {
				next_set_of_instruction_lengths.insert(1);
			} else {
				auto new_instructions = passcode_keypad.routes_between_locations(start_end_pair);
				for (const auto &new_instruction: new_instructions) {
					std::vector<char> new_instructions_with_capping{'A'};
					std::copy(
							new_instruction.begin(),
							new_instruction.end(),
							std::back_inserter(new_instructions_with_capping)
					);
					new_instructions_with_capping.push_back('A');
					long long new_instruction_length{};

					for (auto i{1}; i < new_instructions_with_capping.size(); i++) {
						PairChar lookup_pair{new_instructions_with_capping.at(i - 1),
						                     new_instructions_with_capping.at(i)};
						auto curr_instruction_length = rolling_keypad_map[lookup_pair];
						new_instruction_length += curr_instruction_length;
					}
					next_set_of_instruction_lengths.insert(new_instruction_length);
				}
			}
			auto shortest_instruction_length = *std::ranges::min_element(next_set_of_instruction_lengths);
			std::cout << "Shortest valid instructions on directional keyboard are: " << shortest_instruction_length
			          << std::endl;
			final_passcode_to_length[start_end_pair] = shortest_instruction_length;
		}
		std::cout << std::endl;
		return final_passcode_to_length;
	}

	std::string get_key_pad_instructions_for_code(
			std::string code, std::map<PairChar, std::vector<char>> passcode_to_dkeypad_3_map
	) {
		std::string current_code{'A'};
		current_code += code;
		std::cout << "Processing code after applying initial A: " << current_code << std::endl;
		std::string dkeypad_3_instructions{};
		for (auto i{1}; i < current_code.size(); i++) {
			PairChar curr_pair{current_code.at(i - 1), current_code.at(i)};
			auto next_instructions = passcode_to_dkeypad_3_map[curr_pair];
			std::cout << "Instructions for current pair: " << curr_pair << " are " << next_instructions << std::endl;
			for (auto char_val: next_instructions) {
				dkeypad_3_instructions += char_val;
			}
		}

		std::cout << "Full instructions are: " << dkeypad_3_instructions << std::endl;
		return dkeypad_3_instructions;
	}

	long long get_keypad_instructions_length_for_code(
			std::string code, std::map<PairChar, long long> passcode_to_dkeypad_length
	) {
		std::string current_code{'A'};
		current_code += code;
		std::cout << "Processing code after applying initial A: " << current_code << std::endl;
		long long total_instruction_length{0};
		for (auto i{1}; i < current_code.size(); i++) {
			PairChar curr_pair{current_code.at(i - 1), current_code.at(i)};
			auto next_instructions_length = passcode_to_dkeypad_length[curr_pair];
			std::cout << "Instructions length for current pair: " << curr_pair << " is " << next_instructions_length
			          << std::endl;
			total_instruction_length += next_instructions_length;
		}
		std::cout << "Total instruction length for code: " << code << " is " << total_instruction_length << std::endl;
		return total_instruction_length;
	}

	long long score_code(std::string code, std::string instructions) {
		auto code_val = utils::string_to_type<long long>(utils::split_string(code, "A").at(0));
		auto multiple = code_val * static_cast<long long>(instructions.size());
		std::cout << "Length of instructions * code number: " << instructions.size() << " * "
		          << code_val << " = " << multiple << std::endl;
		return multiple;
	}

	long long score_code_using_length(std::string code, long long length) {
		auto code_val = utils::string_to_type<long long>(utils::split_string(code, "A").at(0));
		auto multiple = code_val * length;
		std::cout << "Length of instructions * code number: " << length << " * "
		          << code_val << " = " << multiple << std::endl;
		return multiple;
	}

	long long Day21Solution::solve_part_a(const utils::InputReader &input_reader) {
		std::vector<std::string> passcodes = input_reader.string_vector();
		std::cout << "Passcodes: " << passcodes << std::endl;
		KeyPad passcode_keypad{"PassCodes", PASSCODE_BUTTONS};
		std::cout << passcode_keypad << std::endl;
		KeyPad dkeypad{"DirectionPad", DIRECTION_BUTTONS};
		std::cout << dkeypad << std::endl;


		auto passcode_to_dkeypad_3_map = create_passcode_to_dkeypad_map(
				passcode_keypad, dkeypad, 2
		);

		long long total_score{0};

		for (auto code: passcodes) {
			auto instructions = get_key_pad_instructions_for_code(code, passcode_to_dkeypad_3_map);
			auto current_score = score_code(code, instructions);
			total_score += current_score;
			std::cout << "Score for code: " << code << " is: " << current_score << "\n" << std::endl;
		}

		return total_score;
	}

	long long Day21Solution::solve_part_b(const utils::InputReader &input_reader) {
		std::vector<std::string> passcodes = input_reader.string_vector();
		std::cout << "Passcodes: " << passcodes << std::endl;
		KeyPad passcode_keypad{"PassCodes", PASSCODE_BUTTONS};
		std::cout << passcode_keypad << std::endl;
		KeyPad dkeypad{"DirectionPad", DIRECTION_BUTTONS};
		std::cout << dkeypad << std::endl;


		auto passcode_to_dkeypad_length = create_passcode_to_dkeypad_len(
				passcode_keypad, dkeypad, 25
		);

		long long total_score{0};

		for (auto code: passcodes) {
			auto instruction_length = get_keypad_instructions_length_for_code(code, passcode_to_dkeypad_length);
			auto current_score = score_code_using_length(code, instruction_length);
			total_score += current_score;
			std::cout << "Score for code: " << code << " is: " << current_score << "\n" << std::endl;
		}

		return total_score;
	}

}