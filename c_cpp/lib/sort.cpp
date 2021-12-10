#ifndef SORT_CPP_
#define SORT_CPP_

/***** Here are some sorting algorithm *****/
#include <time.h>

#include <cmath>
#include <random>

#include "data_structure.hpp"
namespace MyAlgorithm {
template <typename T>
inline void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

#define MAX 100000000
// insertion sort
template <typename T>
void insertion_sort(T a[], int len) {
    for (int i = 1; i < len; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

// merge sort
template <typename T>
void merge(T a[], int p, int q, int r) {
    int len1 = q - p + 1;
    int len2 = r - q;
    T* ar1 = new T[len1 + 1];
    T* ar2 = new T[len2 + 1];
    for (int i = 0; i < len1; i++)
        ar1[i] = a[p + i];
    for (int i = 0; i < len2; i++)
        ar2[i] = a[q + i + 1];
    ar1[len1] = ar2[len2] = MAX;

    for (int i = 0, j = 0, k = p; k <= r; k++) {
        if (ar1[i] <= ar2[j]) {
            a[k] = ar1[i];
            i++;
        } else {
            a[k] = ar2[j];
            j++;
        }
    }
}
template <typename T>
void merge_sort(T a[], int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
        merge_sort(a, p, q);
        merge_sort(a, q + 1, r);
        merge(a, p, q, r);
    }
}

// heap sort
template <typename T>
void heap_sort(T a[], int len) {
    using MyDataStructure::build_max_heap;
    using MyDataStructure::max_heap;
    max_heap<T> temp_heap = build_max_heap(a, len);
    temp_heap.sort();
    for (int i = 0; i < len; i++)
        a[i] = temp_heap[i];
}

// quick sort
template <typename T>
int partition(T a[], int p, int r) {
    T key = a[r];
    int j = p;
    for (int i = p; i < r; i++) {
        if (a[i] < key) {
            T temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            j++;
        }
    }
    a[r] = a[j];
    a[j] = key;
    return j;
}
template <typename T>
int partition(T a[], int p, int r, int index) {
    swap(a[r], a[index]);
    return partition(a, p, r);
}
template <typename T>
void quick_sort(T a[], int p, int r) {
    if (p < r) {
        int q = partition(a, p, r);
        quick_sort(a, p, q - 1);
        quick_sort(a, q + 1, r);
    }
}
// random version
template <typename T>
int random_partition(T a[], int p, int r) {
    srand(time(NULL));
    int i = rand() % (r - p + 1) + p;
    T temp = a[i];
    a[i] = a[r];
    a[r] = temp;
    return partition(a, p, r);
}
template <typename T>
void random_quick_sort(T a[], int p, int r) {
    if (p < r) {
        int q = random_partition(a, p, r);
        random_quick_sort(a, p, q - 1);
        random_quick_sort(a, q + 1, r);
    }
}

// counting sort
// must be used to sort on integers
void counting_sort(int a[], int b[], int len, int max) {
    int* c = new int[max + 1]{0};
    for (int i = 0; i < len; i++)
        c[a[i]]++;
    for (int i = 0; i < max; i++)
        c[i + 1] += c[i];

    for (int i = len - 1; i >= 0; i--) {
        b[c[a[i]] - 1] = a[i];
        c[a[i]]--;
    }
    delete[] c;
}
void counting_sort(int a[], int b[], int len) {
    int max = a[0];
    for (int i = 1; i < len; i++)
        if (max < a[i])
            max = a[i];
    counting_sort(a, b, len, max);
}
void counting_sort(int a[], int len, int max) {
    int* b = new int[len];
    counting_sort(a, b, len, max);
    for (int i = 0; i < len; i++)
        a[i] = b[i];
    delete[] b;
}
void counting_sort(int a[], int len) {
    int* b = new int[len];
    counting_sort(a, b, len);
    for (int i = 0; i < len; i++)
        a[i] = b[i];
    delete[] b;
}

// radix sort - based on decimalism
static const int tenp[] = {1,      10,      100,       1'000,
                           10'000, 100'000, 1'000'000, 10'000'000};
// 得到数字x的第bit+1位数
inline int getbit(int x, int bit) {
    return x / tenp[bit] % 10;
}
void radix_sort(int a[], int len, int max) {
    int d = log10(max) + 1;
    int* temp = new int[len];
    for (int i = 0; i < d; i++) {
        int count[10] = {0};
        for (int j = 0; j < len; j++)
            count[getbit(a[j], i)]++;
        for (int j = 1; j < 10; j++)
            count[j] += count[j - 1];
        for (int j = len - 1; j >= 0; j--)
            temp[--count[getbit(a[j], i)]] = a[j];
        for (int j = 0; j < len; j++)
            a[j] = temp[j];
    }
    delete[] temp;
}
void radix_sort(int a[], int len) {
    int max = a[0];
    for (int i = 0; i < len; i++)
        if (a[i] > max)
            max = a[i];
    radix_sort(a, len, max);
}

// random select
template <typename T>
T randomized_select(T a[], int p, int r, int i) {
    if (p == r)
        return a[p];
    int q = random_partition(a, p, r);
    int k = q - p + 1;
    if (i == k)
        return a[q];
    else if (i < k)
        return randomized_select(a, p, q - 1, i);
    else
        return randomized_select(a, q + 1, r, i - k);
}

// select cost O(n) time even in the worst cases
template <typename T>
int quick_select(T a[], int p, int r, int k);
template <typename T>
int getPivotIndex_quick_select(T a[], int p, int r) {
    if (r - p < 5) {
        insertion_sort(a, r - p + 1);
        return (r + p) / 2;
    }
    int q = p;
    for (int i = p; i + 4 <= r; i += 5) {
        insertion_sort(a + i, 5);
        swap(a[q], a[i + 2]);
        q++;
    }
    return quick_select(a, p, q - 1, (q - p + 1) / 2);
}
template <typename T>
int quick_select(T a[], int p, int r, int k) {
    if (p == r)
        return p;

    int pivotIndex = getPivotIndex_quick_select(a, p, r);
    pivotIndex = partition(a, p, r, pivotIndex);

    // judge divide and conquer
    int num = pivotIndex - p + 1;
    if (k == num)
        return pivotIndex;
    else if (k < num)
        return quick_select(a, p, pivotIndex - 1, k);
    else
        return quick_select(a, pivotIndex + 1, r, k - num);
}
}  // namespace MyAlgorithm
#endif