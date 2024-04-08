#include <string>
#include <vector>
#include <fstream>
#include <iostream>

static bool possible(std::vector<int> tri)
{
	return tri[0] + tri[1] > tri[2] &&
		tri[0] + tri[2] > tri[1] &&
		tri[1] + tri[2] > tri[0];
}

static std::vector<int> getLine(const std::string& line)
{
	std::vector<std::string> words(1);
	for (const char& c : line)
		if (c == ' ' && !words.back().empty()) words.push_back("");
		else if (c != ' ') words.back().push_back(c);
	std::vector<int> triangle{};
	for (const std::string& str : words)
		triangle.push_back(std::stoi(str));
	return triangle;
}

int main()
{
	std::ifstream input{ "input" };
	std::string line{};
	int count{};
	while (!input.eof())
	{
		std::vector<std::vector<int>> tris{};
		for (int i{}; i != 3; i++)
		{
			std::getline(input, line);
			if (line.empty()) break;
			tris.push_back(getLine(line));
		}
		if (tris.empty()) break;
		for (int i{}; i != 3; i++)
			if (possible({ tris[0][i], tris[1][i], tris[2][i] })) count++;
	}

	std::cout << count << std::endl;

	return 0;
}
