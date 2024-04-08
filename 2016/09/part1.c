#include <string>
#include <vector>
#include <fstream>
#include <iostream>

int main()
{
	std::ifstream input{ "input" };
	std::string line{};
	int size{};
	std::getline(input, line);

	for (size_t i{}; i != line.size(); i++)
	{
		if (line[i] == '(')
		{
			int length{ std::stoi(line.substr(++i)) };
			while (line[i++] != 'x');
			int times{ std::stoi(line.substr(i)) };
			size += times * length;
			while (line[++i] != ')');
			i += length;
		}
		else size++;
	}

	std::cout << size << std::endl;

	return 0;
}
