#pragma once

#include "../../../utils/utils.h"
#include "../common_header.h"

namespace solutions
{
    class Day24Solution final : public utils::SolutionTemplate<long long>
    {
    public:
        Day24Solution(): SolutionTemplate(
            2024,
            24,
            1,
            1,
            1,
            1
        )
        {
        }

        long long solve_part_a(const utils::InputReader& input_reader) override;
        long long solve_part_b(const utils::InputReader& input_reader) override;
    };

    struct BinaryOperation
    {
        std::string input_wire_a;
        std::string input_wire_b;
        std::string operation;
        std::string output_wire;

        BinaryOperation() = default;

        explicit BinaryOperation(const std::string& string_in)
        {
            const auto string_vec = utils::split_string(string_in, " ");
            input_wire_a = string_vec.at(0);
            input_wire_b = string_vec.at(2);
            operation = string_vec.at(1);
            output_wire = string_vec.at(4);
        }

        friend bool operator ==(const BinaryOperation& lhs, const BinaryOperation& rhs)
        {
            return (
                (lhs.input_wire_a == rhs.input_wire_a) &&
                (lhs.input_wire_b == rhs.input_wire_b) &&
                (lhs.operation == rhs.operation) &&
                (lhs.output_wire == rhs.output_wire)
            );
        }

        friend bool operator <(const BinaryOperation& lhs, const BinaryOperation& rhs)
        {
            return (
                (lhs.input_wire_a < rhs.input_wire_a) ||
                ((lhs.input_wire_a == rhs.input_wire_a) && (lhs.input_wire_b < rhs.input_wire_b)) ||
                ((lhs.input_wire_a == rhs.input_wire_a) && (lhs.input_wire_b == rhs.input_wire_b) && (lhs.operation <
                    rhs.operation)) ||
                ((lhs.input_wire_a == rhs.input_wire_a) && (lhs.input_wire_b == rhs.input_wire_b) && (lhs.operation ==
                    rhs.operation) && (lhs.output_wire < rhs.output_wire))
            );
        }

        friend std::ostream& operator <<(std::ostream& os, const BinaryOperation& bo)
        {
            os << "BinaryOperation(in_a=" << bo.input_wire_a << ", in_b="
                << bo.input_wire_a << ", operation=" << bo.operation << " ,output_wire="
                << bo.output_wire << ")";
            return os;
        }

        [[nodiscard]] size_t perform_operation(
            const size_t& wire_a_val,
            const size_t& wire_b_val,
            const bool log = false
        ) const
        {
            if (operation == "AND")
            {
                const auto res = wire_a_val & wire_b_val;
                if (log)
                {
                    std::cout << this << "-> Operation " << wire_a_val << " AND " << wire_b_val << " = " << res << std::endl;
                }
                return res;
            }
            if (operation == "XOR")
            {
                const auto res = wire_a_val ^ wire_b_val;
                if (log)
                {
                    std::cout << this << "-> Operation " << wire_a_val << " XOR " << wire_b_val << " = " << res << std::endl;
                }
                return res;
            }
            if (operation == "OR")
            {
                const auto res = wire_a_val | wire_b_val;
                if (log)
                {
                    std::cout << this << "-> Operation " << wire_a_val << " OR " << wire_b_val << " = " << res << std::endl;
                }
                return res;
            }

            throw std::runtime_error("Invalid operation");
        }
    };
}
