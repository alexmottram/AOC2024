#include "day_15.h"

namespace solutions {

	std::map<char, LlVec2D> FACTORY_MOVES{
			{'^', {0,  -1}},
			{'v', {0,  1}},
			{'<', {-1, 0}},
			{'>', {1,  0}}
	};

	FactoryMap get_factory_map(const utils::InputReader &input_reader) {
		std::vector<std::string> map_string{};
		for (auto line: input_reader.string_vector()) {
			if (line.empty()) {
				break;
			} else {
				map_string.push_back(line);
			}
		}
		FactoryMap this_factory(map_string);
		return this_factory;
	}

	FactoryMap get_wide_factory_map(const utils::InputReader &input_reader) {
		std::vector<std::string> map_string{};
		for (auto line: input_reader.string_vector()) {
			if (line.empty()) {
				break;
			} else {
				std::string updated_line{};

				for (auto char_val: line) {
					if (char_val == '@') {
						updated_line += "@.";
					} else if (char_val == 'O') {
						updated_line += "[]";
					} else if (char_val == '#') {
						updated_line += "##";
					} else {
						updated_line += char_val;
						updated_line += char_val;
					}
				}

				map_string.push_back(updated_line);
			}
		}
		FactoryMap this_factory(map_string);
		return this_factory;
	}

	RobotMoves get_robot_directions(const utils::InputReader &input_reader) {
		std::string direction_string{};
		bool hit_instructions{false};

		for (auto line: input_reader.string_vector()) {

			if (hit_instructions) {
				direction_string += line;
			}

			if (line.empty()) {
				hit_instructions = true;
			}
		}

		RobotMoves direction = utils::string_to_vector_type<char>(direction_string);
		return direction;
	}

	void process_single_move(FactoryMap &factory_map, const LlVec2D &move) {
		std::vector<LlVec2D> blocks_to_move{};
		auto robot_loc_set = factory_map.find('@');
		auto robot_loc = *robot_loc_set.begin();
		blocks_to_move.push_back(static_cast<LlVec2D>(robot_loc.vector()));

		while (true) {
			auto next_loc = blocks_to_move.back() + move;
			auto next_val = factory_map.at(next_loc);
			if (next_val == '#') {
				// No movement allowed so leave without changes
				break;
			} else if (next_val == '.') {
				blocks_to_move.push_back(next_loc);
				// Move all into next space
				std::ranges::reverse(blocks_to_move);
				for (auto vec: blocks_to_move) {
					if (vec == static_cast<LlVec2D>(robot_loc.vector())) {
						factory_map.at(vec) = '.';
					} else {
						factory_map.at(vec) = factory_map.at(vec - move);
					}
				}
				break;
			} else {
				// Add item to list of things to move
				blocks_to_move.push_back(next_loc);
			}
		}
	}

	FactoryMap process_moves(FactoryMap &factory_map, const RobotMoves &robot_moves) {

		for (const auto &char_move: robot_moves) {
			auto move = FACTORY_MOVES[char_move];
			process_single_move(factory_map, move);
//			std::cout << "Map after move: " << move << std::endl;
//			std::cout << factory_map << std::endl << std::endl;
		}
		return factory_map;
	}

	std::set<LlVec2D> next_wide_locations(
			const FactoryMap &factory_map, std::set<LlVec2D> current_locations, const LlVec2D &move
	) {
		std::set<LlVec2D> next_locs{};
		if (move.y == 0) {
			std::ranges::transform(
					current_locations,
					std::inserter(next_locs, next_locs.end()),
					[move](auto vec) { return vec + move; }
			);
			return next_locs;
		}

		for (auto vec: current_locations) {
			auto char_at_current_loc = factory_map.at(vec);
			if (char_at_current_loc == '.') {
				continue;
			}

			auto next_loc = vec + move;
			auto char_at_next_loc = factory_map.at(next_loc);
			if (char_at_next_loc == '#') {

				next_locs.insert(next_loc);
			} else if (char_at_next_loc == '[') {

				LlVec2D other_block_side = next_loc + LlVec2D{1, 0};
				next_locs.insert(next_loc);
				next_locs.insert(other_block_side);
			} else if (char_at_next_loc == ']') {

				LlVec2D other_block_side = next_loc + LlVec2D{-1, 0};
				next_locs.insert(next_loc);
				next_locs.insert(other_block_side);
			} else if (char_at_next_loc == '.') {
				next_locs.insert(next_loc);
			}
		}
		return next_locs;
	}

