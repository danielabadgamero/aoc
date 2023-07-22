#include <vector>
#include <string>
#include <fstream>
#include <climits>
#include <iostream>

int main()
{
	std::ifstream input{ "input" };
	std::string line{};

	int totalArea{};
	while (std::getline(input, line))
	{
		size_t sep{ line.find('x') };
		int w{ std::stoi(line.substr(0, sep)) };
		size_t sep2{ line.find('x', sep + 1) };
		int h{ std::stoi(line.substr(sep + 1, sep2 - sep - 1)) };
		int l{ std::stoi(line.substr(sep2 + 1)) };
		std::vector<int> areas{};
		areas.push_back(w * h);
		areas.push_back(h * l);
		areas.push_back(l * w);

		int minArea{ INT_MAX };
		for (const int& a : areas)
		{
			if (a < minArea) minArea = a;
			totalArea += 2 * a;
		}
		totalArea += minArea;
	}

	std::cout << totalArea << std::endl;

	return 0;
}
