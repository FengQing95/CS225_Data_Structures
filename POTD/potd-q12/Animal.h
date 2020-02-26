// Animal.h
#pragma once
#include <string>
#include <iostream>

class Animal{
private:
  std::string type_;
  std::string food_;
public:
  std::string getType();
  void setType(std::string type);
  std::string getFood();
  void setFood(std::string type);
  std::string print();
  Animal();
  Animal(std::string, std::string);
};
