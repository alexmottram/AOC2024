#include "day_20.h"

namespace solutions {

	typedef std::pair<SizeTVec2D, SizeTVec2D> CheatPair;

	std::vector<SizeTVec2D> shortest_path(const CharArray &race_map) {
		auto start_vec = race_map.const_find_unique('S');
		auto end_vec = race_map.const_find_unique('E');
		std::vector<SizeTVec2D> path{start_vec.vector()};
		std::set<SizeTVec2D> visited_locations{start_vec.vector()};
		std::set<SizeTVec2D> rolling_locations{start_vec.vector()};

		while (!visited_locations.contains(end_vec.vector())) {
			std::set<SizeTVec2D> next_locations{};

			for (auto vec: rolling_locations) {
				auto adjacent_vecs = race_map.const_adjacent(vec);
				for (auto adj_vec: adjacent_vecs) {
					bool open_space = race_map.at(adj_vec.vector()) != '#';
					bool unvisited = !visited_locations.contains(adj_vec.vector());

					if (open_space and unvisited) {
						next_locations.insert(adj_vec.vector());
						path.push_back(adj_vec.vector());
						visited_locations.insert(adj_vec.vector());
					}
				}
			}
			if (next_locations.size() > 1) {
				throw std::runtime_error("No single pathway found");
			}
			rolling_locations = next_locations;
		}

		return path;
	}


	SizeTArray create_path_array(const CharArray &race_map, const std::vector<SizeTVec2D> &path) {
		SizeTArray size_t_array(race_map.get_size_x(), race_map.get_size_y(), 0);
		for (auto i{0}; i < path.size(); i++) {
			size_t_array.at(path.at(i)) = i;
		}
		return size_t_array;
	}


	std::map<size_t, std::set<CheatPair>> find_cheat_pairs_using_cheat_time(
			const CharArray &race_map, const std::vector<SizeTVec2D> &race_path, size_t cheat_time
	) {
		std::map<size_t, std::set<CheatPair>> cheat_solutions{};
		auto race_path_map = create_path_array(race_map, race_path);
		auto reversed_path = race_path;
		std::ranges::reverse(reversed_path);

		auto main_reverse_iterator = reversed_path.cbegin();
		auto reversed_iterator_end = reversed_path.cend();

		while (main_reverse_iterator != reversed_iterator_end) {
			auto end_loc = *main_reverse_iterator;
			auto end_loc_ll = static_cast<LlVec2D>(end_loc);
			auto end_val = static_cast<long long>(race_path_map.at(end_loc));

//			std::cout << "Find solutions from reversed location: " << end_loc << std::endl;
			auto secondary_iterator = main_reverse_iterator;
			secondary_iterator++;

			while (secondary_iterator != reversed_iterator_end) {
				auto start_loc = *secondary_iterator;
				auto start_loc_ll = static_cast<LlVec2D>(start_loc);
				auto start_val = static_cast<long long>(race_path_map.at(start_loc));

				auto abs_x_dis = std::abs(end_loc_ll.x - start_loc_ll.x);
				auto abs_y_dis = std::abs(end_loc_ll.y - start_loc_ll.y);
				auto abs_dis = abs_x_dis + abs_y_dis;

				auto time_saving = end_val - start_val - abs_dis;

				if (time_saving > 0 and abs_dis <= cheat_time) {
					cheat_solutions[time_saving].insert({start_loc, end_loc});
				}

				secondary_iterator++;
			}
			main_reverse_iterator++;
		}

		return cheat_solutions;
	}


	void print_race_map_with_path(const CharArray &race_map, const std::vector<SizeTVec2D> &path) {
		auto map_copy = race_map;
		for (auto vec: path) {
			map_copy.at(vec) = 'O';
		}
		std::cout << map_copy << std::endl;
	}


	void print_cheat_save_map(const std::map<size_t, std::set<CheatPair>> &cheat_save_map) {
		for (auto [save, cheat_set]: cheat_save_map) {
			std::cout << "There are " << cheat_set.size() << " cheats that save "
			          << save << " picoseconds." << std::endl;
		}
	}


	size_t count_of_cheats_saving_x_or_more_seconds(
			size_t x, const std::map<size_t, std::set<CheatPair>> &cheat_save_map
	) {
		size_t count_of_cheats{0};
		for (auto [save, cheat_set]: cheat_save_map) {
			if (save >= x) {
				count_of_cheats += cheat_set.size();
			}
		}
		return count_of_cheats;
	}


	long long Day20Solution::solve_part_a(const utils::InputReader &input_reader) {
		CharArray race_map{input_reader.string_vector()};
		std::cout << "Map at beginning: \n" << race_map << std::endl;
		auto race_path = shortest_path(race_map);
		print_race_map_with_path(race_map, race_path);
		auto cheat_pairs = find_cheat_pairs_using_cheat_time(race_map, race_path, 2);
		print_cheat_save_map(cheat_pairs);
		auto count = count_of_cheats_saving_x_or_more_seconds(100, cheat_pairs);
		return static_cast<long long >(count);
	}


	long long Day20Solution::solve_part_b(const utils::InputReader &input_reader) {
		CharArray race_map{input_reader.string_vector()};
		std::cout << "Map at beginning: \n" << race_map << std::endl;
		auto race_path = shortest_path(race_map);
		print_race_map_with_path(race_map, race_path);
		auto cheat_pairs = find_cheat_pairs_using_cheat_time(race_map, race_path, 20);
		print_cheat_save_map(cheat_pairs);
		auto count = count_of_cheats_saving_x_or_more_seconds(100, cheat_pairs);
		return static_cast<long long >(count);
	}

}