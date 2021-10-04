#include <iostream>

typedef char TElemType;

typedef struct BiTnode
{
    TElemType data;
    int visited;
    struct BiTnode *lchild, *rchild;
} BiTNode, *BiTree;

//计算孩子-兄弟树的叶子数
int LeafCount(BiTnode *t)
{
    static int num = 0;
    if (t->lchild == nullptr)
        num++;
    else if (t->rchild != nullptr)
    {
        LeafCount(t->lchild);
        LeafCount(t->rchild);
    }
    else
        LeafCount(t->lchild);
    return num;
}