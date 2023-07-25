#include <string>
#include <vector>
#include <fstream>
#include <iostream>

int main()
{
	std::ifstream input{ "input" };
	std::vector<int> capacities{};
	std::string line{};
	while (std::getline(input, line))
		capacities.push_back(std::stoi(line));

	int count{};
	for (size_t i{}; i != 1ul << capacities.size(); i++)
	{
		int vol{};
		for (size_t b{}; b != capacities.size(); b++)
			if (i & (1 << b)) vol += capacities[b];
		if (vol == 150)
			count++;
	}

	std::cout << count << std::endl;

	return 0;
}
