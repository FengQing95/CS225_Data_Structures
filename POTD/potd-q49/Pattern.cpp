#include "Pattern.h"
#include <string>
#include <iostream>
#include <vector>
#include <map>


bool wordPattern(std::string pattern, std::string str) {

    //write your code her
    std::vector<std::string> words;
    std::string curWord;
    for (size_t i = 0; i < str.size(); ++i) {
        char curLetter = str[i];
        if (curLetter != ' ') {curWord.push_back(curLetter);}
        else {
            words.push_back(curWord);
            curWord = "";
        }
    }
    words.push_back(curWord);

    if (words.size() != pattern.size()) {return false;}
    std::map<char, std::string> char2word;
    for (size_t i = 0; i < words.size(); ++i) {
        if (char2word.find(pattern[i]) == char2word.end()) {
            // check if words[i] has already been in values
            for (auto itr = char2word.begin(); itr != char2word.end(); ++itr) {
                if (words[i] == itr->second) {return false;}
            }
            char2word.insert({pattern[i], words[i]});
        }
        if (char2word[pattern[i]] != words[i]) {return false;}
    }
    return true;
}
