#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

int main()
{
	std::ifstream input{ "input" };
	std::string line{};
	std::vector<std::map<char, int>> freq(8);
	while (std::getline(input, line))
		for (size_t i{}; i != line.size(); i++)
			freq[i][line[i]]++;

	std::string msg{};

	for (const std::map<char, int>& f : freq)
	{
		std::pair<char, int> maxFreq{};
		for (const auto& pair : f)
			if (pair.second > maxFreq.second)
				maxFreq = pair;
		msg.push_back(maxFreq.first);
	}

	std::cout << msg << std::endl;

	return 0;
}
