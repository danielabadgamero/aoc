#include <string>
#include <fstream>
#include <iostream>

bool valid(const std::string& pass)
{
	bool req{};
	for (std::string::const_iterator c{ pass.begin() }; c != pass.end() - 2; c++)
		if (*c + 1 == *(c + 1) && *c + 2 == *(c + 2))
		{
			req = true;
			break;
		}
	if (!req) return false;
	if (pass.find('i') != pass.npos) return false;
	if (pass.find('o') != pass.npos) return false;
	if (pass.find('l') != pass.npos) return false;

	bool firstPair{};
	for (std::string::const_iterator c{ pass.begin() }; c != pass.end() - 1 && c != pass.end(); c++)
		if (*c == *(c + 1))
		{
			if (firstPair) return true;
			else (firstPair = true), c++;
		}
	return false;
}

void inc(std::string& pass)
{
	for (std::string::iterator c{ pass.begin() }; c != pass.end(); c++)
		if (*c == 'i' || *c == 'o' || *c == 'l')
		{
			(*c)++;
			for (std::string::iterator d{ c + 1}; d != pass.end(); d++)
				*d = 'a';
			return;
		}
	for (std::string::reverse_iterator c{ pass.rbegin() }; c != pass.rend(); c++)
		if (*c < 'z')
		{
			(*c)++;
			return;
		}
		else *c = 'a';
}

int main()
{
	std::ifstream input{ "input" };
	std::string pass{};
	std::getline(input, pass);

	do inc(pass);
	while (!valid(pass));

	do inc(pass);
	while (!valid(pass));

	std::cout << pass << std::endl;

	return 0;
}
