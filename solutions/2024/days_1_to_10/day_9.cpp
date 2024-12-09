#include "day_9.h"

namespace solutions {

	std::vector<int> create_standard_view_from_blocks(std::vector<std::pair<int, int>> block_memory_vector) {
		std::vector<int> standard_memory_vector{};
		for (auto block: block_memory_vector) {
			std::vector<int> current_block(block.second, block.first);
			std::copy(current_block.begin(), current_block.end(), std::back_inserter(standard_memory_vector));
		}
		return standard_memory_vector;
	}

	std::vector<int> create_memory_vector(const std::string &line) {
		std::vector<int> memory_vector{};
		bool is_space{false};
		int memory_label{0};
		int next_memory_label{0};
		for (const auto character: line) {
			const int character_int = utils::string_to_type<int>(std::string{character});
			if (is_space) {
				memory_label = -1;
				is_space = false;
			} else {
				memory_label = next_memory_label;
				next_memory_label++;
				is_space = true;
			}
			std::vector<int> next_allocation(static_cast<size_t>(character_int), memory_label);
			std::ranges::copy(next_allocation, std::back_inserter(memory_vector));
		}
		std::cout << "Created memory vector: " << memory_vector << std::endl;
		return memory_vector;
	}

	std::vector<int> create_shifted_memory_vector(const std::vector<int> &memory_vector) {
		const auto memory_count = std::ranges::count_if(
				memory_vector,
				[](auto value) { return value != -1; }
		);
		std::cout << "Count of memory values in vector: " << memory_count
		          << " with vector length " << memory_vector.size() << std::endl;

		std::vector<int> no_spaces_vector{};
		std::ranges::copy_if(
				memory_vector,
				std::back_inserter(no_spaces_vector),
				[](auto value) { return value != -1; }
		);

		size_t backwards_idx{no_spaces_vector.size() - 1};

		std::vector<int> shifted_memory_vector{};

		for (auto forward_idx{0}; forward_idx < memory_count; ++forward_idx) {
			if (memory_vector[forward_idx] == -1) {
				shifted_memory_vector.push_back(no_spaces_vector[backwards_idx]);
				backwards_idx--;
			} else {
				shifted_memory_vector.push_back(memory_vector[forward_idx]);
			}
		}
		std::cout << "Shifted memory vector: " << shifted_memory_vector << std::endl;

		return shifted_memory_vector;
	}

	std::vector<std::pair<int, int>> create_block_memory_vector(const std::string &line) {
		std::vector<std::pair<int, int>> memory_vector{};
		bool is_space{false};
		int memory_label{0};
		int next_memory_label{0};
		for (const auto character: line) {
			const int character_int = utils::string_to_type<int>(std::string{character});
			if (is_space) {
				memory_label = -1;
				is_space = false;
			} else {
				memory_label = next_memory_label;
				next_memory_label++;
				is_space = true;
			}
			memory_vector.emplace_back(memory_label, character_int);
		}
		std::cout << "Created block memory vector: " << memory_vector << std::endl;
		return memory_vector;
	}


	std::vector<std::pair<int, int>> create_shifted_block_memory_vector(
			std::vector<std::pair<int, int>> block_memory_vector
	) {
		std::vector<std::pair<int, int>> blocks_to_move{};
		std::copy_if(
				block_memory_vector.begin(),
				block_memory_vector.end(),
				std::back_inserter(blocks_to_move),
				[](auto block) { return block.first != -1; }
		);
		std::ranges::reverse(blocks_to_move);
		std::cout << "Blocks to move: " << blocks_to_move << std::endl;

		for (auto moving_block: blocks_to_move) {
			bool move_the_block{false};
			size_t space_position{0};
			size_t current_block_position{0};
			auto find_it = std::find_if(
					block_memory_vector.begin(),
					block_memory_vector.end(),
					[moving_block](auto curr_block) { return moving_block == curr_block; }
			);
			current_block_position = find_it - block_memory_vector.begin();

			for (auto i{0}; i < current_block_position; i++) {
				auto curr_search_block = block_memory_vector.at(i);
				if (curr_search_block.first == -1) {
					if (curr_search_block.second >= moving_block.second) {
						move_the_block = true;
						space_position = i;
						break;
					}
				}
			}
			if (move_the_block) {
//				std::cout << "Moving block: " << moving_block << "to space position:  " << space_position << std::endl;
				// Remove the original block by replacing it with a gap
				auto remove_it = std::find_if(
						block_memory_vector.begin(),
						block_memory_vector.end(),
						[moving_block](auto curr_block) { return moving_block == curr_block; }
				);
				size_t original_block_pos = remove_it - block_memory_vector.begin();
				// Clean up space around original block
				if (original_block_pos < (block_memory_vector.size() - 1)) {
					int new_gap = moving_block.second;
					int loc_of_gap = original_block_pos;
					if (block_memory_vector.at(original_block_pos + 1).first == -1) {
						new_gap += block_memory_vector.at(original_block_pos + 1).second;
						block_memory_vector.erase(block_memory_vector.begin() + original_block_pos + 1);
					}
					if (block_memory_vector.at(original_block_pos - 1).first == -1) {
						new_gap += block_memory_vector.at(original_block_pos - 1).second;
						block_memory_vector.erase(block_memory_vector.begin() + original_block_pos - 1);
						loc_of_gap--;
					}
					block_memory_vector.at(loc_of_gap) = {-1, new_gap};
				} else {
					block_memory_vector.erase(block_memory_vector.begin() + original_block_pos);
				}

				// Change the space block
				auto curr_space = block_memory_vector.at(space_position);
				auto new_space_size = curr_space.second - moving_block.second;
				if (new_space_size == 0) {
					block_memory_vector.erase(block_memory_vector.begin() + space_position);
				} else {
					std::pair<int, int> new_space{-1, new_space_size};
					block_memory_vector.at(space_position) = new_space;
				}

				// Insert the moving block
				block_memory_vector.insert(block_memory_vector.begin() + space_position, moving_block);
			}
//			std::cout << "After processing block: " << moving_block
//			          << " new vector is: \n" << create_standard_view_from_blocks(block_memory_vector)
//			          << std::endl;

		}
//		std::cout << "Block memory vector after shifting: " << block_memory_vector << std::endl;
		return block_memory_vector;
	}


	long long score_memory_vector(const std::vector<int> &memory_vector) {
		long long score{0};
		for (auto i{0}; i < memory_vector.size(); ++i) {
			auto val = memory_vector.at(i);
			if (val != -1) {
				score += val * i;
			}
		}
		return score;
	}

	long long Day9Solution::solve_part_a(const utils::InputReader &input_reader) {
		const auto memory_vector = create_memory_vector(input_reader.string_vector()[0]);
		auto shifted_memory_vector = create_shifted_memory_vector(memory_vector);
		auto score = score_memory_vector(shifted_memory_vector);
		return score;
	}

	long long Day9Solution::solve_part_b(const utils::InputReader &input_reader) {
		const auto memory_vector = create_block_memory_vector(input_reader.string_vector()[0]);
		auto shifted_memory_vector = create_shifted_block_memory_vector(memory_vector);
		auto shifted_standard_memory_vector = create_standard_view_from_blocks(shifted_memory_vector);
		auto score = score_memory_vector(shifted_standard_memory_vector);
		return score;
	}
}
