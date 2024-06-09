#pragma clang diagnostic ignored "-Woverloaded-shift-op-parentheses"

#include "../doctest.h"
#include "../utils/utils.h"

TEST_SUITE_BEGIN("Array2D iterators test suite.");

TEST_CASE("Testing base array iterator.")
{
    utils::Array2D<int> int_array{std::vector<std::vector<int>>{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}}};

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

TEST_CASE("Testing basic properties of row first iterator.")
{
    utils::Array2D<int> int_array{std::vector<std::vector<int>>{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}}};

    SUBCASE("Row iterators are equal when initialised.") {
        auto it_a = int_array.row_iter();
        auto it_b = int_array.row_iter();
        CHECK(it_a==it_b);
        CHECK(**it_a==1);
        CHECK(**it_b==1);

        auto row_a = *it_a;
        auto row_b = *it_b;
        CHECK(row_a==row_b);
        CHECK(*row_a==1);
        CHECK(*row_b==1);

        ++row_b;
        CHECK(row_a!=row_b);
        CHECK(*row_a==1);
        CHECK(*row_b==2);

        *row_b = 22;
        CHECK(*row_a==1);
        CHECK(*row_b==22);

        ++row_a;
        CHECK(*row_a==22);
        CHECK(*row_b==22);
    }

    SUBCASE("Row iterators are not equal when one is increased.") {
        auto it_a = int_array.row_iter();
        auto it_b = int_array.row_iter();
        ++it_b;
        CHECK(it_a!=it_b);
        CHECK(**it_a==1);
        CHECK(**it_b==5); // Should return first value from the second row
    }

    SUBCASE("RowIter is not equal when one is increased.") {
        auto it_a = int_array.row_iter();
        auto it_b = int_array.row_iter();
        CHECK(it_a==it_b);  // Equality operation is true
        CHECK(**it_a==1);   // Value is correct for RowIter A
        CHECK(**it_b==1);   // Value is correct for RowIter B
        CHECK((&(**it_a))==(&(**it_b))); // Memory location matches
        CHECK(*(++it_b)==5); // Should return first value from the second row
        CHECK(it_a!=it_b);  // Equality now fails after one iterator is moved by one
        CHECK((&(**it_a))!=(&(**it_b))); // Memory location no longer matches
    }
}

TEST_CASE("Testing row first iterator using explicit for loops.")
{
    utils::Array2D<int> int_array{std::vector<std::vector<int>>{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}}};

    SUBCASE("Creating row iterator and iterating manually (changing number 2).") {
        auto row_iter = int_array.row_iter();
        for (auto outer = row_iter.begin(); outer!=row_iter.end(); ++outer) {
            auto row = *outer;
            for (auto inner = row.begin(); inner!=row.end(); ++inner) {
                if (*inner==2) {
                    *inner = 202;
                }
            }
        }
        CHECK(int_array.at(1, 0)==202);
    }
}

TEST_CASE("Testing row first iterator access and modification using auto.")
{
    utils::Array2D<int> int_array{std::vector<std::vector<int>>{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}}};

    SUBCASE("Accessing values using the iterator.") {
        int expected_value{1};
        int num_rows{0};
        for (auto row : int_array.row_iter()) {
            for (int x : row) {
                CHECK(expected_value==x);
                expected_value++;
            }
            num_rows++;
        }
        CHECK(num_rows==3);
    }

    SUBCASE("Changing the value of 3 in iterator changes it in the array.") {
        CHECK(int_array.at(2, 0)==3);
        for (auto row : int_array.row_iter()) {
            for (auto& x : row) {
                if (x==3) {
                    x = 303;
                }
            }
        }
        CHECK(int_array.at(2, 0)==303);
    }
}

TEST_SUITE_END;