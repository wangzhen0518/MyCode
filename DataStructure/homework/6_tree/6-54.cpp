#include <iostream>
#include <queue>

using std::queue;

typedef int TElemType;
typedef TElemType ElemType;

typedef struct BiTNode
{
    TElemType data;
    int visited;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

#define LIST_INIT_SIZE 100 //线性表存储空间初始分配量
#define LISTINCREMENT 10   //存储空间分配增量

typedef struct
{
    ElemType *elem; //存储空间基址
    int length;     //当前元素个数(表长）
    int listsize;   //当前分配存储容量
    //以sizeof(ElemType)为单位
} SqList;

void Creat(SqList s, BiTNode *&t)
{
    int i = 0;
    queue<BiTNode **> temp;
    temp.push(&t);
    for (; i < s.length; i++)
    {
        BiTNode **q = temp.front();
        temp.pop();
        *q = new BiTNode;
        (*q)->data = s.elem[i];
        (*q)->lchild = nullptr;
        (*q)->rchild = nullptr;
        (*q)->visited = 0;
        temp.push(&(*q)->lchild);
        temp.push(&(*q)->rchild);
    }
}

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
        std::cout << temp->data << std::endl;
        if (temp->lchild != nullptr)
            q.push(temp->lchild);
        if (temp->rchild != nullptr)
            q.push(temp->rchild);
    }
}

int main()
{
    int len = 7;
    SqList s;
    s.length = len;
    s.elem = new ElemType[len];
    for (int i = 0; i < len; i++)
        s.elem[i] = i;
    s.listsize = sizeof(ElemType) * s.length;

    BiTNode *t;
    Creat(s, t);
    PieceOrder(t);
}