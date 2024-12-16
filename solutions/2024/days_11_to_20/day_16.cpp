#include "day_16.h"

namespace solutions {

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

	void show_min_distance_maze(ReindeerMaze maze) {
		CharArray char_maze(maze.get_size_x(), maze.get_size_y(), '.');
		for (auto node: maze.node_iter()) {
			char_maze.at(node.vector()) = node.value.minimum_score();
		}
		std::cout << char_maze << std::endl;
	}

	SetSizeTVec2D get_next_locations(
			const SizeTVec2D &current_location, const ReindeerMaze &maze
	) {
//		auto adjacent_locs = maze.const_adjacent(current_location);
	}

	void populate_maze(ReindeerMaze &maze) {
		SetSizeTVec2D next_locations{};

		while (!next_locations.empty()) {

		}
	}

	long long Day16Solution::solve_part_a(const utils::InputReader &input_reader) {
		auto start_maze = get_reindeer_maze(input_reader);
		std::cout << "Starting maze:" << std::endl;
		show_character_maze(start_maze);
		auto maze = start_maze;
		populate_maze(maze);
		return 0;
	}

	long long Day16Solution::solve_part_b(const utils::InputReader &input_reader) {
		return 0;
	}

}