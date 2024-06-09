#pragma clang diagnostic ignored "-Woverloaded-shift-op-parentheses"

#include "../doctest.h"
#include "../utils/utils.h"

TEST_SUITE_BEGIN("Array2D core features test suite.");

struct VectorsAndInt {
    int x;
    int y;
    int val;
};

TEST_CASE("Basic features of array template with ints.")
{
    utils::Array2D<int> int_array{std::vector<std::vector<int>>{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}}};

    SUBCASE("Access using at method returns correct values.") {
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

    SUBCASE("Test all sizes related to the array function.") {
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

TEST_CASE("Equality operations for an array of ints.")
{
    utils::Array2D<int> int_array_org{std::vector<std::vector<int>>{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}}};
    utils::Array2D<int> int_array_same{std::vector<std::vector<int>>{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}}};
    utils::Array2D<int> int_array_different_size{std::vector<std::vector<int>>{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}}};
    utils::Array2D<int> int_array_different_values{std::vector<std::vector<int>>{{4, 3, 2, 1}, {5, 6, 7, 8}, {9, 10, 11, 12}}};

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

TEST_CASE("Modification of values in array.")
{
    utils::Array2D<int> int_array{std::vector<std::vector<int>>{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}}};

    SUBCASE("Reassigning value in the array.") {
        CHECK(int_array.at(1, 2)==10);
        int_array.at(1, 2) = 20;
        CHECK(int_array.at(1, 2)==20);
    }
}

TEST_CASE("Basic feature testing of node wrappers.")
{
    utils::Array2D<int> int_array{std::vector<std::vector<int>>{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}}};

    SUBCASE("Reading from node wrapper.") {
        auto node = int_array.node_at(1, 2);
        CHECK(node.value==10);
        CHECK(node.x==1);
        CHECK(node.y==2);
    }
    SUBCASE("Modifying value in array using node wrapper.") {
        auto node = int_array.node_at(1, 2);
        CHECK(node.value==10);
        node.value = 20;
        CHECK(node.value==20);
        auto in_array_val = int_array.at(1, 2);
        CHECK(in_array_val==20);
    }
    SUBCASE("Modifying value in array using node wrapper.") {
        auto node = int_array.node_at(1, 2);
        CHECK(node.value==10);
        node.value = 20;
        CHECK(node.value==20);
        auto in_array_val = int_array.at(1, 2);
        CHECK(in_array_val==20);
    }
}

TEST_SUITE_END;