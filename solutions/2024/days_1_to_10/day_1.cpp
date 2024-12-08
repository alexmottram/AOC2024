#include "day_1.h"

#include <ranges>

namespace solutions {

    long long Day1Solution::solve_part_a(const utils::InputReader& input_reader)
    {
        std::vector<std::string> input_str = input_reader.string_vector();
        std::vector<int> left_col;
        std::vector<int> right_col;
        long long diff {0};

        for (const auto& str : input_str)
        {
            std::vector<int> row_split = utils::string_to_vector_type<int>(str, " ");
            left_col.push_back(row_split[0]);
            right_col.push_back(row_split[1]);
        }

        std::sort(left_col.begin(), left_col.end());
        std::sort(right_col.begin(), right_col.end());

        std::cout << "Left col: " << left_col << std::endl;
        std::cout << "Right col: " << right_col << std::endl;

        for (auto i{0}; i<left_col.size(); i++)
        {
            diff += abs(left_col[i]- right_col[i]);
        }

        return diff;
    }

    long long Day1Solution::solve_part_b(const utils::InputReader& input_reader)
    {
        std::vector<std::string> input_str = input_reader.string_vector();
        std::vector<int> left_col;
        std::vector<int> right_col;
        long long diff {0};

        for (const auto& str : input_str)
        {
            std::vector<int> row_split = utils::string_to_vector_type<int>(str, " ");
            left_col.push_back(row_split[0]);
            right_col.push_back(row_split[1]);
        }

        std::map<int, int> right_col_map {};

        for (const auto& val: right_col)
        {
            if (right_col_map.contains(val))
            {
                right_col_map[val]++;
            } else
            {
                right_col_map[val] = 1;
            }
        }

        std::cout << "Right col map: " << right_col_map << std::endl;

        for (const auto& l_val: left_col)
        {
            if (right_col_map.contains(l_val))
            {
                const auto r_val = right_col_map[l_val];
                std::cout << "Multiplying values: " << l_val << ", " << r_val << std::endl;
                diff += (r_val*l_val);
            }

        }
        return diff;
    }
}
