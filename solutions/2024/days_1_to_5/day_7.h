#pragma once

#include "../../../utils/utils.h"

namespace solutions
{
    class Day7Solution final : public utils::SolutionTemplate<long long>
    {
    public:
        Day7Solution(): SolutionTemplate(2024, 7) {}

        static constexpr long long EXPECTED_TEST_A{3749};
        static constexpr long long EXPECTED_SOLUTION_A{3245122495150};
        static constexpr long long EXPECTED_TEST_B{11387};
        static constexpr long long EXPECTED_SOLUTION_B{0};

        long long solve_part_a(utils::InputReader input_reader) override;
        long long solve_part_b(utils::InputReader input_reader) override;
    };

    struct Equation
    {
        long long final_value;
        std::vector<long long> input_values;

        explicit Equation(const std::string& string_input)
        {
            const auto split_string = utils::split_string(string_input, ":", true);
            final_value = utils::string_to_type<long long>(split_string[0]);
            input_values = utils::string_to_vector_type<long long>(split_string[1], " ");
        };

        [[nodiscard]] long long lower_bound() const;
        [[nodiscard]] long long upper_bound() const;
        [[nodiscard]] bool final_value_in_bounds() const;

        friend std::ostream& operator<<(std::ostream& os, const Equation& eq)
        {
            os << "Equation{final_Value=" << eq.final_value << ",inputs=" << eq.input_values << "}";
            return os;
        }
    };

}