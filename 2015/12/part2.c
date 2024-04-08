#include <string>
#include <fstream>
#include <iostream>

int main()
{
	std::ifstream input{ "input" };
	std::string data{};
	std::getline(input, data);

	int sum{};
	std::string buffer{};
	for (size_t i{}; i != data.size(); i++)
		if (data[i] == '{')
		{
			int depth{};
			for (size_t j{ i }; j != data.size(); j++)
			{
				if (data[j] == '{' || data[j] == '[') depth++;
				else if (data[j] == '}' || data[j] == ']') depth--;
				if (depth > 1) continue;
				else if (depth == 0) break;
				if (data.substr(j, 3) == "red")
				{
					while (depth >= 1)
					{
						j++;
						if (data[j] == '{' || data[j] == '[') depth++;
						else if (data[j] == '}' || data[j] == ']') depth--;
					}
					i = j;
					break;
				}
			}
		}
		else if (data[i] == '-' || (data[i] >= '0' && data[i] <= '9')) buffer.push_back(data[i]);
		else if (!buffer.empty())
		{
			sum += std::stoi(buffer);
			buffer.clear();
		}

	std::cout << sum << std::endl;

	return 0;
}
