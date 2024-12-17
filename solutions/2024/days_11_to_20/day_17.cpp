#include "day_17.h"

namespace solutions {


	void ThreeBitComputer::run_code() {
		auto main_iterator = instructions.begin();
		while (main_iterator != instructions.end()) {
			auto secondary_iterator = main_iterator;
			secondary_iterator++;
			if (log) {
				std::cout << "Processing instructions: "
				          << *main_iterator << ", " << *secondary_iterator << std::endl;
			}
			process_instruction(main_iterator, *secondary_iterator);

		}

	}

	ThreeBitComputer::RegType ThreeBitComputer::process_instruction(
			ThreeBitComputer::InstructionIterator &opcode_it, ThreeBitComputer::RegType operand
	) {
		switch (*opcode_it) {
			case 0:
				if (log) {
					std::cout << "Opcode 0 -> Command adv" << std::endl;
				}
				instruction_adv(operand);
				opcode_it++;
				opcode_it++;
				break;
			case 1:
				if (log) {
					std::cout << "Opcode 1 -> Command bxl" << std::endl;
				}
				instruction_bxl(operand);
				opcode_it++;
				opcode_it++;
				break;
			case 2:
				if (log) {
					std::cout << "Opcode 2 -> Command bst" << std::endl;
				}
				instruction_bst(operand);
				opcode_it++;
				opcode_it++;
				break;
			case 3:
				if (log) {
					std::cout << "Opcode 3 -> Command jnz" << std::endl;
				}
				instruction_jnz(opcode_it, operand);
				break;
			case 4:
				if (log) {
					std::cout << "Opcode 4 -> Command bxc" << std::endl;
				}
				instruction_bxc(operand);
				opcode_it++;
				opcode_it++;
				break;
			case 5:
				if (log) {
					std::cout << "Opcode 5 -> Command out" << std::endl;
				}
				instruction_out(operand);
				opcode_it++;
				opcode_it++;
				break;
			case 6:
				if (log) {
					std::cout << "Opcode 6 -> Command bdv" << std::endl;
				}
				instruction_bdv(operand);
				opcode_it++;
				opcode_it++;
				break;
			case 7:
				if (log) {
					std::cout << "Opcode 6 -> Command cdv" << std::endl;
				}
				instruction_cdv(operand);
				opcode_it++;
				opcode_it++;
				break;
			default:
				throw std::runtime_error("Undefined opcode.");
		}
		return 0;
	}

	long long Day17Solution::solve_part_a(const utils::InputReader &input_reader) {
		ThreeBitComputer computer{input_reader.string_vector()};
		std::cout << "Computer initialised with status: \n" << computer << std::endl;
		computer.log = true;
//		computer.reg_A = 33;
		computer.run_code();
		std::cout << "Computer after processing: \n" << computer << std::endl;
		std::string string_output{};
		for (auto val: computer.output) {
			string_output += std::to_string(val);
		}
		auto solution_value = utils::string_to_type<long long>(string_output);
		return solution_value;
	}

	long long Day17Solution::solve_part_b(const utils::InputReader &input_reader) {
		ThreeBitComputer base_computer{input_reader.string_vector()};
		std::cout << "Computer initialised with status: \n" << base_computer << std::endl;

		long long reg_A = 10;
		long long max_repetitions = 100000000000000000;

		while (reg_A < max_repetitions) {
			auto computer = base_computer;
			computer.reg_A = reg_A;

			computer.run_code();

			if (computer.instructions_and_output_match()) {
				return reg_A;
			} else if (computer.last_output_digits_match()) {
				std::cout << "Last digit matched for reg_A: " << reg_A
				          << " computer: " << computer << std::endl;
				reg_A *= 8;
				std::cout << "New reg_A: " << reg_A << std::endl;
			} else {
				reg_A ++;
			}

			if (reg_A % 10000000 == 0) {

				std::cout << "Processed reg A with starting value " << reg_A << std::endl;
				std::cout << "Solved computer " << computer << std::endl;
			}
		}
		return 0;
	}

}