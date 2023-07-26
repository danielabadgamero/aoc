#include <string>
#include <vector>
#include <fstream>
#include <iostream>

int main()
{
	std::ifstream input{ "input" };
	std::string line{};
	std::string code{};
	int button{ 5 };
	while (std::getline(input, line))
	{
		for (const char& c : line)
		{
			int prevButton{ button };
			switch (c)
			{
			case 'L': button -= 1;
				  if (button == 6 || button == 3) button++;
				  break;
			case 'U': button -= 3; break;
			case 'R': button += 1;
				  if (button == 4 || button == 7) button--;
				  break;
			case 'D': button += 3; break;
			}
			if (button < 1 || button > 9) button = prevButton;
		}
		code.push_back(button + '0');
	}

	std::cout << code << std::endl;

	return 0;
}
