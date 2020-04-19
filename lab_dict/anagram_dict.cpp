/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    vector<string> words;
    string word;
    ifstream wordsFile(filename);
    if (wordsFile.is_open()) {
      while (getline(wordsFile, word)) {
        words.push_back(word);
      }
    }
    wordsFile.close();

    for (size_t i = 0; i < words.size(); i++) {
      string curWord = words[i];
      if (curWord.size() >= 2) {
        for (size_t j = 0; j < words.size(); j++) {
          if (anagram(curWord, words[j]) && dict.find(words[j]) == dict.end()) {
            dict[curWord].push_back(words[j]);
          }
        }
      }
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    for (size_t i = 0; i < words.size(); i++) {
      string curWord = words[i];
      if (curWord.size() >= 2) {
        for (size_t j = 0; j < words.size(); j++) {
          if (anagram(curWord, words[j]) && dict.find(words[j]) == dict.end()) {
            dict[curWord].push_back(words[j]);
          }
        }
      }
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    vector<string> res;
    if(dict.find(word) != dict.end()) {
      res = (dict.find(word))->second;
    }
    return res;
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> res;
    for (const std::pair<string, vector<string>> & key_val : dict) {
      if (key_val.second.size() > 1) {
        res.push_back(key_val.second);
      }
    }
    return res;
}


bool AnagramDict::anagram(string word1, string word2) {
  string w1 = word1;
  string w2 = word2;

  std::sort(w1.begin(), w1.end());
  std::sort(w2.begin(), w2.end());
  return w1 == w2;
}
