#include "day_12.h"

namespace solutions {

	typedef utils::Array2D<char> GardenMap;
	typedef std::set<utils::Vec2D<size_t>> SetVec2D;
	typedef std::pair<char, SetVec2D> GardenPlot;

	SetVec2D adjacent_with_char_value(utils::Vec2D<size_t> loc, GardenMap garden_map, bool include_diagonals = false) {
		auto location_char = garden_map.at(loc);
		auto adj_locations = garden_map.adjacent(loc, include_diagonals);
		SetVec2D next_locations{};

		for (auto node: adj_locations) {
			if (node.value() == location_char) {
				next_locations.insert(node.vector());
			}
		}

		return next_locations;
	}

	SetVec2D percolate_from_location(utils::Vec2D<size_t> start_location, GardenMap garden_map) {
		auto location_char = garden_map.at(start_location);
		SetVec2D percolated_locations{start_location};
		auto rolling_locations = adjacent_with_char_value(start_location, garden_map);

		while (!rolling_locations.empty()) {
			std::cout << "Adding locations for char:  " << location_char
			          << " locations: " << rolling_locations << std::endl;
			percolated_locations.insert(rolling_locations.begin(), rolling_locations.end());

			SetVec2D next_locations{};
			for (auto loc: rolling_locations) {
				auto adjacent_and_same = adjacent_with_char_value(loc, garden_map);
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

	std::vector<GardenPlot> get_garden_plots(GardenMap garden_map) {
		std::vector<GardenPlot> all_plots{};
		SetVec2D visited_locations{};

		SetVec2D current_plot{};
		for (auto node_wrapper: garden_map.node_iter()) {

			if (visited_locations.contains(node_wrapper.vector())) {
				// If we have already visited the location carry on.
				continue;
			}
			auto current_char = node_wrapper.value();
			auto plot_locations = percolate_from_location(node_wrapper.vector(), garden_map);
			all_plots.emplace_back(current_char, plot_locations);

			for (auto vec: plot_locations) {
				visited_locations.insert(vec);
			}
		}
		return all_plots;
	}

	long long score_single_garden_plot(GardenPlot the_plot, GardenMap the_garden) {
		long long area_count{0};
		long long border_count{0};

		for (auto loc: the_plot.second) {
			auto adjacent_locs = the_garden.adjacent(loc);
			auto matching_locs = std::count_if(
					adjacent_locs.begin(),
					adjacent_locs.end(),
					[the_plot](auto i) { return the_plot.second.contains(i.vector()); }
			);
			area_count++;

			if (matching_locs == 0) {
				border_count += 4;
			} else if (matching_locs == 1) {
				border_count += 3;
			} else if (matching_locs == 2) {
				border_count += 2;
			} else if (matching_locs == 3) {
				border_count += 1;
			} else if (matching_locs == 4) {
				border_count += 0;
			} else {
				throw std::runtime_error("Incorrect calculation of borders.");
			}
		}

		std::cout << "Area size for plot char: " << the_plot.first << " is: " << area_count << std::endl;
		std::cout << "Border size for plot char: " << the_plot.first << " is: " << border_count << std::endl;
		return area_count * border_count;
	}

	long long score_single_garden_using_edges(GardenPlot the_plot, GardenMap the_garden) {
		long long area_count{0};
		SetVec2D edges{};
		SetVec2D bonus_edge{};
		GardenMap edge_map(the_garden.get_size_x() + 1, the_garden.get_size_y() + 1, 'O');
		for (auto loc: the_plot.second) {
			auto adjacent_locs_with_diags = adjacent_with_char_value(loc, the_garden, true);

			std::set<utils::Vec2D<long long>> signed_adjacent_locs{};
			for (auto i: adjacent_locs_with_diags) {
				if (the_plot.second.contains(i)) {
					signed_adjacent_locs.insert(static_cast<utils::Vec2D<long long>>(i));
				}
			}

			area_count++;
			auto top_left_edge = loc;
			auto top_right_edge = loc + utils::Vec2D<size_t>(1, 0);
			auto bottom_left_edge = loc + utils::Vec2D<size_t>(0, 1);
			auto bottom_right_edge = loc + utils::Vec2D<size_t>(1, 1);

			auto top_vec = static_cast<utils::Vec2D<long long>>(loc) + utils::Vec2D<long long>(0, -1);
			auto bottom_vec = static_cast<utils::Vec2D<long long>>(loc) + utils::Vec2D<long long>(0, 1);
			auto left_vec = static_cast<utils::Vec2D<long long>>(loc) + utils::Vec2D<long long>(-1, 0);
			auto right_vec = static_cast<utils::Vec2D<long long>>(loc) + utils::Vec2D<long long>(1, 0);

			auto top_left_vec = static_cast<utils::Vec2D<long long>>(loc) + utils::Vec2D<long long>(-1, -1);
			auto bottom_left_vec = static_cast<utils::Vec2D<long long>>(loc) + utils::Vec2D<long long>(-1, 1);
			auto top_right_vec = static_cast<utils::Vec2D<long long>>(loc) + utils::Vec2D<long long>(1, -1);
			auto bottom_right_vec = static_cast<utils::Vec2D<long long>>(loc) + utils::Vec2D<long long>(1, 1);

			bool top_left_edge_standard_edge =
					(!signed_adjacent_locs.contains(top_vec)) and (!signed_adjacent_locs.contains(left_vec));
			bool top_left_edge_inverted_edge =
					(signed_adjacent_locs.contains(top_vec)) and (signed_adjacent_locs.contains(left_vec)) and
					(!signed_adjacent_locs.contains(top_left_vec));

			bool bottom_left_edge_standard_edge =
					(!signed_adjacent_locs.contains(bottom_vec)) and (!signed_adjacent_locs.contains(left_vec));
			bool bottom_left_edge_inverted_edge =
					(signed_adjacent_locs.contains(bottom_vec)) and (signed_adjacent_locs.contains(left_vec)) and
					(!signed_adjacent_locs.contains(bottom_left_vec));

			bool top_right_edge_standard_edge =
					(!signed_adjacent_locs.contains(top_vec)) and (!signed_adjacent_locs.contains(right_vec));
			bool top_right_edge_inverted_edge =
					(signed_adjacent_locs.contains(top_vec)) and (signed_adjacent_locs.contains(right_vec)) and
					(!signed_adjacent_locs.contains(top_right_vec));

			bool bottom_right_edge_standard_edge =
					(!signed_adjacent_locs.contains(bottom_vec)) and (!signed_adjacent_locs.contains(right_vec));
			bool bottom_right_edge_inverted_edge =
					(signed_adjacent_locs.contains(bottom_vec)) and (signed_adjacent_locs.contains(right_vec)) and
					(!signed_adjacent_locs.contains(bottom_right_vec));
			// Note inverted edges
			if (top_left_edge_inverted_edge) {
				edges.insert(top_left_edge);
			}
			if (bottom_left_edge_inverted_edge) {
				edges.insert(bottom_left_edge);
			}
			if (top_right_edge_inverted_edge) {
				edges.insert(top_right_edge);
			}
			if (bottom_right_edge_inverted_edge) {
				edges.insert(bottom_right_edge);
			}

			// Note normal and bonus edges
			if (top_left_edge_standard_edge) {
				edges.insert(top_left_edge);
				if (signed_adjacent_locs.contains(top_left_vec)) {
					bonus_edge.insert(top_left_edge);
				}
			}
			if (bottom_left_edge_standard_edge) {
				edges.insert(bottom_left_edge);
				if (signed_adjacent_locs.contains(bottom_left_vec)) {
					bonus_edge.insert(bottom_left_edge);
				}
			}
			if (top_right_edge_standard_edge) {
				edges.insert(top_right_edge);
				if (signed_adjacent_locs.contains(top_right_vec)) {
					bonus_edge.insert(top_right_edge);
				}
			}
			if (bottom_right_edge_standard_edge) {
				edges.insert(bottom_right_edge);
				if (signed_adjacent_locs.contains(bottom_right_vec)) {
					bonus_edge.insert(bottom_right_edge);
				}
			}

		}

		std::cout << "Area size for plot char: " << the_plot.first << " is: "
		          << area_count << std::endl;
		std::cout << "Number of edges for plot char: " << the_plot.first << " is: "
		          << edges.size() << std::endl;
		std::cout << "With additional bonus edges of: " << bonus_edge << std::endl;

		for (auto i: edges) {
			edge_map.at(i) = 'X';
		}
		for (auto i: bonus_edge) {
			edge_map.at(i) = '#';
		}

		std::cout << "Edge map looks like: \n" << edge_map;
		return area_count * (edges.size() + bonus_edge.size());
	}

	long long
	score_all_garden_plots(std::vector<GardenPlot> garden_plots, GardenMap the_garden, bool use_edges = false) {
		std::cout << "Scoring garden plots!" << std::endl;
		long long total_score{0};
		for (auto garden_plot: garden_plots) {
			long long score;
			if (use_edges) {
				score = score_single_garden_using_edges(garden_plot, the_garden);
			} else {
				score = score_single_garden_plot(garden_plot, the_garden);
			}
			std::cout << "Score for plot with letter: " << garden_plot.first
			          << " was: " << score << "\n" << std::endl;
			total_score += score;
		}
		return total_score;
	}

	long long Day12Solution::solve_part_a(const utils::InputReader &input_reader) {
		GardenMap garden_map(input_reader.string_vector());
		std::cout << "Garden map: \n" << garden_map << std::endl;

		auto garden_plots = get_garden_plots(garden_map);

		for (auto plot: garden_plots) {
			std::cout << "Garden plot including: " << plot << std::endl;
		}
		auto score = score_all_garden_plots(garden_plots, garden_map, false);
		return score;
	}

	long long Day12Solution::solve_part_b(const utils::InputReader &input_reader) {
		GardenMap garden_map(input_reader.string_vector());
		std::cout << "Garden map: \n" << garden_map << std::endl;

		auto garden_plots = get_garden_plots(garden_map);

		for (auto plot: garden_plots) {
			std::cout << "Garden plot including: " << plot << std::endl;
		}
		auto score = score_all_garden_plots(garden_plots, garden_map, true);
		return score;
	}

}