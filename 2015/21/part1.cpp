#include <map>
#include <string>
#include <vector>
#include <climits>
#include <sstream>
#include <fstream>
#include <iostream>

struct Entity
{
	int HP{};
	int damage{};
	int armour{};
};

Entity boss{};
Entity player{};

bool play()
{
	int b{ boss.HP };
	int p{ player.HP };
	int pTotal{ player.damage - boss.armour };
	if (pTotal < 1) pTotal = 1;
	int bTotal{ boss.damage - player.armour };
	if (bTotal < 1) bTotal = 1;
	while (true)
	{
		b -= pTotal;
		if (b <= 0) return true;
		p -= bTotal;
		if (p <= 0) return false;
	}
}

int main()
{
	std::ifstream input{ "input" };
	std::string line{};
	while (std::getline(input, line))
	{
		std::stringstream str{ line };
		std::vector<std::string> words{};
		do words.push_back("");
		while (std::getline(str, words.back(), ' '));
		words.pop_back();
		if (boss.HP == 0) boss.HP = std::stoi(words.back());
		else if (boss.damage == 0) boss.damage = std::stoi(words.back());
		else boss.armour = std::stoi(words.back());
	}

	player.HP = 100;
	
	std::map<int, int> attack{};
	attack[4] = 8;
	attack[5] = 10;
	attack[6] = 25;
	attack[7] = 40;
	attack[8] = 74;

	std::map<int, int> defence{};
	defence[1] = 13;
	defence[2] = 31;
	defence[3] = 53;
	defence[4] = 75;
	defence[5] = 102;

	std::map<int, int> extraAttack{};
	extraAttack[0] = 0;
	extraAttack[1] = 25;
	extraAttack[2] = 50;
	extraAttack[3] = 100;

	std::map<int, int> extraDefence{};
	extraDefence[0] = 0;
	extraDefence[1] = 20;
	extraDefence[2] = 40;
	extraDefence[3] = 80;

	std::vector<std::pair<int, int>> wins{};
	for (player.damage = 4; player.damage != 11; player.damage++)
		for (player.armour = 0; player.armour != 8; player.armour++)
			if (play()) wins.push_back({ player.damage, player.armour });

	int minPrice{ INT_MAX };
	for (const auto& pair : wins)
	{
		int a{ pair.first };
		int d{ pair.second };

		int aPrice{ INT_MAX };
		for (int i{ 4 }; i <= a && i <= 8; i++)
			for (int j{}; j + i <= a && j <= 3; j++)
				if (i + j != a) continue;
				else
				{
					int price{ attack[i] + extraAttack[j] };
					if (price < aPrice) aPrice = price;
				}
		int dPrice{ INT_MAX };
		for (int i{ 1 }; i <= d && i <= 5; i++)
			for (int j{}; j + i <= d && j <= 3; j++)
				if (i + j != d) continue;
				else
				{
					int price{ defence[i] + extraDefence[j] };
					if (price < dPrice) dPrice = price;
				}
		if (d == 0) dPrice = 0;
		if (aPrice + dPrice < minPrice) minPrice = aPrice + dPrice;
	}

	std::cout << minPrice << std::endl;

	return 0;
}
