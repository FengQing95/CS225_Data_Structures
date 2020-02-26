// Your code here!
#include<string>
#include "Thing.h"
using namespace std;
using namespace potd;

Thing::Thing(int size){
  props_ct_ = 0;
  props_max_ = size;
  properties_ = new string[props_max_];
  values_ = new string[props_max_];
}

Thing::Thing(const Thing & other){
  props_max_ = other.props_max_;
  props_ct_ = other.props_ct_;
  properties_ = new string[props_max_];
  values_ = new string[props_max_];
  for(int i = 0; i < other.props_ct_; i++){
    properties_[i] = other.properties_[i];
    values_[i] = other.values_[i];
  }
}

Thing & Thing::operator = (const Thing & other){
  this->props_max_ = other.props_max_;
  this->props_ct_ = other.props_ct_;
  this->properties_ = new string[other.props_max_];
  this->values_ = new string[other.props_max_];
  for(int i = 0; i < other.props_ct_; i++){
      this->properties_[i] = other.properties_[i];
      this->values_[i] = other.values_[i];
  }
  return *this;
}

Thing::~Thing(){
  delete[] properties_;
  delete[] values_;
}

int Thing::set_property(string name, string value){
  bool findsame = false;
  for (int index = 0; index < props_ct_; index++){
    if (properties_[index] == name){
      values_[index] = value;
      findsame = true;
      return index;
    }
  }
  if (findsame == false){
    if(props_ct_ == props_max_){
      return -1;
    }


    properties_[props_ct_] = name;
    values_[props_ct_] = value;
    props_ct_++;
    return (props_ct_ - 1);
  }
  return 0;
}

string Thing::get_property(string name){
  for (int index = 0; index < props_ct_; index++){
    if (properties_[index] == name){
      return values_[index];
    }
  }
  return "";
}

//void Thing::_copy(const Thing & other){
/*  this->props_max_ = other.props_max_;
  this->props_ct_ = other.props_ct_;
  this->properties_ = new string[other.props_max_];
  this->values_ = new string[other.props_max_];
  for(int i = 0; i < other.props_ct_; i++){
    this->properties_[i] = other.properties_[i];
    this->values_[i] = other.values_[i];
  }
*/
//}

void Thing::_destroy(){
//  delete []properties_;
//  delete []values_;
}
