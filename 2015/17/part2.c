#include <map>
#include <string>
#include <vector>
#include <climits>
#include <fstream>
#include <iostream>

int main()
{
	std::ifstream input{ "input" };
	std::vector<int> capacities{};
	std::string line{};
	while (std::getline(input, line))
		capacities.push_back(std::stoi(line));

	int min{ INT_MAX };
	std::map<int, int> minimum{};
	for (size_t i{}; i != 1ul << capacities.size(); i++)
	{
		int vol{};
		int count{};
		for (size_t b{}; b != capacities.size(); b++)
			if (i & (1 << b)) (vol += capacities[b]), count++;
		if (vol == 150)
		{
			if (count < min) min = count;
			minimum[count]++;
		}
	}

	std::cout << minimum[min] << std::endl;

	return 0;
}
