#include "Pet.h"
#include "Animal.h"
#include <string>
#include <iostream>
using namespace std;

void Pet::setName(string nu_name){
  name_ = nu_name;
}

string Pet::getName(){
  return name_;
}

void Pet::setOwnerName(string nu_owner_name){
  owner_name_ = nu_owner_name;
}

string Pet::getOwnerName(){
  return owner_name_;
}

string Pet::print(){
  return "My name is " + name_;
}

Pet::Pet(): Animal("cat", "fish"){
  name_ = "Fluffy";
  owner_name_ = "Cinda";
}

Pet::Pet(string type, string food, string name, string owner_name): Animal(type, food)
{
  name_ = name;
  owner_name_ = owner_name;
}
