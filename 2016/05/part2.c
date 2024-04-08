#include <openssl/md5.h>

#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <algorithm>


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

	std::vector<char> pass(8);
	for (int i{}; std::find(pass.begin(), pass.end(), 0) != pass.end(); i++)
	{
		std::string hash{ nextHash(i, id) };
		if (hash[5] > '7') continue;
		if (pass.at(hash[5] - '0')) continue;
		pass[hash[5] - '0'] = hash[6];
	}

	for (const char& c : pass) std::cout << c;
	std::cout << std::endl;

	return 0;
}
