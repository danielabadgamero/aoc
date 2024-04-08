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

	double maxSpeed{};
	std::vector<Reindeer>::iterator max{};
	for (std::vector<Reindeer>::iterator r{ reindeers.begin() }; r != reindeers.end(); r++)
	{
		double meanSpeed{ static_cast<double>(r->speed * r->flightTime) / (r->restTime + r->flightTime) };
		if (meanSpeed > maxSpeed) (maxSpeed = meanSpeed), (max = r);
	}

	const int time{ 2503 };
	int distance{ max->flightTime * max->speed * (1 + (time - (time % (max->flightTime + max->restTime))) / (max->flightTime + max->restTime)) };

	std::cout << distance << std::endl;

	return 0;
}
