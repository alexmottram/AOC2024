#include "day_3.h"

namespace solutions {

    long long find_instructions(std::string instructions)
    {
        long long running_total {0};
        const std::regex multiply_instruction(R"(mul\b\((\d+),(\d+)\))");
        auto words_begin = std::sregex_iterator(
            instructions.begin(), instructions.end(), multiply_instruction
            );
        const auto words_end = std::sregex_iterator();
        for (std::sregex_iterator i = words_begin; i != words_end; ++i)
        {
            const std::smatch& match = *i;
            std::cout << "Match: " << match.str() << "values: "
            << match[1] << ", " << match[2] << '\n';
            running_total += (std::stoll(match[1])* std::stoll(match[2]));
        }

        return running_total;
    }

    long long find_instructions_after_do(const std::string& instructions)
    {
        long long running_total {0};

        std::vector<std::string> instruction_split = utils::split_string(instructions, "do()");
        for (const std::string& sub_instruction: instruction_split)
        {
            std::cout << "Sub-instruction set is: " << sub_instruction << std::endl;
            std::vector<std::string> sub_instruction_split = utils::split_string(sub_instruction, "don't()");
            const auto& do_instructions = sub_instruction_split[0];
            std::cout << "Do instructions are: " << do_instructions << std::endl;
            running_total += find_instructions(do_instructions);
        }

        return running_total;
    }


    long long day_3_part_a(const utils::InputReader& input)
    {
        const std::vector<std::string> instructions_multi_line = input.string_vector();
        const std::string instructions = std::accumulate(
            instructions_multi_line.begin(), instructions_multi_line.end(), std::string("")
            );
        std::cout << "Instructions are: " << instructions << std::endl;

        const long long multiplied_val = find_instructions(instructions);
        return multiplied_val;
    }

    long long day_3_part_b(const utils::InputReader& input)
    {
        const std::vector<std::string> instructions_multi_line = input.string_vector();
        std::string instructions = std::accumulate(instructions_multi_line.begin(), instructions_multi_line.end(), std::string(""));
        std::cout << "Instructions are: " << instructions << std::endl;

        const long long multiplied_val = find_instructions_after_do(instructions);
        return multiplied_val;
    }
}