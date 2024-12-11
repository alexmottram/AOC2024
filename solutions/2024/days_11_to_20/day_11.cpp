#include "day_11.h"

namespace solutions {

	void single_blink_at_stones(std::vector<long long> &stones) {
		for (auto i{0}; i < stones.size(); i++) {
			auto stone_at_i = stones.at(i);
			if (stone_at_i == 0) {
				stones.at(i) = 1;
			} else if (auto stone_str = std::to_string(stone_at_i); stone_str.size() % 2 == 0) {
				auto change_rock = utils::string_to_type<long long>(
						stone_str.substr(0, stone_str.size() / 2)
				);
				auto new_rock = utils::string_to_type<long long>(
						stone_str.substr(stone_str.size() / 2, stone_str.size() / 2)
				);

//				std::cout << "Splitting rock: " << stone_at_i << " at position "
//				          << i << " by changing the first rock to: " << change_rock
//				          << " and adding the second rock: " << new_rock << std::endl;

				stones.at(i) = change_rock;
				stones.insert(stones.begin() + i, new_rock);
				i++;

			} else {
				stones.at(i) *= 2024;
			}
		}
	}

	std::vector<long long> single_blink_at_single_stones(const long long stone) {

		if (stone == 0) {
			return {1};
		} else if (auto stone_str = std::to_string(stone); stone_str.size() % 2 == 0) {
			auto change_rock = utils::string_to_type<long long>(
					stone_str.substr(0, stone_str.size() / 2)
			);
			auto new_rock = utils::string_to_type<long long>(
					stone_str.substr(stone_str.size() / 2, stone_str.size() / 2)
			);
			return {change_rock, new_rock};

		} else {
			auto multiplied_stone = stone * 2024;
			return {multiplied_stone};
		}

	}

	std::vector<long long> multiple_blink_at_stones(std::vector<long long> orig_stones, size_t num_blinks) {
		auto stones = orig_stones;
		for (auto blink_num{1}; blink_num <= num_blinks; blink_num++) {
			std::cout << "Processing blink number: " << blink_num << std::endl;
			single_blink_at_stones(stones);
			std::map<long long, size_t> map_of_stones{};

			for (auto val: stones) {
				if (map_of_stones.contains(val)) {
					map_of_stones[val]++;
				} else {
					map_of_stones[val] = 1;
				}
			}
			std::cout << "Stones after blink " << blink_num << " : " << map_of_stones << std::endl;
		}
		return stones;
	}

	long long calculate_blinks_using_map_count(
			std::vector<long long> first_stones, size_t num_blinks
	) {
		std::map<long long, size_t> counting_map{};

		for (auto stone: first_stones) {
			counting_map[stone] = 1;
		}

		for (auto blink_num{1}; blink_num <= num_blinks; blink_num++) {
			std::cout << "Processing blink number: " << blink_num << std::endl;

			std::map<long long, size_t> next_counting_map{};
			for (auto [key, count]: counting_map) {
				auto val_set = single_blink_at_single_stones(key);
				for (auto val: val_set) {
					if (next_counting_map.contains(val)) {
						auto old_value = next_counting_map[val];
						next_counting_map[val] = count + old_value;
					} else {
						next_counting_map[val] = count;
					}
				}

			}
			counting_map = next_counting_map;

			std::cout << "Stones after blink " << blink_num << " : " << counting_map << std::endl;
		}

		std::cout << "Length of counting map at end is: " << counting_map.size() << std::endl;

		long long total_score{0};
		for (auto [key, count]: counting_map) {
			total_score += count;
		}

		return total_score;
	}

	long long Day11Solution::solve_part_a(const utils::InputReader &input_reader) {
		std::vector<long long> stones = utils::string_to_vector_type<long long>(
				input_reader.string_vector()[0], " "
		);
		std::cout << "Original stones: " << stones << std::endl;
		auto blinked_stones_count = calculate_blinks_using_map_count(stones, 25);

		return blinked_stones_count;
	}

	long long Day11Solution::solve_part_b(const utils::InputReader &input_reader) {
		std::vector<long long> stones = utils::string_to_vector_type<long long>(
				input_reader.string_vector()[0], " "
		);
		std::cout << "Original stones: " << stones << std::endl;
		auto blinked_stones = calculate_blinks_using_map_count(
				stones, 75
		);
		return blinked_stones;
	}

}