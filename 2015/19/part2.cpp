#include <random>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>

std::vector<std::pair<std::string, std::string>> rep{};

int main()
{
	std::ifstream input{ "input" };
	bool molecule{};
	std::string line{};
	std::string mol{};
	while (std::getline(input, line))
	{
		if (line.empty()) molecule = true;
		else if (!molecule)
		{
			std::stringstream str{ line };
			std::vector<std::string> words{};
			do words.push_back("");
			while (std::getline(str, words.back(), ' '));
			rep.push_back({ words[0], words[2] });
		}
		else mol = line;
	}

	int count{};
	while (mol != "e")
		for (const auto& med : rep)
		{
			size_t pos{ mol.find(med.second) };
			if (pos == mol.npos) continue;
			mol.replace(pos, med.second.size(), med.first);
			count++;
			std::random_shuffle(rep.begin(), rep.end());
		}

	std::cout << count << std::endl;

	return 0;
}
