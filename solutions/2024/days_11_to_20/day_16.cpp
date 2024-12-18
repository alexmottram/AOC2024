#include "day_16.h"

namespace solutions {

	std::map<char, LlVec2D> REINDEER_DIRECTION_MAP{
			{'^', {0, -1}},
			{'>', {1, 0}},
			{'v', {0, 1}},
			{'<', {-1, 0}},
	};

	ReindeerMaze get_reindeer_maze(const utils::InputReader &input_reader) {
		std::vector<std::vector<MazeLocation>> vector_input;
		for (auto line: input_reader.string_vector()) {
			std::vector<MazeLocation> current_vector_line{};
			for (auto char_val: line) {
				current_vector_line.emplace_back(char_val);
			}
			vector_input.push_back(current_vector_line);
		}
		ReindeerMaze reindeer_maze{vector_input};
		return reindeer_maze;
	}

	void show_character_maze(ReindeerMaze maze) {
		utils::Array2D<char> char_maze(maze.get_size_x(), maze.get_size_y(), '.');
		for (auto node: maze.node_iter()) {
			char_maze.at(node.vector()) = node.value.map_char;
		}
		std::cout << char_maze << std::endl;
	}

	void show_character_maze_with_path(ReindeerMaze maze, std::set<std::pair<char, SizeTVec2D>> path) {
		utils::Array2D<char> char_maze(maze.get_size_x(), maze.get_size_y(), '.');
		for (auto node: maze.node_iter()) {
			char_maze.at(node.vector()) = node.value.map_char;
		}

		for (auto dir_vec: path) {
			char_maze.at(dir_vec.second) = 'O';
		}

		std::cout << char_maze << std::endl;
	}

	void show_min_distance_maze(ReindeerMaze maze) {
		IntArray int_maze(maze.get_size_x(), maze.get_size_y(), '.');
		for (auto node: maze.node_iter()) {

			int_maze.at(node.vector()) = node.value.minimum_score();
		}
		std::cout << int_maze << std::endl;
	}


	ReindeerMaze populate_maze(ReindeerMaze maze) {

		auto start_node = maze.find_unique(MazeLocation{'S'});
		start_node.value.from_above = -1;
		start_node.value.from_below = -1;
		start_node.value.from_left = 0;
		start_node.value.from_right = -1;
		SetSizeTVec2D current_vectors{start_node.vector()};

		while (!current_vectors.empty()) {
			SetSizeTVec2D next_vectors{};

			for (auto current_vec: current_vectors) {
				for (auto [char_val, move]: REINDEER_DIRECTION_MAP) {

					auto new_loc_ll = static_cast<LlVec2D>(current_vec) + move;
					auto new_loc_size_t = static_cast<SizeTVec2D>(new_loc_ll);
					if (maze.at(new_loc_size_t).map_char != '#') {

						auto shortest_distance = maze.at(current_vec).shortest_distance_to_next_destination(char_val);
						auto current_shorted_distance = maze.at(new_loc_size_t).get_value(char_val);

						if ((current_shorted_distance == -1) or (shortest_distance < current_shorted_distance)) {
							maze.at(new_loc_size_t).set_value(char_val, shortest_distance);
							next_vectors.insert(new_loc_size_t);
						}
					}
				}
			}
			current_vectors = next_vectors;
		}
		return maze;
	}

	std::set<std::pair<char, SizeTVec2D>> find_initial_direction_and_location(
			SizeTVec2D end_vector, const ReindeerMaze &maze
	) {
		std::set<std::pair<char, SizeTVec2D>> initial_directions_and_locations{};

		auto end_node = maze.at(end_vector);
		auto lowest_score = end_node.minimum_score();

		if (end_node.get_value('^') == lowest_score) {
			initial_directions_and_locations.insert({'^', end_vector});
		}

		if (end_node.get_value('v') == lowest_score) {
			initial_directions_and_locations.insert({'v', end_vector});
		}

		if (end_node.get_value('<') == lowest_score) {
			initial_directions_and_locations.insert({'<', end_vector});
		}

		if (end_node.get_value('>') == lowest_score) {
			initial_directions_and_locations.insert({'>', end_vector});
		}
		return initial_directions_and_locations;

	}

