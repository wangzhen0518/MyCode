#include "D:\WorkSpace\Visual Studio Code\review\Calculate\Search.cpp"

bool Judge(BiTree t, BiTNode *pre)
{
    if (t->lchild == NULL && t->rchild == NULL)
        return true; //由于t的关键字比双亲小，在访问双亲的时候已经判断过了，所以此处是符合排序二叉树时的情况
    else if (t->lchild == NULL)
    {
        if (t->rchild->data.key < t->data.key)
            return false;
        if (pre->lchild == t)
        {
            if (t->data.key > pre->data.key ||
                t->rchild->data.key > pre->data.key)
                return false;
            else
                return Judge(t->rchild, t);
        }
        else if (pre->rchild == t)
        {
            if (t->data.key < pre->data.key ||
                t->rchild->data.key < pre->data.key)
                return false;
            else
                return Judge(t->rchild, t);
        }
    }
    else if (t->rchild == NULL)
    {
        if (t->lchild->data.key > t->data.key)
            return false;
        if (pre->lchild == t)
        {
            if (t->data.key > pre->data.key ||
                t->lchild->data.key > pre->data.key)
                return false;
            else
                return Judge(t->lchild, t);
        }
        else if (pre->rchild == t)
        {
            if (t->data.key < pre->data.key ||
                t->lchild->data.key < pre->data.key)
                return false;
            else
                return Judge(t->lchild, t);
        }
    }
    else
    {
        if (t->lchild->data.key > t->data.key ||
            t->rchild->data.key < t->data.key)
            return false;
        if (pre->lchild == t)
        {
            if (t->data.key > pre->data.key ||
                t->lchild->data.key > pre->data.key ||
                t->rchild->data.key > pre->data.key)
                return false;
            else
                return Judge(t->lchild, t) && Judge(t->rchild, t);
        }
        else if (pre->rchild == t)
        {
            if (t->data.key < pre->data.key ||
                t->lchild->data.key < pre->data.key ||
                t->rchild->data.key < pre->data.key)
                return false;
            else
                return Judge(t->lchild, t) && Judge(t->rchild, t);
        }
    }
}