#pragma clang diagnostic ignored "-Woverloaded-shift-op-parentheses"
#include "../doctest.h"
#include "../utils/utils.h"

TEST_SUITE_BEGIN("Maths tools test suite.");

TEST_CASE("Testing factorial function.")
{
	CHECK(utils::factorial(0) == 1);
	CHECK(utils::factorial(1) == 1);
	CHECK(utils::factorial(2) == 2);
	CHECK(utils::factorial(3) == 6);
	CHECK(utils::factorial(10) == 3628800);
}

TEST_CASE("Testing n choose r function.")
{
	CHECK(utils::nCr(1, 1) == 1);
	CHECK(utils::nCr(2, 1) == 2);
	CHECK(utils::nCr(5, 1) == 5);
	CHECK(utils::nCr(5, 2) == 10);
}

TEST_SUITE_END;

