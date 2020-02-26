#include "potd.h"
#include <iostream>
#include <string>

using namespace std;

string stringList(Node *head) {
    // your code here!
    string res = "";
    Node * cur = head;
    unsigned count = 0;

    if (cur){
      res = res + "Node " + to_string(count) + ": " + to_string(cur->data_);
    }
    else{return "Empty list";}
    cur = cur->next_;
    count ++;

    while(cur){
      res = res + " -> " + "Node " + to_string(count) + ": " + to_string(cur->data_);
      cur = cur->next_;
      count ++;
    }
    return res;
}
