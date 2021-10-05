/***** Here are some sorting algorithm *****/
#include "data_structure.hpp"
#include <random>
#include <time.h>
#include <cmath>

#define MAX 100000000
// insertion sort
template <typename T>
void insertion_sort(T a[], int len)
{
    for (int i = 1; i < len; i++)
    {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key)
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

// merge sort
template <typename T>
void merge(T a[], int p, int q, int r)
{
    int len1 = q - p + 1;
    int len2 = r - q;
    T *ar1 = new T[len1 + 1];
    T *ar2 = new T[len2 + 1];
    for (int i = 0; i < len1; i++)
        ar1[i] = a[p + i];
    for (int i = 0; i < len2; i++)
        ar2[i] = a[q + i + 1];
    ar1[len1] = ar2[len2] = MAX;

    for (int i = 0, j = 0, k = p; k <= r; k++)
    {
        if (ar1[i] <= ar2[j])
        {
            a[k] = ar1[i];
            i++;
        }
        else
        {
            a[k] = ar2[j];
            j++;
        }
    }
}
template <typename T>
void merge_sort(T a[], int p, int r)
{
    if (p < r)
    {
        int q = (p + r) / 2;
        merge_sort(a, p, q);
        merge_sort(a, q + 1, r);
        merge(a, p, q, r);
    }
}

// heap sort
template <typename T>
void heap_sort(T a[], int len)
{
    max_heap<T> temp_heap = build_max_heap(a, len);
    temp_heap.sort();
    for (int i = 0; i < len; i++)
        a[i] = temp_heap[i];
}

// quick sort
template <typename T>
int partition(T a[], int p, int r)
{
    int key = a[r];
    int j = p;
    for (int i = p; i < r; i++)
    {
        if (a[i] < key)
        {
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
void quick_sort(T a[], int p, int r)
{
    if (p < r)
    {
        int q = partition(a, p, r);
        quick_sort(a, p, q - 1);
        quick_sort(a, q + 1, r);
    }
}
// random version
template <typename T>
int random_partition(T a[], int p, int r)
{
    srand(time(NULL));
    int i = rand() % (r - p) + p;
    T temp = a[i];
    a[i] = a[r];
    a[r] = temp;
    return partition(a, p, r);
}
template <typename T>
void random_quick_sort(T a[], int p, int r)
{
    if (p < r)
    {
        int q = random_partition(a, p, r);
        random_quick_sort(a, p, q - 1);
        random_quick_sort(a, q + 1, r);
    }
}

// counting sort
// must be used to sort on integers
void counting_sort(int a[], int b[], int len, int max)
{
    int *c = new int[max + 1];
    for (int i = 0; i <= max; i++)
        c[i] = 0;
    for (int i = 0; i < len; i++)
        c[a[i]]++;
    for (int i = 0; i < max; i++)
        c[i + 1] += c[i];

    for (int i = len - 1; i >= 0; i--)
    {
        b[c[a[i]] - 1] = a[i];
        c[a[i]]--;
    }
    delete[] c;
}
void counting_sort(int a[], int b[], int len)
{
    int max = a[0];
    for (int i = 1; i < len; i++)
        if (max < a[i])
            max = a[i];

    counting_sort(a, b, len, max);
}
void counting_sort(int a[], int len, int max)
{
    int *b = new int[len];
    counting_sort(a, b, len, max);
    for (int i = 0; i < len; i++)
        a[i] = b[i];
    delete[] b;
}
void counting_sort(int a[], int len)
{
    int *b = new int[len];
    counting_sort(a, b, len);
    for (int i = 0; i < len; i++)
        a[i] = b[i];
    delete[] b;
}

// radix sort - based on decimalism
void counting_sort(int a[], int len, int max, int d)
{
    int x;
    int *c = new int[max + 1]{0};
    for (int i = 0; i < len; i++)
    {
        x = a[i] % int(pow(10, d)) / int(pow(10, d - 1));
        c[x]++;
    }
    for (int i = 0; i < max; i++)
        c[i + 1] += c[i];

    int *b = new int[len];
    for (int i = len - 1; i >= 0; i--)
    {
        x = a[i] % int(pow(10, d)) / int(pow(10, d - 1));
        b[c[x] - 1] = a[i];
        c[x]--;
    }
    for (int i = 0; i < len; i++)
        a[i] = b[i];
    delete[] b;
    delete[] c;
}
void radix_sort(int a[], int len, int max)
{
    int d = log10(max) + 1;
    int *temp = new int[len];
    for (int i = 1; i <= d; i++)
        counting_sort(a, len, 9, i);
}
void radix_sort(int a[], int len)
{
    int max = a[0];
    for (int i = 0; i < len; i++)
        if (a[i] > max)
            max = a[i];
    radix_sort(a, len, max);
}