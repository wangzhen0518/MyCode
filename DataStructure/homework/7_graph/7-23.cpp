#include <iostream>
#include <queue>

using std::queue;

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
typedef int VexType;

//邻接表
typedef struct ArcNode
{
    int adjvex;              //该弧所指向的顶点的位置
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

//基于深度优先策略，搜索是否存在v->u的路径
bool SearchDFS(ALGraph *g, int v, int u)
{
    bool visited[MAX_VERTEX_NUM] = {false};
    queue<VexNode *> s;
    s.push(&g->vertices[v]);
    visited[v] = true;

    VexNode *temp;
    while (!s.empty())
    {
        temp = s.front();
        s.pop();
        for (ArcNode *arc = temp->firstarc; arc != nullptr; arc = arc->nextarc)
        {
            int w = arc->adjvex;
            if (visited[w] == false)
            {
                if (w == u)
                    return true;
                s.push(&g->vertices[w]);
                visited[w] = true;
            }
        }
    }
    return false;
}