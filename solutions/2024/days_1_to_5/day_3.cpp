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

    long long day_3_part_a(const utils::InputReader& input)
    {
        const std::vector<std::string> instructions_multi_line = input.string_vector();
        const std::string& instructions = instructions_multi_line[0];
        std::cout << "Instructions are: " << instructions << std::endl;
        const long long multiplied_val = find_instructions(instructions);
        return multiplied_val;
    }

    long long day_3_part_b(const utils::InputReader& input)
    {
        const std::vector<std::string> instructions_multi_line = input.string_vector();
        const std::string& instructions = instructions_multi_line[0];
        std::cout << "Instructions are: " << instructions << std::endl;
        const long long multiplied_val = find_instructions(instructions);
        return multiplied_val;
    }
}