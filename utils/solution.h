#pragma once
#include "precompile_header.h"
//#include "input_reader.h"

namespace utils
{
    template <typename solution_type>
    auto print_solution_part(const std::string& part, const int day, const bool is_test, solution_type solution) -> void
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

    //    class Solution {
    //      public:
    //        const int year;
    //        const int day;
    //        const InputReader input_reader{day, year, false};
    //        const InputReader test_input_reader{day, year, true};
    //        long long solution_part_a();
    //        long long solution_part_a(bool is_test);
    //        long long solution_part_b();
    //        long long solution_part_b(bool is_test);
    //        long long solve_part_a(const InputReader);
    //        long long solve_part_b(const InputReader);
    //    }
}
