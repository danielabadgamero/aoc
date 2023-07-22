#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

int grid[1000][1000]{};

int main()
{
	std::ifstream input{ "input" };
	std::string line{};
	int count{};
	while (std::getline(input, line))
	{
		std::stringstream str{ line };
		std::vector<std::string> words(1);
		while (std::getline(str, words.back(), ' '))
			words.push_back("");

		if (words[0] == "toggle")
		{
			int xStart{ std::stoi(words[1].substr(0, words[1].find(','))) };
			int xEnd{ std::stoi(words[3].substr(0, words[3].find(','))) };
			int yStart{ std::stoi(words[1].substr(words[1].find(',') + 1)) };
			int yEnd{ std::stoi(words[3].substr(words[3].find(',') + 1)) };

			for (int y{ yStart }; y <= yEnd; y++)
				for (int x{ xStart }; x <= xEnd; x++)
				{
					count += 2;
					grid[y][x] += 2;
				}
		}
		else
		{
			int xStart{ std::stoi(words[2].substr(0, words[2].find(','))) };
			int xEnd{ std::stoi(words[4].substr(0, words[4].find(','))) };
			int yStart{ std::stoi(words[2].substr(words[2].find(',') + 1)) };
			int yEnd{ std::stoi(words[4].substr(words[4].find(',') + 1)) };
			
			for (int y{ yStart }; y <= yEnd; y++)
				for (int x{ xStart }; x <= xEnd; x++)
					if (words[1] == "on")
					{
						count++;
						grid[y][x]++;
					}
					else if (grid[y][x])
					{
						count--;
						grid[y][x]--;
					}
		}
	}

	std::cout << count << std::endl;

	return 0;
}
