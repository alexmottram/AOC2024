#pragma once

#include "precompile_header.h"

const std::filesystem::path BASE_PATH = std::filesystem::current_path();
const std::filesystem::path INPUT_DATA_FOLDER = "input_data";
const std::filesystem::path TEST_DATA_FOLDER = "test_data";

namespace utils {
    class InputReader {
    public:
        const int day;
        bool test_data;
        std::filesystem::path input_data_filename;
        std::filesystem::path input_data_path;
        std::filesystem::path test_data_filename;
        std::filesystem::path test_data_path;

        // TODO -> add a constructor that doesn't required base_path using the default value instead
        InputReader(int day, bool test_data, std::filesystem::path base_path);

        [[nodiscard]] std::filesystem::path input_data_fullpath() const;

        [[nodiscard]] std::filesystem::path test_data_fullpath() const;

        [[nodiscard]] std::vector<std::string> input_vector() const;

        [[nodiscard]] std::vector<std::string> test_vector() const;

        [[nodiscard]] std::vector<std::string> string_vector() const;

    };
}