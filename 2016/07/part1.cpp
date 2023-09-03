#include <string>
#include <vector>
#include <fstream>
#include <iostream>

static bool hasAbba(const std::string& str)
{
	for (std::string::const_iterator it{ str.begin() }; it != str.end() - 3; it++)
		if (*it == *(it + 3) && *(it + 1) == *(it + 2) && *it != *(it + 1))
			return true;
	return false;
}

int main()
{
	std::ifstream input{ "input" };
	std::string line{};
	int count{};
	while (std::getline(input, line))
	{
		std::vector<std::string> out(1);
		std::vector<std::string> in{};
		bool inside{};
		for (const char& c : line)
			if (c == '[') (inside = true), in.push_back("");
			else if (c == ']') (inside = false), out.push_back("");
			else if (inside) in.back().push_back(c);
			else out.back().push_back(c);
		bool valid{};
		for (const std::string& str : out)
			if (hasAbba(str))
			{
				valid = true;
				break;
			}
		if (!valid) continue;
		for (const std::string& str : in)
			if (hasAbba(str))
			{
				valid = false;
				break;
			}
		if (valid) count++;
	}

	std::cout << count << std::endl;

	return 0;
}
