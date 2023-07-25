#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>

int main()
{
	std::ifstream input{ "input" };
	std::string line{};
	int diff{};
	while (std::getline(input, line))
	{
		diff += 2;
		for (std::string::iterator c{ line.begin() }; c != line.end(); c++)
			if (*c == '\\' || *c == '"') diff++;
	}

	std::cout << diff << std::endl;

	return 0;
}
