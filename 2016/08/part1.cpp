#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

bool grid[6][50]{};

static void printGrid()
{
	for (int i{}; i != 6; i++)
	{
		for (int j{}; j != 50; j++)
			if (grid[i][j]) std::cout << '#';
			else std::cout << '.';
		std::cout << std::endl;
	}
}

int main()
{
	std::ifstream input{ "input" };
	std::string line{};
	while (std::getline(input, line))
	{
		std::vector<std::string> words{};
		std::stringstream str{ line };
		do words.push_back("");
		while (std::getline(str, words.back(), ' '));
		words.pop_back();
		if (words.size() == 2)
		{
			int w{ std::stoi(words[1]) };
			int h{ words[1].back() - '0' };
			for (int i{}; i != w; i++)
				for (int j{}; j != h;  j++)
					grid[j][i] = true;
		}
		else
		{
			int index{ std::stoi(words[2].substr(2)) };
			int offset{ std::stoi(words[4]) };
			if (words[1] == "row")
				for (int i{}; i != offset; i++)
				{
					bool last{ grid[index][49] };
					for (int x{ 49 }; x != 0; x--)
						grid[index][x] = grid[index][x - 1];
					grid[index][0] = last;
				}
			else for (int i{}; i != offset; i++)
			{
				bool last{ grid[5][index] };
				for (int y{ 5 }; y != 0; y--)
					grid[y][index] = grid[y - 1][index];
				grid[0][index] = last;
			}
		}
	}

	int count{};
	for (int i{}; i != 6; i++)
		for (int j{}; j != 50; j++)
			count += grid[i][j];

	printGrid();
	std::cout << count << std::endl;

	return 0;
}
