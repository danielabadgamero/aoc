#include <openssl/md5.h>

#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <iostream>


std::string calculate_md5(const std::string& str)
{
	unsigned char result[MD5_DIGEST_LENGTH]{};
	MD5((unsigned char*)str.c_str(), str.size(), result);

	std::ostringstream sout{};
	sout << std::hex << std::setfill('0');
	for(long long c : result)
		sout << std::setw(2) << (long long)c;
	return sout.str();
}

static std::string nextHash(int& index, const std::string& id)
{
	std::string hash{};
	do hash = calculate_md5(id + std::to_string(index++));
	while (!hash.starts_with("00000"));
	return hash;
}

int main()
{
	std::ifstream input{ "input" };
	std::string id{};
	std::getline(input, id);

	int index{};
	std::string password{};
	for (int i{}; i != 8; i++)
		password.push_back(nextHash(index, id).at(5));

	std::cout << password << std::endl;

	return 0;
}
