#include "Swiftcipher.h"
#include <string>
#include <map>
#include <iostream>
#include <fstream>
using namespace std;

/* Swift Cipher: Frequency of words in a file corresponds to its location in the decrypted sentence */
string decipherer(string filename) {
	string line;
	ifstream infile (filename);
	string res = "";
	map<string, int> wordCount;
	map<int, string> wordCountReverse;

	if(infile.is_open()) {
		while(getline(infile, line)) {
			if (wordCount.find(line) == wordCount.end()) {
				wordCount[line] = 1;
			} else {
				wordCount[line]++;
			}
		}
	}

	for (auto itr: wordCount) {
		wordCountReverse[itr.second] = itr.first;
	}
	for (size_t i = 1; i <= wordCountReverse.size(); i++) {
		if (res.size() > 0) {res.push_back(' ');}
		res += wordCountReverse[i];
	}

	return res;
}
