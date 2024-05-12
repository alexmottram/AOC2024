#include "input_reader.h"

namespace utils {
    InputReader::InputReader(int day, bool test_data, std::filesystem::path base_path)
            :day(day), test_data(test_data)
    {
        this->input_data_filename = "day_"+std::to_string(day)+".txt";
        this->test_data_filename = "day_"+std::to_string(day)+".txt";
        this->input_data_path = base_path/INPUT_DATA_FOLDER;
        this->test_data_path = base_path/TEST_DATA_FOLDER;

        auto input_exists = std::filesystem::exists(this->input_data_fullpath());
        if (!input_exists) {
            std::ofstream input_file(this->input_data_fullpath());
            input_file.close();
        }

        auto test_exists = std::filesystem::exists(this->test_data_fullpath());
        if (!test_exists) {
            std::ofstream test_file(this->test_data_fullpath());
            test_file.close();
        }

    }

    std::filesystem::path InputReader::input_data_fullpath() const
    {
        return input_data_path/input_data_filename;
    }

    std::filesystem::path InputReader::test_data_fullpath() const
    {
        return test_data_path/test_data_filename;
    }

    std::vector<std::string> InputReader::input_vector() const
    {
        std::vector<std::string> input_vector;
        std::string line;
        std::ifstream input_file(this->input_data_fullpath());
        if (!input_file) {
            std::cerr << "Could not open the file: " << this->input_data_fullpath()
                      << std::endl;
        }
        else {
            while (getline(input_file, line)) { // always check whether the file is open
                input_vector.push_back(line);
            }
        }
        std::cout << "Finished loading file: " << this->input_data_fullpath()
                  << std::endl;
        return input_vector;
    }

    std::vector<std::string> InputReader::test_vector() const
    {
        std::vector<std::string> test_data_vector;
        std::string line;
        std::ifstream test_file(this->test_data_fullpath());
        if (!test_file) {
            std::cerr << "Could not open the file: " << this->test_data_fullpath()
                      << std::endl;
        }
        else {
            while (getline(test_file, line)) { // always check whether the file is open
                test_data_vector.push_back(line);
            }
        }
        std::cout << "Finished loading file: " << this->test_data_fullpath()
                  << std::endl;
        return test_data_vector;
    }

    std::vector<std::string> InputReader::string_vector() const
    {
        if (test_data) {
            return this->test_vector();
        }
        else {
            return this->input_vector();
        }
    }

}