#include "potd.h"
#include <vector>
#include <iostream>
using namespace std;

int main() {
	// test your code here!
	std::vector<string> res = topThree("in1.txt");
	for (size_t i = 0; i < res.size(); i++) {
		std::cout << res[i] << std::endl;
	}
	return 0;
}
