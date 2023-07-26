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
	int groupWeight{ totalWeight / 3 };

	int minPackages{ 6 };
	std::unordered_map<int, size_t> packages{};
	packages[6] = UINT64_MAX;

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
		bool valid{};
		for (size_t byte2{}; byte2 != (1ul << weights.size()); byte2++)
			if (byte & byte2) continue;
			else
			{
				int weight2{};
				int weight3{};
				size_t byte3{ ~(byte | byte2) };
				if (!byte) continue;
				for (size_t i{}; i != weights.size(); i++)
				{
					if (byte2 & (1 << i)) weight2 += weights[i];
					if (byte3 & (1 << i)) weight3 += weights[i];
					if (weight2 == groupWeight && weight3 == groupWeight) { valid = true; break; }
				}
				if (valid) break;
			}
		if (!valid) continue;
		minPackages = count;
		if (packages[count] > qe) packages[count] = qe;
	}

	std::cout << packages[minPackages] << std::endl;

	return 0;
}
