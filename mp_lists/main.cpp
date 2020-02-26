#include "./cs225/catch/catch.hpp"
#include "./tests/tests_helper.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "./cs225/PNG.h"
#include "./cs225/HSLAPixel.h"

#include "List.h"

using namespace cs225;

int main() {
  List<int> list1;
  List <int> list2;


  list1.insertBack(1);
  list1.insertBack(3);
  list1.insertBack(4);
  list1.insertBack(6);
  list2.insertBack(2);
  list2.insertBack(5);
  list2.insertBack(7);

  list1.mergeWith(list2);

  return 0;
}
