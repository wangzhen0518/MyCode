#include <iostream>

#define NUM 10

typedef int TElemType;

typedef struct PTNode
{ //树结点定义
    TElemType data;
    int parent;
} PTNode;
typedef struct
{
    PTNode nodes[NUM];
    int r, n; //根的位置和结点数
} Ptree;

typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

BiTNode parent[NUM];

//树的双亲表示法转孩子-兄弟表示法
BiTNode *Change(const Ptree p[], BiTNode *t[], int n)
{
}
BiTNode *Create(const Ptree p[])
{
    //先将所有结点构造完毕
    BiTNode *temp[NUM];
    for (int i = 0; i < NUM; i++)
    {
        temp[i] = new BiTNode;
        temp[i]->data = p->nodes[p->r].data;
        temp[i]->lchild = nullptr;
        temp[i]->rchild = nullptr;
    }

    //再处理指针
    for (int i = 0; i < NUM; i++)
    {
        int parent = p->nodes[i].parent;
        if (temp[parent]->lchild == nullptr) //双亲尚未链接孩子
            temp[parent]->lchild = temp[i];
        else //双亲已经链接孩子，则连到孩子中的最右边
        {
            BiTNode *t = temp[parent]->lchild;
            while (t->rchild != nullptr)
                t = t->rchild;
            t->rchild = temp[i];
        }
    }
    return temp[p->r];
}