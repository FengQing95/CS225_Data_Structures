#include "TreeNode.h"

#include <cstddef>
#include <iostream>
using namespace std;

TreeNode::TreeNode() : left_(NULL), right_(NULL) { }

int TreeNode::getHeight() {
  if(! left_ && ! right_){return 0;}
  else if(! left_){return right_->getHeight() + 1;}
  else if(! right_){return left_->getHeight() + 1;}
  else{return left_->getHeight() > right_->getHeight() ? left_->getHeight() + 1 : right_->getHeight() + 1;}
}
