#include <vector>
#include <string>
#include <fstream>
#include <climits>
#include <iostream>
#include <algorithm>

int main()
{
	std::ifstream input{ "input" };
	std::string line{};

	int totalLength{};
	while (std::getline(input, line))
	{
		size_t sep{ line.find('x') };
		int w{ std::stoi(line.substr(0, sep)) };
		size_t sep2{ line.find('x', sep + 1) };
		int h{ std::stoi(line.substr(sep + 1, sep2 - sep - 1)) };
		int l{ std::stoi(line.substr(sep2 + 1)) };

		int dimensions[3]{ w, h, l };
		std::sort(dimensions, dimensions  + 3);

		totalLength += 2 * (dimensions[0] + dimensions[1]);
		totalLength += w * h * l;
	}

	std::cout << totalLength << std::endl;

	return 0;
}
