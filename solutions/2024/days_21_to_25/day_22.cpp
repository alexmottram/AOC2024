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

	size_t process_secret(const size_t &secret_in) {
		auto multiplied = secret_in * 64;
		auto mixed_stage_1 = multiplied ^ secret_in;
		auto pruned_stage_1 = mixed_stage_1 % MODULO_VALUE;

		auto divided = secret_in / 32;
		auto mixed_stage_2 = divided ^ secret_in;
		auto pruned_stage_2 = mixed_stage_2 % MODULO_VALUE;

		auto multiplied_again = secret_in * 2048;
		auto mixed_stage_3 = multiplied_again ^ secret_in;
		auto pruned_stage_3 = mixed_stage_1 % MODULO_VALUE;
		return pruned_stage_3;
	}

	long long Day22Solution::solve_part_a(const utils::InputReader &input_reader) {
		std::vector<size_t> starting_secrets = get_buyers_starting_secrets(input_reader);
		std::vector<size_t> secrets = starting_secrets;
		std::cout << "Starting secrets: " << starting_secrets << std::endl;

		size_t num_iterations{2000};

		for (auto i{1}; i <= num_iterations; i++) {
			std::cout << "Processing iteration number: " << i << std::endl;
			for (auto &val: secrets) {
				auto new_val = process_secret(val);
				val = new_val;
			}
			std::cout << "Secrets after iteration: " << secrets << std::endl;
		}


		return 0;
	}

	long long Day22Solution::solve_part_b(const utils::InputReader &input_reader) {
		return 0;
	}

}