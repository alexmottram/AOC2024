#include "day_22.h"

#include <utility>

namespace solutions {
    // Brick implementation
    Brick::Brick(const std::string& str)
    {
        auto split_str = utils::split_string(str, "~", true);
        BlockLocation start_block{split_str.at(0), ","};
        BlockLocation end_block{split_str.at(1), ","};
        blocks.insert(start_block);
        BlockLocation direction{0, 0, 0};
        if (start_block.x!=end_block.x) {
            direction.x = (end_block.x>start_block.x) ? 1 : -1;
        }
        else if (start_block.y!=end_block.y) {
            direction.y = (end_block.y>start_block.y) ? 1 : -1;
        }
        else if (start_block.z!=end_block.z) {
            direction.z = (end_block.z>start_block.z) ? 1 : -1;
        }

        while (start_block!=end_block) {
            start_block += direction;
            blocks.insert(start_block);
        }

    }

    std::ostream& operator<<(std::ostream& os, const Brick& b)
    {
        os << "Brick{len=" << b.blocks.size();
        os << ", min_z=" << b.lowest_point() << "}";
        return os;
    }

    bool Brick::intersects(const Brick& other)
    {
        for (auto loc : blocks) {
            if (other.blocks.contains(loc)) {
                return true;
            }
        }
        return false;
    }

    void Brick::move_brick(const BlockLocation& move)
    {
        std::set<BlockLocation> new_locs{};
        for (auto& loc : blocks) {
            new_locs.emplace(loc+move);
        }
        blocks = new_locs;
    }

    Brick::int_type Brick::lowest_point() const
    {
        auto it = std::min_element(
                blocks.begin(),
                blocks.end(),
                [](const Brick::BlockLocation& lhs, const Brick::BlockLocation& rhs) {
                  return lhs.z<rhs.z;
                }
        );
        if (it!=blocks.end()) {
            return it->z;
        }
        else {
            throw std::runtime_error("No minimum value found.");
        }

    }

    Brick::Brick(std::set<BlockLocation> blocks)
            :blocks(std::move(blocks)) { }

    bool operator==(const Brick& lhs, const Brick& rhs)
    {
        return lhs.blocks==rhs.blocks;
    }

    std::vector<Brick> settle_all_bricks(const std::vector<Brick>& unsorted_bricks)
    {
        // Sort bricks so we start with the bottom bricks
        auto sorted_bricks = unsorted_bricks;
        std::sort(sorted_bricks.begin(), sorted_bricks.end(),
                [](const Brick& lhs, const Brick& rhs) {
                  return lhs.lowest_point()<rhs.lowest_point();
                });

        // Start dropping bricks
        std::vector<Brick> settled_bricks{};
        for (auto brick : sorted_bricks) {
            while (brick.can_fall(settled_bricks)) {
                brick.move_brick({0, 0, -1});
            }
            settled_bricks.push_back(brick);
        }
        return settled_bricks;
    }

    bool
    will_bricks_move(const std::vector<Brick>& all_bricks, const Brick& removed_brick)
    {
        auto minus_removed_brick = all_bricks;
        auto end_it = std::remove(minus_removed_brick.begin(), minus_removed_brick.end(),
                    removed_brick);
        minus_removed_brick.erase(end_it, minus_removed_brick.end());
        // Check each brick from the top to the removed brick to see if they can fall
        for (auto brick : all_bricks) {
            // Create a list of all bricks minus the current brick
            auto other_bricks = minus_removed_brick;
            auto end_it_2 = std::remove(other_bricks.begin(), other_bricks.end(),
                    brick);
            other_bricks.erase(end_it_2, other_bricks.end());
            if (brick==removed_brick) {
                return false;
            }
            else {
                while (brick.can_fall(other_bricks)) {
                    return true;
                }
            }
        }
        return false;
    }

    std::vector<Brick> calculate_unstable_bricks(const std::vector<Brick>& all_bricks)
    {
        std::vector<Brick> unstable_bricks{};
        auto inverse_sorted_bricks = all_bricks;
        std::sort(inverse_sorted_bricks.begin(), inverse_sorted_bricks.end(),
                [](const Brick& lhs, const Brick& rhs) {
                  return lhs.lowest_point()>rhs.lowest_point();
                });

        for (const auto& brick : inverse_sorted_bricks) {
            if (will_bricks_move(inverse_sorted_bricks, brick)) {
                unstable_bricks.push_back(brick);
            }
        }
        return unstable_bricks;
    }

    long long day_22_part_a(const utils::InputReader& input)
    {
        auto lines = input.string_vector();
        std::vector<Brick> all_bricks{};
        for (const auto& line : lines) {
            all_bricks.emplace_back(line);
        }
        std::cout << "Bricks before fall: " << std::endl;
        for (const auto& brick : all_bricks) {
            std::cout << brick << std::endl;
        }

        auto settled_bricks = settle_all_bricks(all_bricks);

        std::cout << "Bricks after fall: " << std::endl;
        for (const auto& brick : settled_bricks) {
            std::cout << brick << std::endl;
        }

        auto unstable_bricks = calculate_unstable_bricks(settled_bricks);

        std::cout << "Unstable bricks: " << std::endl;
        for (const auto& brick : unstable_bricks) {
            std::cout << brick << std::endl;
        }

        return settled_bricks.size() - unstable_bricks.size();
    }
}