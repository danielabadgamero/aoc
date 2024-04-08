#include <set>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

int main()
{
	std::ifstream input{ "input" };
	std::string line{};
	std::unordered_map<std::string, std::unordered_map<std::string, int>> people{};
	std::set<std::string> tmp{};
	std::vector<std::string> names{};
	while (std::getline(input, line))
	{
		std::stringstream str{ line };
		std::vector<std::string> words(1);
		while (std::getline(str, words.back(), ' '))
			words.push_back("");
		words[10].pop_back();
		people[words[0]][words[10]] = std::stoi(words[3]) * (words[2] == "gain" ? 1 : -1);
		tmp.emplace(words[0]);
	}
	for (const auto& name : tmp) names.push_back(name);

	int maxHappiness{};
	while (std::next_permutation(names.begin(), names.end()))
	{
		int happiness{};
		for (std::vector<std::string>::iterator n{ names.begin() }; n != names.end() - 1; n++)
		{
			happiness += people[*n][*(n + 1)];
			happiness += people[*(n + 1)][*n];
		}
		happiness += people[names.front()][names.back()];
		happiness += people[names.back()][names.front()];
		if (happiness > maxHappiness) maxHappiness = happiness;
	}

	std::cout << maxHappiness << std::endl;

	return 0;
}
