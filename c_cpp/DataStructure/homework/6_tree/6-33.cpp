#include <iostream>

//用L, R两个数组存储树，分别表示i的左右孩子
static const int n = 10;
static int L[n + 1];
static int R[n + 1];

//判断v是否是u的子孙
bool Search(int u, int v)
{
    if (u == 0)
        return false;
    if (L[u] == v || R[u] == v)
        return true;
    else
        return Search(L[u], v) || Search(R[u], v);
}