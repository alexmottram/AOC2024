#pragma clang diagnostic ignored "-Woverloaded-shift-op-parentheses"

#include "../doctest.h"
#include "../utils/utils.h"

struct VectorsAndInt {
    int x;
    int y;
    int val;
};

TEST_CASE("Testing basic features of array with ints.")
{
    utils::Array2D<int>
            int_array{{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}}};

    SUBCASE("Test the values in the underlying vector match.") {
        std::vector<VectorsAndInt> position_tests{
                {0, 0, 1},
                {1, 0, 2},
                {2, 0, 3},
                {3, 0, 4},
                {0, 1, 5},
                {1, 1, 6},
                {2, 1, 7},
                {3, 1, 8},
                {0, 2, 9},
                {1, 2, 10},
                {2, 2, 11},
                {3, 2, 12},
        };

        for (auto test : position_tests) {
            CHECK(int_array.at(test.x, test.y)==test.val);
        }
    }

    SUBCASE("Test the sizes are all correct.") {
        SUBCASE("Test the underlying vector size.") {
            CHECK(int_array.size()==12);
        }
        SUBCASE("Test the x size of the array.") {
            CHECK(int_array.get_size_x()==4);
        }
        SUBCASE("Test the y size of the array.") {
            CHECK(int_array.get_size_y()==3);
        }
    }

}

TEST_CASE("Testing equality operations with an array with ints.")
{
    utils::Array2D<int> int_array_org{{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}}};
    utils::Array2D<int> int_array_same{{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}}};
    utils::Array2D<int> int_array_different_size{{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}}};
    utils::Array2D<int> int_array_different_values{{{4, 3, 2, 1}, {5, 6, 7, 8}, {9, 10, 11, 12}}};

    SUBCASE("Test equality operation.") {
        SUBCASE("Arrays are equal.") {
            CHECK(int_array_org==int_array_same);
        }

        SUBCASE("Arrays have different sizes.") {
            CHECK(int_array_org!=int_array_different_size);
        }

        SUBCASE("Arrays have different values.") {
            CHECK(int_array_org!=int_array_different_values);
        }

    }
}

TEST_CASE("Testing changing values in an array.")
{
    utils::Array2D<int>
            int_array{{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}}};

    SUBCASE("Reassigning value in the array.") {
        CHECK(int_array.at(1, 2)==10);
        int_array.at(1, 2) = 20;
        CHECK(int_array.at(1, 2)==20);
    }
}

TEST_CASE("Testing base array iterator.")
{
    utils::Array2D<int> int_array{{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}}};

    SUBCASE("Accessing values using the iterator.") {
        int expected_value{1};
        for (auto x : int_array) {
            CHECK(x==expected_value);
            expected_value++;
        }
    }

    SUBCASE("Double value in iterator and testing the array is still doubled after.") {
        int expected_value{2};
        for (auto& x : int_array) {
            x = x*2;
            CHECK(x==expected_value);
            expected_value += 2;
        }

        int expected_value_after{2};
        for (auto x : int_array) {
            CHECK(x==expected_value_after);
            expected_value_after += 2;
        }
    }
}

TEST_CASE("Testing row first iterator.")
{
    utils::Array2D<int> int_array{{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}}};
    utils::Array2D<int> int_array_2{{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}}};

    SUBCASE("Accessing values using the iterator.") {
        int expected_value{1};
        int num_rows {0};
        for (auto row : int_array.row_iter()) {
            for (int x : row) {
                CHECK(expected_value==x);
                expected_value++;
            }
            num_rows ++;
        }
        CHECK(num_rows==3);
    }

    SUBCASE("Row iterator performs basic functions.") {
        auto it = int_array_2.row_iter();
        auto it_2 = int_array_2.row_iter();
        CHECK(it==it_2);

    }

//    SUBCASE("Double value in iterator and testing the array is still doubled after.") {
//        int expected_value{2};
//        for (auto& x : int_array.row_iter()) {
//            x = x*2;
//            CHECK(x==expected_value);
//            expected_value += 2;
//        }
//
//        int expected_value_after{2};
//        for (auto x : int_array) {
//            CHECK(x==expected_value_after);
//            expected_value_after += 2;
//        }
//    }
//    SUBCASE("Accessing values using the iterator.") {
//        int expected_value{1};
//        for (auto& row : int_array.row_iter()) {
//            for (auto& x : row) {
//                CHECK(x==expected_value);
//                expected_value++;
//            }
//        }
//    }

}
