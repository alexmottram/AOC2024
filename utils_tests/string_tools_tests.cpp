#pragma clang diagnostic ignored "-Woverloaded-shift-op-parentheses"
#include "../doctest.h"
#include "../utils/utils.h"

TEST_SUITE_BEGIN("String tools test suite.");

TEST_CASE("Testing string strip white space function.")
{
	CHECK(utils::strip_white_space(std::string("      text   ")) == "text");
	CHECK(utils::strip_white_space("      text   ") == "text");
}

TEST_CASE("Testing split_string by delimiter function.")
{
	std::string test_string{ "a, b, c" };
	SUBCASE("Simple separator keeping white space.")
	{
		CHECK(utils::split_string(test_string, ",", false)
			== std::vector<std::string>{ "a", " b", " c" });
	}
	SUBCASE("Simple separator removing white space.")
	{
		CHECK(utils::split_string(test_string, ",", true)
			== std::vector<std::string>{ "a", "b", "c" });
	}

	std::string longer_test_string{ "a separator b separator c" };

	SUBCASE("String separator keeping white space.")
	{
		CHECK(utils::split_string(longer_test_string, "separator", false)
			== std::vector<std::string>{ "a ", " b ", " c" });
	}
	SUBCASE("String separator removing white space.")
	{
		CHECK(utils::split_string(longer_test_string, "separator", true)
			== std::vector<std::string>{ "a", "b", "c" });
	}
}

TEST_CASE("Testing string_to_type function.")
{
	SUBCASE("String to string.")
	{
		std::string input_str{ " text " };
		std::string output_str{ " text " };
		CHECK(utils::string_to_type<std::string>(input_str) == output_str);
	}

	SUBCASE("String with spaces before, in the middle, and after, to string.")
	{
		std::string input_str{ " text space text " };
		std::string output_str{ " text space text " };
		CHECK(utils::string_to_type<std::string>(input_str) == output_str);
	}

	SUBCASE("Numerical string to integer numerical types.")
	{
		std::string input_str{ "123" };
		int int_num = 123;
		size_t size_t_num = 123;

		CHECK(utils::string_to_type<int>(input_str) == int_num);
		CHECK(utils::string_to_type<size_t>(input_str) == size_t_num);
	}

	SUBCASE("Numerical string to floating point numerical types.")
	{
		std::string input_str{ "456.6" };
		float float_num = 456.6;
		double double_num = 456.6;

		CHECK(utils::string_to_type<float>(input_str) == float_num);
		CHECK(utils::string_to_type<double>(input_str) == double_num);
	}
}
TEST_CASE("Testing string_to_vector_type function.")
{
	SUBCASE("String to vector of strings.")
	{
		std::string input_str{ " text , other with spaces ,something" };
		std::vector<std::string>
			output_str_no_spaces{ " text ", " other with spaces ", "something" };
		CHECK(utils::string_to_vector_type<std::string>(input_str, ",")
			== output_str_no_spaces);
	}
	SUBCASE(
		"String to vector of strings removing white spaces before and after lettres.")
	{
		std::string input_str{ " text , other with spaces ,something" };
		std::vector<std::string>
			output_str_no_spaces{ "text", "other with spaces", "something" };
		CHECK(utils::string_to_vector_type<std::string>(input_str, ",", true)
			== output_str_no_spaces);
	}

	SUBCASE("String to vector of chars.")
	{
		std::string input_str{ "text" };
		std::vector<char> output_char{ 't', 'e', 'x', 't' };
		CHECK(utils::string_to_vector_type<char>(input_str) == output_char);
	}

	SUBCASE("String to vector of chars with comma delimiter.")
	{
		std::string input_str{ "t,e,x,t" };
		std::vector<char> output_char{ 't', 'e', 'x', 't' };
		CHECK(utils::string_to_vector_type<char>(input_str, ",") == output_char);
	}

	SUBCASE("Numerical string to integer numerical types.")
	{
		std::string input_str{ "123,  5" };
		std::vector<int> int_num{ 123, 5 };
		std::vector<size_t> size_t_num{ 123, 5 };

		CHECK(utils::string_to_vector_type<int>(input_str, ",") == int_num);
		CHECK(utils::string_to_vector_type<size_t>(input_str, ",") == size_t_num);
	}

	SUBCASE("Numerical string to floating point numerical types.")
	{
		std::string input_str{ "123,  5.6" };
		std::vector<float> float_num{ 123.0, 5.6 };
		std::vector<double> double_num{ 123.0, 5.6 };

		CHECK(utils::string_to_vector_type<float>(input_str, ",") == float_num);
		CHECK(utils::string_to_vector_type<double>(input_str, ",") == double_num);
	}

    SUBCASE("Invalid numerical string to int.")
    {
        std::string invalid_input{ "abc" };
        CHECK_THROWS_AS(utils::string_to_type<int>(invalid_input), std::invalid_argument);
    }

    SUBCASE("Invalid numerical string to float.")
    {
        std::string invalid_input{ "12.3abc" };
        CHECK_THROWS_AS(utils::string_to_type<float>(invalid_input), std::invalid_argument);
    }

    SUBCASE("Empty string to numerical type.")
    {
        std::string empty_input{ "" };
        CHECK_THROWS_AS(utils::string_to_type<int>(empty_input), std::invalid_argument);
    }

}

TEST_SUITE_END;