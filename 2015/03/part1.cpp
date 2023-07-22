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

	Coords pos{ 0, 0 };
	std::unordered_set<Coords, Hash> locations{};
	for (const char& c : instructions)
	{
		locations.emplace(pos);
		switch (c)
		{
		case '^': pos.y++; break;
		case '<': pos.x--; break;
		case '>': pos.x++; break;
		case 'v': pos.y--; break;
		}
	}
	locations.emplace(pos);

	std::cout << locations.size() << std::endl;

	return 0;
}
