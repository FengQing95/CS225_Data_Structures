#pragma once
#include "Animal.h"
#include "string"

class Pet: public Animal{
  private:
    std::string name_;
    std::string owner_name_;
  public:
    void setName(std::string nu_name);
    std::string getName();
    void setOwnerName(std::string nu_owner_name);
    std::string getOwnerName();
    std::string print();
    Pet();
    Pet(std::string, std::string, std::string, std::string);
};
