#include "potd.h"
#include <iostream>

void insertSorted(Node **Head, Node *insert) {
  Node ** cur = Head;
  while(* cur){
    if((*cur)->data_ >= insert->data_){
      break;
    }
    else{
      cur = &((*cur)->next_);
    }
  }
  Node * temp = * cur;
  * cur = insert;
  insert->next_ = temp;
}
