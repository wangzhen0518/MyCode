#include <stdio.h>
#include <stdlib.h>

#include <queue>
#include <stack>

using std::queue;
using std::stack;

typedef char TElemType;

/**********二叉树**********/
//二叉链表
typedef struct BiTNode {
    TElemType data;
    int visited;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

//三叉链表
typedef struct BiTnode3 {
    TElemType data;
    struct BiTnode3 *lchild, *rchild, *parent;
} BiTNode3, *BiTree3;

//遍历
//中序遍历
bool InOrder(const BiTree t) {
    if (t != NULL) {
        InOrder(t->lchild);
        //访问t
        InOrder(t->rchild);
    } else
        return true;
}

//先序遍历
bool PreOrder(const BiTree t) {
    if (t != NULL) {
        //访问t
        PreOrder(t->lchild);
        PreOrder(t->rchild);
    } else
        return false;
}

//后序遍历
bool PostOrder(const BiTree t) {
    if (t != NULL) {
        PostOrder(t->lchild);
        PostOrder(t->rchild);
        //访问t
    } else
        return true;
}

//构造二叉树
bool CreateBiTree(BiTree* t) {
    char ch;
    ch = getchar();
    if (ch == '@')
        *t = NULL;
    else {
        *t = (BiTNode*)malloc(sizeof(BiTNode));
        if (*t == NULL) return false;
        (*t)->data = ch;
        CreateBiTree(&((*t)->lchild));
        CreateBiTree(&((*t)->rchild));
    }
    return true;
}

//非递归中序遍历
bool InOrderTraverse(BiTree t) {
    stack<BiTNode*> s;
    BiTNode* p;
    if (t == nullptr) return false;
    s.push(t);
    while (!s.empty()) {
        //向左走到头
        while ((p = s.top()) != nullptr)
            s.push(p->lchild);
        s.pop();
        if (!s.empty()) {
            p = s.top();
            s.pop();
            s.push(p->rchild);
        }
    }

    return true;
}

//非递归先序遍历
bool PreOrderTraverse(BiTree t) {
    stack<BiTNode*> s;
    BiTNode* p;
    if (t == nullptr) return false;
    s.push(t);
    while (!s.empty()) {
        p = s.top();  //访问
        s.pop();
        //先将右孩子入栈，再将左孩子入栈，以实现先访问左孩子，再访问右孩子
        if (p->rchild != nullptr) s.push(p->rchild);
        if (p->lchild != nullptr) s.push(p->lchild);
    }
    return true;
}

//非递归后序遍历
bool PostOrderTraverse(BiTree t) {
    stack<BiTNode*> s;
    BiTNode* p;
    if (t == nullptr) return false;
    s.push(t);
    while (!s.empty()) {
        p = s.top();
        //如果左节点非空，且左节点未访问，则向左走到头
        while (p->lchild != nullptr && p->lchild->visited == 0)
            s.push(p->lchild);

        p = s.top();
        if (p->rchild == nullptr &&
            p->visited == 0)  // p无右节点，且尚未访问，进行访问
        {
            p->visited = 1;  //访问结点
            s.pop();         //退栈

            p = s.top();
            if (p->rchild != nullptr &&
                p->rchild->visited == 0)  // p有右节点，且右节点尚未入栈
                s.push(p->rchild);
            else  // p无右节点，或已入过栈，则p左右节点均已访问过，对p进行访问
            {
                p->visited = 1;  //访问
                s.pop();         //退栈
            }
        } else if (
            p->rchild->visited ==
            1)  // p有右节点，但已入过栈，则p左右节点均已访问过，对p进行访问
        {
            p->visited = 1;  //访问
            s.pop();         //退栈
        } else               // p有右节点，且右节点未入栈
            s.push(p->rchild);
    }
}

/**********树**********/
//双亲表示法
#define MAX_TREE_SIZE 20
typedef struct PTNode {
    TElemType data;
    int parent;
} PTNode;
typedef struct {
    PTNode nodes[MAX_TREE_SIZE];
    int r, n;  //根的位置和结点数
} PTree;

//孩子兄弟表示法
typedef struct CSNode {
    TElemType data;
    struct CSNode *firstChild, *nextSibling;
} CSNode, *CSTree;

//哈夫曼树
const int n = 20;         //叶结点数
const int m = 2 * n - 1;  //总结点数
typedef struct {
    float weight;
    int parent, leftChild, rightChild;
} HTNode, HuffmanTree[m];

//构造哈夫曼树
#define MaxNum 1000000
void CreatHuffmanTree(HuffmanTree t, float fr[]) {
    // t中前n项存储叶结点，也即给定权的值
    // t的后m-n项存储非叶结点，由各叶结点构造而得
    //初始化
    int i = 0;
    for (; i < n; i++)
        t[i].weight = fr[i];
    for (i = 0; i < m; i++) {
        t[i].parent = -1;
        t[i].leftChild = -1;
        t[i].rightChild = -1;
    }

    //构造
    for (i = n; i < m; i++) {
        int min1, min2;
        min1 = min2 = MaxNum;
        int pos1 = 0, pos2 = 0;
        //找得前n项中未加入树的最小的2个值
        for (int j = 0; j < i; i++)
            if (t[j].parent == -1) {
                if (t[j].weight < min1) {
                    pos2 = pos1;
                    min2 = min1;
                    pos1 = j;
                    min1 = t[j].weight;
                } else if (t[j].weight < min2) {
                    pos2 = j;
                    min2 = t[j].weight;
                }
            }
        t[i].leftChild = pos1;
        t[i].rightChild = pos2;
        t[i].weight = t[pos1].weight + t[pos2].weight;
        t[pos1].parent = t[pos2].parent = i;
    }
}
