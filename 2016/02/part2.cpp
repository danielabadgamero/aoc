#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_map>

struct Pos
{
	int x{};
	int y{};
};

int main()
{
	std::ifstream input{ "input" };
	std::string line{};
	std::string code{};
	Pos pos{ -2, 0 };
	std::unordered_map<int, std::unordered_map<int, char>> map{};
	for (int i{ -2 }; i != 3; i++) map[i][0] = static_cast<char>(i + 7 + '0');
	map[0][2] = '1';
	map[0][1] = '3';
	map[0][-1] = 'B';
	map[0][-2] = 'D';
	map[-1][1] = '2';
	map[1][1] = '4';
	map[1][-1] = 'C';
	map[-1][-1] = 'A';
	while (std::getline(input, line))
	{
		for (const char& c : line)
		{
			Pos prevPos{ pos };
			switch (c)
			{
			case 'L': pos.x--; break;
			case 'U': pos.y++; break;
			case 'R': pos.x++; break;
			case 'D': pos.y--; break;
			}
			if (!map.contains(pos.x)) pos = prevPos;
			else if (!map[pos.x].contains(pos.y)) pos = prevPos;
		}
		code.push_back(map[pos.x][pos.y]);
	}
	
	std::cout << code << std::endl;

	return 0;
}
