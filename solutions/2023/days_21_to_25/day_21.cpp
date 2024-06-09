#include "day_21.h"

namespace solutions {

    long long day_21_part_a(const utils::InputReader& input, size_t max_steps)
    {
        std::vector<std::string> data_in = input.string_vector();
        utils::Array2D<char> garden{data_in};
        std::cout << garden << std::endl;

        size_t step{0};

        std::set<utils::Array2D<char>::NodeType> touched_locs = garden.find('S');
        std::set<utils::Array2D<char>::NodeType> current_locs = touched_locs;
        std::set<utils::Array2D<char>::NodeType> found_locs{};

        while (step<=max_steps) {
            std::set<utils::Array2D<char>::NodeType> next_locs{};
            if (step%2==0) {
                for (auto loc : current_locs) {
                    if (loc.value!='#') {
                        loc.value = 'O';
                        found_locs.emplace(loc);
                    }
                }
            }

            for (auto loc : current_locs) {
                auto adjacent_nodes = garden.adjacent(loc.x, loc.y, false);
                for (auto new_loc : adjacent_nodes) {
                    if (!touched_locs.contains(new_loc) && (new_loc.value != '#')) {
                        next_locs.insert(new_loc);
                    }
                }
            }

            std::cout << garden << std::endl;
            current_locs = next_locs;
            step++;
        }

        return found_locs.size();
    }

    long long day_21_part_b(const utils::InputReader& input)
    {
        std::vector<std::string> data_in = input.string_vector();
        utils::Array2D<char> garden{data_in};
        std::cout << garden << std::endl;
        return 0;
    }
}
