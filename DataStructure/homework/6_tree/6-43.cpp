#include <iostream>

typedef char TElemType;

typedef struct BiTNode
{
    TElemType data;
    int visited;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

//将所有结点的左右子树交换
void Exchange(BiTNode *t)
{
    BiTNode *p;
    if (t == nullptr)
        return;
    else
    {
        //对t的左右孩子交换其左右子树
        Exchange(t->lchild);
        Exchange(t->rchild);

        //交换t的左右子树
        p = t->lchild;
        t->lchild = t->rchild;
        t->rchild = p;
    }
}