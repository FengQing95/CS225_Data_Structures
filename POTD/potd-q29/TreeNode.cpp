#include "TreeNode.h"
#include <iostream>
#include <vector>

TreeNode * deleteNode(TreeNode* root, int key) {
  TreeNode *& cur = root;
  if(! cur){return root;}

  else{
    if(cur->left_ && isDeleted(cur->left_, key)){return root;}
    if(root->val_ == key){
      delete_(root);
      return root;
    }
    if(cur->right_ && isDeleted(cur->right_, key)){return root;}
  }
  return root;
}

bool isDeleted(TreeNode *& cur, int key){
  if(cur->left_ && isDeleted(cur->left_, key)){return true;}

  if(cur->val_ == key){
    delete_(cur);
    return true;
  }

  if(cur->right_ && isDeleted(cur->right_, key)){return true;}

  return false;
}

void delete_(TreeNode *& tar){
  if(! tar->left_ && ! tar->right_){
    delete tar;
    tar = NULL;
  }
  else if(! tar->left_ || ! tar->right_){
    TreeNode * tem;
    if(tar->left_){tem = tar->left_;}
    else{tem = tar->right_;}
    delete tar;
    tar = tem;
  }
  else{
    tar->val_ = tar->right_->val_;
    delete tar->right_;
    tar->right_ = NULL;
  }
}


void inorderPrint(TreeNode* node)
{
    if (!node)  return;
    inorderPrint(node->left_);
    std::cout << node->val_ << " ";
    inorderPrint(node->right_);
}

void deleteTree(TreeNode* root)
{
  if (root == NULL) return;
  deleteTree(root->left_);
  deleteTree(root->right_);
  delete root;
  root = NULL;
}
