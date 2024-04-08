#include <string>
#include <vector>
#include <cstdint>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

struct Wire
{
	enum Op
	{
		UNDEF,
		NONE,
		AND,
		OR,
		LSHIFT,
		RSHIFT,
		NOT,
	} operation{};
	Op savedOp{};
	Wire* inA{};
	Wire* inB{};
	uint16_t imm{};
	uint16_t savedImm{};

	int in()
	{
		if (operation != UNDEF)
		{
			savedOp = operation;
			savedImm = imm;
		}
		switch (operation)
		{
		case NONE:
			return (inA ? inA->in() : imm);
		case NOT:
			imm = ~inA->in();
			break;
		case AND:
			imm = (inA ? inA->in() : imm) & inB->in();
			break;
		case OR:
			imm = inA->in() | inB->in();
			break;
		case LSHIFT:
			imm = inA->in() << imm;
			break;
		case RSHIFT:
			imm = inA->in() >> imm;
			break;
		case UNDEF: return imm;
		}
		operation = UNDEF;
		return imm;
	}
};

static bool isNumber(const std::string& str)
{
	for (const char& c : str)
		if (c < '0' || c > '9') return false;
	return true;
}

int main()
{
	std::ifstream input{ "input" };
	std::string line{};
	std::vector<std::vector<std::string>> text{};
	while (std::getline(input, line))
	{
		std::vector<std::string> words(1);
		std::stringstream str{ line };
		while (std::getline(str, words.back(), ' '))
			words.push_back("");
		words.pop_back();
		text.push_back(words);
	}

	std::unordered_map<std::string, Wire> circuit{};
	
	for (const std::vector<std::string>& line : text)
		circuit.emplace(line.back(), Wire{});

	for (const std::vector<std::string>& line : text)
	{
		switch (line.size())
		{
		case 3:
			if (isNumber(line[0]))
				circuit[line.back()].imm = static_cast<uint16_t>(std::stoi(line[0]));
			else circuit[line.back()].inA = &circuit[line[0]];
			circuit[line.back()].operation = Wire::NONE;
			break;
		case 4:
			circuit[line.back()].inA = &circuit[line[1]];
			circuit[line.back()].operation = Wire::NOT;
			break;
		case 5:
			if (isNumber(line[0]))
				circuit[line.back()].imm = static_cast<uint16_t>(std::stoi(line[0]));
			else circuit[line.back()].inA = &circuit[line[0]];
			if (isNumber(line[2]))
				circuit[line.back()].imm = static_cast<uint16_t>(std::stoi(line[2]));
			else circuit[line.back()].inB = &circuit[line[2]];

			if (line[1] == "AND")
				circuit[line.back()].operation = Wire::AND;
			else if (line[1] == "OR")
				circuit[line.back()].operation = Wire::OR;
			else if (line[1] == "LSHIFT")
				circuit[line.back()].operation = Wire::LSHIFT;
			else circuit[line.back()].operation = Wire::RSHIFT;
			break;
		}
	}

	Wire* wire{ &circuit["a"] };
	
	circuit["b"].imm = wire->in();

	for (auto& pair : circuit)
	{
		pair.second.operation = pair.second.savedOp;
		if (pair.first != "b")
			pair.second.imm = pair.second.savedImm;
	}

	std::cout << wire->in() << std::endl;

	return 0;
}