	void process_wide_single_move(FactoryMap &factory_map, const LlVec2D &move) {
		std::vector<std::set<LlVec2D>> blocks_to_move{};
		auto robot_loc_set = factory_map.find('@');
		std::set<LlVec2D> robot_loc{static_cast<LlVec2D>((*robot_loc_set.begin()).vector())};
		blocks_to_move.push_back(robot_loc);

		while (true) {
			auto next_locs = next_wide_locations(
					factory_map, blocks_to_move.back(), move
			);

			std::set<char> items_in_locations{};

			for (auto loc: next_locs) {
				items_in_locations.insert(factory_map.at(loc));
			}
			bool all_spaces = std::ranges::all_of(
					items_in_locations,
					[](auto i) { return i == '.'; }
			);

			if (items_in_locations.contains('#')) {
				// No movement allowed so leave without changes
				break;
			} else if (all_spaces) {
				blocks_to_move.push_back(next_locs);
				// Move all into next space
				std::ranges::reverse(blocks_to_move);
				for (auto i{0}; i < blocks_to_move.size(); i++) {
					if (i == (blocks_to_move.size() - 1)){
						for (auto vec: blocks_to_move.at(i)){
							factory_map.at(vec) = '.';
						}
					} else {
						for (auto vec: blocks_to_move.at(i)){
							auto prev_vec = vec - move;
							if(blocks_to_move.at(i+1).contains(prev_vec)){
								factory_map.at(vec) = factory_map.at(prev_vec);
							} else {
								factory_map.at(vec) = '.';
							}
						}
					}
				}
				break;
			} else {
				// Add item to list of things to move
				blocks_to_move.push_back(next_locs);
			}
		}
	}

	FactoryMap process_wide_moves(FactoryMap &factory_map, const RobotMoves &robot_moves) {

		for (const auto &char_move: robot_moves) {
			auto move = FACTORY_MOVES[char_move];
			process_wide_single_move(factory_map, move);
//			std::cout << "Map after move: " << move << std::endl;
//			std::cout << factory_map << std::endl << std::endl;
		}
		return factory_map;
	}

	long long score_factory_map(FactoryMap factory_map) {
		long long running_score{0};
		for (auto node: factory_map.node_iter()) {
			if (node.value == 'O' or node.value == '[') {
				long long score = (100 * static_cast<long long>(node.y)) + static_cast<long long>(node.x);
				running_score += score;
			}
		}
		return running_score;
	}

	long long Day15Solution::solve_part_a(const utils::InputReader &input_reader) {
		auto factory_map = get_factory_map(input_reader);
		auto robot_directions = get_robot_directions(input_reader);
		std::cout << "Factory map: \n" << factory_map << std::endl;
		std::cout << "Robot directions: \n" << robot_directions << std::endl;

		auto changed_factory_map = factory_map;
		process_moves(changed_factory_map, robot_directions);
		std::cout << "Changed factory map: \n" << changed_factory_map << std::endl;
		auto final_score = score_factory_map(changed_factory_map);
		return final_score;
	}

	long long Day15Solution::solve_part_b(const utils::InputReader &input_reader) {
		auto factory_map = get_wide_factory_map(input_reader);
		auto robot_directions = get_robot_directions(input_reader);
		std::cout << "Factory map: \n" << factory_map << std::endl;
		std::cout << "Robot directions: \n" << robot_directions << std::endl;

		auto changed_factory_map = factory_map;
		process_wide_moves(changed_factory_map, robot_directions);
		std::cout << "Changed factory map: \n" << changed_factory_map << std::endl;
		auto final_score = score_factory_map(changed_factory_map);
		return final_score;
	}

}