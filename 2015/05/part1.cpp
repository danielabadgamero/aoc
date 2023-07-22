#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

constexpr std::string forbidden[]{ "ab", "cd", "pq", "xy" };
constexpr char vowels[]{ 'a', 'e', 'i', 'o', 'u' };

int main()
{
	std::ifstream input{ "input" };
	std::string line{};
	int count{};
	while (std::getline(input, line))
	{
		bool nice{ true };
		for (const std::string& str : forbidden)
			if (line.find(str) != line.npos)
			{
				nice = false;
				break;
			}
		if (!nice) continue;
		int vowelCount{};
		for (const char& c : vowels)
			if (vowelCount >= 3) break;
			else vowelCount += std::count(line.begin(), line.end(), c);
		if (vowelCount < 3) continue;
		nice = false;
		for (std::string::iterator c{ line.begin() }; c != line.end() - 1; c++)
			if (*c == *(c + 1))
			{
				nice = true;
				break;
			}
		if (nice) count++;
	}
	
	std::cout << count << std::endl;

	return 0;
}
