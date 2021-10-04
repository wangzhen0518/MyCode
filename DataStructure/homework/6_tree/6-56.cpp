#include<iostream>

typedef int TElemType;

//线索二叉树
typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

//在先序线索二叉树中，查找p的先序序列后继
BiTNode* Search(BiTNode*p)
{

}