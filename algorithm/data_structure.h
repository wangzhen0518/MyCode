#ifndef DATA_STRUCTURE_
#define DATA_STRUCTURE_

#include <algorithm>
#include <iostream>
#include <vector>

namespace MyDataStructure {
template <typename T>
class stack {
private:
    T *ar = nullptr;
    int max_size = 0;
    int mem_num = 0;
    const static int EX_LEN = 10;

public:
    stack() {}
    stack(int len) : max_size(len) { ar = new T[len]; }
    ~stack() { delete[] ar; }
    stack(const stack &s) : max_size(s.max_size), mem_num(s.mem_num) {
        ar = new T[s.max_size];
        for (int i = 0; i < mem_num; i++)
            ar[i] = s.ar[i];
    }
    const stack &operator=(const stack &s) {
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
    const T &top() { return ar[mem_num - 1]; }
    bool isempty() { return mem_num == 0; }
    bool push(const T &t) {
        if (mem_num == max_size) {
            max_size += EX_LEN;
            T *temp = new T[max_size];  // TODO: using try to allocate memory
            for (int i = 0; i < mem_num; i++)
                temp[i] = ar[i];
            temp[mem_num] = t;
            delete[] ar;
            ar = temp;
        } else
            ar[mem_num++] = t;
        return true;
    }
    bool pop() {
        if (mem_num == 0)
            return false;
        else
            mem_num--;
    }
    int size() { return mem_num; }
    int capacity() { return max_size; }
};

template <typename T>
class queue {
private:
    T *ar = nullptr;
    int head = 0;
    int rear = 0;
    int mem_num = 0;
    int max_size = 0;
    const static int EX_LEN = 10;

public:
    queue() {}
    queue(int len) : max_size(len) { ar = new T[len]; }
    ~queue() { delete[] ar; }
    queue(const queue &q)
        : max_size(q.max_size), mem_num(q.mem_num), rear(q.mem_num) {
        ar = new T[q.max_size];
        for (int i = 0, j = q.head; i < mem_num; i++, j = (j + 1) % max_size)
            ar[i] = q.ar[j];
    }
    const queue &operator=(const queue &q) {
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
    const T &top() { return ar[mem_num - 1]; }
    bool isempty() { return mem_num == 0; }
    bool enqueue(const T &t) {
        if (mem_num == max_size) {
            T *temp =
                new T[max_size + EX_LEN];  // TODO: using try to allocate memory
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
    bool dequeue() {
        if (mem_num == 0)
            return false;
        else {
            mem_num--;
            head = (head + 1) % max_size;
        }
    }
    int size() { return mem_num; }
    int capacity() { return max_size; }
};

template <typename T>
struct list_node {
    T key;
    list_node *next;
    list_node *prev;
};
template <typename T>
class list {
private:
    list_node<T> *head;
    list_node<T> *rear;

public:
    list() {
        head = rear = new list_node<T>;
        head->prev = nullptr;
        head->next = nullptr;
    }
    ~list() {
        list_node<T> *p = head;
        list_node<T> *q = head;
        while (q != nullptr) {
            q = q->next;
            delete p;
            p = q;
        }
    }
    list_node<T> *search(const T &key) {
        list_node<T> *t = head;
        while (t != nullptr && t->key != key)
            t = t->next;
        return t;
    }
    bool list_delete(list_node<T> *t) {
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
    bool list_insert(const T &key) {
        rear->next = new list_node<T>;
        rear->next->prev = rear;
        rear = rear->next;
        rear->next = nullptr;
        rear->key = key;
        return true;
    }
    void show() {
        if (head != nullptr) {
            list_node<T> *q = head->next;
            while (q != nullptr) {
                std::cout << q->key << " ";
                q = q->next;
            }
            std::cout << "\n";
        } else
            std::cout << "empty list\n";
    }
};

template <typename T>
class max_heap {
protected:
    std::vector<T> m_ar;
    int m_heap_size = 0;
    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

public:
    // const T& operator[](int n) { return m_ar[n]; }
    T &operator[](int n) { return m_ar[n]; }
    int length() { return m_ar.size(); }
    const int heap_size() { return m_heap_size; }
    void max_heapify(int i)  // maintain the max_heap
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
    max_heap() {}
    max_heap(T a[], int len)
        : m_ar(len),
          m_heap_size(len)  // creat a max_heap
    {
        for (int i = 0; i < len; i++)
            m_ar[i] = a[i];
        for (int i = (len - 1) / 2; i >= 0; i--)
            max_heapify(i);
    }
    virtual ~max_heap() {}
    void sort() {
        for (int i = m_ar.size() - 1; i >= 1; i--) {
            T temp = m_ar[i];
            m_ar[i] = m_ar[0];
            m_ar[0] = temp;
            m_heap_size--;
            max_heapify(0);
        }
    }
};

template <typename T>
max_heap<T> build_max_heap(T a[], int len) {
    return max_heap<T>(a, len);
}

template <typename T>
class max_priority_queue : public max_heap<T> {
private:
    const static int MAX = 100000000;

public:
    using mh = max_heap<T>;
    max_priority_queue() : max_heap<T>() {}
    max_priority_queue(T a[], int len) : max_heap<T>(a, len) {}
    void increase_key(int i, T k) {
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
    void insert(T k) {
        if (mh::m_ar.size() == mh::m_heap_size)
            mh::m_ar.push_back(-MAX);
        else
            mh::m_ar[mh::m_heap_size] = -MAX;
        mh::m_heap_size++;
        increase_key(mh::m_heap_size - 1, k);
    }
    const T &maximum() { return mh::m_ar[0]; }
    T extract_max() {
        T temp = mh::m_ar[0];
        mh::m_ar[0] = mh::m_ar[mh::m_heap_size - 1];
        mh::m_heap_size--;
        mh::max_heapify(0);
        return temp;
    }
    void show() {
        using std::cout;
        using std::endl;
        using std::for_each;
        for_each(mh::m_ar.begin(), mh::m_ar.begin() + mh::m_heap_size,
                 [](T x) { cout << x << " "; });
        cout << endl;
    }
    ~max_priority_queue() {}
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
 * 	void show() { std::cout << "a: " << a << ", b: " << b << std::endl; }
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
 * 	void show() { std::cout << "a: " << test1<T>::a << ", b: " << b <<
 * std::endl; }
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