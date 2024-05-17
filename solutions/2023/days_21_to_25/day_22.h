#pragma once

#include "../../../utils/utils.h"

namespace solutions {

    struct Brick {
        typedef int int_type;
        typedef utils::Vec3D<int_type> BlockLocation;

        std::set<BlockLocation> blocks{};

        Brick(std::set<BlockLocation> blocks);
        Brick(const std::string& str);

        friend std::ostream& operator<<(std::ostream& os, const Brick& b);
        friend bool operator==(const Brick& lhs, const Brick& rhs);

        bool intersects(const Brick& other);

        void move_brick(const BlockLocation& move);

        int_type lowest_point() const;

        bool can_fall(std::vector<Brick> other_bricks){
            BlockLocation fall_one {0,0,-1};
            std::set<BlockLocation> new_locs{};
            for (auto& loc : blocks) {
                new_locs.emplace(loc+fall_one);
            }
            Brick new_brick {new_locs};

            if (new_brick.lowest_point()<1){
                return false;
            }

            for (auto other_brick: other_bricks){
                if (new_brick.intersects(other_brick)){
                    return false;
                }
            }
            return true;
        }

    };

    long long day_22_part_a(const utils::InputReader& input);
//    long long day_22_part_b(const utils::InputReader& input);
}