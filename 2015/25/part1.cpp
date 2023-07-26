#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>

int main()
{
	std::ifstream input{ "input" };
	std::vector<char> instructions{ std::istreambuf_iterator<char>(input), {} };
	int floor{};
	for (const char& c : instructions)
		if (c == '(') floor++;
		else if (c == ')') floor--;

	std::cout << floor << std::endl;

	return 0;
}
