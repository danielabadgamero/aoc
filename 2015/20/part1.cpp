#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

int main()
{
	std::ifstream input{ "input" };
	std::string line{};
	std::getline(input, line);
	int num{ std::stoi(line) / 10 };

	std::vector<int> houses(num);
	for (size_t i{ 1 }; i != houses.size(); i++)
		for (size_t j{ i }; j <= houses.size(); j += i)
			houses[j] += static_cast<int>(i);

	std::vector<int>::iterator it{ std::find_if(houses.begin(), houses.end(),
				[num](const int& n) { return n >= num; }) };

	std::cout << std::distance(houses.begin(), it) << std::endl;

	return 0;
}
