#include "potd.h"
#include <iostream>

double sum(vector<double>::iterator start, vector<double>::iterator end){
  double res = 0.0;
  for(auto itr = start; itr != end; ++itr){
    res = res + *itr;
  }
  return res;
}

vector<double>::iterator max_iter(vector<double>::iterator start, vector<double>::iterator end){
  vector<double>::iterator cur = start;
  for(auto itr = start; itr != end; ++itr){
    if (*itr > *cur){cur = itr;}
  }
  return cur;
}

void sort_vector(vector<double>::iterator start, vector<double>::iterator end){
  if(start == end){return;}
  else{
    auto itr = start;
    auto nextItr = std::next(itr, 1);
    auto maxItr = max_iter(start, end);
    double temp = *itr;
    *itr = *maxItr;
    *maxItr = temp;
    sort_vector(nextItr, end);
  }
}
