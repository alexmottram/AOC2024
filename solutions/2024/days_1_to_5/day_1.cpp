#include "day_1.h"

#include <ranges>

namespace solutions {

    const std::map<std::string, int> DIGITS_MAP{
            {"one", 1},
            {"two", 2},
            {"three", 3},
            {"four", 4},
            {"five", 5},
            {"six", 6},
            {"seven", 7},
            {"eight", 8},
            {"nine", 9},
    };

    long long find_first_digit(const std::string& str, bool include_strings)
    {
        std::string build_str{};
        for (const auto val : str) {
            if (std::isdigit(val)) { return val-'0'; }
            if (include_strings) {
                build_str.push_back(val);
                for (auto const& [digit_str, digit_val] : DIGITS_MAP) {
                    if (build_str.find(digit_str)!=std::string::npos) {
                        return digit_val;
                    }
                }
            }
        }
        std::cout << "No digit found in first front scan." << std::endl;
        return 0;

    }

    long long find_last_digit(std::string str, const bool include_strings)
    {
        std::string build_str{};
        for (const char & val : std::ranges::reverse_view(str)) {
            const auto val_copy = val;
            if (std::isdigit(val_copy)) { return val-'0'; }
            if (include_strings) {
                std::string sub_str{val_copy};
                build_str.insert(0, sub_str);
                for (auto const& [digit_str, digit_val] : DIGITS_MAP) {
                    if (build_str.find(digit_str)!=std::string::npos) {
                        return digit_val;
                    }
                }
            }
        }

        std::cout << "No digit found in reverse scan." << std::endl;
        return 0;

    }

    int combine_two_digits(const long long a, const long long b)
    {
        std::stringstream ss;
        ss << a << b;
        const int combined_num = std::stoi(ss.str());
        return combined_num;
    }

    long long day_1_part_a(const utils::InputReader& input)
    {
        std::vector<std::string> data_in = input.string_vector();
        std::vector<int> nums_out{};
        int num_sum{0};

        for (const auto& line : data_in) {
            const auto first_digit = find_first_digit(line, false);
            const auto last_digit = find_last_digit(line, false);
            int num = combine_two_digits(first_digit, last_digit);
            nums_out.push_back(num);
            num_sum += num;
        }
        std::cout << "Vector of nums out: " << nums_out << std::endl;
        return num_sum;
    }

    long long day_1_part_b(const utils::InputReader& input)
    {
        std::vector<std::string> data_in = input.string_vector();
        std::vector<int> nums_out{};
        int num_sum{0};

        for (const auto& line : data_in) {
            const auto first_digit = find_first_digit(line, true);
            const auto last_digit = find_last_digit(line, true);
            int num = combine_two_digits(first_digit, last_digit);
            nums_out.push_back(num);
            num_sum += num;
        }
        return num_sum;
    }
}
