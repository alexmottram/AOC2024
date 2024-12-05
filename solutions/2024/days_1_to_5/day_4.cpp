#include "day_4.h"

namespace solutions
{
    std::map<std::string, std::vector<utils::Vec2D<long long>>> directions{
        {"UP", {{0, 0}, {0, -1}, {0, -2}, {0, -3}}},
        {"DOWN", {{0, 0}, {0, 1}, {0, 2}, {0, 3}}},
        {"LEFT", {{0, 0}, {-1, 0}, {-2, 0}, {-3, 0}}},
        {"RIGHT", {{0, 0}, {1, 0}, {2, 0}, {3, 0}}},
        {"UP-LEFT", {{0, 0}, {-1, -1}, {-2, -2}, {-3, -3}}},
        {"UP-RIGHT", {{0, 0}, {1, -1}, {2, -2}, {3, -3}}},
        {"DOWN-RIGHT", {{0, 0}, {1, 1}, {2, 2}, {3, 3}}},
        {"DOWN-LEFT", {{0, 0}, {-1, 1}, {-2, 2}, {-3, 3}}},
    };

    std::vector<std::map<utils::Vec2D<long long>, char>> cross_mass_types{
        {{{0, 0}, 'A'}, {{1, 1}, 'M'}, {{-1, 1}, 'M'}, {{-1, -1}, 'S'}, {{1, -1}, 'S'}},
        {{{0, 0}, 'A'}, {{1, 1}, 'M'}, {{-1, 1}, 'S'}, {{-1, -1}, 'S'}, {{1, -1}, 'M'}},
        {{{0, 0}, 'A'}, {{1, 1}, 'S'}, {{-1, 1}, 'S'}, {{-1, -1}, 'M'}, {{1, -1}, 'M'}},
        {{{0, 0}, 'A'}, {{1, 1}, 'S'}, {{-1, 1}, 'M'}, {{-1, -1}, 'M'}, {{1, -1}, 'S'}},
    };

    bool is_word_xmas(utils::Array2D<char> word_search, const std::vector<utils::Vec2D<long long>>& vecs)
    {
        const std::vector<char> characters{'X', 'M', 'A', 'S'};

        for (size_t i{0}; i < characters.size(); ++i)
        {
            if (not word_search.vector_in_array(vecs[i]))
            {
                std::cout << "Vector: " << vecs[i] << " out of bounds." << std::endl;
                return false;
            }

            const auto x_val = static_cast<size_t>(vecs[i].x);
            const auto y_val = static_cast<size_t>(vecs[i].y);

            if (word_search.at(x_val, y_val) != characters[i])
            {
                return false;
            }
        }

        return true;
    }

    int xmas_from_location(const utils::Array2D<char>& word_search, const utils::Vec2D<size_t> start_loc)
    {
        std::cout << "Looking at location: " << start_loc << std::endl;
        int xmas_count{0};
        const auto x_val = static_cast<long long>(start_loc.x);
        const auto y_val = static_cast<long long>(start_loc.y);
        utils::Vec2D<long long> pos_neg_start{x_val, y_val};

        for (const auto& [directions, vecs] : directions)
        {
            std::vector<utils::Vec2D<long long>> locations(vecs.size());
            std::cout << "Looking applying " << directions << " vector adjustments: " << vecs << " to: " <<
                pos_neg_start << std::endl;
            std::transform(
                vecs.begin(), vecs.end(), locations.begin(), [pos_neg_start](const utils::Vec2D<long long> vec)
                {
                    return pos_neg_start + vec;
                }
            );
            std::cout << "Searching for xmas in vectors: " << locations.size() << std::endl;

            if (is_word_xmas(word_search, locations))
            {
                xmas_count++;
            }
        }
        return xmas_count;
    }

    long long count_xmas(utils::Array2D<char> word_search)
    {
        const auto all_xs = word_search.find('X');
        long long xmas_count{0};
        for (auto x : all_xs)
        {
            xmas_count += xmas_from_location(word_search, x.vector());
        }
        return xmas_count;
    }


    bool is_cross_mass(utils::Array2D<char>& word_search, const utils::Vec2D<size_t> start_loc)
    {
        std::cout << "Looking at location: " << start_loc << std::endl;
        const auto x_val = static_cast<long long>(start_loc.x);
        const auto y_val = static_cast<long long>(start_loc.y);
        utils::Vec2D<long long> pos_neg_start{x_val, y_val};

        for (auto vector_char_map : cross_mass_types)
        {
            std::vector<std::pair<utils::Vec2D<long long>, char>> locations_and_char_vec(vector_char_map.size());
            std::cout << "Applying " << vector_char_map << " to: " << pos_neg_start << std::endl;
            std::transform(
                vector_char_map.begin(),
                vector_char_map.end(),
                locations_and_char_vec.begin(),
                [pos_neg_start](auto vec_char)
                {
                    utils::Vec2D<long long> pos_vec {pos_neg_start + vec_char.first};
                    std::pair<utils::Vec2D<long long>, char> output_pair {pos_vec, vec_char.second};
                    return output_pair;
                }
            );
            std::cout << "Checking if all locations are in array: " << locations_and_char_vec << std::endl;
            const bool vectors_in_array = std::all_of(
                locations_and_char_vec.begin(),
                locations_and_char_vec.end(),
                [word_search](const auto& vec_char) { return word_search.vector_in_array(vec_char.first); }
            );
            std::cout << "Results: " << vectors_in_array << std::endl;

            if (vectors_in_array)
            {
                const bool matches_cross = std::all_of(
                locations_and_char_vec.begin(),
                locations_and_char_vec.end(),
                    [word_search](auto vec_and_char)
                    {
                        auto val_at = word_search.at(vec_and_char.first.x, vec_and_char.first.y);
                        return val_at == vec_and_char.second;
                    }
                );
                if (matches_cross) { return true; }

            }
        }
        return false;
    }

    long long count_cross_mass(utils::Array2D<char> word_search)
    {
        const auto all_xs = word_search.find('A');
        long long xmas_count{0};
        for (auto x : all_xs)
        {
            if (is_cross_mass(word_search, x.vector()))
            {
                xmas_count++;
            }
        }
        return xmas_count;
    }

    long long day_4_part_a(const utils::InputReader& input)
    {
        const utils::Array2D<char> word_search{input.string_vector()};
        std::cout << word_search << std::endl;
        auto xmas_count = count_xmas(word_search);
        return xmas_count;
    }

    long long day_4_part_b(const utils::InputReader& input)
    {
        const utils::Array2D<char> word_search{input.string_vector()};
        std::cout << word_search << std::endl;
        auto cross_mass_count = count_cross_mass(word_search);
        return cross_mass_count;
    }
}
