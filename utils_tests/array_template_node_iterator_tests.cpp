#pragma clang diagnostic ignored "-Woverloaded-shift-op-parentheses"

#include "../doctest.h"
#include "../utils/utils.h"

TEST_SUITE_BEGIN("Array2D node iterators test suite.");

TEST_CASE("Testing array node iterator.")
{
    utils::Array2D<int> int_array{std::vector<std::vector<int>>{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}}};

    SUBCASE("Accessing values using the node iterator.") {
        int expected_value{1};
        int expected_x{0};
        int expected_y{0};
        for (auto node : int_array.node_iter()) {
            CHECK(node.value==expected_value);
            CHECK(node.x==expected_x);
            CHECK(node.y==expected_y);
            expected_value++;
            if (expected_x==3) {
                expected_x = 0;
                expected_y++;
            }
            else {
                expected_x++;
            }
        }
    }

    SUBCASE("Double value in rwo node iterator and testing the array is still doubled after.") {
        int expected_value{2};
        for (auto x : int_array.node_iter()) {
            x.value = x.value*2;
            CHECK(x.value==expected_value);
            expected_value += 2;
        }

        int expected_value_after{2};
        for (auto x : int_array.node_iter()) {
            CHECK(x.value==expected_value_after);
            expected_value_after += 2;
        }
    }
}

TEST_CASE("Testing row first node iterator.")
{
    utils::Array2D<int> int_array{std::vector<std::vector<int>>{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}}};

    SUBCASE("Row node iterators are equal when initialised.") {
        auto it_a = int_array.node_row_iter();
        auto it_b = int_array.node_row_iter();
        CHECK(it_a==it_b);

        CHECK((**it_a).value==1);
        CHECK((**it_a).x==0);
        CHECK((**it_a).y==0);

        CHECK((**it_b).value==1);
        CHECK((**it_b).x==0);
        CHECK((**it_b).y==0);

        auto row_a = *it_a;
        auto row_b = *it_b;
        CHECK(row_a==row_b);
        CHECK((*row_a).value==1);
        CHECK((*row_a).x==0);
        CHECK((*row_a).y==0);

        CHECK((*row_b).value==1);
        CHECK((*row_b).x==0);
        CHECK((*row_b).y==0);

        ++row_b;
        CHECK(row_a!=row_b);
        CHECK((*row_a).value==1);
        CHECK((*row_a).x==0);
        CHECK((*row_a).y==0);

        CHECK((*row_b).value==2);
        CHECK((*row_b).x==1);
        CHECK((*row_b).y==0);

        (*row_b).value = 22;
        CHECK((*row_a).value==1);
        CHECK((*row_b).value==22);

        ++row_a;
        CHECK((*row_a).value==22);
        CHECK((*row_a).x==1);
        CHECK((*row_a).y==0);
        CHECK((*row_b).value==22);
        CHECK((*row_b).x==1);
        CHECK((*row_b).y==0);
    }

    SUBCASE("Row node iterators are not equal when one is increased.") {
        auto it_a = int_array.node_row_iter();
        auto it_b = int_array.node_row_iter();
        ++it_b;
        CHECK(it_a!=it_b);
        CHECK((**it_a).value==1);
        // Should return first value from the second row
        CHECK((**it_b).value==5);
        CHECK((**it_b).x==0);
        CHECK((**it_b).y==1);
    }

    SUBCASE("Row node iterators are not equal when one is increased.") {
        auto it_a = int_array.node_row_iter();
        auto it_b = int_array.node_row_iter();
        CHECK(it_a==it_b);  // Equality operation is true
        // Value is correct for RowIter A
        auto node_a = **it_a;
        CHECK(node_a.value==1);
        CHECK(node_a.x==0);
        CHECK(node_a.y==0);
        // Value is correct for RowIter B
        auto node_b = **it_b;
        CHECK(node_b.value==1);
        CHECK(node_b.x==0);
        CHECK(node_b.y==0);
        // Memory location matches
        CHECK((&(**it_a).value)==(&(**it_b).value));
        // Should return first value from the second row
        auto node_b2 = *(++it_b);
        CHECK(node_b2.value==5);
        CHECK(node_b2.x==0);
        CHECK(node_b2.y==1);
        // Equality now fails after one iterator is moved by one
        CHECK(it_a!=it_b);
        // Memory location no longer matches
        CHECK((&(**it_a).value)!=(&(**it_b).value));
    }
}

TEST_CASE("Testing row first node iterator.")
{
    utils::Array2D<int> int_array{std::vector<std::vector<int>>{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}}};

    SUBCASE("Row node iterators are equal when initialised.") {
        for (auto node_row : int_array.node_row_iter()) {
            for (auto node : node_row) {

            }
        }
    }

}

TEST_SUITE_END;