#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>

struct Pos
{
	int x{};
	int y{};
} pos{};

int main()
{
	std::ifstream input{ "input" };
	std::string step{};
	int dir{};
	while (std::getline(input, step, ' '))
	{
		if (step[0] == 'R') dir++; else dir--;
		dir += 4; dir %= 4;
		int num{ std::stoi(step.substr(1)) };
		switch (dir)
		{
		case 0: pos.y += num; break;
		case 1: pos.x += num; break;
		case 2: pos.y -= num; break;
		case 3: pos.x -= num; break;
		}
	}

	std::cout << std::abs(pos.x) + std::abs(pos.y) << std::endl;

	return 0;
}
