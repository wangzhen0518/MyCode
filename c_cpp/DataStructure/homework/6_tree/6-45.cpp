#include <iostream>

typedef int TElemType;

typedef struct BiTNode
{
    TElemType data;
    int visited;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

//删除值为x的结点，及其子树
//处理删除操作的子函数，p为待删结点的双亲
void Delete(BiTNode *t, BiTNode *p)
{
    if (t == nullptr)
        return;
    Delete(t->lchild, t);
    Delete(t->rchild, t);
    if (p->lchild == t)
        p->lchild = nullptr;
    else
        p->rchild = nullptr;
    free(t);
}
void DeleteX(BiTNode *t, int x)
{
    if (t == nullptr)
        return;
    if (t->lchild != nullptr && t->lchild->data == x)
        Delete(t->lchild, t);
    else if (t->rchild != nullptr && t->rchild->data == x)
        Delete(t->rchild, t);
    else
    {
        DeleteX(t->lchild, x);
        DeleteX(t->rchild, x);
    }
}