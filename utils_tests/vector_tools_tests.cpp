#pragma clang diagnostic ignored "-Woverloaded-shift-op-parentheses"
#include "../doctest.h"
#include "../utils/utils.h"

TEST_SUITE_BEGIN("Vector tools test suite.");

TEST_CASE("Testing 2d vector class Vec2D.")
{
    utils::Vec2D<int> vec_a{6, 5};
    utils::Vec2D<int> vec_b{-2, -10};
    REQUIRE(vec_a.x == 6);
    REQUIRE(vec_a.y == 5);
    REQUIRE(vec_b.x == -2);
    REQUIRE(vec_b.y == -10);

    SUBCASE("Testing vector sum")
    {
        auto vec_sum = vec_a + vec_b;
        CHECK(vec_sum.x == 4);
        CHECK(vec_sum.y == -5);
    }

    SUBCASE("Testing vector subtract")
    {
        auto vec_minus = vec_a - vec_b;
        CHECK(vec_minus.x == 8);
        CHECK(vec_minus.y == 15);
    }

    SUBCASE("Testing vector less than")
    {
        utils::Vec2D<int> vec_nearly_a{6, 6};
        CHECK(vec_b < vec_a);
        CHECK(vec_a < vec_nearly_a);
    }

    SUBCASE("Testing vector equality")
    {
        utils::Vec2D<int> vec_same_as_a{6, 5};
        CHECK(vec_same_as_a == vec_a);
        CHECK_FALSE(vec_a == vec_b);
    }

    SUBCASE("Testing vector greater than")
    {
        CHECK(vec_a > vec_b);
    }
}


TEST_CASE("Testing 2d vector class Vec2D conversions.")
{
    SUBCASE("Convert int to long long")
    {
        int int_x {6};
        int int_y {5};
        utils::Vec2D<int> vec_int{6, 5};
        utils::Vec2D<long long> expected_vec_long_long{6, 5};
        utils::Vec2D<long long> vec_long_long (int_x, int_y);
        CHECK(vec_long_long == expected_vec_long_long);
    }
}


TEST_CASE("Testing 2d vector class Vec2D std iterator and container compatability.")
{
    SUBCASE("Testing creating a vector with int type")
    {
        std::vector<utils::Vec2D<int>> vector_of_vecs;
        vector_of_vecs.push_back({5, 10});
        vector_of_vecs.emplace_back(6, 12);
        CHECK(vector_of_vecs[0] == utils::Vec2D<int>{5, 10});
        CHECK(vector_of_vecs[1] == utils::Vec2D<int>{6, 12});
    }

    SUBCASE("Testing creating a vector with int default values")
    {
        std::vector<utils::Vec2D<int>> vector_of_vec_2ds(10);
    }

    SUBCASE("Testing transforming 2D vecs in a map")
    {
        // std::map<utils::Vec2D<int>, int> input_map{{{1, 1}, 1}, {{2, 2}, 2}};
        // std::map<utils::Vec2D<int>, int> expected_output_map{{{1, 1}, 2}, {{2, 2}, 4}};
        //
        // std::vector<std::pair<utils::Vec2D<int>, int>> update_vector{};
        //
        // std::transform(
        //     input_map.begin(),
        //     input_map.end(),
        //     update_vector.begin(),
        //     [](auto i_pair) { return i_pair; }
        // );

        // std::map<utils::Vec2D<int>, int> updated_map(update_vector.begin(), update_vector.end());
        //
        // for (auto [key, vals] : input_map)
        // {
        //     CHECK(updated_map[key]==vals);
        // }
        //
        // std::vector<std::pair<utils::Vec2D<int>, int>> update_vector_2{};
        // std::transform(
        //     input_map.begin(),
        //     input_map.end(),
        //     update_vector_2.begin(),
        //     [](auto i_pair)
        //     {
        //         std::pair<utils::Vec2D<int>, int> updated_pair {i_pair.first, i_pair.second * 2};
        //         return updated_pair;
        //     }
        // );
        //
        // std::map<utils::Vec2D<int>, int> updated_map_2(update_vector_2.begin(), update_vector_2.end());
        //
        // for (auto [key, vals] : expected_output_map)
        // {
        //     CHECK(updated_map_2[key]==vals);
        // }
    }
}

TEST_SUITE_END;
