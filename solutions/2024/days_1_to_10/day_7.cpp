#include "day_7.h"

namespace solutions
{
    long long Equation::lower_bound() const
    {
        long long lower_bound_val{0};
        for (const auto num : input_values)
        {
            if (lower_bound_val == 0)
            {
                lower_bound_val = num;
            }
            else if (num == 1)
            {
                lower_bound_val = lower_bound_val * num;
            }
            else
            {
                lower_bound_val += num;
            }
        }
        return lower_bound_val;
    }


    long long Equation::upper_bound() const
    {
        long long upper_bound_val{0};
        for (const auto num : input_values)
        {
            if (upper_bound_val == 0)
            {
                upper_bound_val = num;
            }
            else if (num == 1)
            {
                upper_bound_val += num;
            }
            else
            {
                upper_bound_val *= num;
            }
        }
        return upper_bound_val;
    }

    bool Equation::final_value_in_bounds() const
    {
        return (final_value >= lower_bound()) and (final_value <= upper_bound());
    }

    std::vector<Equation> get_equations(const utils::InputReader& input_reader)
    {
        std::vector<Equation> equations;
        for (const auto& line : input_reader.string_vector())
        {
            equations.emplace_back(line);
        }
        return equations;
    }

    std::set<long long> optional_values(const long long current_input, const std::set<long long>& rolling_values)
    {
        std::set<long long> next_rolling_values{};
        for (const auto rolling_value : rolling_values)
        {
            const auto diff_from_division = rolling_value % current_input;
            const auto after_division = rolling_value / current_input;
            const auto after_subtract = rolling_value - current_input;
            if (diff_from_division == 0)
            {
                next_rolling_values.insert(after_division);
            }

            if (after_subtract >= 0)
            {
                next_rolling_values.insert(after_subtract);
            }
        }
        return next_rolling_values;
    }

    long long solve_equations(const Equation& equation)
    {
        if (equation.final_value_in_bounds())
        {
            std::set<long long> rolling_values{equation.final_value};
            auto inputs_val_copy = equation.input_values;
            std::ranges::reverse(inputs_val_copy);

            for (const auto val : inputs_val_copy)
            {
                if (rolling_values.empty())
                {
                    std::cout << "Ran out of viable options for equation: " << equation << std::endl;
                    return 0;
                }

                rolling_values = optional_values(val, rolling_values);
            }
            if (rolling_values.contains(0))
            {
                std::cout << "Found solution for equation: " << equation << std::endl;
                return equation.final_value;
            }
            else
            {
                std::cout << "No zero value found at end for equation: " << equation << std::endl;
                return 0;
            }
        }
        else
        {
            std::cout << "Final value out of bounds for equation: " << equation << std::endl;
            return 0;
        }
    }

    long long score_equation_list(const std::vector<Equation>& all_equations)
    {
        long long total_score{0};

        for (const auto& equation : all_equations)
        {
            const auto score = solve_equations(equation);
            total_score += score;
        }

        return total_score;
    }

    std::set<long long> optional_values_with_three_operators(
        const long long current_input,
        const long long max_value,
        const std::set<long long>& rolling_values
    )
    {
        std::set<long long> next_rolling_values{};
        for (const auto rolling_value : rolling_values)
        {
            const auto after_multiplication = rolling_value * current_input;
            const auto after_addition = rolling_value + current_input;
            const auto after_combination = utils::string_to_type<long long>(
                 std::to_string(rolling_value) + std::to_string(current_input)
            );

            // std::cout << "Rolling value: " << rolling_value << ", current value: " << current_input
            // << " max value: " << max_value << " and multiply, add and concat: " << after_multiplication
            // << ", " << after_addition << ", " << after_combination << std::endl;

            if (after_multiplication <= max_value)
            {
                next_rolling_values.insert(after_multiplication);
            }
            if (after_addition <= max_value)
            {
                next_rolling_values.insert(after_addition);
            }
            if (after_combination <= max_value)
            {
                next_rolling_values.insert(after_combination);
            }
        }
        return next_rolling_values;
    }

    long long solve_equation_with_three_operators(const Equation& equation)
    {
        bool first_iteration{true};
        std::set<long long> rolling_values{};

        for (const auto val : equation.input_values)
        {

            if (first_iteration)
            {
                rolling_values.insert(val);
                first_iteration = false;
            }
            else
            {
                if (rolling_values.empty())
                {
                    std::cout << "Ran out of viable options for equation: " << equation << std::endl;
                    return 0;
                }
                rolling_values = optional_values_with_three_operators(val, equation.final_value, rolling_values);
            }
        }
        if (rolling_values.contains(equation.final_value))
        {
            std::cout << "Found solution for equation: " << equation << std::endl;
            return equation.final_value;
        }
        else
        {
            std::cout << "No matching final value founds: " << equation << std::endl;
            return 0;
        }
    }

    long long score_equation_list_with_three_operators(const std::vector<Equation>& all_equations)
    {
        long long total_score{0};

        for (const auto& equation : all_equations)
        {
            const auto score = solve_equation_with_three_operators(equation);
            total_score += score;
        }

        return total_score;
    }


    long long Day7Solution::solve_part_a(const utils::InputReader input_reader)
    {
        const std::vector<Equation> all_equations = get_equations(input_reader);
        std::cout << "Loaded equations: \n" << all_equations << std::endl;
        const auto score = score_equation_list(all_equations);
        return score;
    }

    long long Day7Solution::solve_part_b(const utils::InputReader input_reader)
    {
        const std::vector<Equation> all_equations = get_equations(input_reader);
        std::cout << "Loaded equations: \n" << all_equations << std::endl;
        const auto score = score_equation_list_with_three_operators(all_equations);
        return score;
    }
}
