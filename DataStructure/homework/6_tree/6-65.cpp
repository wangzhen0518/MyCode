#include <iostream>

#define NUM 10

typedef int TElemType;

typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

BiTNode Front[NUM]; //前序序列
BiTNode Mid[NUM];   //中序序列

//根据前序、中序序列，构造二叉树
BiTree Create(const BiTNode F[], const BiTNode I[], int FL = 0, int FR = NUM, int IL = 0, int IR = NUM)
{
    //FL, FR, IL, IR 分别为先序、中序序列查找起始、终止位置
    if (FL > FR)
        return nullptr;
    int k;
    int LeftNum;
    BiTNode *root = new BiTNode(F[FL]);
    //查找根在中序中的位置
    for (int i = IL; i < IR; i++)
    {
        if (root->data == I[i].data)
        {
            k = i;
            break;
        }
    }
    LeftNum = k - IL;

    //左子树, 先序起始位置+1, 先序结束位置为左子树结点个数, 中序起始位置不变, 中序结束位置为根的左边
    root->lchild = Create(F, I, FL + 1, FL + LeftNum, IL, k - 1);

    //右子树, 先序起始为左子树起始位置右边, 先序结束位置不变, 中序起始位置为根右边, 中序结束位置不变
    root->rchild = Create(F, I, FL + LeftNum + 1, FR, k + 1, IR);
}
