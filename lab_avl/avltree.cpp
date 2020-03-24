/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node * rchild = t->right;
    t->right = rchild->left;
    rchild->left = t;

    t->height = heightOrNeg1(t->left) > heightOrNeg1(t->right) ? heightOrNeg1(t->left) : heightOrNeg1(t->right);
    t->height = t->height + 1;
    rchild->height = heightOrNeg1(rchild->left) > heightOrNeg1(rchild->right) ? heightOrNeg1(rchild->left) : heightOrNeg1(rchild->right);
    rchild->height = rchild->height + 1;
    t = rchild;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node * lchild = t->left;
    Node * tem = lchild->right;
    t->left = tem;
    lchild->right = t;

    t->height = heightOrNeg1(t->left) > heightOrNeg1(t->right) ? heightOrNeg1(t->left) : heightOrNeg1(t->right);
    t->height = t->height + 1;
    t = lchild;
    t->height = heightOrNeg1(t->left) > heightOrNeg1(t->right) ? heightOrNeg1(t->left) : heightOrNeg1(t->right);
    t->height = t->height + 1;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    int lheight = heightOrNeg1(subtree->left);
    int rheight = heightOrNeg1(subtree->right);
    if (lheight - rheight < -1){
      int rbalance = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
      if (rbalance == 1){rotateLeft(subtree);}
      else{rotateRightLeft(subtree);}
    }
    else if(lheight - rheight > 1){
      int lbalance = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
      if(lbalance == -1){rotateRight(subtree);}
      else{rotateLeftRight(subtree);}
    }

    subtree->height = heightOrNeg1(subtree->left) > heightOrNeg1(subtree->right) ? heightOrNeg1(subtree->left) : heightOrNeg1(subtree->right);
    subtree->height = subtree->height + 1;
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (! subtree){subtree = new Node(key, value);}
    else if (subtree->key < key){insert(subtree->right, key, value);}
    else if (subtree->key > key){insert(subtree->left, key, value);}
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node * lchild = subtree->left;
            while(lchild->right){lchild = lchild->right;}
            rebalance(lchild);
        } else {
            /* one-child remove */
            // your code here
            Node * tem;
            if(subtree->left){tem = subtree->left;}
            else{tem = subtree->right;}
            delete subtree;
            subtree = tem;
        }
        // your code here
        rebalance(subtree);
    }
}
