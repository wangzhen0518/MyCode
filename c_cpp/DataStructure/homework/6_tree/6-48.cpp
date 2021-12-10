#include <iostream>
#include<stack>

using std::stack;

typedef int TElemType;

typedef struct BiTNode
{
    TElemType data;
    int visited;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

//寻找p，q的最近共同祖先
BiTNode *Search(BiTNode *p, BiTNode *q, BiTree t)
{
    stack<BiTNode *> s;
    
}