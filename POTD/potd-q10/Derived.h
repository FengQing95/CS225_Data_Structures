#pragma once
#include <string>
#include <iostream>
#include "Base.h"

class Derived: public Base {
public:
  std::string foo();
  std::string bar();
  virtual ~Derived();
};
