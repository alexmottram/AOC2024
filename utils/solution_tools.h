#pragma once
#include "../doctest.h"


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
        const int YEAR;
        const int DAY;

        const sol_T EXPECTED_TEST_A{0};
        const sol_T EXPECTED_SOLUTION_A{0};
        const sol_T EXPECTED_TEST_B{0};
        const sol_T EXPECTED_SOLUTION_B{0};

        SolutionTemplate(
            int year,
            int day,
            sol_T expected_test_A = 0,
            sol_T expected_solution_A = 0,
            sol_T expected_test_B = 0,
            sol_T expected_solution_B = 0
        ):
            YEAR(year),
            DAY(day),
            EXPECTED_TEST_A(expected_test_A),
            EXPECTED_SOLUTION_A(expected_solution_A),
            EXPECTED_TEST_B(expected_test_B),
            EXPECTED_SOLUTION_B(expected_solution_B)
        {
        }

        virtual ~SolutionTemplate() = default;

        void print_solution_part(
            const std::string& part,const bool is_test, sol_T solution)
        {
            std::cout << "Solution for day " << DAY << " part " << part;
            if (is_test)
            {
                std::cout << " using test data: ";
            }
            else
            {
                std::cout << " using real data: ";
            }
            std::cout << solution << std::endl;
        }

        sol_T solution_part_a(const bool is_test = false)
        {
            const auto input_reader = get_input_reader(is_test);
            const auto solution =  solve_part_a(input_reader);
            print_solution_part("A", is_test, solution);
            return solution;
        }

        sol_T solution_part_b(const bool is_test = false)
        {
            const auto input_reader = get_input_reader(is_test);
            const auto solution =  solve_part_b(input_reader);
            print_solution_part("B", is_test, solution);
            return solution;
        }

        [[nodiscard]] InputReader get_input_reader(bool is_test = false) const
        {
			if (DAY == 0){
				throw std::runtime_error("Day should not be 0.");
			}
            return {DAY, YEAR, is_test};
        }

        virtual sol_T solve_part_a(const InputReader& input_reader) = 0;
        virtual sol_T solve_part_b(const InputReader& input_reader) = 0;
    };


}
