//
// Created by Alexander Mottram on 04/12/2023.
//
#pragma once

#include "precompile_header.h"

namespace utils
{

	std::string strip_white_space(std::string string_in);

	std::vector<std::string> split_string(
		const std::string& s,
		const std::string& delimiter,
		const bool& strip_white_space = false
	);


	template<typename T>
	T string_to_type(const std::string& s)
	{
		std::stringstream ss{ s };
		T t;
		ss >> t;
		return t;
	}

	template<>
	std::string string_to_type<std::string>(const std::string& s);

	template<typename T>
	std::vector<T> string_to_vector_type(
		const std::string& s,
		const std::string& delimiter,
		const bool& remove_white_space
	)
	{
		std::vector<T> output{};
		auto string_vec = split_string(s, delimiter, remove_white_space);

		for (const auto& token : string_vec)
		{
			if (!token.empty())
			{
				T typed_token{};
				typed_token = string_to_type<T>(token);
				output.push_back(typed_token);
			}
		}
		return output;
	}

	template<typename T>
	std::vector<T> string_to_vector_type(
		const std::string& s, const std::string& delimiter
	)
	{
		return string_to_vector_type<T>(s, delimiter, false);
	}

	template<typename T>
	std::vector<T> string_to_vector_type(const std::string& s)
	{
		std::vector<T> output{};
		for (char token : s)
		{
			std::string str_token{ token };
			T typed_token = string_to_type<T>(str_token);
			output.push_back(typed_token);
		}
		return output;
	}

}
