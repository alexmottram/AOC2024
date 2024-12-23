#pragma once

#include <utility>

#include "../../../utils/utils.h"
#include "../common_header.h"

namespace solutions
{
    class Day23Solution final : public utils::SolutionTemplate<long long>
    {
    public:
        Day23Solution(): SolutionTemplate(
            2024,
            23,
            7,
            1,
            1,
            1
        )
        {
        }

        long long solve_part_a(const utils::InputReader& input_reader) override;
        long long solve_part_b(const utils::InputReader& input_reader) override;
    };

    struct LanPC
    {
        std::string label{};
        std::set<std::string> linked_pcs{};

        LanPC() = default;

        explicit LanPC(std::string label): label(std::move(label)), linked_pcs({})
        {
        };

        void link_pcs(LanPC& pc_other)
        {
            linked_pcs.insert(pc_other.label);
            pc_other.linked_pcs.insert(label);
        }

        friend bool operator <(const LanPC& lp_a, const LanPC& lp_b)
        {
            return lp_a.label < lp_b.label;
        }

        friend std::ostream& operator <<(std::ostream& os, const LanPC& lp)
        {
            os << "LanComputer(label=" << lp.label << " linked_pcs=";
            for (const auto& linked_pc : lp.linked_pcs)
            {
                os << linked_pc << " ,";
            }
            os << ")";
            return os;
        }
    };
}
