#include "Animal.h"
#include <string>
#include <iostream>

std::string Animal::getType(){
  return type_;
}

void Animal::setType(std::string type){
  type_ = type;
}

std::string Animal::getFood(){
  return food_;
}

void Animal::setFood(std::string food){
  food_ = food;
}

std::string Animal::print(){
  std::string res = "I am a ";
  res = res.append(type_);
  res = res.append(".");
  return res;
}

Animal::Animal(){
  food_ = "fish";
  type_ = "cat";
}

Animal::Animal(std::string type, std::string food){
  type_ = type;
  food_ = food;
}
