/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() {
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode * cur = head_;
  while(cur){
    ListNode * prev = cur;
    cur = cur->next;
    delete prev;
  }
  tail_ = NULL;
  length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  ListNode * cur = new ListNode(ndata);
  if(head_ == NULL){
    cur->prev = NULL;
    cur->next = NULL;
    head_ = cur;
    tail_ = cur;
  }
  else{
    cur->prev = NULL;
    cur->next = head_;
    head_->prev = cur;
    head_ = cur;
  }
  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  ListNode * cur = new ListNode(ndata);
  if(tail_ == NULL){
    cur->prev = NULL;
    cur->next = NULL;
    head_ = cur;
    tail_ = cur;
  }
  else{
    cur->next = NULL;
    cur->prev = tail_;
    tail_->next = cur;
    tail_ = cur;
  }
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  if((! start) || length_ < splitPoint){return NULL;}
  if(splitPoint < 1){return start;}

  ListNode * cur = start;
  for(int i = 0; i < splitPoint - 1 && cur; i++){
    if(cur->next){cur = cur->next;}
  }

  if(cur){
    cur = cur->next;
    cur->prev->next = NULL;
    tail_ = cur->prev;
    cur->prev = NULL;
    return cur;
  }

  return NULL;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three
  * elements in the list starting for the first three elements. If the
  * end of the list has a set of 1 or 2 elements, no rotation all be done
  * on the last 1 or 2 elements.
  *
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  int count = 0;
  ListNode * cur = head_;
  while (count + 2 < length_){
    ListNode * left = cur;
    ListNode * middle = left->next;
    ListNode * right = middle->next;
    T temp = left->data;
    left->data = middle->data;
    middle->data = right->data;
    right->data = temp;
    cur = right->next;
    count = count + 3;
  }
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  if(!head_ || !tail_ || startPoint == endPoint){return;}
  ListNode * temp = NULL;
  ListNode * cur = startPoint;
  ListNode * originStart = startPoint;
  ListNode * originStartPrev = startPoint->prev;
  ListNode * originEnd = endPoint;
  ListNode * originEndNext = endPoint->next;

  while(cur != endPoint){
    temp = cur->prev;
    cur->prev = cur->next;
    cur->next = temp;
    cur = cur->prev;
  }

  temp = cur->prev;
  cur->prev = originStartPrev;
  cur->next = temp;
  endPoint = originStart;
  endPoint->next = originEndNext;
  startPoint = originEnd;
  startPoint->prev = originStartPrev;

  if(! originStartPrev){
    head_ = cur;
  }
  else{
    originStartPrev->next = originEnd;
  }

  if(! originEndNext){
    tail_ = endPoint;
  }
  else{
    originEndNext->prev = originStart;
  }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  if(length_ <= 1){return;}
  ListNode * startPoint = head_;
  ListNode * endPoint = head_;

  while(endPoint){
    for(int i = 0; i < n - 1; i++){
      if(! endPoint->next){
        reverse(startPoint, endPoint);
        return;
      }
      endPoint = endPoint->next;
    }

    reverse(startPoint, endPoint);
    if(! endPoint->next){return;}
    else{
      startPoint = endPoint->next;
      endPoint = startPoint;
    }
  }
  //for(ListNode * cur = head_; cur; cur = cur->next){std::cout << cur->data << std::endl;}
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  if(! first){return second;}
  if(! second){return first;}

  ListNode * left = NULL;
  ListNode * right = NULL;

  if(first->data < second->data){
    left = first;
    right = first;
    first = first->next;
  }
  else{
    left = second;
    right = second;
    second = second->next;
  }

  while(first && second){
    if(first->data < second->data){
      right->next = first;
      right = first;
      first = first->next;
    }
    else{
      right->next = second;
      right = second;
      second = second->next;
    }
  }

  if(first){right->next = first;}
  else{right->next = second;}
  return left;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  if(chainLength <= 1){return start;}
  ListNode * left = start;
  ListNode * right = split(start, chainLength / 2);
  left = mergesort(left, chainLength / 2);
  right = mergesort(right, chainLength - chainLength / 2);
  return merge(left, right);
}
