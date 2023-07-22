#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <unordered_map>

int main()
{
	std::ifstream input{ "input" };
	std::string line{};
	std::vector<std::vector<std::string>> text{};
	std::unordered_map<std::string, std::unordered_map<std::string, int>> cities{};
	while (std::getline(input, line))
	{
		std::stringstream str{ line };
		std::vector<std::string> words(1);
		while (std::getline(str, words.back(), ' '))
			words.push_back("");
		words.pop_back();
		words.erase(std::find(words.begin(), words.end(), "to"));
		words.erase(std::find(words.begin(), words.end(), "="));
		text.push_back(words);
		cities[words.front()] = {};
		cities[words[1]] = {};
	}

	for (auto& city : cities)
		for (const auto& dest : cities)
		{
			if (city.first == dest.first) continue;

			std::vector<std::vector<std::string>>::iterator it{ std::find_if(text.begin(), text.end(),
					[city,dest](const std::vector<std::string>& B)
					{
						return (city.first == B[0] && dest.first == B[1]) ||
						       (city.first == B[1] && dest.first == B[0]);
					}) };
			if (it == text.end()) continue;
			std::vector<std::string> path{ *it };
			city.second.emplace(dest.first, std::stoi(path[2]));
		}

	for (const auto& city : cities)
		for (const auto& path : city.second)
			std::cout << city.first << " to " << path.first << ": " << path.second << std::endl;

	return 0;
}
