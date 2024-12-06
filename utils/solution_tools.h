#pragma once
#include <complex.h>

#include "precompile_header.h"
#include "input_reader.h"

namespace utils
{
    template <typename solution_output_type>
    auto print_solution_part(const std::string& part, const int day, const bool is_test,
                             solution_output_type solution) -> void
    {
        std::cout << "Solution for day " << day << " part " << part;
        if (is_test)
        {
            std::cout << " for test data: ";
        }
        else
        {
            std::cout << " for real data: ";
        }
        std::cout << solution << std::endl;
    }

    template <typename sol_T>
    class SolutionTemplate
    {
    public:
        static constexpr int YEAR{0};
        static constexpr int DAY{0};
        virtual ~SolutionTemplate() = default;

        sol_T solution_part_a(const bool is_test=false)
        {
            auto input_reader = get_input_reader(is_test);
            return solution_part_a(input_reader);
        };

        sol_T solution_part_b(const bool is_test=false)
        {
            auto input_reader = get_input_reader(is_test);
            return solution_part_b(input_reader);
        };

        [[nodiscard]] static InputReader get_input_reader(bool is_test=false)
        {
            return {DAY, YEAR, is_test};
        }

        virtual sol_T solve_part_a(InputReader input_reader);
        virtual sol_T solve_part_b(InputReader input_reader);
    };
}
