#pragma once

#include "../../../utils/utils.h"

namespace solutions {
    using CharNode = utils::NodeWrapper<size_t, char>;
    using CharArray = utils::Array2D<char>;

    struct PartNumber {
        std::vector<CharNode> nodes{};
        bool is_engine {};
        int part_number {};

        PartNumber(std::vector<CharNode> nodes, CharArray schematic)
                :nodes(nodes), is_engine(false), part_number(0)
        {
            // Calculate part number
            std::string number_str{};
            for (auto node : nodes) {
                number_str.push_back(node.value);
            }
            part_number = utils::string_to_type<size_t>(number_str);

            // Calculate if it is an engine
            std::set<CharNode> adjacent_locs{};
            for (auto node : nodes) {
                auto adj_locs = schematic.adjacent(node, true);
                adjacent_locs.insert(adj_locs.begin(), adj_locs.end());
            }

            for (auto node : adjacent_locs) {
                if (!isdigit(node.value) && node.value!='.') {
                    is_engine = true;
                    return;
                }
            }
        }

        friend std::ostream& operator<<(std::ostream& os, const PartNumber& pn)
        {

            os << "PartNumber{" << pn.part_number;
            os << ", is_engine: " << pn.is_engine << "}";
            return os;
        }

    };

    long long day_3_part_a(const utils::InputReader& input);

    long long day_3_part_b(const utils::InputReader& input);
}