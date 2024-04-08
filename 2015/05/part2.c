#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

int main()
{
	std::ifstream input{ "input" };
	std::string line{};
	int count{};
	while (std::getline(input, line))
	{
		bool nice{};
		for (std::string::iterator c{ line.begin() }; c != line.end() - 1; c++)
		{
			std::string pair{ *c };
			pair.push_back(*(c + 1));
			size_t pos{ line.find(pair, std::distance(line.begin(), c) + 2) };
			if (pos != line.npos)
			{
				nice = true;
				break;
			}
		}
		if (!nice) continue;
		nice = false;
		for (std::string::iterator c{ line.begin() }; c != line.end() - 2; c++)
			if (*c == *(c + 2))
			{
				nice = true;
				break;
			}
		if (nice) count++;
	}
	
	std::cout << count << std::endl;

	return 0;
}
