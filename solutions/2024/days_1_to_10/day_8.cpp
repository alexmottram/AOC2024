#include "day_8.h"

namespace solutions
{
    std::set<utils::Vec2D<size_t>> antinode_location_for_pair(
        utils::Vec2D<size_t> first_antenna,
        utils::Vec2D<size_t> second_antenna,
        const utils::Array2D<char>& town_map
    )
    {
        std::set<utils::Vec2D<size_t>> antinode_locations{};
        const auto first_antenna_long = static_cast<utils::Vec2D<long long>>(first_antenna);
        const auto second_antenna_long = static_cast<utils::Vec2D<long long>>(second_antenna);

        const auto first_antinode = first_antenna_long + (first_antenna_long - second_antenna_long);
        const auto second_antinode = second_antenna_long + (second_antenna_long - first_antenna_long);

        if (town_map.vector_in_array(first_antinode))
        {
            antinode_locations.insert(static_cast<utils::Vec2D<size_t>>(first_antinode));
        }

        if (town_map.vector_in_array(second_antinode))
        {
            antinode_locations.insert(static_cast<utils::Vec2D<size_t>>(second_antinode));
        }
        std::cout << "Antennas: " << first_antenna_long << ", "  << second_antenna_long
        << " produced antinodes: " << first_antinode << ", " << second_antinode << std::endl;
        return antinode_locations;
    }
    std::set<utils::Vec2D<size_t>> repeating_antinode_location_for_pair(
          utils::Vec2D<size_t> first_antenna,
          utils::Vec2D<size_t> second_antenna,
          const utils::Array2D<char>& town_map
      )
    {
        std::set<utils::Vec2D<size_t>> antinode_locations{};
        auto first_antenna_long = static_cast<utils::Vec2D<long long>>(first_antenna);
        auto second_antenna_long = static_cast<utils::Vec2D<long long>>(second_antenna);
        const auto antenna_separation = first_antenna_long - second_antenna_long;

        // auto first_dir_antinodes = first_antenna_long + antenna_separation;
        // auto second_dir_antinodes = second_antenna_long - antenna_separation;

        while (town_map.vector_in_array(first_antenna_long))
        {
            antinode_locations.insert(static_cast<utils::Vec2D<size_t>>(first_antenna_long));
            first_antenna_long = first_antenna_long + antenna_separation;
        }

        while (town_map.vector_in_array(second_antenna_long))
        {
            antinode_locations.insert(static_cast<utils::Vec2D<size_t>>(second_antenna_long));
            second_antenna_long = second_antenna_long - antenna_separation;
        }

        return antinode_locations;
    }

    std::set<utils::Vec2D<size_t>> find_antinode_locations(
        const char& character, utils::Array2D<char> town_map, const bool repeater=false
    )
    {
        std::set<utils::Vec2D<size_t>> antinode_locations{};
        auto antenna_locations = town_map.find(character);
        std::vector<utils::Vec2D<size_t>> antenna_vector;
        std::ranges::transform(
            antenna_locations,
            std::inserter(antenna_vector, antenna_vector.end()),
            [](auto node) { return node.vector(); }
        );
        std::cout << "Antenna locations for char '" << character
            << "' are: \n" << antenna_vector << std::endl;

        std::set<std::pair<utils::Vec2D<size_t>, utils::Vec2D<size_t>>> antenna_pairs;
        for (auto first_antenna_idx{0};
             first_antenna_idx < antenna_vector.size();
             first_antenna_idx++)
        {
            for (auto second_antenna_idx{first_antenna_idx+1};
                 second_antenna_idx < antenna_vector.size();
                 second_antenna_idx++)
            {
                antenna_pairs.insert({antenna_vector[first_antenna_idx], antenna_vector[second_antenna_idx]});
            }
        }

        std::cout << "Antenna pairs for char '" << character
            << "' are: \n" << antenna_pairs << std::endl;

        for (auto [first_antenna, second_antenna] : antenna_pairs)
        {
            std::set<utils::Vec2D<size_t>> antenna_pair_antinodes {};
            if (repeater)
            {
                antenna_pair_antinodes = repeating_antinode_location_for_pair(first_antenna, second_antenna, town_map);
            } else
            {
                antenna_pair_antinodes = antinode_location_for_pair(first_antenna, second_antenna, town_map);
            }

            antinode_locations.insert(antenna_pair_antinodes.begin(), antenna_pair_antinodes.end());
        }

        std::cout << "Antinode locations for char '" << character
            << "' are: \n" << antinode_locations << std::endl;
        return antinode_locations;
    }

    auto unique_locations_of_antinodes(
        const utils::Array2D<char>& town_map,
        const bool repeater = false) -> std::set<utils::Vec2D<size_t>>
    {
        std::set<char> character_set{};
        std::ranges::copy(town_map, std::inserter(character_set, character_set.begin()));
        character_set.erase('.');
        std::cout << "Unique characters in town map: " << character_set << std::endl;

        std::set<utils::Vec2D<size_t>> antinode_locations{};
        for (auto character : character_set)
        {
            auto character_antinodes = find_antinode_locations(character, town_map, repeater);
            antinode_locations.insert(character_antinodes.begin(), character_antinodes.end());
        }
        std::cout << "Number of antinode locations found: " << antinode_locations.size() << std::endl;
        return antinode_locations;
    }

    long long Day8Solution::solve_part_a(const utils::InputReader input_reader)
    {
        const utils::Array2D<char> town_map{input_reader.string_vector()};
        std::cout << "Town map: \n" << town_map << std::endl;
        const auto unique_locations = unique_locations_of_antinodes(town_map);
        auto town_map_with_locations = town_map;
        for (const auto location : unique_locations)
        {
            town_map_with_locations.at(location) = '+';
        }
        std::cout << "Final town map with antinode locations marked: \n" << town_map_with_locations << std::endl;
        return static_cast<long long>(unique_locations.size());
    }

    long long Day8Solution::solve_part_b(const utils::InputReader input_reader)
    {
        const utils::Array2D<char> town_map{input_reader.string_vector()};
        std::cout << "Town map: \n" << town_map << std::endl;
        const auto unique_locations = unique_locations_of_antinodes(town_map, true);
        auto town_map_with_locations = town_map;
        for (const auto location : unique_locations)
        {
            town_map_with_locations.at(location) = '+';
        }
        std::cout << "Final town map with antinode locations marked: \n" << town_map_with_locations << std::endl;
        return static_cast<long long>(unique_locations.size());
    }
}
