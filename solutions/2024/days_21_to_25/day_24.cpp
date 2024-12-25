#include "day_24.h"

namespace solutions
{
    typedef std::set<std::set<std::string>> DoubleSetStrings;
    constexpr size_t NUMBER_OF_BITS{60};

    std::map<std::string, size_t> get_input_wires(const utils::InputReader& input_reader)
    {
        std::map<std::string, size_t> wires;
        for (const auto& line : input_reader.string_vector())
        {
            if (line.empty()) { break; }
            auto split_line = utils::split_string(line, ":", true);
            const auto bit_val = utils::string_to_type<int>(split_line.at(1));
            wires[split_line.at(0)] = bit_val;
        }
        return wires;
    }

    std::set<BinaryOperation> get_binary_operations(const utils::InputReader& input_reader)
    {
        std::set<BinaryOperation> operations;
        bool process_lines{false};

        for (const auto& line : input_reader.string_vector())
        {
            if (process_lines)
            {
                operations.emplace(line);
            }

            if (line.empty())
            {
                process_lines = true;
            }
        }
        return operations;
    }

    std::map<std::string, size_t> resolve_logic(

        const std::map<std::string, size_t>& wire_inputs,
        const std::set<BinaryOperation>& operations
    )
    {
        std::map<std::string, size_t> all_wires{};
        std::ranges::copy(wire_inputs, std::inserter(all_wires, all_wires.begin()));
        auto reducing_operations = operations;

        while (!reducing_operations.empty())
        {
            std::set<BinaryOperation> next_reducing_operations;
            for (const auto& operation : reducing_operations)
            {
                if (all_wires.contains(operation.input_wire_a) and all_wires.contains(operation.input_wire_b))
                {
                    auto val_a = all_wires[operation.input_wire_a];
                    auto val_b = all_wires[operation.input_wire_b];
                    all_wires[operation.output_wire] = operation.perform_operation(val_a, val_b, true);
                }
                else
                {
                    next_reducing_operations.insert(operation);
                }
            }
            reducing_operations = next_reducing_operations;
        }
        return all_wires;
    }

    size_t bit_string_to_decimal(const std::string& bit_string)
    {
        const size_t decimal_val = strtoull(bit_string.c_str(), nullptr, 2);
        return decimal_val;
    }

    std::string decimal_to_bit_string(const size_t& decimal_val)
    {
        std::string binary = std::bitset<NUMBER_OF_BITS>(decimal_val).to_string();
        return binary;
    }

    std::string wire_creation(const size_t num, const char start_char)
    {
        if (num < 10)
        {
            std::stringstream num_ss{};
            num_ss << start_char << "0" << num;
            return num_ss.str();
        }

        std::stringstream num_ss{};
        num_ss << start_char << num;
        return num_ss.str();
    }

    size_t wire_to_number(const std::string& wire_in)
    {
        return stoi(wire_in.substr(1, wire_in.size() - 1));
    }

    std::string get_max_z_wire(const std::map<std::string, BinaryOperation>& output_to_operation_map)
    {
        size_t max_z_val{0};
        std::string max_z_wire{};
        for (const auto& key : output_to_operation_map | std::views::keys)
        {
            if (*(key.begin()) == 'z')
            {
                if (const auto this_z_val = wire_to_number(key); this_z_val > max_z_val)
                {
                    max_z_val = this_z_val;
                    max_z_wire = key;
                }
            }
        }
        return max_z_wire;
    }

    size_t create_decimal_from_wires(const std::map<std::string, size_t>& wires)
    {
        std::map<std::string, size_t> z_wires{};
        std::ranges::copy_if(
            wires,
            std::inserter(z_wires, z_wires.begin()),
            [](auto i) { return *(i.first.begin()) == 'z'; }
        );
        std::cout << "Z starting wires are:" << z_wires << std::endl;
        std::string binary_string{};

        for (const auto v : z_wires | std::views::values)
        {
            binary_string = std::to_string(v) + binary_string;
        }
        const auto decimal_val = bit_string_to_decimal(binary_string);
        std::cout << "Binary string: " << binary_string
            << " which is in decimal: " << decimal_val << std::endl;

        return z_wires.size();
    }

    std::set<std::string> get_wires_in_tree(
        const std::set<std::string>& end_wires,
        const std::map<std::string, BinaryOperation>& output_to_operation_map,
        const std::set<std::string>& wildcards
    )
    {
        std::set<std::string> rolling_wires{end_wires};
        std::map<std::string, BinaryOperation> reduced_map{};
        bool wild_cards_hit {false};
        while (!rolling_wires.empty())
        {
            std::set<std::string> next_wires{};
            for (const auto& curr_wire : rolling_wires)
            {
                if (wild_cards_hit==false and wildcards.contains(curr_wire))
                {
                    auto wildcard_copy = wildcards;
                    wildcard_copy.erase(curr_wire);
                    std::ranges::copy_if(
                        wildcard_copy,
                        std::inserter(next_wires, next_wires.begin()),
                        [reduced_map](auto i) { return !reduced_map.contains(i); }
                    );
                    wild_cards_hit = true;
                }
                if (output_to_operation_map.contains(curr_wire))
                {
                    const auto& curr_operation = output_to_operation_map.at(curr_wire);
                    next_wires.insert(curr_operation.input_wire_a);
                    next_wires.insert(curr_operation.input_wire_b);
                    reduced_map[curr_wire] = curr_operation;
                }
                else
                {
                    reduced_map[curr_wire] = {};
                }
            }
            rolling_wires = next_wires;
        }
        std::set<std::string> connected_wires{};
        std::ranges::transform(
            reduced_map,
            std::inserter(connected_wires, connected_wires.end()),
            [](auto pair) { return pair.first; }
        );
        // std::cout << "Connected points to end wire: " << end_wire << " are: " << reduced_map << std::endl;
        return connected_wires;
    }

