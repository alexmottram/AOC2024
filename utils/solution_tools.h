#pragma once
#pragma clang diagnostic ignored "-Woverloaded-shift-op-parentheses"
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
        int year;
        int day;

        sol_T EXPECTED_TEST_A{0};
        sol_T EXPECTED_TEST_B{0};
        sol_T EXPECTED_SOLUTION_A{0};
        sol_T EXPECTED_SOLUTION_B{0};

        SolutionTemplate(int year, int day):
            year(year), day(day)
        {
        }

        virtual ~SolutionTemplate() = default;

        sol_T solution_part_a(const bool is_test = false)
        {
            const auto input_reader = get_input_reader(is_test);
            return solve_part_a(input_reader);
        };

        sol_T solution_part_b(const bool is_test = false)
        {
            const auto input_reader = get_input_reader(is_test);
            return solve_part_b(input_reader);
        };

        [[nodiscard]] InputReader get_input_reader(bool is_test = false) const
        {
            return {day, year, is_test};
        }

        virtual sol_T solve_part_a(InputReader input_reader) = 0;
        virtual sol_T solve_part_b(InputReader input_reader) = 0;
    };

    // template<out_T>
    // void run_test_suite(SolutionTemplate<out_T> SolTemplate)
    // {
    //     std::stringstream test_suite_sstring;
    //     test_suite_sstring << "Test suite for year: " << SolTemplate::YEAR << " and day: " << solution_template::DAY;
    //     std::string test_suite_string{test_suite_sstring.str()};
    //     TEST_SUITE_BEGIN("Inside test suite for solution template");
    //     CHECK(true);
    //     std::cout << "Hit test suite: " << std::endl;
    //     TEST_SUITE_END;
    // }
}
