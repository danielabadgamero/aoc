#include <map>
#include <set>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>

int main()
{
	std::ifstream input{ "input" };
	std::string line{};
	std::set<std::string> possible{};
	while (std::getline(input, line))
	{
		std::stringstream str{ line };
		std::vector<std::string> words{};
		do words.push_back("");
		while (std::getline(str, words.back(), '-'));
		words.pop_back();
		std::map<int, std::set<char>> times{};
		std::string enc{};
		for (size_t i{}; i != words.size() - 1; i++) enc.append(words[i]);
		for (char c{ 'a' }; c <= 'z'; c++)
		{
			int count{ static_cast<int>(std::count(enc.begin(), enc.end(), c)) };
			if (count) times[count].emplace(c);
		}
		std::string id{ words.back().substr(0, 3) };
		std::string checksum{ words.back().substr(4, 5) };
		std::vector<char> mostCommon{};
		int count{};
		bool valid{ true };
		for (std::map<int, std::set<char>>::reverse_iterator letters{ times.rbegin() }; letters != times.rend(); letters++)
		{
			for (const char& c : letters->second)
			{
				if (c != checksum[count++])
				{
					valid = false;
					break;
				}
				if (count == 5) break;
			}
			if (count == 5) break;
		}
		if (!valid) continue;
		possible.emplace(line);
	}

	int id{};
	for (const std::string& s : possible)
	{
		bool found{};
		std::vector<std::string> words(1);
		for (const char& c : s)
			if (c == '-') words.push_back("");
			else words.back().push_back(c);
		id = std::stoi(words.back());
		int offset{ id % 26 };
		words.pop_back();
		for (std::string& str : words)
		{
			for (char& c : str)
				if (c + offset > 'z')
					c = 'a' + offset - ('z' - c) - 1;
				else c += offset;
			if (str.find("north") != str.npos) { found = true; break; }
		}
		if (found) break;
	}

	std::cout << id << std::endl;

	return 0;
}
