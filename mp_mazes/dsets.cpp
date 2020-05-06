/* Your code here! */
#include "dsets.h"
#include <iostream>
#include <vector>

using std::vector;

void DisjointSets::addelements(int num) {
  for (int i = 0; i < num; i++) {
    s.push_back(-1);
  }
}


int DisjointSets::find(int elem) {
  if (s[elem] < 0) {
    return elem;
  } else {
    int res = find(s[elem]);
    s[elem] = res;
    return res;
  }
}


void DisjointSets::setunion(int a, int b) {
  int root_a = find(a);
  int root_b = find(b);

  int newSize = s[root_a] + s[root_b];
  if (s[root_a] < s[root_b]) {
    s[root_b] = root_a;
    s[root_a] = newSize;
  } else {
    s[root_a] = root_b;
    s[root_b] = newSize;
  }
}


int DisjointSets::size(int elem) {
  return -1 * s[find(elem)];
}

void DisjointSets::clear() {
  s.clear();
}
