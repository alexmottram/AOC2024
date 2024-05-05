#pragma clang diagnostic ignored "-Woverloaded-shift-op-parentheses"
#include "../doctest.h"
#include "../utils/utils.h"

TEST_SUITE_BEGIN("Vector tools test suite.");

TEST_CASE("Testing 2d vector class Vec2D.")
{
	utils::Vec2D vec_a{ 6, 5 };
	utils::Vec2D vec_b{ -2, -10 };
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
		utils::Vec2D vec_nearly_a{ 6, 6 };
		CHECK(vec_b < vec_a);
		CHECK(vec_a < vec_nearly_a);
	}

	SUBCASE("Testing vector equality")
	{
		utils::Vec2D vec_same_as_a{ 6, 5 };
		CHECK(vec_same_as_a == vec_a);
		CHECK_FALSE(vec_a == vec_b);
	}

	SUBCASE("Testing vector greater than.")
	{
		CHECK(vec_a > vec_b);
	}

}
TEST_SUITE_END;