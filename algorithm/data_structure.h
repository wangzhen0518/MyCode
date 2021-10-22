#ifndef DATA_STRUCTURE_
#define DATA_STRUCTURE_

#include <algorithm>
#include <iostream>
#include <vector>

namespace MyDataStructure {
// stack
template <typename T>
class stack {
private:
    T* ar = nullptr;
    int max_size = 0;
    int mem_num = 0;
    const static int EX_LEN = 10;

public:
    stack() {}
    stack(int len) : max_size(len) { ar = new T[len]; }
    ~stack() { delete[] ar; }
    stack(const stack& s) : max_size(s.max_size), mem_num(s.mem_num) {
        ar = new T[s.max_size];
        for (int i = 0; i < mem_num; i++)
            ar[i] = s.ar[i];
    }
    const stack& operator=(const stack& s) {
        if (this != &s) {
            delete[] ar;
            mem_num = s.mem_num;
            max_size = s.max_size;
            ar = new T[max_size];
            for (int i = 0; i < mem_num; i++)
                ar[i] = s.ar[i];
        }
        return *this;
    }
    const T& top() { return ar[mem_num - 1]; }
    bool isempty() { return mem_num == 0; }
    bool push(const T& t);
    bool pop();
    int size() { return mem_num; }
    int capacity() { return max_size; }
};

// queue
template <typename T>
class queue {
private:
    T* ar = nullptr;
    int head = 0;
    int rear = 0;
    int mem_num = 0;
    int max_size = 0;
    const static int EX_LEN = 10;

public:
    queue() {}
    queue(int len) : max_size(len) { ar = new T[len]; }
    ~queue() { delete[] ar; }
    queue(const queue& q)
        : max_size(q.max_size), mem_num(q.mem_num), rear(q.mem_num) {
        ar = new T[q.max_size];
        for (int i = 0, j = q.head; i < mem_num;
             i++, j = (j + 1) % max_size)
            ar[i] = q.ar[j];
    }
    const queue& operator=(const queue& q) {
        if (this != &q) {
            delete[] ar;
            mem_num = q.mem_num;
            max_size = q.max_size;
            ar = new T[max_size];
            for (int i = 0, j = q.head; i < mem_num;
                 i++, j = (j + 1) % max_size)
                ar[i] = q.ar[j];
            head = 0;
            rear = mem_num;
        }
        return *this;
    }
    const T& top() { return ar[mem_num - 1]; }
    bool isempty() { return mem_num == 0; }
    bool enqueue(const T& t);
    bool dequeue();
    int size() { return mem_num; }
    int capacity() { return max_size; }
};

// list
template <typename T>
class list {
public:
    template <typename U>
    struct list_node {
        U key;
        list_node* prev;
        list_node* next;

        list_node() : prev(nullptr), next(nullptr) {}
        list_node(list_node* p, list_node* n) : prev(p), next(n) {}
    };

private:
    list_node<T>* head;
    list_node<T>* rear;

public:
    list();
    ~list();
    list_node<T>* search(const T& key);
    bool list_delete(list_node<T>* t);
    bool list_insert(const T& key);
    void show();
};

// max_heap
template <typename T>
class max_heap {
protected:
    std::vector<T> m_ar;
    int m_heap_size = 0;
    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

public:
    const T& operator[](int n) { return m_ar[n]; }
    T& operator[](int n) { return m_ar[n]; }
    int length() { return m_ar.size(); }
    const int heap_size() { return m_heap_size; }
    void max_heapify(int i);
    max_heap() {}
    max_heap(T a[], int len);
    virtual ~max_heap() {}
    void sort();
};

template <typename T>
max_heap<T> build_max_heap(T a[], int len) {
    return max_heap<T>(a, len);
}

// max_priority_queue
template <typename T>
class max_priority_queue : public max_heap<T> {
private:
    const static int MAX = 100000000;

public:
    using mh = max_heap<T>;
    max_priority_queue() : max_heap<T>() {}
    max_priority_queue(T a[], int len) : max_heap<T>(a, len) {}
    void increase_key(int i, T k);
    void insert(T k);
    const T& maximum() { return mh::m_ar[0]; }
    T extract_max();
    void show();
    ~max_priority_queue() {}
};

// binary search tree
template <typename T>
class BSTree {
public:
    template <typename U>

    struct BSTNode {
        U key;
        BSTNode* lchild;
        BSTNode* rchild;
        BSTNode* parent;
        BSTNode(U value, BSTNode* l, BSTNode* r, BSTNode* p)
            : key(value), lchild(l), rchild(r), parent(p) {}
        BSTNode()
            : lchild(nullptr), rchild(nullptr), parent(nullptr) {}
    };

private:
    BSTNode<T>* root;

public:
    BSTree() {}
    ~BSTree() {}
};

//! QUESTION
/*
 * 对于类继承后，派生类访问基类元素存在问题。
 * version 1 如下
 * #include <iostream>
 *
 * class test1
 * {
 * protected:
 * 	int a;
 *
 * public:
 * 	test1(int _a) : a(_a) {}
 * 	~test1() {}
 * };
 *
 * class test2 : public test1
 * {
 * private:
 * 	int b;
 *
 * public:
 * 	test2(int _a, int _b) : test1(_a), b(_b) {}
 * 	~test2() {}
 * 	void show() { std::cout << "a: " << a << ", b:
 * " << b << std::endl; }
 * };
 *
 * int main()
 * {
 * 	test2 t(1, 2);
 * 	t.show();
 * 	return 0;
 * }
 * 这里派生类test2直接访问了基类test1的元素a，但是可以正常执行。
 *
 * version2
 * #include <iostream>
 *
 * template <typename T>
 * class test1
 * {
 * protected:
 * 	T a;
 *
 * public:
 * 	test1(T _a) : a(_a) {}
 * 	~test1() {}
 * };
 *
 * template <typename T>
 * class test2 : public test1<T>
 * {
 * private:
 * 	T b;
 *
 * public:
 * 	test2(T _a, T _b) : test1<T>(_a), b(_b) {}
 * 	~test2() {}
 * 	void show() { std::cout << "a: " <<
 * test1<T>::a << ", b: " << b << std::endl; }
 * };
 *
 * int main()
 * {
 * 	test2<int> t(1, 2);
 * 	t.show();
 * 	return 0;
 * }
 * 与version1基本没有区别，只是将类给成了模版。
 * 这里test2访问test1类的成员a必须加上类限定符，否则会出错，这是为什么？
 */

//? Answer
/*
 * 自己想了一种可能。
 * 模版类只是告诉编译器如何生成特定类型的类，但并不具有模版类这个类。
 * 所以访问时，必须指定访问哪种具体化的类的成员。
 */

}  // namespace MyDataStructure

#endif