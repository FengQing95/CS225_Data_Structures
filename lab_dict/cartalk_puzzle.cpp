/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>
#include <iostream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    /* Your code goes here! */
    map<string, int> words;
    string word;
    ifstream wordsFile(word_list_fname);
    if (wordsFile.is_open()) {
      while (getline(wordsFile, word)) {
        if (word.size() > 1) {
          words[word] = 1;
        }
        // avoid repeated words
      }
    }

    for (pair< const string, int> & key_val : words) {
      string curWord = key_val.first;
      string curWord1 = curWord.substr(1);
      string curWord2 = curWord[0] + curWord.substr(2);
      if (d.homophones(curWord, curWord1) && d.homophones(curWord, curWord2)) {
        ret.push_back({curWord, curWord1, curWord2});
      }
    }

    return ret;
}
