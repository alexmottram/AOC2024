#include "day_10.h"

namespace solutions {
	typedef utils::ConstNode<size_t, int> trail_node;

	std::set<trail_node> valid_adjacent_locations(
			const trail_node &current_node,
			const utils::Array2D<int>& topographic_map
	) {
		std::set<trail_node> valid_adj_nodes{};
		auto adjacent_locs = topographic_map.const_adjacent(current_node);

		std::copy_if(
				adjacent_locs.begin(),
				adjacent_locs.end(),
				std::inserter(valid_adj_nodes, valid_adj_nodes.begin()),
				[current_node](auto new_node) {
					return (new_node.value == (current_node.value + 1));
				}
		);

		return valid_adj_nodes;
	}

	long long score_single_trailhead(
			trail_node &trailhead,
			utils::Array2D<int> &topographic_map
	) {
		auto start_loc = trailhead;
		auto next_locs = valid_adjacent_locations(start_loc, topographic_map);

		while (!next_locs.empty()) {
			// Check to see if we have hit end locations
			bool all_trail_ends = std::all_of(
					next_locs.begin(),
					next_locs.end(),
					[](auto loc) { return loc.value == 9; }
			);
			if (all_trail_ends) {
				std::cout << "Hit trail end for head: " << trailhead
				          << " with score: " << next_locs.size() << std::endl;
				return next_locs.size();
			}

			// Find next locations
			std::set<trail_node> new_locations{};
			for (auto loc: next_locs) {
				std::set<trail_node> connected_locs = valid_adjacent_locations(loc, topographic_map);
				std::copy(
						connected_locs.begin(),
						connected_locs.end(),
						std::inserter(new_locations, new_locations.end())
				);
			}

			std::cout << "Next locations are: " << new_locations << std::endl;
			next_locs = new_locations;
		}
		return 0;
	}

	long long find_all_trailhead_scores(utils::Array2D<int> &topographic_map) {

		long long score{0};
		std::set<trail_node> trailheads = topographic_map.const_find(0);
		for (auto trailhead: trailheads) {
			std::cout << "Starting hike for trailhead: " << trailhead << std::endl;
			std::cout << "Topographic map looks like: \n" << topographic_map << std::endl;
			score += score_single_trailhead(trailhead, topographic_map);
		}
		return score;
	}

	std::map<trail_node, size_t> rated_valid_adjacent_locations(
			std::pair<const utils::ConstNode<unsigned long long int, int>, unsigned long long int> current_node,
			const utils::Array2D<int> &topographic_map
	) {
		std::map<trail_node, size_t> valid_adj_nodes{};
		auto adjacent_locs = topographic_map.const_adjacent(current_node.first);

		for (auto loc: adjacent_locs) {
			if (loc.value == (current_node.first.value + 1)) {
				valid_adj_nodes[loc] = current_node.second;
			}
		}
		return valid_adj_nodes;
	}

	long long rate_single_trailhead(
			trail_node &trailhead,
			utils::Array2D<int> &topographic_map
	) {
		std::pair<const utils::ConstNode<unsigned long long int, int>, unsigned long long int> start_loc{trailhead, 1};
		auto next_locs = rated_valid_adjacent_locations(start_loc, topographic_map);

		while (!next_locs.empty()) {
			// Check to see if we have hit end locations
			bool all_trail_ends = std::all_of(
					next_locs.begin(),
					next_locs.end(),
					[](auto loc) { return loc.first.value == 9; }
			);
			if (all_trail_ends) {
				long long ratings = std::accumulate(
						next_locs.begin(),
						next_locs.end(),
						0,
						[](auto running_rating, auto i) {
							return running_rating + i.second;
						}
				);
				std::cout << "Hit trail end for head: " << trailhead
				          << " with rating: " << ratings << std::endl;
				return ratings;
			}

			// Find next locations
			std::map<trail_node, size_t> new_locations{};
			for (auto loc: next_locs) {
				auto connected_locs = rated_valid_adjacent_locations(loc, topographic_map);
				for (auto connected_loc: connected_locs) {
					if (new_locations.contains(connected_loc.first)) {
						new_locations[connected_loc.first] += connected_loc.second;
					} else {
						new_locations[connected_loc.first] = connected_loc.second;
					}
				}
			}
			std::cout << "Next locations are: " << new_locations << std::endl;
			next_locs = new_locations;
		}
		return 0;
	}

	long long find_all_trailhead_ratings(utils::Array2D<int> &topographic_map) {

		long long rate{0};
		std::set<trail_node> trailheads = topographic_map.const_find(0);
		for (auto trailhead: trailheads) {
			std::cout << "Starting hike for trailhead: " << trailhead << std::endl;
			std::cout << "Topographic map looks like: \n" << topographic_map << std::endl;
			rate += rate_single_trailhead(trailhead, topographic_map);
		}
		return rate;
	}

	long long Day10Solution::solve_part_a(const utils::InputReader &input_reader) {
		utils::Array2D<int> topographic_map(input_reader.string_vector());
		std::cout << "Topographic map looks like: \n" << topographic_map << std::endl;
		auto score = find_all_trailhead_scores(topographic_map);
		return score;
	}

	long long Day10Solution::solve_part_b(const utils::InputReader &input_reader) {
		utils::Array2D<int> topographic_map(input_reader.string_vector());
		std::cout << "Topographic map looks like: \n" << topographic_map << std::endl;
		auto rating = find_all_trailhead_ratings(topographic_map);
		return rating;
	}

}