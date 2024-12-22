#include "day_22.h"

namespace solutions {
	size_t MODULO_VALUE = 16777216;

	std::vector<size_t> get_buyers_starting_secrets(const utils::InputReader &input_reader) {
		std::vector<size_t> secrets{};
		auto vec_input_str = input_reader.string_vector();
		for (auto line: vec_input_str) {
			secrets.push_back(utils::string_to_type<long long>(line));
		}
		return secrets;
	}

	size_t process_secret(const size_t &secret_in, size_t command_number) {
		auto pre_mix_and_prune {0};
		switch (command_number){
			case 1:
				pre_mix_and_prune = secret_in * 64;
				break;
			case 2:
				pre_mix_and_prune = secret_in / 32;
				break;
			case 3:
				pre_mix_and_prune = secret_in * 2048;
				break;
			default:
				throw std::runtime_error("Unknown command_number.");
		}
		auto mixed_stage = pre_mix_and_prune ^ secret_in;
		auto pruned_stage = mixed_stage % MODULO_VALUE;
		return pruned_stage;
	}

	long long Day22Solution::solve_part_a(const utils::InputReader &input_reader) {
		std::vector<size_t> starting_secrets = get_buyers_starting_secrets(input_reader);
		std::vector<size_t> secrets = starting_secrets;
		std::cout << "Starting secrets: " << starting_secrets << std::endl;

		size_t num_iterations{10};
		size_t command {1};

		for (auto i{1}; i <= num_iterations; i++) {
			std::cout << "Processing iteration number: " << i << std::endl;
			for (auto &val: secrets) {
				auto new_val = process_secret(val, command);
				val = new_val;
			}
			std::cout << "Secrets after iteration: " << secrets << std::endl;
			if (command == 3) {
				command =1;
			} else {
				command ++;
			}
		}


		return 0;
	}

	long long Day22Solution::solve_part_b(const utils::InputReader &input_reader) {
		return 0;
	}

}