#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>
#include <unordered_set>

struct Pos
{
	int x{};
	int y{};

	bool operator==(const Pos& p) const
	{
		return p.x == x && p.y == y;
	}
} pos{};

struct Hash
{
	size_t operator()(const Pos& pos) const
	{
		return (static_cast<size_t>(pos.x) << 32) | static_cast<size_t>(pos.y);
	}
};

int main()
{
	std::ifstream input{ "input" };
	std::string step{};
	int dir{};
	std::unordered_set<Pos, Hash> history{};
	while (std::getline(input, step, ' '))
	{
		if (step[0] == 'R') dir++; else dir--;
		dir += 4; dir %= 4;
		int num{ std::stoi(step.substr(1)) };
		bool doubled{};

		for (int i{}; i != num; i++)
		{
			pos.y += (1 - dir) % 2;
			pos.x += (2 - dir) % 2;
			if (history.contains(pos))
			{
				doubled = true;
				break;
			}
			history.emplace(pos);
		}

		if (doubled) break;
	}

	std::cout << std::abs(pos.x) + std::abs(pos.y) << std::endl;

	return 0;
}
