#include <set>
#include <stack>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <climits>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <unordered_map>

int main()
{
	std::ifstream input{ "input" };
	std::string line{};
	std::unordered_map<std::string, std::unordered_map<std::string, int>> distances{};
	std::set<std::string> tmp{};
	while (std::getline(input, line))
	{
		std::stringstream str{ line };
		std::vector<std::string> words(1);
		while (std::getline(str, words.back(), ' '))
			words.push_back("");
		words.pop_back();
		words.erase(std::find(words.begin(), words.end(), "to"));
		words.erase(std::find(words.begin(), words.end(), "="));
		distances[words[0]][words[1]] = std::stoi(words[2]);
		distances[words[1]][words[0]] = std::stoi(words[2]);
		tmp.emplace(words[0]);
		tmp.emplace(words[1]);
	}
	std::vector<std::string> cities{};
	for (const auto& city : tmp)
		cities.push_back(city);

	int maxDistance{};
	while (std::next_permutation(cities.begin(), cities.end()))
	{
		int distance{};
		for (std::vector<std::string>::iterator city{ cities.begin() }; city != cities.end() - 1; city++)
			distance += distances[*city][*(city + 1)];
		if (distance > maxDistance) maxDistance = distance;
	}

	std::cout << maxDistance << std::endl;

	return 0;
}
