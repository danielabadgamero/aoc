#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

struct Reindeer
{
	int speed{};
	int flightTime{};
	int restTime{};
	bool flying{ true };
	int chrono{};
	int distance{};
	int points{};
};

int main()
{
	std::ifstream input{ "input" };
	std::string line{};
	std::vector<Reindeer> reindeers{};
	while (std::getline(input, line))
	{
		std::stringstream str{ line };
		std::vector<std::string> words(1);
		while (std::getline(str, words.back(), ' ')) words.push_back("");
		reindeers.push_back
			({
			 	std::stoi(words[3]),
				std::stoi(words[6]),
				std::stoi(words[13]),
			});
	}

	for (int s{}; s <= 2503; s++)
	{
		int maxDist{};
		for (Reindeer& r : reindeers)
		{
			r.chrono++;
			if (r.flying)
			{
				r.distance += r.speed;
				if (r.chrono == r.flightTime)
				{
					r.chrono = 0;
					r.flying = false;
				}
			}
			else if (r.chrono == r.restTime)
			{
				r.chrono = 0;
				r.flying = true;
			}
			if (r.distance > maxDist) maxDist = r.distance;
		}
		for (Reindeer& r : reindeers)
			if (r.distance == maxDist) r.points++;
	}

	int maxPoints{};
	for (Reindeer& r : reindeers)
		if (r.points > maxPoints) maxPoints = r.points;
	
	std::cout << maxPoints << std::endl;

	return 0;
}
