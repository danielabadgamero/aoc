#include <stack>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

struct Pos
{
	int x{};
	int y{};

	bool operator==(const Pos& B) const
	{
		return x == B.x && y == B.y;
	}
};

struct Hash
{
	size_t operator()(const Pos& p) const
	{
		return (static_cast<size_t>(p.x) << 32) | p.y;
	}
};

int countNeighbours(const std::unordered_map<Pos, bool, Hash>& grid, const Pos& p)
{
	int count{};
	for (int ny{ p.y - 1 }; ny != p.y + 2; ny++)
		for (int nx{ p.x - 1 }; nx != p.x + 2; nx++)
			if (ny == p.y && nx == p.x) continue;
			else if (grid.at({ nx, ny })) count++;
	return count;
}

void step(std::unordered_map<Pos, bool, Hash>& grid)
{
	grid.at({ 0, 0 }) = true;
	grid.at({ 0, 99 }) = true;
	grid.at({ 99, 0 }) = true;
	grid.at({ 99, 99 }) = true;
	std::stack<Pos> newState{};
	for (int x{}; x != 100; x++)
		for (int y{}; y != 100; y++)
		{
			int count{ countNeighbours(grid, { x, y }) };
			if (grid.at({ x, y }))
			{
				if (count != 2 && count != 3) newState.push({ x, y });
			}
			else if (count == 3) newState.push({ x, y });
		}

	while (!newState.empty())
	{
		grid[newState.top()] = !grid[newState.top()];
		newState.pop();
	}

	grid.at({ 0, 0 }) = true;
	grid.at({ 0, 99 }) = true;
	grid.at({ 99, 0 }) = true;
	grid.at({ 99, 99 }) = true;
}

int main()
{
	std::ifstream input{ "input" };
	std::string line{};
	int inputY{};
	std::unordered_map<Pos, bool, Hash> lights{};
	while (std::getline(input, line))
	{
		for (int x{}; x != static_cast<int>(line.size()); x++)
			lights.emplace(Pos{ x, inputY }, line[x] == '#');
		inputY++;
	}

	for (int x{ -1 }; x != 101; x++)
	{
		lights.emplace(Pos{ x, -1 }, false);
		lights.emplace(Pos{ x, 100 }, false);
	}
	for (int y{}; y != 100; y++)
	{
		lights.emplace(Pos{ -1, y }, false);
		lights.emplace(Pos{ 100, y }, false);
	}

	for (int i{}; i != 100; i++)
		step(lights);

	long int count{ std::count_if(lights.begin(), lights.end(), [](auto& state) { return state.second; }) };
	std::cout << count << std::endl;

	return 0;
}
