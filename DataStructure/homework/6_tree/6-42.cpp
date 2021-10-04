#include <iostream>

typedef char TElemType;

typedef struct BiTnode
{
    TElemType data;
    int visited;
    struct BiTnode *lchild, *rchild;
} BiTNode, *BiTree;

//计算叶子数
int LeafCount(BiTnode *t)
{
    static int num = 0;
    if (t->lchild == nullptr && t->rchild == nullptr)
        num++;
    else if (t->lchild != nullptr)
    {
        if (t->rchild == nullptr)
            LeafCount(t->lchild);
        if (t->rchild != nullptr)
        {
            LeafCount(t->lchild);
            LeafCount(t->rchild);
        }
    }
    else
        LeafCount(t->rchild);
    return num;
}