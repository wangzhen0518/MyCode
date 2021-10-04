#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_VERTEX_NUM 20
#define INF (INT_MAX / 5)

typedef struct VexNode
{
    int id; //编号
    int w;  //权值
} VexNode;

//邻接矩阵
typedef struct ArcNode
{
    int w; //边权
} ArcNode, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct
{
    VexNode vertices[MAX_VERTEX_NUM]; //顶点向量
    AdjMatrix adj;                    //邻接矩阵
    int vexnum, arcnum;               //顶点数和弧数
    bool directional;                 //t：有向图，f：无向图
    bool weighted;                    //t：带权图，f：等权图
} MGraph;

int A[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
int Path[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

void prn_pass(int j, int k)
{
    if (Path[j][k] != -1)
    {
        prn_pass(j, Path[j][k]);
        printf(", %d", Path[j][k]);
        prn_pass(Path[j][k], k);
    }
}
void Floyd_path(MGraph *G)
{
    //Path[j][k] = m 表示从j到k的最短路径经过m

    int j, k, m;
    for (j = 0; j < G->vexnum; j++)
        for (k = 0; k < G->vexnum; k++)
        {
            A[j][k] = G->adj[j][k].w;
            Path[j][k] = -1;
        } //各数组的初始化
    for (m = 0; m < G->vexnum; m++)
        for (j = 0; j < G->vexnum; j++)
            for (k = 0; k < G->vexnum; k++)
                //从j到k，经过m点比不经过路径短
                if ((A[j][m] + A[m][k]) < A[j][k])
                {
                    A[j][k] = A[j][m] + A[m][k];
                    Path[j][k] = m;
                } //修改数组A和Path的元素值
    for (j = 0; j < G->vexnum; j++)
        for (k = 0; k < G->vexnum && k != j; k++)
        {
            printf("%d到%d的最短路径为:\n", j, k);
            printf("%d", j);
            prn_pass(j, k);
            printf(", %d\n", k);
            printf("最短路径长度为: %d\n", A[j][k]);
            printf("\n");
        }
} // end of Floyd

/**********生成图，测试代码**********/
//小工具，随机图生成器，生成边表存储在文件filename中
//生成一个随机图包括n个顶点，每个顶点和其它任何顶点连边的概率为p
void randGenGraph(int n, float p, bool weighted, bool directional, const char *filename, int seed)
{
    srand(seed); //确保生成的图可以重现
    //保存文件内容，文件大小不超过5Mbytes，不断把随机生成的图信息写入字符串content中
    char *content = (char *)malloc(5000000);
    if (!content)
    {
        printf("分配存储空间失败\n");
        exit(0);
    }
    FILE *fp = fopen(filename, "wb");
    if (!fp)
    {
        printf("生成图文件 %s 时出错!\n", filename);
        exit(0);
    }

    long offset = 0; //content当前的写入位置
    long ne = 0;     //生成边数

    for (int i = 0; i < n; ++i)
        offset += sprintf(content + offset, "%3d\t %3d\n", i, rand() % 100); //写入结点的编号以及结点随机权值

    int pn = (int)(10000 * p);
    if (directional)
    {                               //有向图
        for (int i = 0; i < n; ++i) //写入随机边
            for (int j = 0; j < n; ++j)
                if (i != j && rand() % 10000 < pn)
                {
                    offset += sprintf(content + offset, "%3d\t %3d\t %4d\n", i, j, weighted ? rand() % 100 : 1);
                    ne++;
                }
    }
    else
    {                               //无向图
        for (int i = 0; i < n; ++i) //写入随机边
            for (int j = i + 1; j < n; ++j)
                if (rand() % 10000 < pn)
                {
                    offset += sprintf(content + offset, "%3d\t %3d\t %4d\n", i, j, weighted ? rand() % 100 : 1);
                    ne++;
                }
    }

    char ch[40];
    int sz = sprintf(ch, "%3d\t %3d\t %5s\t %5s\n", n, ne, weighted ? "true" : "false", directional ? "true" : "false");
    fwrite(&ch, sz, 1, fp);         //写入图的顶点数目和边的数目
    fwrite(content, offset, 1, fp); //写入图的顶点和边信息
    fclose(fp);
    free(content);
}

//从文件中读入图，在内存中生成图的表示
void initGraph(MGraph *g, const char *gfile)
{
    FILE *fp = fopen(gfile, "r");
    if (!fp)
    {
        printf("读取图数据文件出错\n");
        exit(0);
    }

    char bv[10];
    //读取图的基本信息 ,图的类型，顶点数，边数等
    fscanf(fp, "%u%lu", &(g->vexnum), &(g->arcnum));
    fscanf(fp, "%s", bv);
    g->weighted = strcmp(bv, "true") == 0 ? true : false;
    fscanf(fp, "%s", bv);
    g->directional = strcmp(bv, "true") == 0 ? true : false;

    //读取顶点信息：id，w，degree； 没有 edges（读边信息时加上）
    for (int i = 0; i < g->vexnum; ++i)
    {
        fscanf(fp, "%d%d", &(g->vertices[i].id), &(g->vertices[i].w));
        printf("顶点 %d - 权 %d\n", g->vertices[i].id, g->vertices[i].w);
    }

    //初始化邻接矩阵
    for (int i = 0; i < g->vexnum; i++)
        for (int j = 0; j < g->vexnum; j++)
            g->adj[i][j].w = INF;

    //读取边信息: g.e[i]: id,h,t,w; 同时每条边要修改顶点的edges和degree
    for (unsigned long i = 0; i < g->arcnum; ++i)
    {
        int h, t; //边的头尾
        int w;    //边的权值
        fscanf(fp, "%u%u%d", &h, &t, &w);
        ArcNode *edge = (ArcNode *)malloc(sizeof(ArcNode));
        edge->w = w; //读入权
        //插入边
        g->adj[t][h] = *edge;
        printf("边:%u-%u => %d\n", t, h, edge->w);
        if (g->directional == false) //无向图的弧头h也要加边
            g->adj[h][t] = *edge;
    }
    fclose(fp);
}

//打印邻接表的信息
void printG(MGraph *g)
{
    printf("图的基本信息：顶点数(%u)-边数(%ul)-%s-%s\n", g->vexnum, g->arcnum, g->weighted ? "加权图" : "等权图", g->directional ? "有向图" : "无向图");
    for (int i = 0; i < g->vexnum; ++i)
    {
        printf("ID(%u)-权(%d)-弧表 t(eid|w)：%u ", g->vertices[i].id, g->vertices[i].w, g->vertices[i].id);
        for (int j = 0; j < g->vexnum; j++)
            if (j != i && g->adj[i][j].w != INF)
                printf("-> %u(%d) ", j, g->adj[i][j].w);
        printf("\n");
    }
}

int main()
{
    int seed = 121;
    char filename[10] = "g2.txt";
    randGenGraph(MAX_VERTEX_NUM, 0.2, true, true, filename, seed);
    MGraph *g = (MGraph *)malloc(sizeof(MGraph));

    printf("size of g = %ld\n", sizeof(MGraph));
    initGraph(g, filename);
    printG(g);
    Floyd_path(g);
    return 0;
}