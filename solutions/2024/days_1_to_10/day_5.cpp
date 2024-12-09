#include "day_5.h"

namespace solutions
{
    std::map<int, std::set<int>> get_requirements(const utils::InputReader& input)
    {
        std::map<int, std::set<int>> requirements{};
        for (const auto& line : input.string_vector())
        {
            if (line.empty()) { break; }
            auto split_line = utils::string_to_vector_type<int>(line, "|");

            auto it = requirements.find(split_line[0]);
            if (it == requirements.end())
            {
                requirements[split_line[0]] = std::set<int>{split_line[1]};
            }
            else
            {
                it->second.insert(split_line[1]);
            }
        }
        return requirements;
    }

    std::vector<std::vector<int>> get_page_updates(const utils::InputReader& input)
    {
        bool after_empty_line{false};
        std::vector<std::vector<int>> page_updates{};
        for (const auto& line : input.string_vector())
        {
            if (after_empty_line)
            {
                auto split_line = utils::string_to_vector_type<int>(line, ",");
                page_updates.push_back(split_line);
            }
            if (line.empty()) { after_empty_line = true; }
        }
        return page_updates;
    }

    bool is_valid_page_update(std::vector<int> page_update, std::map<int, std::set<int>> requirements)
    {
        std::set<int> prev_pages{};
        for (auto page : page_update)
        {
            auto check_pages = requirements[page];
            std::set<int> broken_pages{};

            std::copy_if(
                check_pages.begin(),
                check_pages.end(),
                std::inserter(broken_pages, broken_pages.end()),
                [prev_pages](auto check_page) { return prev_pages.contains(check_page); }
            );

            if (!broken_pages.empty()) { return false; }
            prev_pages.insert(page);
        }

        return true;
    }


    long long get_middle_page_score(std::vector<int> page_update)
    {
        return page_update[page_update.size() / 2];
    }

    long long calculate_middle_page_count(std::vector<std::vector<int>> page_updates,
                                          std::map<int, std::set<int>> requirements)
    {
        long long middle_page_score{0};
        for (const auto& page_update : page_updates)
        {
            if (is_valid_page_update(page_update, requirements))
            {
                auto curr_score = get_middle_page_score(page_update);
                std::cout << "Middle value " << curr_score << " for valid update: " << page_update << std::endl;
                middle_page_score += curr_score;
            }
        }
        return middle_page_score;
    }


    std::vector<int> get_correct_page_order(
        const std::vector<int>& orig_page_order, const std::map<int, std::set<int>>& requirements
    )
    {
        const std::set<int> pages_present{orig_page_order.begin(), orig_page_order.end()};
        std::set<int> pages_with_rules{};
        std::set<int> pages_to_rules{};
        std::vector<std::pair<int, std::set<int>>> reduced_requirements{};

        for (const int& page : pages_present)
        {
            std::set<int> pages_to_and_present{};
            if (requirements.contains(page))
            {
                const auto& to_page_set = requirements.at(page);
                std::copy_if(
                    to_page_set.begin(),
                    to_page_set.end(),
                    std::inserter(pages_to_and_present, pages_to_and_present.end()),
                    [pages_present](auto check_page) { return pages_present.contains(check_page); }
                );
            }

            pages_with_rules.insert(page);
            pages_to_rules.insert(pages_to_and_present.begin(), pages_to_and_present.end());
            reduced_requirements.emplace_back(page, pages_to_and_present);
        }

        std::cout << "Pages present in original page order: " << orig_page_order << std::endl;
        std::cout << "Pages with rules: " << pages_with_rules << std::endl;
        std::sort(
            reduced_requirements.begin(),
            reduced_requirements.end(),
            [](auto a, auto b) { return a.second.size() > b.second.size(); }
        );
        std::cout << "Reduced requirements: " << reduced_requirements << std::endl;

        std::vector<int> ordered_output{};
        std::transform(
            reduced_requirements.begin(),
            reduced_requirements.end(),
            std::inserter(ordered_output, ordered_output.begin()),
            [](auto val) { return val.first; }
        );

        std::cout << "Ordered page list: " << reduced_requirements << std::endl;
        return ordered_output;
    }

    std::vector<std::vector<int>> order_page_updates(const std::vector<std::vector<int>>& orig_page_updates,
                                                     const std::map<int, std::set<int>>& requirements)
    {
        std::vector<std::vector<int>> correct_page_updates{};

        for (const auto& orig_page : orig_page_updates)
        {
            auto corrected_page = get_correct_page_order(orig_page, requirements);
            correct_page_updates.push_back(corrected_page);
        }

        return correct_page_updates;
    }

    long long day_5_part_a(const utils::InputReader& input)
    {
        const auto requirements = get_requirements(input);
        std::cout << "Requirements:\n" << requirements << std::endl;
        const auto page_updates = get_page_updates(input);
        std::cout << "Page Updates:\n" << page_updates << std::endl;
        long long middle_page_count = calculate_middle_page_count(page_updates, requirements);
        return middle_page_count;
    }

    long long day_5_part_b(const utils::InputReader& input)
    {
        const auto requirements = get_requirements(input);
        std::cout << "Requirements:\n" << requirements << std::endl;
        const auto page_updates = get_page_updates(input);
        std::vector<std::vector<int>> incorrectly_ordered_page_updates{};

        for (const auto& page_update : page_updates)
        {
            if (!is_valid_page_update(page_update, requirements))
            {
                incorrectly_ordered_page_updates.push_back(page_update);
            }
        }

        std::cout << "Incorrect page Updates:\n" << page_updates << std::endl;
        const auto correctly_ordered_pages = order_page_updates(incorrectly_ordered_page_updates, requirements);
        const long long middle_page_count = calculate_middle_page_count(correctly_ordered_pages, requirements);
        return middle_page_count;
    }
}
