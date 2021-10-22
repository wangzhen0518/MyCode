#ifndef DATA_STRUCTURE_CPP_
#define DATA_STRUCTURE_CPP_

#include "data_structure.h"

#include <algorithm>
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
        for (int i = 0; i < mem_num; i++)
            temp[i] = ar[i];
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
list<T>::list_node<T>* list<T>::search(const T& key) {
    list_node<T>* t = head;
    while (t != nullptr && t->key != key)
        t = t->next;
    // return t;
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
    for (int i = 0; i < len; i++)
        m_ar[i] = a[i];
    for (int i = (len - 1) / 2; i >= 0; i--)
        max_heapify(i);
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

}  // namespace MyDataStructure

#endif