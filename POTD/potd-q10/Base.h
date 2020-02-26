#pragma once
#include <string>
#include <iostream>

class Base{
public:
  std::string foo();
  virtual std::string bar();
  virtual ~Base();
};
