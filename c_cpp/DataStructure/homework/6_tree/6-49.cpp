#include <iostream>

typedef int TElemType;

typedef struct BiTNode
{
    TElemType data;
    int visited;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

//判断给定二叉树是否是完全二叉树
bool Judge(BiTree t)
{
    //t为空指针
    if (t == nullptr)
        return true;
    //t的左右子树有一个为空
    else if ((t->lchild != nullptr && t->rchild == nullptr) || (t->lchild == nullptr && t->rchild != nullptr))
        return false;
    //t的左右子树均为空
    else if (t->lchild == nullptr && t->rchild == nullptr)
        return true;
    //t的左右子树均不为空
    else
        return Judge(t->lchild) && Judge(t->rchild);
}