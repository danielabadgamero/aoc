#include <vector>
#include <cstdint>
#include <sstream>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

int main()
{
	std::ifstream input{ "input" };
	std::unordered_map<std::string, std::unordered_set<std::string>> rep{};
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
			rep[words[0]].emplace(words[2]);
		}
		else mol = line;
	}

	std::unordered_set<std::string> molecules{};

	for (const auto& med : rep)
		for (const std::string& m : med.second)
		{
			size_t next{ UINT64_MAX };
			while ((next = mol.find(med.first, next + 1)) != mol.npos)
			{
				std::string tmp{ mol };
				tmp.erase(next, med.first.size());
				tmp.insert(next, m);
				molecules.emplace(tmp);
			}
		}

	std::cout << molecules.size() << std::endl;

	return 0;
}
