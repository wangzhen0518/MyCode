#include <iostream>
#include <queue>

#define MAX 1000000000

using std::queue;

typedef int TElemType;

typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

//计算孩子-兄弟树的深度
int Deep(BiTree t)
{
    int deep = 0;
    queue<BiTNode *> q;
    BiTNode *temp;
    BiTNode *item; //标记一层结束
    item->data = MAX;
    item->lchild = item->rchild = nullptr;

    q.push(t);
    q.push(item);
    while (!q.empty())
    {
        //一层结束，深度+1
        if (q.front() == item)
        {
            deep++;
            q.pop();
            q.push(item);
        }

        if (!q.empty())
        {
            temp = q.front()->lchild;
            q.pop();
            //将兄弟全部入栈
            while (temp != nullptr)
            {
                q.push(temp);
                temp = temp->rchild;
            }
        }
    }
}