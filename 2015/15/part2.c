#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

int main()
{
	std::ifstream input{ "input" };
	std::string line{};
	std::vector<std::vector<int>> i{};
	while (std::getline(input, line))
	{
		std::stringstream str{ line };
		std::vector<std::string> words(1);
		while (std::getline(str, words.back(), ' '))
			words.push_back("");
		words.pop_back();
		i.push_back
			({ {
				std::stoi(words[2]),
				std::stoi(words[4]),
				std::stoi(words[6]),
				std::stoi(words[8]),
				std::stoi(words[10])
			} });
	}

	int maxScore{};

	for (int a{ 1 }; a != 98; a++)
		for (int b{ 1 }; b != 98; b++)
			for (int c{ 1 }; c != 98; c++)
				for (int d{ 1 }; d != 98; d++)
					if (a + b + c + d != 100) continue;
					else
					{
						if (a * i[0][4] + b * i[1][4] +
								c * i[2][4] +
								d * i[3][4] != 500) continue;
						int score{ 1 };
						for (int j{}; j != 4; j++)
						{
							int ingredient{ a * i[0][j] + b * i[1][j] +
								c * i[2][j] + d * i[3][j] };
							if (ingredient < 0) ingredient = 0;
							score *= ingredient;
						};
						if (score > maxScore) maxScore = score;
					}

	std::cout << maxScore << std::endl;

	return 0;
}
