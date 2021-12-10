#include <iostream>

#define INFINITY INT_MAX  //最大值
#define MAX_VERTEX_NUM 20 //最大顶点个数

typedef enum
{
    DG,      //有向无权图
    DN,      //有向有权图
    UDG,     //无向无权图
    UDN      //无向有权图
} GraphKind; //图的类型

typedef int WType;
typedef int InfoType;
typedef char VexType;

//邻接表
typedef struct ArcNode
{
    int adjvex;              //该弧所指向的顶点的位置
    int lf;                  //标记是左孩子还是右孩子
    struct ArcNode *nextarc; //指向下一条弧的位置
    InfoType *info;          //有关弧的信息
} ArcNode;
typedef struct VexNode
{
    int id;
    VexType data;      //顶点信息
    ArcNode *firstarc; //指向第一条依附于该顶点的弧
} VexNode, AdjList[MAX_VERTEX_NUM];
typedef struct ALGraph
{
    AdjList vertices;
    int vexnum, arcnum; //顶点数和边数
    GraphKind kind;     //图的种类
} ALGraph;

//输出表达式的逆波兰式
void Traveral(ALGraph *g, VexNode *v)
{
    if (v->firstarc == nullptr)
        std::cout << v->data;
    //左右孩子均有
    else if (v->firstarc->lf == 0 && v->firstarc->nextarc != nullptr)
    {
        Traveral(g, &g->vertices[v->firstarc->adjvex]);
        Traveral(g, &g->vertices[v->firstarc->nextarc->adjvex]);
        std::cout << v->data;
    }
    else if (v->firstarc->lf == 1 && v->firstarc->nextarc != nullptr)
    {
        Traveral(g, &g->vertices[v->firstarc->nextarc->adjvex]);
        Traveral(g, &g->vertices[v->firstarc->adjvex]);
        std::cout << v->data;
    }
    //只有左/右孩子
    else if (v->firstarc->nextarc == nullptr)
    {
        Traveral(g, &g->vertices[v->firstarc->adjvex]);
        std::cout << v->data;
    }
}
void NiPolish(ALGraph *g)
{
    Traveral(g, &g->vertices[0]);
}