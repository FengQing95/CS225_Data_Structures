#include "Node.h"

void mergeList(Node *first, Node *second) {
  while (second){
    if(!first){
      first = second;
      break;
    }
    else if (! first->next_){
      first->next_ =  second;
      break;
    }
    Node * temp1 = first->next_;
    Node * temp2 = second->next_;
    first->next_ = second;
    second->next_ = temp1;
    first = temp1;
    second = temp2;
  }
}

Node::Node() {
    numNodes++;
}

Node::Node(const Node &other) {
    this->data_ = other.data_;
    this->next_ = other.next_;
    numNodes++;
}

Node::~Node() {
    numNodes--;
}

int Node::numNodes = 0;
