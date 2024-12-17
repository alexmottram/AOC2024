#pragma once

#include "../../../utils/utils.h"

namespace solutions {
	class Day17Solution final : public utils::SolutionTemplate<long long> {
	public:
		Day17Solution() : SolutionTemplate(
				2024,
				17,
				3310,
				713412671,
				117440,
				109019476330651
		) {}

		long long solve_part_a(const utils::InputReader &input_reader) override;

		long long solve_part_b(const utils::InputReader &input_reader) override;
	};

	struct ThreeBitComputer {

		typedef size_t RegType;
		typedef std::list<RegType> InstructionList;
		typedef InstructionList::iterator InstructionIterator;

		InstructionList instructions{};
		InstructionList output{};
		RegType reg_A{};
		RegType reg_B{};
		RegType reg_C{};
		RegType temp_mem{};
		bool log{false};

		ThreeBitComputer(std::vector<std::string> string_vec) {
			auto a_text = string_vec.at(0);
			auto b_text = string_vec.at(1);
			auto c_text = string_vec.at(2);
			auto program_text = string_vec.at(4);

			auto reg_A_str = utils::split_string(a_text, ":", true).at(1);
			auto reg_B_str = utils::split_string(b_text, ":", true).at(1);
			auto reg_C_str = utils::split_string(c_text, ":", true).at(1);
			auto program_str = utils::split_string(program_text, ":", true).at(1);

			reg_A = utils::string_to_type<RegType>(reg_A_str);
			reg_B = utils::string_to_type<RegType>(reg_B_str);
			reg_C = utils::string_to_type<RegType>(reg_C_str);
			temp_mem = 0;

			auto program_vec = utils::string_to_vector_type<RegType>(program_str, ",");
			for (const auto &val: program_vec) {
				instructions.push_back(val);
			}
		}

		friend std::ostream &operator<<(std::ostream &os, const ThreeBitComputer &tbc) {
			os << "ThreeBitComputer(regA=" << tbc.reg_A
			   << ", regB=" << tbc.reg_B
			   << ", regC=" << tbc.reg_C
			   << ", instructions=" << tbc.instructions
			   << ", output=" << tbc.output
			   << ")";
			return os;
		}

		RegType &combo_operand(RegType x) {
			if ((x >= 0) and (x < 4)) {
				temp_mem = x;
				return temp_mem;
			} else if (x == 4) {
				return reg_A;
			} else if (x == 5) {
				return reg_B;
			} else if (x == 6) {
				return reg_C;
			} else {
				throw std::runtime_error("Invalid combo oeprand.");
			}
		}

		void run_code();

		RegType process_instruction(InstructionIterator &opcode, RegType operand);

		bool instructions_and_output_match() const {
			if (instructions.size() == output.size()) {
				auto i_it = instructions.cbegin();
				auto o_it = output.cbegin();
				while (i_it != instructions.cend() or o_it != output.cend()) {
					if ((*i_it) != (*o_it)) {
						return false;
					}
					i_it++;
					o_it++;
				}
				return true;
			}
			return false;
		}

		bool last_output_digits_match() const {
			if (instructions.size() >= output.size()) {
				auto reverse_instructions = instructions;
				auto reverse_output = output;
				std::ranges::reverse(reverse_instructions);
				std::ranges::reverse(reverse_output);
				auto i_it = reverse_instructions.cbegin();
				auto o_it = reverse_output.cbegin();
				while (o_it != reverse_output.cend()) {
					if ((*i_it) != (*o_it)) {
						return false;
					}
					i_it++;
					o_it++;
				}
				return true;
			}
			return false;
		}

		void instruction_adv(RegType operand) {
			RegType denom{1};
			for (auto i{0}; i < combo_operand(operand); i++) {
				denom *= 2;
			}
			auto division = reg_A / denom;
			if (log) {
				std::cout << "Division of " << reg_A << "/" << denom << "=" << division << std::endl;
			}
			reg_A = division;
		}

		void instruction_bdv(RegType operand) {
			RegType denom{1};
			for (auto i{0}; i < combo_operand(operand); i++) {
				denom *= 2;
			}
			auto division = reg_A / denom;
			if (log) {
				std::cout << "Division of " << reg_A << "/" << denom << "=" << division << std::endl;
			}
			reg_B = division;
		}

		void instruction_cdv(RegType operand) {
			RegType denom{1};
			for (auto i{0}; i < combo_operand(operand); i++) {
				denom *= 2;
			}
			auto division = reg_A / denom;
			if (log) {
				std::cout << "Division of " << reg_A << "/" << denom << "=" << division << std::endl;
			}
			reg_C = division;
		}


		void instruction_bxl(RegType operand) {
			auto bitwise_xor = operand ^ reg_B;
			if (log) {
				std::cout << "Bitwise XOR of " << operand << "^" << reg_B << "=" << bitwise_xor << std::endl;
			}
			reg_B = bitwise_xor;
		}

		void instruction_bst(RegType operand) {
			auto modulo_8 = combo_operand(operand) % 8;
			if (log) {
				std::cout << "Modulo " << combo_operand(operand) << "%" << 8 << "=" << modulo_8
				          << std::endl;
			}
			reg_B = modulo_8;
		}

		void instruction_jnz(InstructionIterator &main_iterator, RegType operand) {
			if (reg_A != 0) {
				auto new_main_iterator = instructions.begin();
				for (auto i{0}; i < operand; i++) {
					new_main_iterator++;
				}
				auto original_pos = std::distance(main_iterator, instructions.begin());
				auto new_pos = std::distance(new_main_iterator, instructions.begin());
				if (log) {
					std::cout << "Moving iterator from position=" << original_pos << ", val=" << *main_iterator
					          << " to position=" << new_pos << ", val=" << *new_main_iterator << std::endl;
				}
				main_iterator = new_main_iterator;
			} else {
				main_iterator++;
				main_iterator++;
			}

		}

		void instruction_bxc(RegType operand) {
			auto bitwise_xor = reg_B ^ reg_C;
			if (log) {
				std::cout << "Bitwise XOR of " << reg_B << "^" << reg_C << "=" << bitwise_xor << std::endl;
			}
			reg_B = bitwise_xor;
		}

		void instruction_out(RegType operand) {
			auto modulo = combo_operand(operand) % 8;
			std::string modulo_str = std::to_string(modulo);
			auto modulo_vec = utils::string_to_vector_type<RegType>(modulo_str);
			if (log) {
				std::cout << "Modulo of " << combo_operand(operand) << "%" << 8 << "=" << modulo_vec
				          << ". Sending this to output." << std::endl;
			}
			for (auto val: modulo_vec) {
				output.push_back(val);
			}
			if (log) {
				std::cout << "New output is: " << output << std::endl;
			}
		}


	};

}
