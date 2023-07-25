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
		for (std::string::iterator c{ line.begin() + 1 }; c != line.end() - 1; c++)
			if (*c == '\\')
				switch (*(c + 1))
				{
				case '\\':
				case '"':
					diff++;
					c++;
					break;
				case 'x':
					diff += 3;
					c += 3;
					break;
				}
	}

	std::cout << diff << std::endl;

	return 0;
}
