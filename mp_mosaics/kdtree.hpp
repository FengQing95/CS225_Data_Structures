/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
     if (first[curDim] < second[curDim]) {return true;}
     else if (first[curDim] == second[curDim]) {return  first < second;}
     else {return false;}
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     double cur = 0;
     double future = 0;
     for (int i = 0; i < Dim; i++) {
       future += (potential[i] - target[i]) * (potential[i] - target[i]);
       cur += (currentBest[i] - target[i]) * (currentBest[i] - target[i]);
     }
     if (future < cur) {return true;}
     else if (future == cur) {return (currentBest > potential);}
     else {return false;}
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::buildTree(int left, int right, int d) {
  if (right < left) {return NULL;}

  int avg = (left + right) / 2;
  pick(left, right, avg, d);

  KDTreeNode * newNode = new KDTreeNode(pointVec[avg]);
  newNode->right = buildTree(avg + 1, right, (d + 1) % Dim);
  newNode->left = buildTree(left, avg - 1, (d + 1) % Dim);

  return newNode;
}

template <int Dim>
void KDTree<Dim>::pick(int left, int right, int k, int d) {
  if (right < left) {return;}

  int j = divide(left, right, (left + right) / 2, d);
  if (k < j) {pick(left, j - 1, k, d);}
  else if (k == j) {return;}
  else {pick(j + 1, right, k, d);}
}

template <int Dim>
int KDTree<Dim>::divide(int left, int right, int pivot, int d) {
  Point<Dim> pivotValue = pointVec[pivot];
  exchange(pivot, right);

  int res = left;
  for (int i = left; i <= right - 1; ++i) {
    if (smallerDimVal(pointVec[i], pivotValue, d)) {
      exchange(i, res);
      res += 1;
    }
  }
  exchange(right, res);

  return res;
}

template <int Dim>
void KDTree<Dim>::exchange(int i, int j) {
  Point<Dim> temp = pointVec[i];
  pointVec[i] = pointVec[j];
  pointVec[j] = temp;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
     for (size_t i = 0; i < newPoints.size(); ++i) {pointVec.push_back(newPoints[i]);}
     root = buildTree(0, newPoints.size() - 1, 0);
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
   pointVec = other.pointVec;
   root = buildTree(root, 0, pointVec.size() - 1, 0);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
   if (this != &rhs) {
     delete this;
     this = new KDTree(rhs);
   }

  return *this;
}

template <int Dim>
void KDTree<Dim>::delete_helper(KDTreeNode * root) {
  if (!root) {return;}
  delete_helper(root->left);
  delete_helper(root->right);
  delete root;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   delete_helper(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
     return findNearestNeighbor_helper(root, query, root->point, 0);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor_helper(KDTreeNode * root, const Point<Dim> target, Point<Dim> cur, int d) const {
  if (!root->left && !root->right) {return root->point;}

  bool flag = false;
  if (smallerDimVal(target, root->point, d)) {
    if (! (root->left)) {
      cur = findNearestNeighbor_helper(root->right, target, cur, (d + 1) % Dim);
    }
    else {
      flag = true;
      cur = findNearestNeighbor_helper(root->left, target, cur, (d + 1) % Dim);
    }
  }

  else {
    if (! (root->right)) {
      cur = findNearestNeighbor_helper(root->left, target, cur, (d + 1) % Dim);
      flag = true;
    }
    else {
      cur = findNearestNeighbor_helper(root->right, target, cur, (d + 1) % Dim);
    }
  }

  if (shouldReplace(target, cur, root->point)) {cur = root->point;}
  double curValue = 0;
  for (int i = 0; i < Dim; ++i) {curValue += (cur[i] - target[i]) * (cur[i] - target[i]);}

  if (((root->point)[d] - target[d]) * ((root->point)[d] - target[d]) <= curValue) {
    if (flag) {
      if (root->right) {
        Point<Dim> nearest = findNearestNeighbor_helper(root->right, target, cur, (d + 1) % Dim);
        if (shouldReplace(target, cur, nearest)) {cur = nearest;}
      }
    }
    else {
      if (root->left) {
        Point<Dim> nearest = findNearestNeighbor_helper(root->left, target, cur, (d + 1) % Dim);
        if (shouldReplace(target, cur, nearest)) {cur = nearest;}
      }
    }
  }

  return cur;
}
