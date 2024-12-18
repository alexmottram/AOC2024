#include "day_18.h"

namespace solutions {

	std::vector<SizeTVec2D> get_bytes(const utils::InputReader &input_reader) {
		std::vector<SizeTVec2D> bytes{};
		for (auto line: input_reader.string_vector()) {
			auto line_vals = utils::string_to_vector_type<size_t>(line, ",", true);
			bytes.emplace_back(line_vals.at(0), line_vals.at(1));
		}
		return bytes;
	}

	CharArray create_memory_map(const std::vector<SizeTVec2D> &bytes) {
		size_t max_x{0};
		size_t max_y{0};

		for (auto vec: bytes) {
			if (vec.x > max_x) {
				max_x = vec.x;
			}
			if (vec.y > max_y) {
				max_y = vec.y;
			}
		}
		return CharArray(max_x + 1, max_y + 1, '.');
	}

	CharArray create_dropped_memory_map(CharArray memory_map, std::vector<SizeTVec2D> bytes, size_t num_to_drop) {
		if (num_to_drop == 0) {
			return memory_map;
		}
		for (auto i{0}; i < num_to_drop; i++) {
			memory_map.at(bytes.at(i)) = '#';
		}
		return memory_map;
	}

	SetSizeTVec2D
	get_next_valid_adjacent_locations(SizeTVec2D current_loc, CharArray memory_map, SizeTArray count_memory_map) {
		SizeTVec2D start_loc{0, 0};
		SetSizeTVec2D next_locations{};
		for (auto adj_node: memory_map.const_adjacent(current_loc)) {
			bool open_space = memory_map.at(adj_node.vector()) == '.';
			bool unvisited_space = count_memory_map.at(adj_node.vector()) == 0;
			bool not_start = adj_node.vector() != start_loc;
			if (open_space and unvisited_space and not_start) {
				next_locations.insert(adj_node.vector());
			}
		}
		return next_locations;
	}

	size_t solve_memory_map_maze(CharArray memory_map, bool log_solutions=false) {
		SizeTArray count_memory_map{memory_map.get_size_x(), memory_map.get_size_y(), 0};
		SetSizeTVec2D rolling_locations = get_next_valid_adjacent_locations({0, 0}, memory_map, count_memory_map);
		SizeTVec2D end_loc{memory_map.get_size_x() - 1, memory_map.get_size_y() - 1};

		size_t count{0};
		while (count_memory_map.at(end_loc) == 0) {

			if (rolling_locations.empty()) {
				count = 0;
				break;
			}

			count++;
			SetSizeTVec2D next_locations{};

			for (auto loc: rolling_locations) {
				memory_map.at(loc) = 'O';
				count_memory_map.at(loc) = count;
				auto valid_adj_locs = get_next_valid_adjacent_locations(loc, memory_map, count_memory_map);
				next_locations.insert(valid_adj_locs.begin(), valid_adj_locs.end());
			}
			rolling_locations = next_locations;
		}
		if (log_solutions) {
			std::cout << "Char map after finding path: \n" << memory_map << std::endl;
			std::cout << "Count map after finding path: \n" << count_memory_map << std::endl;
		}
		std::cout << "Route length of solution: " << count << std::endl;
		return count;
	}

	long long Day18Solution::solve_part_a(const utils::InputReader &input_reader) {

		auto bytes = get_bytes(input_reader);
		std::cout << "Bytes in: " << bytes << std::endl;
		auto mem_map = create_memory_map(bytes);

		size_t num_drops{1024};
		if (mem_map.get_size_x() < 10) {
			num_drops = 12;
		}

		auto dropped_mem_map = create_dropped_memory_map(mem_map, bytes, num_drops);
		std::cout << "Dropped memory map: \n" << dropped_mem_map << std::endl;
		auto route_length = solve_memory_map_maze(dropped_mem_map, true);
		return route_length;
	}

	long long Day18Solution::solve_part_b(const utils::InputReader &input_reader) {

		auto bytes = get_bytes(input_reader);
		std::cout << "Bytes in: " << bytes << std::endl;
		auto mem_map = create_memory_map(bytes);

		for (auto i{1}; i < bytes.size(); i++) {

			std::cout << "Dropping " << i << " bytes." << std::endl;
			auto dropped_mem_map = create_dropped_memory_map(mem_map, bytes, i);
			auto route_length = solve_memory_map_maze(dropped_mem_map);
			if (route_length == 0) {
				std::cout << "First byte to cause the path to break is: " << bytes.at(i - 1) << std::endl;
				break;
			}
		}
		return 0;
	}

}