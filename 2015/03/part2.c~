#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>
#include <unordered_set>

struct Coords
{
	int x{};
	int y{};

	bool operator==(const Coords& B) const
	{
		return x == B.x && y == B.y;
	}
};

struct Hash
{
	size_t operator()(const Coords& c) const
	{
		return (static_cast<size_t>(c.x) << 32) || static_cast<size_t>(c.y);
	}
};

int main()
{
	std::ifstream input{ "input" };
	std::vector<char> instructions{ std::istreambuf_iterator<char>(input), {} };

	int turn{};
	Coords pos[2]{};
	std::unordered_set<Coords, Hash> locations{};
	for (const char& c : instructions)
	{
		locations.emplace(pos[turn]);
		switch (c)
		{
		case '^': pos[turn].y++; break;
		case '<': pos[turn].x--; break;
		case '>': pos[turn].x++; break;
		case 'v': pos[turn].y--; break;
		}
		turn = !turn;
	}
	locations.emplace(pos[turn]);

	std::cout << locations.size() << std::endl;

	return 0;
}
