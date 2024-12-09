#include "day_9.h"

namespace solutions
{
    std::vector<int> create_memory_vector(const std::string& line)
    {
        std::vector<int> memory_vector{};
        bool is_space{false};
        int memory_label{0};
        int next_memory_label{0};
        for (const auto character : line)
        {
            const int character_int = utils::string_to_type<int>(std::string{character});
            if (is_space)
            {
                memory_label = -1;
                is_space = false;
            }
            else
            {
                memory_label = next_memory_label;
                next_memory_label++;
                is_space = true;
            }
            std::vector<int> next_allocation(static_cast<size_t>(character_int), memory_label);
            std::ranges::copy(next_allocation, std::back_inserter(memory_vector));
        }
        std::cout << "Created memory vector: " << memory_vector << std::endl;
        return memory_vector;
    }

    std::vector<int> create_shifted_memory_vector(const std::vector<int>& memory_vector)
    {
        const auto memory_count = std::ranges::count_if(
            memory_vector,
            [](auto value) { return value != -1; }
        );
        std::cout << "Count of memory values in vector: " << memory_count
            << " with vector length " << memory_vector.size() << std::endl;

        std::vector<int> no_spaces_vector {};
        std::ranges::copy_if(
            memory_vector,
            std::back_inserter(no_spaces_vector),
            [](auto value){return value != -1; }
            );

        size_t backwards_idx {no_spaces_vector.size() - 1};

        std::vector<int> shifted_memory_vector {};

        for (auto forward_idx{0}; forward_idx < memory_count; ++forward_idx)
        {
            if (memory_vector[forward_idx] == -1)
            {
                shifted_memory_vector.push_back(no_spaces_vector[backwards_idx]);
                backwards_idx --;
            } else
            {
                shifted_memory_vector.push_back(memory_vector[forward_idx]);
            }
        }
        std::cout << "Shifted memory vector: " << shifted_memory_vector << std::endl;

        return shifted_memory_vector;
    }

    long long score_memory_vector(const std::vector<int>& memory_vector)
    {
        long long score{0};
        for(auto i{0}; i < memory_vector.size(); ++i)
        {
            score += memory_vector[i]* i;
        }
        return score;
    }

    long long Day9Solution::solve_part_a(const utils::InputReader& input_reader)
    {
        const auto memory_vector = create_memory_vector(input_reader.string_vector()[0]);
        auto shifted_memory_vector = create_shifted_memory_vector(memory_vector);
        auto score = score_memory_vector(shifted_memory_vector);
        return score;
    }

    long long Day9Solution::solve_part_b(const utils::InputReader& input_reader)
    {
        return 0;
    }
}
