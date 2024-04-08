#include <string>
#include <vector>
#include <fstream>
#include <iostream>

static std::vector<std::string> getABAs(const std::string& str)
{
	std::vector<std::string> v{};
	for (std::string::const_iterator it{ str.begin() }; it != str.end() - 2; it++)
		if (*it == *(it + 2) && *it != *(it + 1))
			v.push_back(str.substr(it - str.begin(), 3));
	return v;
}

static bool hasBAB(const std::string& str, const std::string& aba)
{
	std::string bab{};
	bab.push_back(aba[1]);
	bab.push_back(aba[0]);
	bab.push_back(aba[1]);
	return str.find(bab) != str.npos;
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
		std::vector<std::string> ABAs{};
		for (const std::string& str : out)
		{
			std::vector<std::string> a{ getABAs(str) };
			for (const std::string& s : a) ABAs.push_back(s);
		}
		bool valid{};
		for (const std::string& aba : ABAs)
		{
			for (const std::string& str : in)
				if (hasBAB(str, aba))
				{
					valid = true;
					break;
				}
			if (valid) break;
		}
		if (valid) count++;
	}

	std::cout << count << std::endl;

	return 0;
}
