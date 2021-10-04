#include <stdlib.h>
#include <stdio.h>
#include <climits>

#define MAX_VERTEX_NUM 20
#define INF (INT_MAX / 5)

/**********邻接矩阵实现**********/
typedef int *ShortPathTable;
typedef bool **PathMatrix;

//邻接矩阵
typedef struct ArcNode
{
    int w; //边权
} ArcNode, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct VexNode
{
    int id; //编号
    int w;  //权值
} VexNode;
typedef struct
{
    VexNode vertices[MAX_VERTEX_NUM]; //顶点向量
    AdjMatrix adj;                    //邻接矩阵
    int vexnum, arcnum;               //顶点数和弧数
    bool directional;                 //t：有向图，f：无向图
    bool weighted;                    //t：带权图，f：等权图
} MGraph;

void Dijkstra(MGraph *g, int v0, PathMatrix p, ShortPathTable d)
{
    //p[w][v]为true表示，v在v0到w的最短路径上
    //d存储当前v0到v的路径长度

    //初始化
    bool final[MAX_VERTEX_NUM]; //标识该点是否已进入集合S
    for (int v = 0; v < g->vexnum; v++)
    {
        final[v] = false;
        d[v] = g->adj[v0][v].w;
        for (int w = 0; w < g->vexnum; w++)
            p[v][w] = false;
        if (d[v] < INF)
            p[v][v0] = true;
    }
    d[v0] = 0;
    final[v0] = true;
    for (int i = 1; i < g->vexnum; i++) //每次循环找到1个点，并更新，故总共循环(vexnum-1)次
    {
        int v;
        //首先找出当前图中的最短路径
        int min = INF;
        for (int m = 0; m < g->vexnum; m++)
        {
            //对于还不在集合S，即还未找到最短路径的点进行搜索
            //如果当前v0到m的距离小于min，更新min，并用v记录下点m
            if (!final[m] && d[m] < min)
            {
                min = d[m];
                v = m;
            }
        }
        //当未搜索完全部最短路径前，必有点m的d[m]<INF, 所以v必定更新
        //将当前不在集合S中的最短距离的点m记入集合S
        final[v] = true;
        //更新剩余点的d
        for (int w = 0; w < g->vexnum; w++)
        {
            //如果点w不在集合S中，并且从新加入的点到w的距离比原先小，则更新d[w]
            if (!final[w] && (min + g->adj[v][w].w) < d[w])
            {
                d[w] = min + g->adj[v][w].w;
                p[w][v] = true;
            }
        }
    }
}

//打印出从顶点v0到其余所有顶点的最短路径
void printPath(MGraph *g, PathMatrix p, ShortPathTable d, int v0)
{
    for (int v = 0; v < g->vexnum && v != v0; v++)
    {
        printf("v0(%d) -> v(%d):\n", v0, v);
        printf("%d", v0);
        for (int w = 0; w < g->vexnum; w++)
            if (p[v][w] == true)
                printf(", %d", w);
        printf(", %d\n", v);
        printf("路径长度为：%d\n\n", d[v]);
    }
}

/**********邻接表实现**********/
//邻接表
typedef struct ArcNode
{
    int adjvex;              //该弧所指向的顶点的位置
    struct ArcNode *nextarc; //指向下一条弧的位置
    int w;                   //弧的权
} ArcNode;
typedef struct VexNode
{
    int id;
    int degree;        //顶点的(出度)度
    int w;             //顶点的权
    ArcNode *firstarc; //指向第一条依附于该顶点的弧
} VexNode, AdjList[MAX_VERTEX_NUM];
typedef struct
{
    AdjList vertices;
    int vexnum, arcnum; //顶点数和边数
    bool directional;   //t：有向图，f：无向图
    bool weighted;      //t：带权图，f：等权图
} ALGraph;

//路径存储结构
typedef struct
{
    int vex_id[MAX_VERTEX_NUM]; //记录路径上每个点的id
    int len;
} Path;

