#include <iostream>
#include <queue>

using std::queue;

typedef int TElemType;

typedef struct BiTNode
{
    TElemType data;
    int visited;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

//层序遍历
void PieceOrder(BiTree t)
{
    queue<BiTNode *> q;
    BiTNode *temp;

    q.push(t);
    while (!q.empty())
    {
        temp = q.front();
        q.pop();
        //visit temp
        if (temp->lchild != nullptr)
            q.push(temp->lchild);
        if (temp->rchild != nullptr)
            q.push(temp->rchild);
    }
}