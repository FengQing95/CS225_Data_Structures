#include "Base.h"
#include "Derived.h"
#include <string>
#include <iostream>

std::string Derived::foo(){
  return "I will not eat them.";
}

std::string Derived::bar(){
  return "And Ham";
}

Derived::~Derived(){}
