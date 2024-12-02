#include "day_2.h"

namespace solutions
{
    bool numbers_in_range(const int diff)
    {
        return not(diff > 3 or diff < -3 or diff == 0);
    }

    int sum_of_sign(const int running_sum, const int val)
    {
        auto out_val = running_sum;
        if (val > 0)
        {
            out_val++;
        }
        else if (val < 0)
        {
            out_val--;
        }
        return out_val;
    }

    bool passes_safety_test(const std::vector<int>& report)
    {
        std::vector<int> report_diff{};
        for (auto i{1}; i < report.size(); i++)
        {
            report_diff.push_back(report[i] - report[i - 1]);
        }

        std::cout << "Diff vector: " << report_diff << std::endl;

        const bool all_in_range = std::all_of(report_diff.begin(), report_diff.end(), numbers_in_range);
        const bool all_pos = std::all_of(report_diff.begin(), report_diff.end(), [](const int i) { return i > 0; });
        const bool all_neg = std::all_of(report_diff.begin(), report_diff.end(), [](const int i) { return i < 0; });

        return all_in_range and (all_pos or all_neg);
    }

    bool passes_after_removing_index(const std::vector<int>& report, const size_t index)
    {
        auto report_copy = report;
        report_copy.erase(report_copy.begin() + index);
        std::cout << "Testing after removing index: " << index << " from report: " << report_copy << std::endl;
        return passes_safety_test(report_copy);
    }

    bool passes_with_problem_solver(const std::vector<int>& report)
    {
        std::vector<int> report_diff{};
        for (auto i{1}; i < report.size(); i++)
        {
            report_diff.push_back(report[i] - report[i - 1]);
        }

        auto pos_or_neg = std::accumulate(report_diff.begin(), report_diff.end(), 0, sum_of_sign);
        bool expect_pos{false};
        if (pos_or_neg > 0) { expect_pos = true; }

        const auto first_out_of_range = std::find_if(
            report_diff.begin(),
            report_diff.end(),
            [](const int i) { return not numbers_in_range(i); }
        ) - report_diff.begin();

        const auto first_in_wrong_direction = std::find_if(
            report_diff.begin(),
            report_diff.end(),
            [expect_pos](const int i)
            {
                if (expect_pos)
                {
                    return i < 0;
                }
                else
                {
                    return i > 0;
                }
            }) - report_diff.begin();

        std::cout << "First out of range: " << first_out_of_range << std::endl;
        std::cout << "First in wrong direction: " << first_in_wrong_direction << std::endl;

        size_t first_fail_loc = std::min(first_out_of_range, first_in_wrong_direction);
        std::cout << "First location failing: " << first_fail_loc << std::endl;
        bool passes_left = passes_after_removing_index(report, first_fail_loc);
        bool passes_right = passes_after_removing_index(report, first_fail_loc + 1);
        return passes_left or passes_right;
    }

    bool is_report_safe(const std::vector<int>& report, bool enable_problem_resolver)
    {
        const bool initial_safety_test = passes_safety_test(report);
        if (initial_safety_test)
        {
            return true;
        }

        if (enable_problem_resolver)
        {
            bool solved_by_problem_solver = passes_with_problem_solver(report);
            return solved_by_problem_solver;
        }

        return initial_safety_test;
    }


    long long day_2_part_a(const utils::InputReader& input)
    {
        auto input_str = input.string_vector();
        int safe_report_count{0};
        for (const auto& report_str : input_str)
        {
            auto report_int = utils::string_to_vector_type<int>(report_str, " ");
            std::cout << "Running for report: " << report_int << std::endl;

            if (is_report_safe(report_int, false))
            {
                std::cout << "Report is safe: " << report_int << std::endl;
                safe_report_count++;
            }
            else
            {
                std::cout << "Report is unsafe: " << report_int << std::endl;
            }
        }
        return safe_report_count;
    }

    long long day_2_part_b(const utils::InputReader& input)
    {
        auto input_str = input.string_vector();
        int safe_report_count{0};
        for (const auto& report_str : input_str)
        {
            auto report_int = utils::string_to_vector_type<int>(report_str, " ");
            std::cout << "Running for report: " << report_int << std::endl;
            if (is_report_safe(report_int, true))
            {
                std::cout << "Report is safe: " << report_int << std::endl;
                safe_report_count++;
            }
            else
            {
                std::cout << "Report is unsafe: " << report_int << std::endl;
            }
        }
        return safe_report_count;
    }
}
