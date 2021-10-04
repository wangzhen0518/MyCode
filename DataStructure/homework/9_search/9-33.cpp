#include <iostream>

typedef int TElemType;

/**********二叉树**********/
//二叉链表
typedef struct BiTNode
{
    TElemType data;
    int visited;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

void PrintX(BiTNode *t, int x)
{
    if (t == nullptr)
        return;
    else if (t->data < x)
        PrintX(t->rchild, x);
    else if (t->data >= x)
    {
        PrintX(t->rchild, x);
        std::cout << t->data << " ";
        PrintX(t->lchild, x);
    }
}