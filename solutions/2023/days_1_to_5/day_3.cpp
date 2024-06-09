#include "day_3.h"

namespace solutions {

    long long day_3_part_a(const utils::InputReader& input)
    {
        auto input_vector = input.string_vector();
        utils::Array2D<char> schematic{input_vector};
        std::cout << schematic << std::endl;
        std::vector<PartNumber> parts{};
        std::vector<CharNode> nums{};
        for (auto row : schematic.node_row_iter()) {
            for (auto node : row) {
                if (isdigit(node.value)) {
                    nums.emplace_back(node);
                }
                else {
                    if (!nums.empty()) {
                        parts.emplace_back(nums, schematic);
                        nums.clear();
                    }
                }
            }
            if (!nums.empty()) {
                parts.emplace_back(nums, schematic);
                nums.clear();
            }
        }

        std::cout << parts << std::endl;

        std::vector<PartNumber> engine_parts;
        std::copy_if(
                parts.begin(),
                parts.end(),
                std::back_inserter(engine_parts),
                [](auto part) { return part.is_engine; }
        );

        std::cout << "Engine parts:" << engine_parts << std::endl;
        size_t sum_of_parts = std::accumulate(
                engine_parts.begin(),
                engine_parts.end(),
                0,
                [](size_t total, PartNumber part) {
                    return total + part.part_number;
                }
        );

        std::vector<int> engine_numbers {};
        for (auto part: engine_parts){
            engine_numbers.emplace_back(part.part_number);
        }
        std::cout << "All engine numbers: " << std::endl << engine_numbers << std::endl;

        return sum_of_parts;
    }

    long long day_3_part_b(const utils::InputReader& input)
    {
        return 0;
    }
}