#include <vector>
#include <fstream>
#include <iostream>

int main()
{
	std::ifstream input{ "input" };
	std::vector<char> instructions{ std::istreambuf_iterator<char>(input), {} };
	int floor{};
	std::vector<char>::iterator c{ instructions.begin() };
	for (; c != instructions.end(); c++)
		if (floor == -1) break;
		else if (*c == '(') floor++;
		else if (*c == ')') floor--;
	
	std::cout << c - instructions.begin() << std::endl;

	return 0;
}
