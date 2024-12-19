#include "day_19.h"

namespace solutions {

	std::vector<std::vector<char>> get_towels_available(const utils::InputReader &input_reader) {
		std::vector<std::vector<char>> towels{};
		for (auto line: input_reader.string_vector()) {
			if (line.empty()) {
				break;
			}
			auto split_by_comma = utils::split_string(line, ",", true);
			for (auto towel_string: split_by_comma) {
				towels.emplace_back(utils::string_to_vector_type<char>(towel_string));
			}
		}
		return towels;
	}

	std::vector<std::vector<char>> get_designs_required(const utils::InputReader &input_reader) {
		std::vector<std::vector<char>> designs{};
		bool process_lines{false};
		for (auto line: input_reader.string_vector()) {
			if (line.empty()) {
				process_lines = true;
				continue;
			}
			if (process_lines) {
				designs.emplace_back(utils::string_to_vector_type<char>(line));
			}
		}
		return designs;
	}

	std::vector<std::vector<char>> iterative_valid_designs(
			const std::vector<char> &design, const std::vector<std::vector<char>> &towels
	) {
		std::vector<std::vector<char>> designs_minus_a_towel{};
		for (auto towel: towels) {
			// std::cout << "Compared: " << design << " to " << towel << std::endl;
			// If the design is shorter than the current towel pass
			if (design.size() < towel.size()) {
				continue;
			}

			// If any char in towel doesn't match the design
			bool match{true};
			for (auto i{0}; i < towel.size(); i++) {
				if (design.at(i) != towel.at(i)) {
					match = false;
				}
			}

			if (match) {
				// Designs match, so lets make a copy of the remaining end of the design
				std::vector<char> shortened_design{design.cbegin() + towel.size(), design.cend()};
				if (shortened_design.empty()) {
					// If the length is zero, then we have succeeded
					std::cout << "Found a solution." << std::endl;
				}

				// std::cout << "Adding back new shortened design: " << shortened_design << std::endl;
				designs_minus_a_towel.push_back(shortened_design);
			}

		}
		return designs_minus_a_towel;
	}

	std::map<std::vector<char>, std::set<std::vector<char>>> create_process_map(
			const std::vector<char> &design, const std::vector<std::vector<char>> &towels
	) {
		long long combinations{0};
		std::set<std::vector<char>> current_reducing_design{design};
		std::map<std::vector<char>, std::set<std::vector<char>>> processing_map{};
		std::cout << "Processing design: " << design << std::endl;
		while (!current_reducing_design.empty()) {

			std::set<std::vector<char>> next_reducing_design{};
			for (auto reducing_design: current_reducing_design) {
				auto next_designs = iterative_valid_designs(reducing_design, towels);
				for (auto next_design: next_designs) {
					// For every design, add it to the map by adding the previous score
					next_reducing_design.insert(next_design);
					if (!processing_map.contains(reducing_design)) {
						processing_map[reducing_design] = {next_design};
					} else {
						processing_map[reducing_design].insert(next_design);
					}
				}
			}
			current_reducing_design = next_reducing_design;
			std::cout << "Next shortened designs to process: \n" << current_reducing_design << std::endl;
		}

		std::cout << "Created processing map: " << processing_map << std::endl;
		return processing_map;

	}

	long long count_solutions_on_map(
			std::vector<char> design, std::map<std::vector<char>, std::set<std::vector<char>>> processing_map
	) {
		std::vector<char> start_char{};
		std::map<std::vector<char>, std::set<std::vector<char>>> inverted_map{};

		for (auto [key, value]: processing_map) {
			for (auto val: value) {
				if (inverted_map.contains(val)) {
					inverted_map[val].insert(key);
				} else {
					inverted_map[val] = {key};
				}
			}
		}
		std::cout << "Inverted map looks like: \n" << inverted_map << std::endl;

		if (inverted_map.contains(start_char)) {
			std::map<std::vector<char>, long long> route_map{};
			route_map[start_char] = 1;
			std::set<std::vector<char>> rolling_locs = {start_char};
			while (!rolling_locs.empty()) {
				std::set<std::vector<char>> next_locs{};
				auto smallest = std::min_element(
						rolling_locs.begin(),
						rolling_locs.end(),
						[](auto i, auto j){return i.size() < j.size();}
						);

				for (auto curr_loc: rolling_locs) {
					if (curr_loc.size() == (*smallest).size()) {
						auto temp_locs = inverted_map[curr_loc];
						for (auto temp_loc: temp_locs) {
							if (route_map.contains(curr_loc)) {
								route_map[temp_loc] += route_map[curr_loc];
							} else {
								route_map[temp_loc] = route_map[curr_loc];
							}
							next_locs.insert(temp_loc);
						}
					} else {
						next_locs.insert(curr_loc);
					}


				}
				rolling_locs = next_locs;
			}
			auto combo_count = route_map[design];
			std::cout << "Design " << design << " has " << combo_count << " combos." << std::endl;
			return combo_count;
		}
		return 0;
	}

	long long count_valid_designs(
			const std::vector<std::vector<char>> &designs, const std::vector<std::vector<char>> &towels
	) {
		long long valid_count{0};

		for (auto design: designs) {
			auto process_map = create_process_map(design, towels);
			auto num_solutions = count_solutions_on_map(design, process_map);
			if (num_solutions != 0) {
				valid_count++;
			}
		}
		return valid_count;
	}

	long long count_total_valid_combinations(
			const std::vector<std::vector<char>> &designs, const std::vector<std::vector<char>> &towels
	) {
		long long valid_count{0};

		for (auto design: designs) {
			auto process_map = create_process_map(design, towels);
			auto num_solutions = count_solutions_on_map(design, process_map);
			valid_count += num_solutions;
		}

		return valid_count;
	}

	long long Day19Solution::solve_part_a(const utils::InputReader &input_reader) {
		auto towels = get_towels_available(input_reader);
		std::cout << "Towels available: \n" << towels << std::endl;
		auto designs = get_designs_required(input_reader);
		std::cout << "Designs required: \n" << designs << std::endl;
		auto count_of_valid_designs = count_valid_designs(designs, towels);
		std::cout << "Count of valid designs is: " << count_of_valid_designs << std::endl;
		return count_of_valid_designs;
	}

	long long Day19Solution::solve_part_b(const utils::InputReader &input_reader) {
		auto towels = get_towels_available(input_reader);
		std::cout << "Towels available: \n" << towels << std::endl;
		auto designs = get_designs_required(input_reader);
		std::cout << "Designs required: \n" << designs << std::endl;
		auto combo_count = count_total_valid_combinations(designs, towels);
		std::cout << "Count of valid combinations is: " << combo_count << std::endl;
		return combo_count;
	}

}