#include "day_22.h"

namespace solutions
{
    typedef std::list<int> MonkeyInstructions;
    size_t MODULO_VALUE = 16777216;

    std::vector<size_t> get_buyers_starting_secrets(const utils::InputReader& input_reader)
    {
        std::vector<size_t> secrets{};
        auto vec_input_str = input_reader.string_vector();
        for (auto line : vec_input_str)
        {
            secrets.push_back(utils::string_to_type<long long>(line));
        }
        return secrets;
    }

    size_t process_secret(const size_t& secret_in, size_t command_number)
    {
        auto pre_mix_and_prune{0};
        switch (command_number)
        {
        case 1:
            pre_mix_and_prune = secret_in * 64;
            break;
        case 2:
            pre_mix_and_prune = secret_in / 32;
            break;
        case 3:
            pre_mix_and_prune = secret_in * 2048;
            break;
        default:
            throw std::runtime_error("Unknown command_number.");
        }
        auto mixed_stage = pre_mix_and_prune ^ secret_in;
        auto pruned_stage = mixed_stage % MODULO_VALUE;
        return pruned_stage;
    }

    long long Day22Solution::solve_part_a(const utils::InputReader& input_reader)
    {
        std::vector<size_t> starting_secrets = get_buyers_starting_secrets(input_reader);
        std::vector<size_t> secrets = starting_secrets;
        std::cout << "Starting secrets: " << starting_secrets << std::endl;

        constexpr size_t num_iterations{2000};

        for (auto i{1}; i <= num_iterations; i++)
        {
            std::cout << "Processing iteration number: " << i << std::endl;
            for (auto& val : secrets)
            {
                const auto new_val = process_secret(val, 1);
                const auto new_val_2 = process_secret(new_val, 2);
                const auto new_val_3 = process_secret(new_val_2, 3);
                val = new_val_3;
            }
            std::cout << "Secrets after iteration: " << secrets << std::endl;
        }

        std::vector<long long> negative_values{};


        std::cout << "Final result: " << secrets << std::endl;
        size_t total{0};
        for (const auto x : secrets)
        {
            total += x;
        }
        std::cout << "Total sum is: " << total << std::endl;
        return static_cast<long long>(total);
    }

    size_t last_digit(const size_t number)
    {
        const std::string as_str = std::to_string(number);
        std::string final_digit_as_char{as_str.back()};
        const auto final_digit_as_num = utils::string_to_type<size_t>(std::string(final_digit_as_char));
        return final_digit_as_num;
    }

    long long Day22Solution::solve_part_b(const utils::InputReader& input_reader)
    {
        const std::vector<size_t> starting_secrets = get_buyers_starting_secrets(input_reader);
        std::vector<size_t> secrets = starting_secrets;
        std::vector<std::vector<int>> prices{};
        std::cout << "Starting secrets: " << starting_secrets << std::endl;

        constexpr size_t num_iterations{2000};
        std::map<MonkeyInstructions, size_t> change_to_value_map;
        std::map<MonkeyInstructions, std::set<size_t>> change_hit_already_map;
        std::vector<MonkeyInstructions> monkey_instructions{};

        for (auto i{0}; i < secrets.size(); i++)
        {
            monkey_instructions.emplace_back();
            prices.emplace_back();
        }

        for (auto i{1}; i <= num_iterations; i++)
        {
            std::cout << "Processing iteration number: " << i << std::endl;
            for (auto monkey_num{0}; monkey_num < secrets.size(); monkey_num++)
            {
                auto& val = secrets.at(monkey_num);
                auto& price_history = prices.at(monkey_num);
                auto& curr_monkey_instruction = monkey_instructions.at(monkey_num);

                const auto new_val = process_secret(val, 1);
                const auto new_val_2 = process_secret(new_val, 2);
                const auto next_secret = process_secret(new_val_2, 3);

                const auto last_price = last_digit(val);
                const auto next_price = last_digit(next_secret);

                price_history.emplace_back(next_secret);

                curr_monkey_instruction.emplace_back(next_price - last_price);

                if (curr_monkey_instruction.size() > 4)
                {
                    curr_monkey_instruction.pop_front();
                }

                if (curr_monkey_instruction.size() == 4)
                {
                    if (!change_hit_already_map.contains(curr_monkey_instruction))
                    {
                        change_hit_already_map[curr_monkey_instruction] = {};
                    }

                    auto hit_sets = change_hit_already_map[curr_monkey_instruction];
                    if (!hit_sets.contains(monkey_num))
                    {
                        change_hit_already_map[curr_monkey_instruction].insert(monkey_num);
                        if (change_to_value_map.contains(curr_monkey_instruction))
                        {
                            change_to_value_map[curr_monkey_instruction] += next_price;
                        }
                        else
                        {
                            change_to_value_map[curr_monkey_instruction] = next_price;
                        }
                    }
                }
                val = next_secret;
            }
            // std::cout << "Secrets after iteration: " << secrets << std::endl;
            // std::cout << "Monkey instructions after iteration: " << monkey_instructions << std::endl;
        }

        size_t max_score{0};
        std::list<int> winning_instructions{};
        for (const auto& [instructions, score] : change_to_value_map)
        {
            if (score > max_score)
            {
                max_score = score;
                winning_instructions = instructions;
            }
        }
        std::cout << "Winning instructions are: " << winning_instructions << " with score: " << max_score << std::endl;
        return static_cast<long long>(max_score);
    }
}
