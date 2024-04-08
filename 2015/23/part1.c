#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <unordered_map>

std::unordered_map<std::string, unsigned int> registers{};
size_t pc{};

int main()
{
	std::ifstream input{ "input" };
	std::string line{};
	std::vector<std::vector<std::string>> programme{};
	registers.emplace("a", 0);
	registers.emplace("b", 0);
	while (std::getline(input, line))
	{
		std::stringstream str{ line };
		std::vector<std::string> words{};
		do words.push_back("");
		while (std::getline(str, words.back(), ' '));
		if (words[1].back() == ',') words[1].pop_back();
		programme.push_back(words);
	}

	std::unordered_map<std::string, void(*)(const std::vector<std::string>&)> instructions{};

	instructions["hlf"] = [](const std::vector<std::string>& i)
	{
		registers[i[1]] /= 2;
		pc++;
	};

	instructions["tpl"] = [](const std::vector<std::string>& i)
	{
		registers[i[1]] *= 3;
		pc++;
	};

	instructions["inc"] = [](const std::vector<std::string>& i)
	{
		registers[i[1]]++;
		pc++;
	};

	instructions["jmp"] = [](const std::vector<std::string>& i)
	{
		pc += std::stoi(i[1]);
	};

	instructions["jie"] = [](const std::vector<std::string>& i)
	{
		if ((registers[i[1]] & 0b1) == 0)
			pc += std::stoi(i[2]);
		else pc++;
	};

	instructions["jio"] = [](const std::vector<std::string>& i)
	{
		if (registers[i[1]] == 1)
			pc += std::stoi(i[2]);
		else pc++;
	};

	while (pc < programme.size())
		instructions[programme[pc][0]](programme[pc]);

	std::cout << registers["b"] << std::endl;

	return 0;
}
