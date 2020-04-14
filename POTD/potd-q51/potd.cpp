#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;


vector<string> topThree(string filename) {
    string line;
    ifstream infile (filename);
    vector<string> ret;

    int count = 0;
    std::map<string, int> str2count;
    std::map<int, string> count2tr;
    if (infile.is_open()) {
        while (getline(infile, line)) {
            // do things
            if (str2count.find(line) == str2count.end()) {
                str2count[line] = 1;
            } else {
                str2count[line]++;
            }
            count++;
        }
    }

    for (auto itr : str2count) {
        count2tr[itr.second] = itr.first;
    }
    for (int i = count; i > 0; i--) {
        if (count2tr.find(i) != count2tr.end()) {ret.push_back(count2tr[i]);}
        if (ret.size() == 3) {
            break;
        }
    }

    infile.close();
    return ret;
}
