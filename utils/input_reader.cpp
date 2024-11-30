#include "input_reader.h"

namespace utils {
    InputReader::InputReader(int day, int year, bool test_data, std::filesystem::path base_path)
            :day(day), test_data(test_data)
    {
        this->input_data_filename = "day_"+std::to_string(day)+".txt";
        this->test_data_filename = "day_"+std::to_string(day)+".txt";
        auto data_path = base_path/"data";
        auto path_with_year = data_path/std::to_string(year);
        this->input_data_path = path_with_year/INPUT_DATA_FOLDER;
        this->test_data_path = path_with_year/TEST_DATA_FOLDER;

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

    InputReader::InputReader(int day, int year, bool test_data)
            :InputReader(day, year, test_data, default_base_path()) { }

    std::filesystem::path InputReader::default_base_path()
    {
        auto base_path_parent = BASE_PATH.parent_path();
        return base_path_parent;
    }

    std::filesystem::path InputReader::input_data_fullpath() const
    {
        return input_data_path/input_data_filename;
    }

    std::filesystem::path InputReader::test_data_fullpath() const
    {
        return test_data_path/test_data_filename;
    }

    std::vector<std::string> InputReader::string_vector() const
    {
        std::ifstream input_file;
        if (test_data) {
            input_file = this->test_data_fullpath();
            std::cout << "Loading test data from path: "
                << this->test_data_fullpath() << std::endl;
        }
        else {
            input_file = this->input_data_fullpath();
            std::cout << "Loading input data from path: "
                << this->input_data_fullpath() << std::endl;
        }

        std::vector<std::string> input_vector;

        if (!input_file) {
            std::cerr << "Could not open the file: " << this->input_data_fullpath()
                      << std::endl;
            throw std::runtime_error("File does not exist.");
        }
        else {
            std::string line;
            while (getline(input_file, line)) { // always check whether the file is open
                input_vector.push_back(line);
            }
        }
        std::cout << "Finished loading file: " << this->input_data_fullpath()
                  << std::endl;
        return input_vector;
    }

}