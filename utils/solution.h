#pragma once
#include "input_reader.h"

namespace utils {
    class Solution {
      public:
        const int year;
        const int day;
        const InputReader input_reader{day, year, false};
        const InputReader test_input_reader{day, year, true};
        long long solution_part_a();
        long long solution_part_a(bool is_test);
        long long solution_part_b();
        long long solution_part_b(bool is_test);
        long long solve_part_a(const InputReader);
        long long solve_part_b(const InputReader);
    }
}
