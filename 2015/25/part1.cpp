#include <string>
#include <vector>
#include <fstream>
#include <iostream>

static size_t prev(size_t num)
{
	if (num == 1) return 20151125;
	else return (prev(num - 1) * 252533) % 33554393;
}

int main()
{
	std::ifstream input{ "input" };

	const int row{ 2981 };
	const int col{ 3075 };

	size_t num{ 1 };
	for (int i{ 1 }; i != row; i++) num += i;
	for (int i{ 1 }; i != col; i++) num += i + row;

	num = prev(num);

	std::cout << num << std::endl;

	return 0;
}
