#include "Hash.h"
#include <string>

unsigned long bernstein(std::string str, int M)
{
	unsigned long b_hash = 5381;
	//Your code here
	for (unsigned long i = 0; i < str.size(); ++i) {
		b_hash *= 33;
		b_hash += int(str[i]);
	}
	return b_hash % M;
}

std::string reverse(std::string str)
{
    std::string output = "";
	//Your code here
	for (int i = str.size() - 1; i >= 0; --i) {output.push_back(str[i]);}

	return output;
}