    std::set<std::string> find_missing_inputs(
        const size_t output_num,
        const std::map<std::string, BinaryOperation>& output_to_operation_map,
        const std::set<std::string>& wildcards
    )
    {
        std::set<std::string> output_wires{wire_creation(output_num, 'z')};
        std::set<std::string> input_wires_required{};

        for (auto i{0}; i < output_num; ++i) //TODO -> drop to < for addition operation
        {
            input_wires_required.insert(wire_creation(i, 'x'));
            input_wires_required.insert(wire_creation(i, 'y'));
            output_wires.insert(wire_creation(i, 'z'));
        }

        const auto wires_in_tree = get_wires_in_tree(output_wires, output_to_operation_map, wildcards);
        std::set<std::string> missing_inputs{};

        for (const auto& wire : input_wires_required)
        {
            if (!wires_in_tree.contains(wire))
            {
                missing_inputs.insert(wire);
            }
        }
        // std::cout << "Missing inputs for output: " << output_wire
        //     << " are: " << missing_inputs << std::endl;
        return missing_inputs;
    }

    DoubleSetStrings get_all_combinations(const std::set<std::string>& wires, const int num_in_combination)
    {
        const auto wire_size = wires.size();
        std::vector<std::string> wire_vector;
        std::ranges::copy(wires, std::back_inserter(wire_vector));

        std::string bitmask(num_in_combination, 1); // K leading 1's
        bitmask.resize(wire_size, 0); // N-K trailing 0's

        // print integers and permute bitmask
        DoubleSetStrings combinations{};
        do
        {
            std::set<std::string> next_line{};
            for (int i = 0; i < wire_size; ++i) // [0..N-1] integers
            {
                if (bitmask[i]) next_line.insert(wire_vector.at(i));;
            }
            combinations.insert(next_line);
        }
        while (std::ranges::prev_permutation(bitmask).found);
        return combinations;
    }

    bool check_for_missing_inputs_with_bonus_wires(
        const std::map<std::string, BinaryOperation>& output_to_operation,
        const std::set<std::string>& wildcard_wires
    )
    {
        std::cout << "Processing for wild card wires: " << wildcard_wires << std::endl;
        const auto max_z_wire = get_max_z_wire(output_to_operation);
        const auto max_z_num = wire_to_number(max_z_wire);
        std::cout << "Maximum z value found is: " << max_z_wire << " with number: " << max_z_num << std::endl;

        for (auto i{1}; i <= max_z_num; i++)
        {
            if (auto val = find_missing_inputs(i, output_to_operation, wildcard_wires); !val.empty())
            {
                std::cout << "Failed at numeric position " << i << " from missing inputs " << val << std::endl <<
                    std::endl;
                return false;
            }
        }
        return true;
    }

    size_t score_wildcard_combo(
        const std::map<std::string, BinaryOperation>& output_to_operation,
        const std::set<std::string>& wildcard_wires,
        const size_t max_z_num
    )
    {
        std::cout << "Scoring wild card wires: " << wildcard_wires << std::endl;
        for (auto i{1}; i < max_z_num; i++)
        {
            auto missing_inputs = find_missing_inputs(i, output_to_operation, wildcard_wires);
            if (!missing_inputs.empty())
            {
                std::cout << "Failed at numeric position " << i << " from missing inputs "
                    << missing_inputs << std::endl << std::endl;
                return i;
            }
        }
        return max_z_num;
    }

    long long Day24Solution::solve_part_a(const utils::InputReader& input_reader)
    {
        auto input_wires = get_input_wires(input_reader);
        auto binary_operations = get_binary_operations(input_reader);
        std::cout << "Input wires: \n" << input_wires << std::endl;
        std::cout << "Binary operations: \n" << binary_operations << std::endl;
        auto all_wires = resolve_logic(input_wires, binary_operations);
        std::cout << "All wires are: \n" << all_wires << std::endl;
        auto final_number = create_decimal_from_wires(all_wires);
        return 0;
    }

    long long Day24Solution::solve_part_b(const utils::InputReader& input_reader)
    {
        auto input_wires = get_input_wires(input_reader);
        auto binary_operations = get_binary_operations(input_reader);
        std::cout << "Input wires: \n" << input_wires << std::endl;
        std::cout << "Binary operations: \n" << binary_operations << std::endl;

        std::map<std::string, BinaryOperation> output_to_operation{};
        std::set<std::string> wires_for_switching{};
        for (const auto& operation : binary_operations)
        {
            output_to_operation[operation.output_wire] = operation;
            wires_for_switching.insert(operation.output_wire);
        }

        const auto all_combinations = get_all_combinations(wires_for_switching, 2);
        std::cout << "All combinations are: \n" << all_combinations << std::endl;

        const auto max_z_wire = get_max_z_wire(output_to_operation);
        const auto max_z_num = wire_to_number(max_z_wire);

        std::set<std::set<std::string>> potential_solutions{};
        for (const auto& wildcard_combo : all_combinations)
        {
            const auto wild_card_score = score_wildcard_combo(output_to_operation, wildcard_combo, max_z_num);
            std::cout << "Wild card score for wilds cards: " << wildcard_combo << " is: " << wild_card_score << std::endl;
        }
        std::cout << "All valid wildcard combos: " << potential_solutions << std::endl;
        return 0;
    }
}