typedef VexNode *LElemType;
typedef struct ListNode
{
    LElemType node;
    struct ListNode *next;
} ListNode, *List;

//#define INF (INT_MAX / 5)
void Dijkstra(ALGraph *g, int v0, Path *p)
{
    //其实准确来说，fringe不完全是边界，而是当前搜索的边界，加上已经找到最短路径的点
    //记录点是否在fringe内
    bool infringe[MAX_VERTEX_NUM] = {false}; //检查final是否全部初始化为false
    //初始化path
    for (int i = 0; i < g->vexnum; i++)
    {
        for (int j = 0; j < g->vexnum; j++)
            p[i].vex_id[j] = -1;
        p[i].len = INF;
    }
    p[v0].len = 0;
    infringe[v0] = true;
    int lastvex[MAX_VERTEX_NUM]; //记录最短路径中，每个点的前一个点，以得到路径
    for (int i = 0; i < g->vexnum; i++)
        lastvex[i] = -1;

    //初始化fringe
    List fringe = (ListNode *)malloc(sizeof(ListNode));
    ListNode *q = (ListNode *)malloc(sizeof(ListNode));
    if (!fringe || !q)
    {
        printf("内存不够！\n");
        exit(-1);
    }
    fringe->node = NULL;
    fringe->next = q;
    q->node = &g->vertices[v0];
    q->next = NULL;

    //对于最短路径上的点进行标记，从源点到目标点的最短路径上的上一个点存入lastvex中
    while (fringe->next != NULL)
    {
        int min = INF;
        ListNode *v = NULL;
        //找当前边界上，到v0最近的点
        for (ListNode *m = fringe; m->next != NULL; m = m->next)
        {
            if (p[m->next->node->id].len < min)
            {
                v = m;
                min = p[m->next->node->id].len;
            }
        }
        q = v->next;
        v->next = q->next; //将v从fringe中删除
        //infringe[q->node->id] = false;
        //考虑q的所有邻点
        for (ArcNode *edge = g->vertices[q->node->id].firstarc; edge != NULL; edge = edge->nextarc)
        {
            //不在fringe中的全部加入
            if (infringe[edge->adjvex] == false)
            {
                ListNode *m = (ListNode *)malloc(sizeof(ListNode));
                m->node = &g->vertices[edge->adjvex];
                m->next = v->next;
                v->next = m;
                infringe[edge->adjvex] = true;
                p[edge->adjvex].len = p[q->node->id].len + edge->w;
                lastvex[edge->adjvex] = q->node->id;
            }
            //对于在fringe中的点，如果从q走更近，则更新路径
            else if (p[edge->adjvex].len > p[q->node->id].len + edge->w)
            {
                p[edge->adjvex].len = p[q->node->id].len + edge->w;
                lastvex[edge->adjvex] = q->node->id;
            }
        }
        free(q);
    }
    //利用lastvex整理出最短路径
    //路径倒序存储
    for (int i = 0; i < g->vexnum; i++)
    {
        if (i != v0)
        {
            int k = lastvex[i];
            int j = 0;
            while (k != -1)
            {
                p[i].vex_id[j++] = k;
                k = lastvex[k];
            }
        }
        else
            p[i].vex_id[0] = v0;
    }
}

//打印路径
void printPath(ALGraph *g, int v0, Path *p)
{
    for (int i = 0; i < g->vexnum; i++)
    {
        printf("v0(%d)->v(%d):\n", v0, i);
        if (p[i].len == INF)
        {
            printf("不连通！\n\n");
            continue;
        }
        int j = 0;
        //由于路径倒序存储，找到最后一个点，倒序打印
        while (p[i].vex_id[j] != -1)
            j++;
        j--;
        for (; j >= 0; j--)
            printf("%d, ", p[i].vex_id[j]);
        printf("%d\n", i);
        printf("最短路径长度为：%d\n\n", p[i].len);
    }
}
