#include "day_14.h"

namespace solutions {

	ToiletRobot::ToiletRobot(std::string str_vec) {
		auto equal_split = utils::split_string(str_vec, " ");
		auto position_strs = utils::string_to_vector_type<long long>(
				utils::split_string(equal_split.at(0), "=").at(1), ","
		);
		auto velocity_strs = utils::string_to_vector_type<long long>(
				utils::split_string(equal_split.at(1), "=").at(1), ","
		);
		start = {position_strs.at(0), position_strs.at(1)};
		position = {position_strs.at(0), position_strs.at(1)};
		velocity = {velocity_strs.at(0), velocity_strs.at(1)};
	}

	utils::Vec2D<long long> ToiletRobot::move(long long moves, const ToiletMap &toilets) {
		auto max_x = static_cast<long long>(toilets.get_size_x());
		auto max_y = static_cast<long long>(toilets.get_size_y());
		position.x = (position.x + (moves * velocity.x)) % max_x;
		position.y = (position.y + (moves * velocity.y)) % max_y;
		if (position.x < 0) { position.x += max_x; }
		if (position.y < 0) { position.y += max_y; }
		return position;
	}

	long long score_toilet_map(ToiletMap toilet_map) {
		long long top_left_score{0};
		long long top_right_score{0};
		long long bottom_left_score{0};
		long long bottom_right_score{0};

		auto x_middle = toilet_map.get_size_x() / 2;
		auto y_middle = toilet_map.get_size_y() / 2;

		for (auto node: toilet_map.node_iter()) {
			if (node.x < x_middle and node.y < y_middle) {
				top_left_score += node.value;
			}
			if (node.x > x_middle and node.y < y_middle) {
				top_right_score += node.value;
			}
			if (node.x < x_middle and node.y > y_middle) {
				bottom_left_score += node.value;
			}
			if (node.x > x_middle and node.y > y_middle) {
				bottom_right_score += node.value;
			}
		}

		auto total_score = top_left_score * top_right_score * bottom_left_score * bottom_right_score;

		return total_score;
	}

	SetVec2D xmas_adjacent_with_char_value(utils::Vec2D<size_t> loc, ToiletCharMap toilet_map, bool include_diagonals = false) {
		auto location_char = toilet_map.at(loc);
		auto adj_locations = toilet_map.adjacent(loc, include_diagonals);
		SetVec2D next_locations{};

		for (auto node: adj_locations) {
			if (node.value == location_char) {
				next_locations.insert(node.vector());
			}
		}
		return next_locations;
	}

	SetVec2D xmas_percolate_from_location(utils::Vec2D<size_t> start_location, ToiletCharMap toilet_map) {
		auto location_char = toilet_map.at(start_location);
		SetVec2D percolated_locations{start_location};
		auto rolling_locations = xmas_adjacent_with_char_value(start_location, toilet_map);

		while (!rolling_locations.empty()) {
			percolated_locations.insert(rolling_locations.begin(), rolling_locations.end());

			SetVec2D next_locations{};
			for (auto loc: rolling_locations) {
				auto adjacent_and_same = xmas_adjacent_with_char_value(loc, toilet_map);
				std::copy_if(
						adjacent_and_same.begin(),
						adjacent_and_same.end(),
						std::inserter(next_locations, next_locations.end()),
						[percolated_locations](auto i) { return !percolated_locations.contains(i); }
				);
			}
			rolling_locations = next_locations;
		}

		return percolated_locations;
	}


	long long xmas_tree_score(ToiletCharMap toilet_map) {
		size_t xmas_tree_score{0};
		SetVec2D visited_set{};

		for (auto node: toilet_map.node_iter()) {
			if (!visited_set.contains(node.vector()) and node.value=='#') {
				auto set_of_nodes = xmas_percolate_from_location(node.vector(), toilet_map);
				visited_set.insert(set_of_nodes.begin(), set_of_nodes.end());
				xmas_tree_score = std::max(set_of_nodes.size(), xmas_tree_score);
			}
		}

		return xmas_tree_score;
	}

	long long Day14Solution::solve_part_a(const utils::InputReader &input_reader) {
		long long num_moves{100};
		std::vector<ToiletRobot> robots{};

		for (auto line: input_reader.string_vector()) {
			robots.emplace_back(line);
		}

		std::cout << "Printing out robots at start: \n" << robots << std::endl;

		auto robot_at_max_x = std::max_element(
				robots.begin(),
				robots.end(),
				[](auto i, auto j) {
					return i.start.x < j.start.x;
				}
		);

		auto robot_at_max_y = std::max_element(
				robots.begin(),
				robots.end(),
				[](auto i, auto j) {
					return i.start.y < j.start.y;
				}
		);

		auto x_len = robot_at_max_x->start.x + 1;
		auto y_len = robot_at_max_y->start.y + 1;
		std::cout << "X length: " << x_len << " and y length: " << y_len << std::endl;

		ToiletMap toilet_map(x_len, y_len, 0);

		for (auto robot: robots) {
			auto vec = robot.move(num_moves, toilet_map);
			std::cout << "Robot after move: " << robot << std::endl;
			toilet_map.at(static_cast<utils::Vec2D<size_t>>(vec))++;
		}

		std::cout << "Robot map after movement: \n" << toilet_map << std::endl;
		auto total_score = score_toilet_map(toilet_map);
		return total_score;
	}

	long long Day14Solution::solve_part_b(const utils::InputReader &input_reader) {
		long long num_moves{70505};
		std::vector<ToiletRobot> robots{};

		for (const auto &line: input_reader.string_vector()) {
			robots.emplace_back(line);
		}

		std::cout << "Printing out robots at start: \n" << robots << std::endl;

		auto robot_at_max_x = std::max_element(
				robots.begin(),
				robots.end(),
				[](auto i, auto j) {
					return i.start.x < j.start.x;
				}
		);

		auto robot_at_max_y = std::max_element(
				robots.begin(),
				robots.end(),
				[](auto i, auto j) {
					return i.start.y < j.start.y;
				}
		);

		auto x_len = robot_at_max_x->start.x + 1;
		auto y_len = robot_at_max_y->start.y + 1;
		std::cout << "X length: " << x_len << " and Y length: " << y_len << std::endl;

		ToiletMap toilet_map_orig(x_len, y_len, 0);

		for (auto i{1}; i <= num_moves; i++) {

			ToiletCharMap toilet_map(x_len, y_len, ' ');
			for (auto &robot: robots) {
				auto vec = robot.move(1, toilet_map_orig);
				toilet_map.at(static_cast<utils::Vec2D<size_t>>(vec)) = '#';
			}

			auto total_score = xmas_tree_score(toilet_map);
			if (total_score > 10) {
				std::cout << "Score for move: " << i << " is: " << total_score << std::endl;
				std::cout << "Robot map after movement " << i << ": \n" << toilet_map << std::endl;
			}
		}
		return num_moves;
	}

}