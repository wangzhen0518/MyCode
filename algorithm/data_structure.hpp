#include <vector>
#include <iostream>
#include <algorithm>

template <typename T>
class max_heap
{
protected:
    std::vector<T> m_ar;
    int m_heap_size = 0;
    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

public:
    //const T& operator[](int n) { return m_ar[n]; }
    T &operator[](int n) { return m_ar[n]; }
    int length() { return m_ar.size(); }
    const int heap_size() { return m_heap_size; }
    void max_heapify(int i) // maintain the max_heap
    {
        int large = i;
        int l = left(i);
        int r = right(i);
        if (l < m_heap_size && m_ar[i] < m_ar[l])
            large = l;
        if (r < m_heap_size && m_ar[large] < m_ar[r])
            large = r;
        if (large != i)
        {
            T temp = m_ar[i];
            m_ar[i] = m_ar[large];
            m_ar[large] = temp;
            max_heapify(large);
        }
    }
    max_heap() {}
    max_heap(T a[], int len) : m_ar(len), m_heap_size(len) //creat a max_heap
    {
        for (int i = 0; i < len; i++)
            m_ar[i] = a[i];
        for (int i = (len - 1) / 2; i >= 0; i--)
            max_heapify(i);
    }
    virtual ~max_heap() {}
    void sort()
    {
        for (int i = m_ar.size() - 1; i >= 1; i--)
        {
            T temp = m_ar[i];
            m_ar[i] = m_ar[0];
            m_ar[0] = temp;
            m_heap_size--;
            max_heapify(0);
        }
    }
};

template <typename T>
max_heap<T> build_max_heap(T a[], int len)
{
    return max_heap<T>(a, len);
}

template <typename T>
class max_priority_queue : public max_heap<T>
{
private:
    const static int MAX = 100000000;

public:
    using mh = max_heap<T>;
    max_priority_queue() : max_heap<T>() {}
    max_priority_queue(T a[], int len) : max_heap<T>(a, len) {}
    void increase_key(int i, T k)
    {
        if (mh::m_ar[i] > k)
            return;
        else
        {
            mh::m_ar[i] = k;
            while (i > 0 && mh::m_ar[mh::parent(i)] < mh::m_ar[i])
            {
                T temp = mh::m_ar[i];
                mh::m_ar[i] = mh::m_ar[mh::parent(i)];
                mh::m_ar[mh::parent(i)] = temp;
                i = mh::parent(i);
            }
        }
    }
    void insert(T k)
    {
        if (mh::m_ar.size() == mh::m_heap_size)
            mh::m_ar.push_back(-MAX);
        else
            mh::m_ar[mh::m_heap_size] = -MAX;
        mh::m_heap_size++;
        increase_key(mh::m_heap_size - 1, k);
    }
    const T &maximum() { return mh::m_ar[0]; }
    T extract_max()
    {
        T temp = mh::m_ar[0];
        mh::m_ar[0] = mh::m_ar[mh::m_heap_size - 1];
        mh::m_heap_size--;
        mh::max_heapify(0);
        return temp;
    }
    void show()
    {
        using std::cout;
        using std::endl;
        using std::for_each;
        for_each(mh::m_ar.begin(), mh::m_ar.begin() + mh::m_heap_size, [](T x)
                 { cout << x << " "; });
        cout << endl;
    }
    ~max_priority_queue() {}
};

//! QUESTION
/*
对于类继承后，派生类访问基类元素存在问题。
version 1 如下
#include <iostream>

class test1
{
protected:
	int a;

public:
	test1(int _a) : a(_a) {}
	~test1() {}
};

class test2 : public test1
{
private:
	int b;

public:
	test2(int _a, int _b) : test1(_a), b(_b) {}
	~test2() {}
	void show() { std::cout << "a: " << a << ", b: " << b << std::endl; }
};

int main()
{
	test2 t(1, 2);
	t.show();
	return 0;
}
这里派生类test2直接访问了基类test1的元素a，但是可以正常执行。

version2
#include <iostream>

template <typename T>
class test1
{
protected:
	T a;

public:
	test1(T _a) : a(_a) {}
	~test1() {}
};

template <typename T>
class test2 : public test1<T>
{
private:
	T b;

public:
	test2(T _a, T _b) : test1<T>(_a), b(_b) {}
	~test2() {}
	void show() { std::cout << "a: " << test1<T>::a << ", b: " << b << std::endl; }
};

int main()
{
	test2<int> t(1, 2);
	t.show();
	return 0;
}
与version1基本没有区别，只是将类给成了模版。
这里test2访问test1类的成员a必须加上类限定符，否则会出错，这是为什么？
*/

//? Answer
/*
自己想了一种可能。
模版类只是告诉编译器如何生成特定类型的类，但并不具有模版类这个类。
所以访问时，必须指定访问哪种具体化的类的成员。
*/

