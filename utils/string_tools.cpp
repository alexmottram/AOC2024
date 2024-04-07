//
// Created by Alexander Mottram on 04/12/2023.
//

#include "string_tools.h"

namespace utils
{

	std::string strip_white_space(std::string string_in)
	{
		size_t start_white_space{ 0 };
		size_t end_white_space{ string_in.size() };

		bool first_non_white_space{ true };

		for (auto i{ 0 }; i < string_in.size(); i++)
		{
			const auto& curr_char = string_in.at(i);
			if (first_non_white_space)
			{
				if (curr_char != ' ')
				{
					first_non_white_space = false;
					start_white_space = i;
				}
			}

			if (curr_char != ' ')
			{
				end_white_space = i;
			}
		}
		std::string string_out = string_in.substr(
			start_white_space,
			end_white_space - start_white_space + 1
		);
		return string_out;
	}

	std::vector<std::string> split_string(
		const std::string& s,
		const std::string& delimiter,
		const bool& remove_white_space
	)
	{
		size_t pos_start{ 0 };
		size_t pos_end;
		auto delim_len = delimiter.length();

		std::string token;
		std::vector<std::string> res;

		while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos)
		{
			token = s.substr(pos_start, pos_end - pos_start);
			pos_start = pos_end + delim_len;
			if (remove_white_space)
			{
				token = strip_white_space(token);
			}
			res.push_back(token);
		}
		token = s.substr(pos_start);
		if (!token.empty())
		{
			if (remove_white_space)
			{
				token = strip_white_space(token);
			}
			res.push_back(token);
		}
		return res;
	}

	template<>
	std::string string_to_type<std::string>(const std::string& s)
	{
		std::stringstream ss{ s };
		std::string t;
		std::getline(ss, t);
		return t;
	}

	std::vector<int> string_to_vector_type(const std::string& s)
	{
		std::vector<int> output{};
		for (char token : s)
		{
			std::string str_token{ token };
			int typed_token = string_to_type<int>(str_token);
			output.push_back(typed_token);
		}
		return output;
	}
} // namespace utils