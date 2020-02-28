#include "Node.h"
#include <iostream>

using namespace std;

void push(Node ** head, int tar){
  Node * tem = new Node();
  tem->data_ = tar;
  tem->next_ = * head;
  * head = tem;
}

void pop(Node ** head, int tar){
  Node ** cur = head;
  while(*cur){
    int curVal = (*cur)->data_;

    if(curVal == tar){
      Node * temp = * cur;
      * cur = (*cur)->next_;
      delete temp;
      break;
    }
    else{cur = & (*cur)->next_;}
  }
}

bool exist(Node * head, int tar){
  if(! head){
    return false;
  }
  Node * cur = head;
  while(cur){
    if (cur->data_ == tar){
      return true;}
    else{cur = cur->next_;}
  }
  return false;
}

Node *listSymmetricDifference(Node *first, Node *second) {
  Node * res = NULL;
  Node * cur = first;

  while(cur){
    if(! exist(res, cur->data_)){push(& res, cur->data_);}
    cur = cur->next_;
  }

  cur = second;
  while(cur){
    int curVal = cur->data_;
    if(exist(res, curVal)){pop(& res, curVal);}
    else{push(& res, curVal);}
    cur = cur->next_;
  }

  return res;
}

Node::Node() {
    numNodes++;
}

Node::Node(Node &other) {
    this->data_ = other.data_;
    this->next_ = other.next_;
    numNodes++;
}

Node::~Node() {
    numNodes--;
}

int Node::numNodes = 0;
