#include "day_6.h"

namespace solutions
{
    void add_move_to_history(utils::Array2D<char>& layout_history)
    {
    }

    std::map<char, std::pair<char, utils::Vec2D<long long>>> DIRECTION_MAP{
        {'^', {'>', {1, 0}}},
        {'>', {'v', {0, 1}}},
        {'v', {'<', {-1, 0}}},
        {'<', {'^', {0, -1}}},
    };

    std::set<std::pair<char, utils::Vec2D<long long>>> directions_and_locations_covered_by_guard(utils::Array2D<char> layout)
    {
        std::set<std::pair<char, utils::Vec2D<long long>>> locations_visited{};
        std::pair<char, utils::Vec2D<long long>> guard{'^', {0, -1}};
        const auto initial_loc_set = layout.find(guard.first);
        const auto set_iterator = initial_loc_set.begin();
        auto curr_loc = static_cast<utils::Vec2D<long long>>(set_iterator->vector());
        locations_visited.insert({guard.first, curr_loc});
        auto layout_history = layout;

        while (locations_visited.size() != layout.size())
        {
            const auto next_loc = curr_loc + guard.second;
            if (!layout.vector_in_array(next_loc)) { break; }

            if (layout.at(next_loc) != '.')
            {
                guard = DIRECTION_MAP[guard.first];
            }
            else
            {
                layout.at(curr_loc) = '.';
                layout.at(next_loc) = guard.first;
                if (layout_history.at(next_loc) != '.')
                {
                    layout_history.at(next_loc) = '+';
                }
                else
                {
                    layout_history.at(next_loc) = guard.first;
                }
                locations_visited.insert({guard.first, next_loc});
                curr_loc = next_loc;
            }
        }
        std::cout << "Layout history: \n" << layout_history << std::endl;
        return locations_visited;
    }

    bool forms_loop(
        utils::Vec2D<long long> current_location,
        const utils::Array2D<char>& layout,
        std::set<std::pair<char, utils::Vec2D<long long>>> visited_locations){
        return false;
    }

    utils::Array2D<char> get_layout(const utils::InputReader& input_reader)
    {
        utils::Array2D<char> get_layout{input_reader.string_vector()};
        return get_layout;
    }

    long long Day6Solution::solve_part_a(const utils::InputReader input_reader)
    {
        const utils::Array2D<char> layout = get_layout(input_reader);
        std::cout << layout << std::endl;
        const auto directions_and_locations = directions_and_locations_covered_by_guard(layout);
        std::set<utils::Vec2D<long long>> locations_visited{};
        for (auto location : directions_and_locations | std::views::values)
        {
            locations_visited.insert(location);
        }
        return static_cast<long long>(locations_visited.size());
    }

    long long Day6Solution::solve_part_b(const utils::InputReader input_reader)
    {
        const utils::Array2D<char> layout = get_layout(input_reader);
        std::cout << layout << std::endl;
        const auto directions_and_locations = directions_and_locations_covered_by_guard(layout);
        return 1;
    }
}
