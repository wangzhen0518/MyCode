#include <iostream>

typedef int TElemType;

//平衡二叉排序树
//平衡二叉排序树-二叉链表
typedef struct BBSTNode
{
    TElemType data;
    int Bfactor; //平衡因子
    int lsize;
    struct BBSTNode *lchild, *rchild, *parent;
} BBSTNode, *BBSTree;

//树中第k小的结点
BBSTNode *Search(BBSTree t, int k)
{
    if (t->lsize == k)
        return t;
    else if (t->lsize > k)
        return Search(t->lchild, k);
    else if (t->lsize < k)
        return Search(t->rchild, k - t->lsize);
}