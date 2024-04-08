#include <string>
#include <vector>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <unordered_map>

int main()
{
	std::ifstream input{ "input" };
	std::string line{};
	int totalWeight{};
	std::vector<int> weights{};
	while (std::getline(input, line))
	{
		weights.push_back(std::stoi(line));
		totalWeight += weights.back();
	}
	int groupWeight{ totalWeight / 4 };

	int minPackages{ 5 };
	std::unordered_map<int, size_t> packages{};
	packages[5] = UINT64_MAX;

	for (size_t byte{}; byte != (1ul << weights.size()); byte++)
	{
		int weight{};
		int count{};
		size_t qe{ 1 };
		for (size_t i{}; i != weights.size(); i++)
		{
			if (byte & (1 << i)) (weight += weights[i]), count++, (qe *= weights[i]);
			if (count > minPackages) break;
		}
		if (weight != groupWeight) continue;
		if (count > minPackages) continue;
		minPackages = count;
		if (packages[count] > qe) packages[count] = qe;
	}

	std::cout << packages[minPackages] << std::endl;

	return 0;
}
