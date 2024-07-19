#include "day_2.h"

namespace solutions {

	enum COLOURS {
		Blue, Red, Green
	};

	std::map<std::string, COLOURS> COLOUR_MAP{
			{"blue",  Blue},
			{"red",   Red},
			{"green", Green},

	};

	struct RoundScore {

	public:
		int red{0};
		int blue{0};
		int green{0};

		explicit RoundScore(const std::string &str)
				: red(0), blue(0), green(0) {
			auto split_str = utils::split_string(str, ",", true);
			for (const auto &colour_str: split_str) {
				auto score_str = utils::split_string(colour_str, " ", true).at(0);
				int score = utils::string_to_type<int>(score_str);
				for (auto const &[key, value]: COLOUR_MAP) {
					if (colour_str.find(key) != std::string::npos) {
						add_to_score(value, score);
					}
				}
			}
		}

		void add_to_score(const COLOURS &colour, const int &value) {
			switch (colour) {
				case COLOURS::Blue:
					blue += value;
					break;
				case COLOURS::Red:
					red += value;
					break;
				case COLOURS::Green:
					green += value;
					break;
				default:
					throw std::logic_error("Cannot accept colour.");
			}
		}

		bool score_valid(
				const int &max_red, const int &max_blue, const int &max_green
		) const {
			return ((red <= max_red) && (blue <= max_blue) && (green <= max_green));
		}

		friend std::ostream &operator<<(std::ostream &os, const RoundScore &r) {
			os << "RoundScore(red=" << r.red << ", blue=" << r.blue;
			os << ", green=" << r.green << ")";
			return os;
		}

	};

	int get_game_number(const std::string &game) {
		auto game_rounds_split = utils::split_string(
				game, ":", true
		);
		auto game_num_str = utils::split_string(game_rounds_split.at(0), " ").at(1);
		int game_num = utils::string_to_type<int>(game_num_str);
		return game_num;
	}

	std::vector<std::string> get_game_rounds(const std::string &game) {
		auto game_rounds_split = utils::split_string(game, ":", true);
		auto rounds = utils::split_string(
				game_rounds_split.at(1), ";", true
		);
		return rounds;
	}

	long long day_2_part_a(const utils::InputReader &input) {
		size_t valid_game_sum{0};
		int max_red{12};
		int max_blue{14};
		int max_green{13};

		std::vector<std::string> games = input.string_vector();
		for (const auto &game: games) {
			int game_num = get_game_number(game);
			auto rounds = get_game_rounds(game);
			bool all_valid{true};

			for (const auto &round: rounds) {
				auto round_score = RoundScore(round);
				bool valid_score = round_score.score_valid(
						max_red, max_blue, max_green
				);
				std::cout << round_score << " --> is valid: " << valid_score
				          << std::endl;
				if (!valid_score) { all_valid = false; }
			}
			if (all_valid) {
				std::cout << "Game " << game_num << " is all valid, adding to score."
				          << std::endl;
				valid_game_sum += game_num;
			}
		}
		return valid_game_sum;
	}

	long long day_2_part_b(const utils::InputReader &input) {
		size_t total_score{0};

		std::vector<std::string> games = input.string_vector();
		for (const auto &game: games) {
			int max_red{0};
			int max_blue{0};
			int max_green{0};

			int game_num = get_game_number(game);
			auto rounds = get_game_rounds(game);

			for (const auto &round: rounds) {
				auto round_score = RoundScore(round);
				max_red = std::max(round_score.red, max_red);
				max_blue = std::max(round_score.blue, max_blue);
				max_green = std::max(round_score.green, max_green);
			}
			long long game_score = max_red * max_blue * max_green;
			std::cout << "Score for game " << game_num << " --> ";
			std::cout << game_score << std::endl;
			total_score += game_score;
		}
		return total_score;
	}
}