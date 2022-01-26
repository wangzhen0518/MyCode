#ifndef DATA_STRUCTURE_CPP_
#define DATA_STRUCTURE_CPP_

#include "data_structure.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

namespace MyDataStructure {
// stack
template <typename T>
bool stack<T>::push(const T& t) {
  if (mem_num == max_size) {
    max_size += EX_LEN;
    T* temp = new T[max_size];  // TODO: using try
                                // to allocate
                                // memory
    for (int i = 0; i < mem_num; i++) temp[i] = ar[i];
    temp[mem_num] = t;
    delete[] ar;
    ar = temp;
  } else
    ar[mem_num++] = t;
  return true;
}
template <typename T>
bool stack<T>::pop() {
  if (mem_num == 0)
    return false;
  else
    mem_num--;
}

// queue
template <typename T>
bool queue<T>::enqueue(const T& t) {
  if (mem_num == max_size) {
    T* temp = new T[max_size + EX_LEN];  // TODO: using try to
                                         // allocate memory
    for (int i = 0, j = head; i < mem_num; i++, j = (j + 1) % max_size)
      temp[i] = ar[i];
    temp[mem_num] = t;
    delete[] ar;
    ar = temp;
    max_size += EX_LEN;
    mem_num++;
    head = 0;
    rear = mem_num;
  } else {
    ar[rear++] = t;
    mem_num++;
  }
  return true;
}
template <typename T>
bool queue<T>::dequeue() {
  if (mem_num == 0)
    return false;
  else {
    mem_num--;
    head = (head + 1) % max_size;
  }
}

// list
template <typename T>
list<T>::list() {
  head = new list_node<T>;
  rear = new list_node<T>;
}
template <typename T>
list<T>::~list() {
  list_node<T>* p = head;
  list_node<T>* q = head;
  while (q != nullptr) {
    q = q->next;
    delete p;
    p = q;
  }
}
template <typename T>
list_node<T>* list<T>::search(const T& key) {
  list_node<T>* t = head;
  while (t != nullptr && t->key != key) t = t->next;
  return t;
}
template <typename T>
bool list<T>::list_delete(list_node<T>* t) {
  if (t->prev != nullptr)
    t->prev->next = t->next;
  else
    head = t->next;
  if (t->next != nullptr)
    t->next->prev = t->prev;
  else
    rear = t->prev;
  delete t;
  return true;
}
template <typename T>
bool list<T>::list_insert(const T& key) {
  rear->next = new list_node<T>;
  rear->next->prev = rear;
  rear = rear->next;
  rear->next = nullptr;
  rear->key = key;
  return true;
}
template <typename T>
void list<T>::show() {
  if (head != nullptr) {
    list_node<T>* q = head->next;
    while (q != nullptr) {
      std::cout << q->key << " ";
      q = q->next;
    }
    std::cout << "\n";
  } else
    std::cout << "empty list\n";
}

// max heap
template <typename T>
void max_heap<T>::max_heapify(int i)  // maintain the max_heap
{
  int large = i;
  int l = left(i);
  int r = right(i);
  if (l < m_heap_size && m_ar[i] < m_ar[l]) large = l;
  if (r < m_heap_size && m_ar[large] < m_ar[r]) large = r;
  if (large != i) {
    T temp = m_ar[i];
    m_ar[i] = m_ar[large];
    m_ar[large] = temp;
    max_heapify(large);
  }
}
template <typename T>  // creat a max_heap
max_heap<T>::max_heap(T a[], int len) : m_ar(len), m_heap_size(len) {
  for (int i = 0; i < len; i++) m_ar[i] = a[i];
  for (int i = (len - 1) / 2; i >= 0; i--) max_heapify(i);
}
template <typename T>
void max_heap<T>::sort() {
  for (int i = m_ar.size() - 1; i >= 1; i--) {
    T temp = m_ar[i];
    m_ar[i] = m_ar[0];
    m_ar[0] = temp;
    m_heap_size--;
    max_heapify(0);
  }
}

// max_priority_queue
template <typename T>
void max_priority_queue<T>::increase_key(int i, T k) {
  if (mh::m_ar[i] > k)
    return;
  else {
    mh::m_ar[i] = k;
    while (i > 0 && mh::m_ar[mh::parent(i)] < mh::m_ar[i]) {
      T temp = mh::m_ar[i];
      mh::m_ar[i] = mh::m_ar[mh::parent(i)];
      mh::m_ar[mh::parent(i)] = temp;
      i = mh::parent(i);
    }
  }
}
template <typename T>
void max_priority_queue<T>::insert(T k) {
  if (mh::m_ar.size() == mh::m_heap_size)
    mh::m_ar.push_back(-MAX);
  else
    mh::m_ar[mh::m_heap_size] = -MAX;
  mh::m_heap_size++;
  increase_key(mh::m_heap_size - 1, k);
}
template <typename T>
T max_priority_queue<T>::extract_max() {
  T temp = mh::m_ar[0];
  mh::m_ar[0] = mh::m_ar[mh::m_heap_size - 1];
  mh::m_heap_size--;
  mh::max_heapify(0);
  return temp;
}
template <typename T>
void max_priority_queue<T>::show() {
  using std::cout;
  using std::endl;
  using std::for_each;
  for_each(mh::m_ar.begin(), mh::m_ar.begin() + mh::m_heap_size,
           [](T x) { cout << x << " "; });
  cout << endl;
}

// binary search tree
// TODO: 用非递归方法重写
template <typename T>
void BSTree<T>::preOrder(BSTNode<T>* t) const {
  if (t != nullptr) {
    std::cout << t->key << " ";
    preOrder(t->lchild);
    preOrder(t->rchild);
  }
}
template <typename T>
void BSTree<T>::preOrder() const {
  preOrder(root);
}

template <typename T>
void BSTree<T>::inOrder(BSTNode<T>* t) const {
  if (t != nullptr) {
    inOrder(t->lchild);
    std::cout << t->key << " ";
    inOrder(t->rchild);
  }
}
template <typename T>
void BSTree<T>::inOrder() const {
  inOrder(root);
}

template <typename T>
void BSTree<T>::postOrder(BSTNode<T>* t) const {
  if (t != nullptr) {
    postOrder(t->lchild);
    postOrder(t->rchild);
    std::cout << t->key << " ";
  }
}
template <typename T>
void BSTree<T>::postOrder() const {
  postOrder(root);
}

template <typename T>
BSTNode<T>* BSTree<T>::search(BSTNode<T>* t, const T& key) const {
  while (t != nullptr && t->key != key) {
    if (t->key > key)
      t = t->lchild;
    else
      t = t->rchild;
  }
  return t;
}
template <typename T>
BSTNode<T>* BSTree<T>::search(const T& key) const {
  return search(root, key);
}

template <typename T>
BSTNode<T>* BSTree<T>::minimum(BSTNode<T>* t) const {
  if (t == nullptr) return nullptr;

  while (t->lchild != nullptr) t = t->lchild;
  return t;
}
template <typename T>
T BSTree<T>::minimum() const {
  BSTNode<T>* p = minimum(root);
  if (p != nullptr)
    return p->key;
  else
    return T(NULL);
}

template <typename T>
BSTNode<T>* BSTree<T>::maximum(BSTNode<T>* t) const {
  if (t == nullptr) return nullptr;

  while (t->rchild != nullptr) t = t->rchild;
  return t;
}
template <typename T>
T BSTree<T>::maximum() const {
  BSTNode<T>* p = maximum(root);
  if (p != nullptr)
    return p->key;
  else
    return T(NULL);
}

template <typename T>
BSTNode<T>* BSTree<T>::predecessor(BSTNode<T>* x) {
  if (x == nullptr) return nullptr;

  if (x->lchild != nullptr)
    return maximum(x->lchild);
  else {
    BSTNode<T>* p = x->parent;
    while (p != nullptr && x == p->lchild) {
      x = p;
      p = x->parent;
    }
    return p;
  }
}
template <typename T>
BSTNode<T>* BSTree<T>::successor(BSTNode<T>* x) {
  if (x == nullptr) return nullptr;

  if (x->rchild != nullptr)
    return minimum(x->rchild);
  else {
    BSTNode<T>* p = x->parent;
    while (p != nullptr && x == p->rchild) {
      x = p;
      p = x->parent;
    }
    return p;
  }
}

template <typename T>
BSTNode<T>* BSTree<T>::insert(BSTNode<T>* t, BSTNode<T>* x) {
  BSTNode<T>* p = nullptr;
  while (t != nullptr) {
    p = t;
    if (t->key == x->key) return nullptr;
    if (t->key > x->key)
      t = t->lchild;
    else
      t = t->rchild;
  }
  if (p == nullptr)  // empty tree
    root = x;
  else {
    x->parent = p;
    if (p->key > x->key)
      p->lchild = x;
    else
      p->rchild = x;
  }
  return x;
}
template <typename T>
bool BSTree<T>::insert(const T& key) {
  BSTNode<T>* x = new BSTNode<T>(key);
  if (insert(root, x) == nullptr) {
    delete x;
    return false;
  } else
    return true;
}

template <typename T>
void BSTree<T>::transplant(BSTNode<T>* u, BSTNode<T>* v) {
  if (u->parent == nullptr)
    root = v;
  else if (u == u->parent->lchild)
    u->parent->lchild = v;
  else
    u->parent->rchild = v;
  if (v != nullptr) v->parent = u->parent;
}
template <typename T>
BSTNode<T>* BSTree<T>::remove(BSTNode<T>* x) {
  if (x->lchild == nullptr)
    transplant(x, x->rchild);
  else if (x->rchild == nullptr)
    transplant(x, x->lchild);
  else {
    BSTNode<T>* suc = minimum(x);
    if (suc->parent != x) {
      transplant(suc, suc->rchild);
      suc->rchild = x->rchild;
      suc->rchild->parent = suc;
    }
    transplant(x, suc);
    suc->lchild = x->lchild;
    suc->lchild->parent = suc;
  }
  return x;
}
/*
 * another implementation maybe worse because z.key = y.key
 * when the key type is class, this action probably cost lots of time
 * another reason:
 * 算法导论第3版中文版p173有提到
 * The node we delete is not same as the node pass in to the remove
 * function in this method. Therefore, if there are other pointers
 * point to the node that we exactly delete in the program,
 * they may point to an error place after delete action.
 * It is a potential hazard.
 *
 * template <class T>
 * BSTNode<T>* BSTree<T>::remove(BSTNode<T>* &tree, BSTNode<T> *z)
 * {
 *     BSTNode<T> *x=NULL;
 *     BSTNode<T> *y=NULL;
 *
 *     if ((z->left == NULL) || (z->right == NULL) )
 *         y = z;
 *     else
 *         y = successor(z);
 *
 *     if (y->left != NULL)
 *         x = y->left;
 *     else
 *         x = y->right;
 *
 *     if (x != NULL)
 *         x->parent = y->parent;
 *
 *     if (y->parent == NULL)
 *         tree = x;
 *     else if (y == y->parent->left)
 *         y->parent->left = x;
 *     else
 *         y->parent->right = x;
 *
 *     if (y != z)
 *         z->key = y->key;
 *
 *     return y;
 * }
 */
template <typename T>
bool BSTree<T>::remove(const T& key) {
  BSTNode<T>* x = search(root, key);
  if (x != nullptr) {
    x = remove(x);
    delete x;
    return true;
  }
  return false;
}

template <typename T>
void BSTree<T>::print(BSTNode<T>* t, const T& key, int direction) const {
  if (t != nullptr) {
    if (direction == 0)
      std::cout << std::setw(2) << t->key << " is root" << std::endl;
    else
      std::cout << std::setw(2) << t->key << " is " << key << "'s "
                << std::setw(12)
                << ((direction == 1) ? "right child" : "left child")
                << std::endl;
    print(t->lchild, t->key, -1);
    print(t->rchild, t->key, 1);
  }
}
template <typename T>
void BSTree<T>::print() {
  if (root != nullptr)
    print(root, root->key, 0);
  else
    std::cout << "empty tree\n";
}

template <typename T>
void BSTree<T>::destroy(BSTNode<T>*& t) {
  if (t != nullptr) {
    destroy(t->lchild);
    destroy(t->rchild);
    delete t;
    t = nullptr;
  }
}
template <typename T>
void BSTree<T>::destroy() {
  destroy(root);
}

/******************** red black tree ********************/
template <typename T>
void RBTree<T>::preOrder(RBTNode<T>* t) const {
  if (t != nil) {
    std::cout << t->key << " ";
    preOrder(t->lchild);
    preOrder(t->rchild);
  }
}
template <typename T>
void RBTree<T>::preOrder() const {
  preOrder(root);
  std::cout << std::endl;
}

template <typename T>
void RBTree<T>::inOrder(RBTNode<T>* t) const {
  if (t != nil) {
    inOrder(t->lchild);
    std::cout << t->key << " ";
    inOrder(t->rchild);
  }
}
template <typename T>
void RBTree<T>::inOrder() const {
  inOrder(root);
  std::cout << std::endl;
}

template <typename T>
void RBTree<T>::postOrder(RBTNode<T>* t) const {
  if (t != nil) {
    postOrder(t->lchild);
    postOrder(t->rchild);
    std::cout << t->key << " ";
  }
}
template <typename T>
void RBTree<T>::postOrder() const {
  postOrder(root);
  std::cout << std::endl;
}

template <typename T>
void RBTree<T>::print(RBTNode<T>* t, const T& key, int direction) const {
  if (t != nil) {
    if (direction == 0)
      std::cout << std::setw(2) << t->key << " is root, color is "
                << (t->color == RBTNodeColor::red ? "red" : "black")
                << std::endl;
    else
      std::cout << std::setw(2) << t->key << " is " << key << "'s "
                << std::setw(12)
                << ((direction == 1) ? "right child" : "left child")
                << ", color is " << std::setw(6)
                << (t->color == RBTNodeColor::red ? "red" : "black")
                << std::endl;
    print(t->lchild, t->key, -1);
    print(t->rchild, t->key, 1);
  }
}
template <typename T>
void RBTree<T>::print() const {
  if (root != nil)
    print(root, root->key, 0);
  else
    std::cout << "empty tree\n";
}

template <typename T>
RBTNode<T>* RBTree<T>::search(RBTNode<T>* t, const T& key) const {
  while (t != nil && t->key != key) {
    if (t->key > key)
      t = t->lchild;
    else
      t = t->rchild;
  }
  return t;
}
template <typename T>
RBTNode<T>* RBTree<T>::search(const T& key) const {
  return search(root, key);
}

template <typename T>
RBTNode<T>* RBTree<T>::minimum(RBTNode<T>* t) const {
  while (t->lchild != nil) t = t->lchild;
  return t;
}
template <typename T>
T RBTree<T>::minimum() const {
  RBTNode<T>* p = minimum(root);
  if (p != nil)
    return p->key;
  else
    return T(NULL);
}

template <typename T>
RBTNode<T>* RBTree<T>::maximum(RBTNode<T>* t) const {
  while (t->rchild != nil) {
    t = t->rchild;
  }
  return t;
}
template <typename T>
T RBTree<T>::maximum() const {
  RBTNode<T>* p = maximum(root);
  if (p != nil)
    return p->key;
  else
    return T(NULL);
}

template <typename T>
void RBTree<T>::LeftRotate(RBTNode<T>* x) {
  RBTNode<T>* y = x->rchild;
  y->parent = x->parent;
  x->rchild = y->lchild;
  if (y->lchild != nil) y->lchild->parent = x;
  if (x->parent == nil)
    root = y;
  else if (x == x->parent->lchild)
    x->parent->lchild = y;
  else
    x->parent->rchild = y;
  y->lchild = x;
  x->parent = y;
}
template <typename T>
void RBTree<T>::RightRotate(RBTNode<T>* x) {
  RBTNode<T>* y = x->lchild;
  y->parent = x->parent;
  x->lchild = y->rchild;
  if (y->rchild != nil) y->rchild->parent = x;
  if (x->parent == nil)
    root = y;
  else if (x == x->parent->lchild)
    x->parent->lchild = y;
  else
    x->parent->rchild = y;
  y->rchild = x;
  x->parent = y;
}

template <typename T>
RBTNode<T>* RBTree<T>::insert(RBTNode<T>* t, RBTNode<T>* x) {
  RBTNode<T>* p = nil;
  while (t != nil) {
    p = t;
    if (t->key == x->key) return nil;
    if (t->key > x->key)
      t = t->lchild;
    else
      t = t->rchild;
  }
  x->parent = p;
  if (p == nil)
    root = x;
  else {
    if (p->key > x->key)
      p->lchild = x;
    else
      p->rchild = x;
  }
  x->lchild = x->rchild = nil;
  insert_fixup(x);
  return x;
}
template <typename T>
bool RBTree<T>::insert(const T& key) {
  RBTNode<T>* x = new RBTNode<T>(key);
  if (insert(root, x) == nil) {
    delete x;
    return false;
  } else
    return true;
}
template <typename T>
void RBTree<T>::insert_fixup(RBTNode<T>* z) {
  RBTNode<T>* p = z->parent;
  while (p->color == RBTNodeColor::red) {
    if (p == p->parent->lchild) {
      RBTNode<T>* uncle = p->parent->rchild;
      // case1
      // uncle is red
      if (uncle->color == RBTNodeColor::red) {
        p->parent->color = RBTNodeColor::red;
        p->color = RBTNodeColor::black;
        uncle->color = RBTNodeColor::black;
        z = p->parent;
        p = z->parent;
      }
      // case2
      // uncle is black and z is p's rchild
      else if (z == p->rchild) {
        z = p;
        LeftRotate(z);
        p = z->parent;
      }
      // case3
      // uncle is black and z is p's lchild
      else {
        p->color = RBTNodeColor::black;
        z = p->parent;
        z->color = RBTNodeColor::red;
        RightRotate(z);
        p = z->parent;
      }
    }
    // same as if, just z == p->parent->rchild
    else {
      RBTNode<T>* uncle = p->parent->lchild;
      // case1
      // uncle is red
      if (uncle->color == RBTNodeColor::red) {
        p->parent->color = RBTNodeColor::red;
        p->color = RBTNodeColor::black;
        uncle->color = RBTNodeColor::black;
        z = p->parent;
        p = z->parent;
      }
      // case2
      // uncle is black and z is p's lchild
      else if (z == p->lchild) {
        z = p;
        RightRotate(z);
        p = z->parent;
      }
      // case3
      // uncle is black and z is p's rchild
      else {
        p->color = RBTNodeColor::black;
        z = p->parent;
        z->color = RBTNodeColor::red;
        LeftRotate(z);
        p = z->parent;
      }
    }
  }
  root->color = RBTNodeColor::black;
}

template <typename T>
void RBTree<T>::transplant(RBTNode<T>* u, RBTNode<T>* v) {
  if (u->parent == nil)
    root = v;
  else if (u == u->parent->lchild)
    u->parent->lchild = v;
  else
    u->parent->rchild = v;
  if (v != nil) v->parent = u->parent;
}
template <typename T>
RBTNode<T>* RBTree<T>::remove(RBTNode<T>* z) {
  RBTNode<T>* x;
  RBTNodeColor origin_c = z->color;
  if (z->lchild == nil) {
    x = z->rchild;
    transplant(z, z->rchild);
  } else if (z->rchild == nil) {
    x = z->lchild;
    transplant(z, z->lchild);
  } else {
    RBTNode<T>* suc = minimum(z->rchild);
    origin_c = suc->color;
    x = suc->rchild;
    x->parent = suc;  // x may be nil
    if (suc->parent != z) {
      transplant(suc, suc->rchild);
      suc->rchild = z->rchild;
      z->rchild->parent = suc;
    }
    transplant(z, suc);
    suc->lchild = z->lchild;
    z->lchild->parent = suc;
    suc->color = z->color;
  }
  if (origin_c == RBTNodeColor::black) remove_fixup(x);
  return x;
}
template <typename T>
bool RBTree<T>::remove(const T& key) {
  RBTNode<T>* x = search(root, key);
  if (x != nil) {
    x = remove(x);
    delete x;
    return true;
  }
  return false;
}
template <typename T>
void RBTree<T>::remove_fixup(RBTNode<T>* z) {
  RBTNode<T>* p = z->parent;
  while (z != root && z->color == RBTNodeColor::black) {
    if (z == p->lchild) {
      RBTNode<T>* s = p->rchild;
      // case1
      // sibling is red
      if (s->color == RBTNodeColor::red) {
        s->color = RBTNodeColor::black;
        p->color = RBTNodeColor::red;
        LeftRotate(p);
        s = p->rchild;
      }
      // case2
      // sibling is black
      // and both of its children are black
      if (s->lchild->color == RBTNodeColor::black &&
          s->rchild->color == RBTNodeColor::black) {
        s->color = RBTNodeColor::red;
        z = p;
        p = z->parent;
      }
      // case3 - end case
      // sibling is black, and its rchild is red
      else if (s->rchild->color == RBTNodeColor::red) {
        s->color = p->color;
        p->color = RBTNodeColor::black;
        s->rchild->color = RBTNodeColor::black;
        LeftRotate(p);
        break;
      }
      // case 4
      // sibling is black, its rchild is black
      // and its lchild is red
      else {
        s->color = RBTNodeColor::red;
        s->lchild->color = RBTNodeColor::black;
        RightRotate(s);
        s = p->rchild;
      }
    }
    // same as if, just z == p->parent->rchild
    else {
      RBTNode<T>* s = p->lchild;
      // case1
      // sibling is red
      if (s->color == RBTNodeColor::red) {
        s->color = RBTNodeColor::black;
        p->color = RBTNodeColor::red;
        RightRotate(p);
        s = p->lchild;
      }
      // case2
      // sibling is black
      // and both of its children are black
      if (s->lchild->color == RBTNodeColor::black &&
          s->rchild->color == RBTNodeColor::black) {
        z->color = RBTNodeColor::red;
        s->color = RBTNodeColor::red;
        z = p;
        p = z->parent;
      }
      // case3 - end case
      // sibling is black, and its lchild is red
      else if (s->lchild->color == RBTNodeColor::red) {
        s->color = p->color;
        p->color = RBTNodeColor::black;
        s->lchild->color = RBTNodeColor::black;
        RightRotate(p);
        break;
      }
      // case4
      // sibling is black, its lchild is black
      // and its rchild is red
      else {
        s->color = RBTNodeColor::red;
        s->rchild->color = RBTNodeColor::black;
        LeftRotate(s);
        s = p->lchild;
      }
    }
  }
  z->color = RBTNodeColor::black;
}

template <typename T>
void RBTree<T>::destroy(RBTNode<T>* t) {
  if (t != nil) {
    destroy(t->lchild);
    destroy(t->rchild);
    delete t;
  }
}
template <typename T>
void RBTree<T>::destroy() {
  if (root != nil) {
    destroy(root);
    root = nil;
  }
}

}  // namespace MyDataStructure

#endif