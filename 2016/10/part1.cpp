#include <set>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>

std::vector<std::string> split(const std::string& str)
{
	std::vector<std::string> words(1);
	for (const char& c : str)
		if (c == ' ') words.push_back("");
		else words.back().push_back(c);
	return words;
}

struct Output
{
	int dest{};
	bool bin{};
};

int main()
{
	std::ifstream input{ "input", std::ios::binary };
	std::unordered_map<int, Output[2]> instr{};
	std::unordered_map<int, std::set<int>> bots{};

	std::string line{};
	while (std::getline(input, line))
	{
		std::vector<std::string> words{ split(line) };
		if (words.size() == 6)
			bots[std::stoi(words.at(5))].emplace(std::stoi(words.at(1)));
		else
		{
			instr[std::stoi(words.at(1))][0] = { std::stoi(words.at(6)), words.at(5) == "output" };
			instr[std::stoi(words.at(1))][1] = { std::stoi(words.at(11)), words.at(10) == "output" };
		}
	}

	bool found{};
	while (!found) for (auto& bot : bots)
	{
		if (bot.second.size() == 2)
		{
			if (*bot.second.begin() == 17 && *std::next(bot.second.begin(), 1) == 61)
			{
				std::cout << bot.first << std::endl;
				found = true;
				break;
			}
			if (!instr[bot.first][0].bin)
				bots[instr[bot.first][0].dest].emplace(*bot.second.begin());
			bot.second.erase(*bot.second.begin());
			if (!instr[bot.first][1].bin)
				bots[instr[bot.first][1].dest].emplace(*bot.second.begin());
			bot.second.erase(bot.second.begin());
		}
	}

	return 0;
}
