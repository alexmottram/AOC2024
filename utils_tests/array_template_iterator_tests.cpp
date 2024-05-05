#pragma clang diagnostic ignored "-Woverloaded-shift-op-parentheses"

#include "../doctest.h"
#include "../utils/utils.h"

TEST_SUITE_BEGIN("Array2D iterators test suite.");

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

TEST_CASE("Testing basic properties of row first iterator.")
{
    utils::Array2D<int> int_array{{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}}};

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

    SUBCASE("Row iterators are not equal when one is increased.") {
        auto it_a = int_array.row_iter();
        auto it_b = int_array.row_iter();
        CHECK(it_a==it_b);
        CHECK(**it_a==1);
        CHECK(++(*it_b)==2); // Should return first value from the second row
    }
}

TEST_CASE("Testing row first iterator returns all values.")
{
    utils::Array2D<int> int_array{{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}}};

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
}

TEST_CASE("Test a standard vector iterator.")
{
    std::vector<int> int_vector{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    SUBCASE("Accessing vector using iterators.") {
        auto it_a = int_vector.begin();
        auto it_b = int_vector.begin();
        CHECK(*it_a==1);
        CHECK(*it_b==1);

        ++it_a;
        CHECK(*it_a==2);
        CHECK(*it_b==1);

        *it_a = 22;
        CHECK(*it_a==22);

        ++it_a;
        ++it_b;
        CHECK(*it_a==3);
        CHECK(*it_b==22);

        // Insert operation invalidates the iterators
        int_vector.insert(it_b, 101);
    }

}

TEST_SUITE_END;