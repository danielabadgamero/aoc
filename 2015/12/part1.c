#include <string>
#include <fstream>
#include <iostream>

int main()
{
	std::ifstream input{ "input" };
	std::string data{};
	std::getline(input, data);

	int sum{};
	std::string buffer{};
	for (const char& c : data)
		if (c == '-' || (c >= '0' && c <= '9'))
			buffer.push_back(c);
		else if (!buffer.empty())
		{
			sum += std::stoi(buffer);
			buffer.clear();
		}

	std::cout << sum << std::endl;

	return 0;
}
