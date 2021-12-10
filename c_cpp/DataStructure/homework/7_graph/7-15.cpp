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
typedef int VexType;

//邻接矩阵
typedef struct ArcCell
{
    WType w;        // WType为边权值类型
    InfoType *info; //该弧相关信息指针
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct MGraph
{
    VexType vexs[MAX_VERTEX_NUM]; //顶点向量
    AdjMatrix adj;                //邻接矩阵
    int vexnum, arcnum;           //顶点数和弧数
    GraphKind kind;               //图的种类标志
} MGraph;

bool InsertVex(MGraph &g, const VexType &v)
{
    if (g.vexnum == MAX_VERTEX_NUM)
    {
        std::cout << "no space";
        return false;
    }

    g.vexs[g.vexnum++] = v;
    for (int i = 0; i < g.vexnum; i++)
        g.adj[g.vexnum - 1][i].w = INFINITY;

    return true;
}

bool InsertArc(MGraph &g, int v, int u, int w)
{
    //有向图
    if (g.kind == DG || g.kind == DN)
        g.adj[v][u].w = w;
    //无向图
    else
    {
        g.adj[v][u].w = w;
        g.adj[u][v].w = w;
    }
}

bool DeleteVex(MGraph &g, const VexType &v)
{
    if (g.vexnum == 0)
        return false;

    for (int i = v + 1; i < g.vexnum; i++)
        g.vexs[i - 1] = g.vexs[i];
    g.vexs[g.vexnum - 1] = -1;

    //先将邻接矩阵v行以下的上移一行
    for (int i = v + 1; i < g.vexnum; i++)
        for (int j = 0; j < g.vexnum; j++)
            g.adj[i - 1][j] = g.adj[i][j];
    for (int i = 0; i < g.vexnum; i++)
        g.adj[g.vexnum - 1][i].w = INFINITY;
    //再将v列以后的左移一行
    for (int i = 0; i < g.vexnum - 1; i++)
        for (int j = v + 1; j < g.vexnum; j++)
            g.adj[i][j - 1] = g.adj[i][j];
    for (int i = 0; i < g.vexnum; i++)
        g.adj[i][g.vexnum - 1].w = INFINITY;

    g.vexnum--;

    return true;
}

bool DeleteArc(MGraph &g, int v, int u)
{
    //有向图
    if (g.kind == DG || g.kind == DN)
        g.adj[v][u].w = INFINITY;
    //无向图
    else
    {
        g.adj[v][u].w = INFINITY;
        g.adj[u][v].w = INFINITY;
    }
}
