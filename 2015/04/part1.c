#include <openssl/md5.h>

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

int main()
{
	std::ifstream input{ "input" };
	std::string key{ std::istreambuf_iterator<char>(input), {} };
	size_t index{ key.find('\n') };
	while (index != key.npos)
	{
		key.erase(index);
		index = key.find('\n');
	}

	bool found{};
	int i{};
	for (; !found; i++)
	{
		std::string str{ key + std::to_string(i) };
		std::string result{ calculate_md5(str) };
		for (int c{}; c != 5; c++)
			if (result[c] != '0') break;
			else if (c == 4) found = true;
	}
	std::cout << --i << std::endl;

	return 0;
}
