#pragma once
#include <iostream>
#include <vector>
using namespace std;

#include <cstddef>

class Stack {
public:
  int size() const;
  bool isEmpty() const;
  void push(int value);
  int pop();
private:
  vector<int> v;
};
