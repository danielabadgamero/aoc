#include <stack>
#include <vector>
#include <climits>
#include <sstream>
#include <fstream>
#include <iostream>

struct Boss
{
	int HP{ 55 };
	int damage{ 8 };
};

enum Spell
{
	missile,
	drain,
	shield,
	poison,
	recharge
};

struct Player
{
	int HP{ 50 };
	int mana{ 500 };
	int armour{};
	enum Effect
	{
		shield,
		poison,
		recharge,

		total_effects
	};
	int timer[total_effects]{};
};

struct Turn
{
	Boss boss{};
	Player player{};
	int manaSpent{};
	Spell spell{};
};

int minMana{ INT_MAX };

static void round(Turn& t)
{
	if (t.manaSpent > minMana) return;
	if (t.player.timer[Player::shield])
	{
		t.player.armour = 7;
		t.player.timer[Player::shield]--;
		if (t.player.timer[Player::shield] == 0) t.player.armour = 0;
	}
	if (t.player.timer[Player::poison])
	{
		t.boss.HP -= 3;
		t.player.timer[Player::poison]--;
	}
	if (t.player.timer[Player::recharge])
	{
		t.player.mana += 101;
		t.player.timer[Player::recharge]--;
	}
	switch (t.spell)
	{
	case missile:
		if (t.player.mana < 53) return;
		t.player.mana -= 53;
		t.manaSpent += 53;
		t.boss.HP -= 4;
		break;
	case drain:
		if (t.player.mana < 73) return;
		t.player.mana -= 73;
		t.manaSpent += 73;
		t.boss.HP -= 2;
		t.player.HP += 2;
		break;
	case shield:
		if (t.player.mana < 113) return;
		if (t.player.timer[Player::shield]) return;
		t.player.mana -= 113;
		t.manaSpent += 113;
		t.player.timer[Player::shield] = 6;
		break;
	case poison:
		if (t.player.mana < 173) return;
		if (t.player.timer[Player::poison]) return;
		t.player.mana -= 173;
		t.manaSpent += 173;
		t.player.timer[Player::poison] = 6;
		break;
	case recharge:
		if (t.player.mana < 229) return;
		if (t.player.timer[Player::recharge]) return;
		t.player.mana -= 229;
		t.manaSpent += 229;
		t.player.timer[Player::recharge] = 5;
		break;
	}

	if (t.boss.HP <= 0)
		if (t.manaSpent < minMana) minMana = t.manaSpent;

	if (t.player.timer[Player::shield])
	{
		t.player.armour = 7;
		t.player.timer[Player::shield]--;
		if (t.player.timer[Player::shield] == 0) t.player.armour = 0;
	}
	if (t.player.timer[Player::poison])
	{
		t.boss.HP -= 3;
		t.player.timer[Player::poison]--;
	}
	if (t.player.timer[Player::recharge])
	{
		t.player.mana += 101;
		t.player.timer[Player::recharge]--;
	}

	t.player.HP -= t.boss.damage - t.player.armour;

	if (t.player.HP <= 0) return;

	for (int i{}; i != 5; i++)
	{
		Turn next{ t };
		next.spell = static_cast<Spell>(i);
		round(next);
	}
}

int main()
{
	std::ifstream input{ "input" };

	for (int i{}; i != 5; i++)
	{
		Turn t{};
		t.spell = static_cast<Spell>(i);
		round(t);
	}

	std::cout << minMana << std::endl;

	return 0;
}
