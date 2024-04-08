#include <string>
#include <vector>
#include <fstream>
#include <iostream>

void lookAndSay(std::string& num)
{
	std::string newNum{};
	for (std::string::iterator c{ num.begin() }; c != num.end();)
	{
		char n{ *c };
		int count{};
		while (n == *c && c != num.end())
			count++, c++;
		newNum.append(std::to_string(count));
		newNum.push_back(n);
	}
	num = newNum;
}

int main()
{
	std::ifstream input{ "input" };
	std::string number{};
	std::getline(input, number);

	for (int i{}; i != 40; i++)
		lookAndSay(number);

	std::cout << number.size() << std::endl;

	return 0;
}
