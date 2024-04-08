#include <map>
#include <string>
#include <vector>
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
	defence[0] = 0;
	defence[1] = 13;
	defence[2] = 31;
	defence[3] = 53;
	defence[4] = 75;
	defence[5] = 102;

	std::map<int, int> extra{};
	extra[0] = 0;
	extra[1] = 25;
	extra[2] = 50;
	extra[3] = 100;
	extra[4] = 20;
	extra[5] = 40;
	extra[6] = 80;

	std::vector<std::pair<int, int>> defeats{};
	for (player.damage = 4; player.damage != 12; player.damage++)
		for (player.armour = 0; player.armour != 9; player.armour++)
			if (!play()) defeats.push_back({ player.damage, player.armour });

	int maxPrice{};
	for (const auto& pair : defeats)
	{
		int a{ pair.first };
		int d{ pair.second };

		int maxTempPrice{};
		for (int weapon{ 4 }; weapon != 9; weapon++)
			for (int armour{}; armour != 6; armour++)
				for (int ring1{}; ring1 != 7; ring1++)
					for (int ring2{}; ring2 != 7; ring2++)
					{
						if (ring1 == ring2 && ring1 != 0) continue;
						int totalAttack{ weapon };
						int totalDefence{ armour };
						if (ring1 < 4) totalAttack += ring1;
						else totalDefence += ring1 - 3;
						if (ring2 < 4) totalAttack += ring2;
						else totalDefence += ring2 - 3;
						if (totalAttack != a || totalDefence != d) continue;
						int price{ attack[weapon] + defence[armour] };
						price += extra[ring1];
						price += extra[ring2];
						if (price > maxTempPrice) maxTempPrice = price;
					}

		if (maxTempPrice > maxPrice) maxPrice = maxTempPrice;
	}

	std::cout << maxPrice << std::endl;

	return 0;
}
