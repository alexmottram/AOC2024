#pragma clang diagnostic ignored "-Woverloaded-shift-op-parentheses"
#include "../doctest.h"
#include "../utils/utils.h"

struct VectorsAndInt
{
	int x;
	int y;
	int val;
};

TEST_CASE("Testing array with ints.")
{
	utils::Array2D<int>
		test_string{{{ 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 }}};

	SUBCASE("Test the values in the underlying vector match.")
	{
		std::vector<VectorsAndInt> position_tests{
			{ 0, 0, 1 },
			{ 1, 0, 2 },
			{ 2, 0, 3 },
			{ 3, 0, 4 },
			{ 0, 1, 5 },
			{ 1, 1, 6 },
			{ 2, 1, 7 },
			{ 3, 1, 8 },
			{ 0, 2, 9 },
			{ 1, 2, 10 },
			{ 2, 2, 11 },
			{ 3, 2, 12 },
		};

		for (auto test : position_tests)
		{
			CHECK(test_string.at(test.x, test.y) == test.val);
		}
	}

	SUBCASE("Test the sizes are all correct.")
	{
		SUBCASE("Test the underlying vector size.")
		{
			CHECK(test_string.size() == 12);
		}
		SUBCASE("Test the x size of the array.")
		{
			CHECK(test_string.get_size_x() == 4);
		}
		SUBCASE("Test the y size of the array.")
		{
			CHECK(test_string.get_size_y() == 3);
		}

	}
}