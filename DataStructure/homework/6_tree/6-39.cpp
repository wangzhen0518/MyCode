#include <iostream>

typedef char TElemType;

typedef struct BiTNode
{
    TElemType data;
    int visited;
    struct BiTNode *lchild, *rchild, *parent;
    int mark; //mark=0, 1, 2 标记到这个顶点是向左/向右/访问
} BiTNode, *BiTree;

//在二叉链表中增加mark和parent，进行非递归&不用栈的后序遍历
void PostOrder(BiTree t)
{
    BiTNode *p;
    p = t;
    while (p != nullptr)
    {
        switch (p->mark)
        {
        case 0:
            p->mark = 1;
            if (p->lchild != nullptr)
                p = p->lchild;
            break;
        case 1:
            p->mark = 2;
            if(p->rchild!=nullptr)
                p = p->rchild;
            break;
        case 2:
            p->mark = 0;
            //visit
            p = p->parent;
            break;
        }
    }
}