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

int main()
{
	std::ifstream input{ "input" };
	std::string line{};
	int count{};
	while (std::getline(input, line))
	{
		std::vector<std::string> words(1);
		for (const char& c : line)
			if (c == ' ' && !words.back().empty()) words.push_back("");
			else if (c != ' ') words.back().push_back(c);
		std::vector<int> triangle{};
		for (const std::string& str : words)
			triangle.push_back(std::stoi(str));
		if (possible(triangle)) count++;
	}

	std::cout << count << std::endl;

	return 0;
}