	std::set<std::pair<char, SizeTVec2D>> next_locations_on_path(
			std::pair<char, SizeTVec2D> direction_and_location, const ReindeerMaze &maze, bool is_start_loc = false
	) {
		std::map<char, std::map<char, long long >> SUPER_MAP{
				{'^', {{'^', 1}, {'<', 1001}, {'>', 1001}}},
				{'v', {{'v', 1}, {'<', 1001}, {'>', 1001}}},
				{'>', {{'>', 1}, {'^', 1001}, {'v', 1001}}},
				{'<', {{'<', 1}, {'^', 1001}, {'v', 1001}}},
		};
		std::set<std::pair<char, SizeTVec2D>> output_dir_loc{};

		auto curr_maze_node = maze.at(direction_and_location.second);
		auto next_loc_ll = static_cast<LlVec2D>(direction_and_location.second) -
		                   REINDEER_DIRECTION_MAP[direction_and_location.first];
		auto next_loc_size_t = static_cast<SizeTVec2D>(next_loc_ll);
		auto next_maze_node = maze.at(next_loc_ll);


		for (auto [new_dir, allowed_diff]: SUPER_MAP[direction_and_location.first]) {
			auto curr_val = curr_maze_node.get_value(direction_and_location.first);
			auto next_val = next_maze_node.get_value(new_dir);
			auto diff = curr_val - next_val;
			if (diff == allowed_diff) {
				output_dir_loc.insert({new_dir, next_loc_size_t});
			}

		}
		return output_dir_loc;
	}


	std::set<std::pair<char, SizeTVec2D>> get_solution_route(const ReindeerMaze &maze) {
		auto end_vector = maze.const_find_unique(MazeLocation{'E'}).vector();
		auto start_vector = maze.const_find_unique(MazeLocation{'S'}).vector();

		auto current_directions_and_locations = find_initial_direction_and_location(end_vector, maze);

		std::cout << "Found the following start location: " << current_directions_and_locations << std::endl;

		std::set<std::pair<char, SizeTVec2D>> all_directions_and_locations{current_directions_and_locations};

		while (!current_directions_and_locations.empty()) {
			std::set<std::pair<char, SizeTVec2D>> next_directions_and_locations{};
			for (auto direction_and_vector: current_directions_and_locations) {
				if (direction_and_vector.second == start_vector){
					continue;
				}
				auto new_locations = next_locations_on_path(direction_and_vector, maze, false);
				std::copy_if(
						new_locations.begin(), new_locations.end(),
						std::inserter(next_directions_and_locations, next_directions_and_locations.begin()),
						[all_directions_and_locations](auto i) {
							return !all_directions_and_locations.contains(i);
						}
				);
			}
			all_directions_and_locations.insert(
					current_directions_and_locations.begin(), current_directions_and_locations.end());

			current_directions_and_locations = next_directions_and_locations;
		}
		return all_directions_and_locations;
	}

	long long Day16Solution::solve_part_a(const utils::InputReader &input_reader) {
		auto start_maze = get_reindeer_maze(input_reader);
		std::cout << "Starting maze:" << std::endl;
		show_character_maze(start_maze);
		auto maze = populate_maze(start_maze);
		show_min_distance_maze(maze);
		auto end_node = maze.find_unique(MazeLocation{'E'});
		auto min_score = end_node.value.minimum_score();
		return min_score;
	}

	long long Day16Solution::solve_part_b(const utils::InputReader &input_reader) {
		auto start_maze = get_reindeer_maze(input_reader);
		std::cout << "Starting maze:" << std::endl;
		show_character_maze(start_maze);
		auto maze = populate_maze(start_maze);
		show_min_distance_maze(maze);
		auto end_node = maze.find_unique(MazeLocation{'E'});
		auto solution_route = get_solution_route(maze);

		show_character_maze_with_path(maze, solution_route);

		SetSizeTVec2D locations_only{};
		for (auto [direction, location]: solution_route) {
			locations_only.insert(location);
		}
		return static_cast<long long>(locations_only.size());
	}

}