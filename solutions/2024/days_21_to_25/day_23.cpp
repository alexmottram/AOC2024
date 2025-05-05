#include "day_23.h"

namespace solutions
{
    size_t LOOP_SIZE{3};

    std::map<std::string, LanPC> create_lan_pcs(const utils::InputReader& input_reader)
    {
        std::map<std::string, LanPC> lan_pcs{};

        for (const auto& line : input_reader.string_vector())
        {
            auto pc_strings = utils::split_string(line, "-", true);

            const auto& pc_a = pc_strings.at(0);
            const auto& pc_b = pc_strings.at(1);

            if (!lan_pcs.contains(pc_a))
            {
                const LanPC lan_pc_a{pc_a};
                lan_pcs[pc_a] = lan_pc_a;
            }
            if (!lan_pcs.contains(pc_b))
            {
                const LanPC lan_pc_b{pc_b};
                lan_pcs[pc_b] = lan_pc_b;
            }
        }

        for (const auto& line : input_reader.string_vector())
        {
            auto pc_strings = utils::split_string(line, "-", true);

            const auto& pc_a = pc_strings.at(0);
            const auto& pc_b = pc_strings.at(1);
            auto& lan_pc_a = lan_pcs.at(pc_a);
            auto& lan_pc_b = lan_pcs.at(pc_b);
            lan_pc_a.link_pcs(lan_pc_b);
        }

        return lan_pcs;
    }

    std::set<std::string> get_all_linked_locations(
        const std::set<std::string>& current_locations,
        const std::map<std::string, LanPC>& lan_pc_map
    )
    {
        std::set<std::string> linked_locations{};
        for (const auto& curr_loc : current_locations)
        {
            auto linked_locs = lan_pc_map.at(curr_loc);
            for (const auto& loc : linked_locs.linked_pcs)
            {
                if (!current_locations.contains(loc))
                {
                    linked_locations.insert(loc);
                }
            }
        }
        return linked_locations;
    }

    long long Day23Solution::solve_part_a(const utils::InputReader& input_reader)
    {
        auto all_linked_pcs = create_lan_pcs(input_reader);
        std::set<std::set<std::string>> matching_lan_pcs_links{};

        for (const auto& [label, lan_pc] : all_linked_pcs)
        {
            std::cout << "Original linked Lan PCs " << label << ": " << lan_pc << std::endl;
            if (label.at(0) == 't')
            {
                size_t link_num{0};
                std::vector<std::vector<std::string>> rolling_linked_pcs{{label}};
                while (link_num < LOOP_SIZE)
                {
                    std::vector<std::vector<std::string>> next_linked_pcs{};
                    for (const auto& vec_labels : rolling_linked_pcs)
                    {
                        for (const auto& next_pc : all_linked_pcs[vec_labels.back()].linked_pcs)
                        {
                            auto copy_curr_labels = vec_labels;
                            copy_curr_labels.push_back(next_pc);
                            next_linked_pcs.push_back(copy_curr_labels);
                        }
                    }
                    rolling_linked_pcs = next_linked_pcs;
                    link_num++;
                }

                // std::cout << "All pc label combinations: \n" << rolling_linked_pcs;
                std::set<std::set<std::string>> set_of_links{};

                for (auto vec_labels : rolling_linked_pcs)
                {
                    if (vec_labels.front() == vec_labels.back())
                    {
                        std::set<std::string> set_of_labels{};
                        std::copy(
                            vec_labels.begin(),
                            vec_labels.end() - 1,
                            std::inserter(set_of_labels, set_of_labels.begin())
                        );
                        set_of_links.insert(set_of_labels);
                    }
                }
                std::cout << "Linked PC combinations: " << set_of_links << std::endl << std::endl;
                matching_lan_pcs_links.insert(set_of_links.begin(), set_of_links.end());
            }
        }
        const auto size_ll = static_cast<long long>(matching_lan_pcs_links.size());
        std::cout << "Number of linked pc sets is: " << size_ll << std::endl;
        std::cout << "Matching links: " << matching_lan_pcs_links << std::endl;
        return size_ll;
    }

    long long Day23Solution::solve_part_b(const utils::InputReader& input_reader)
    {
        auto all_linked_pcs = create_lan_pcs(input_reader);
        std::set<std::set<std::string>> all_largest_networks{};

        for (const auto& [label, lan_pc] : all_linked_pcs)
        {
            std::cout << "Original linked Lan PCs " << label << ": " << lan_pc << std::endl;
            std::set<std::set<std::string>> rolling_location_sets{{label}};
            std::set<std::set<std::string>> all_location_sets{{label}};

            while (!rolling_location_sets.empty())
            {
                std::set<std::set<std::string>> next_location_sets{};

                for (const auto& current_network : rolling_location_sets)
                {
                    auto linked_labels = get_all_linked_locations(
                        current_network,
                        all_linked_pcs
                    );

                    for (const auto& next_loc : linked_labels)
                    {
                        // Check that all process_set locations are in
                        bool all_connected_network{true};
                        for (const auto& check_loc : current_network)
                        {
                            const auto& next_loc_linked_pcs = all_linked_pcs[next_loc].linked_pcs;
                            if (!next_loc_linked_pcs.contains(check_loc))
                            {
                                all_connected_network = false;
                            }
                        }
                        // If all are in, add it to the next locations and all locations
                        if (all_connected_network)
                        {
                            auto extended_network = current_network;
                            extended_network.insert(next_loc);
                            next_location_sets.insert(extended_network);
                            all_location_sets.insert(extended_network);
                        }
                    }
                }
                rolling_location_sets = next_location_sets;
            }

            auto largest_set = *std::ranges::max_element(
                all_location_sets,
                [](auto i, auto j) { return i.size() < j.size(); }
            );

            std::cout << "Map of linked pcs after connecting: " << largest_set << std::endl;
            all_largest_networks.insert(largest_set);
        }

        auto absolute_largest_network = *std::ranges::max_element(
            all_largest_networks,
            [](auto i, auto j) { return i.size() < j.size(); }
        );

        const auto size_ll = static_cast<long long>(absolute_largest_network.size());
        std::vector<std::string> largest_network_passcode {absolute_largest_network.begin(), absolute_largest_network.end()};
        std::ranges::sort(largest_network_passcode);
        std::cout << "Number pcs in largest network is : " << size_ll << std::endl;
        std::cout << "Passcode is: " << largest_network_passcode << std::endl;
        return size_ll;
    }
}
