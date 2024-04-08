#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <unordered_map>

int main()
{
	std::ifstream input{ "input" };
	std::string line{};
	const std::unordered_map<std::string, int> real
	{
		{ "children:", 3 },
		{ "cats:", 7 },
		{ "samoyeds:", 2 },
		{ "pomeranians:", 3 },
		{ "akitas:", 0 },
		{ "vizslas:", 0 },
		{ "goldfish:", 5 },
		{ "trees:", 3 },
		{ "cars:", 2 },
		{ "perfumes:", 1 }
	};
	int sue{};
	while (std::getline(input, line))
	{
		std::vector<std::string> words{};
		std::stringstream str{ line };
		do words.push_back("");
		while (std::getline(str, words.back(), ' '));
		bool valid{ true };
		for (int i{}; i != 3; i++)
		{
			std::string item{ words[i * 2 + 2] };
			int num{ std::stoi(words[i * 2 + 3]) };
			if (item == "cats:" || item == "trees:")
			{
				if (real.at(item) >= num) valid = false;
			}
			else if (item == "pomeranians:" || item == "goldfish:")
			{
				if (real.at(item) <= num) valid = false;
			}
			else if (real.at(item) != num)
				valid = false;
		}
		if (valid)
		{
			sue = std::stoi(words[1]);
			break;
		}
	}

	std::cout << sue << std::endl;

	return 0;
}
