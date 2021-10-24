#include <stdlib.h>

#include <cstring>
#include <iostream>
#include <queue>
#include <stack>

using std::queue;
using std::stack;

#define INFINITY 100000000  //最大值
#define MAX_VERTEX_NUM 20   //最大顶点个数
typedef enum {
    DG,       //有向无权图
    DN,       //有向有权图
    UDG,      //无向无权图
    UDN       //无向有权图
} GraphKind;  //图的类型
typedef int WType;
typedef int InfoType;
typedef int VexType;

//邻接矩阵
typedef struct ArcCell {
    WType w;         // WType为边权值类型
    InfoType* info;  //该弧相关信息指针
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct MGraph {
    VexType vexs[MAX_VERTEX_NUM];  //顶点向量
    AdjMatrix adj;                 //邻接矩阵
    int vexnum, arcnum;            //顶点数和弧数
    GraphKind kind;                //图的种类标志
} MGraph;

//邻接表1
typedef struct ArcNode {
    int adjvex;               //该弧所指向的顶点的位置
    struct ArcNode* nextarc;  //指向下一条弧的位置
    InfoType* info;           //有关弧的信息
} ArcNode;
typedef struct VexNode {
    int id;
    VexType data;       //顶点信息
    ArcNode* firstarc;  //指向第一条依附于该顶点的弧
} VexNode, AdjList[MAX_VERTEX_NUM];
typedef struct ALGraph {
    AdjList vertices;
    int vexnum, arcnum;  //顶点数和边数
    GraphKind kind;      //图的种类
} ALGraph;

#define MAX_VERTEX_NUM 20  //最大顶点个数

//邻接表2
typedef struct ArcNode2 {
    int adjvex;                //该弧所指向的顶点的位置
    struct ArcNode2* nextarc;  //指向下一条弧的位置
    int w;                     //弧的权
} ArcNode2;
typedef struct VexNode2 {
    int id;
    int degree;          //顶点的(出度)度
    int w;               //顶点的权
    ArcNode2* firstarc;  //指向第一条依附于该顶点的弧
} VexNode2, AdjList2[MAX_VERTEX_NUM];
typedef struct ALGraph2 {
    AdjList2 vertices;
    int vexnum, arcnum;  //顶点数和边数
    bool directional;    // t：有向图，f：无向图
    bool weighted;       // t：带权图，f：等权图
} ALGraph2;

//十字链表
typedef struct ArcNode3 {
    int tailvex, headvex;
    InfoType* info;
    struct ArcNode3 *hlink, *tlink;
} ArcNode3;  //弧结点类型定义
typedef struct VNode {
    VexType data;
    ArcNode3 *firstin, *firstout;
} VNode;
typedef struct OLGraph {
    int vexnum;
    VNode xlist[MAX_VERTEX_NUM];
} OLGraph;

//无向图的邻接多重表的实现
typedef struct EdgeNode {
    int ivex, jvex;  //该边依附的两个结点在图中的位置
    InfoType* info;
    struct EdgeNode *ilink, *jlink;  //分别指向依附于这两个顶点的下一条边
} EdgeNode;
typedef struct VexNoden {
    VexType data;
    EdgeNode* firstedge;
} VexNoden;
typedef struct AMGraph {
    int vexnum;
    VexNoden mullist[MAX_VERTEX_NUM];
} AMGraph;

#define NUM 20
typedef struct {
    VexNode* vexs[NUM];
    int len;
} Path;

// BFS
Path SearchOnGraph_BFS(ALGraph* G, int id1, int id2,
                       int (*Goal)(VexNode* v, int id)) {
    VexNode* s;
    //初始化访问数组
    int visit[NUM] = {0};

    //初始化路径
    Path path;  // path中的每个成员指向图中的一个顶点
    for (int i = 0; i < NUM; i++)
        path.vexs[i] = NULL;
    path.vexs[0] = &G->vertices[id1];
    path.len = 1;
    int lastvex[NUM];  // lastvexs记录每一个顶点的上一个顶点在path.vexs中的下标
    for (int i = 0; i < NUM; i++)
        lastvex[i] = -1;

    //初始化fringe
    queue<VexNode*> fringe;
    if ((*Goal)(&G->vertices[id1], id2) == 1)  // G->vertices[id1]就是目标顶点
        return path;
    fringe.push(&G->vertices[id1]);
    visit[id1] = 1;

    int i = 0;
    while (!fringe.empty()) {
        s = fringe.front();
        fringe.pop();
        int sn = 0;
        //访问s的所有未被访问的邻顶
        while (path.vexs[sn] != s)  //找到s在path中的下标
            sn++;
        for (ArcNode* w = s->firstarc; w != NULL; w = w->nextarc) {
            if (visit[w->adjvex] == 0)  //如果这个顶点未被访问过
            {
                i++;
                visit[w->adjvex] = 1;                    //标记w被访问
                path.vexs[i] = &G->vertices[w->adjvex];  // w加入路径
                lastvex[i] = sn;                         // w前一个点是s

                if ((*Goal)(&G->vertices[w->adjvex], id2) == 1)  //找到目标点
                {
                    //开始对path进行调整，删除多余的顶点
                    int k = i;
                    while (k > 0) {
                        i--;
                        k = lastvex[k];
                        path.vexs[i] = path.vexs[k];
                        path.len++;
                    }
                    k = 0;
                    while (k < path.len) {
                        path.vexs[k] = path.vexs[i];
                        k++;
                        i++;
                    }
                    while (k < NUM)
                        path.vexs[k++] = NULL;
                    return path;
                } else
                    fringe.push(&G->vertices[w->adjvex]);
            }
        }
    }
    printf("No Goal!\n");
    exit(-1);  //未找到目标
}

// DFS
Path SearchOnGraph_DFS(ALGraph* G, int id1, int id2,
                       int (*Goal)(VexNode* v, int id)) {
    VexNode* s;
    //初始化访问数组
    int visit[MAX_VERTEX_NUM] = {0};

    //初始化路径
    Path path;  // path中的每个成员指向图中的一个顶点
    for (int i = 0; i < NUM; i++)
        path.vexs[i] = NULL;
    path.vexs[0] = &G->vertices[id1];
    path.len = 1;
    int lastvex
        [MAX_VERTEX_NUM];  // lastvexs记录每一个顶点的上一个顶点在path.vexs中的下标
    for (int i = 0; i < MAX_VERTEX_NUM; i++)
        lastvex[i] = -1;

    //初始化fringe
    stack<VexNode*> fringe;
    if ((*Goal)(&G->vertices[id1], id2) == 1)  // G->vertices[0]就是目标顶点
        return path;
    fringe.push(&G->vertices[id1]);
    visit[id1] = 1;

    int i = 0;
    while (!fringe.empty()) {
        s = fringe.top();
        fringe.pop();
        //访问s的所有未被访问的邻顶
        int sn = 0;
        while (path.vexs[sn] != s)  //找到s在path中的下标
            sn++;
        for (ArcNode* w = s->firstarc; w != NULL; w = w->nextarc) {
            if (visit[w->adjvex] == 0)  //如果这个顶点未被访问过
            {
                i++;
                visit[w->adjvex] = 1;                    //标记w被访问
                path.vexs[i] = &G->vertices[w->adjvex];  // w加入路径
                lastvex[i] = sn;                         // w前一个点是s

                if ((*Goal)(&G->vertices[w->adjvex], id2) == 1)  //找到目标点
                {
                    //开始对path进行调整，删除多余的顶点
                    int k = i;
                    while (k > 0) {
                        i--;
                        k = lastvex[k];
                        path.vexs[i] = path.vexs[k];
                        path.len++;
                    }
                    k = 0;
                    while (k < path.len) {
                        path.vexs[k] = path.vexs[i];
                        k++;
                        i++;
                    }
                    while (k < MAX_VERTEX_NUM)
                        path.vexs[k++] = NULL;
                    return path;
                } else
                    fringe.push(&G->vertices[w->adjvex]);
            }
        }
    }
    printf("No Goal!\n");
    exit(-1);  //未找到目标
}

//打印路径
void printPath(Path path) {
    printf("%3d", path.vexs[0]->id);
    for (int i = 1; i < path.len; i++) {
        printf("->%3d", path.vexs[i]->id);
    }
}

// Goal目标函数: 找2点之间一条路径
int Goal(VexNode* v, int id) {
    if (v->id == id)
        return 1;
    else
        return 0;
}

//构造生成树
typedef VexType TElemType;
typedef struct CSNode {
    TElemType data;
    struct CSNode *firstchild, *nextsibling;
} CSNode;
//广度优先搜索遍历图时，在内存中构造生成树
CSNode* BFStree(ALGraph* G, int v) {
    //初始化
    CSNode *T, *ptr, *q, *vertices[MAX_VERTEX_NUM] = {nullptr};
    CSNode* now;  //增加now指针指向构造的树当前层的第一个顶点
    ArcNode* p;

    //先将G的所有顶点建立相应的树结点
    for (int i = 0; i < G->vexnum; i++) {
        vertices[i] = (CSNode*)malloc(sizeof(CSNode));
        if (vertices[i] == nullptr) {
            printf("Not Enough Space.\n");
            return nullptr;
        }
        vertices[i]->data = G->vertices[i].data;
        vertices[i]->firstchild = nullptr;
        vertices[i]->nextsibling = nullptr;
    }

    //标记相应点是否已访问
    bool visited[MAX_VERTEX_NUM] = {false};
    queue<int> Q;
    int w, k;

    // visit v
    visited[v] = true;  //标记起始点v已访问
    T = vertices[v];    //根节点
    Q.push(v);          // v入队

    //生成树
    while (!Q.empty()) {
        w = Q.front();
        Q.pop();
        q = NULL;  //孩子-兄弟表示， 理解标记Q非常重要
        // p的所有邻点为兄弟，均为w的孩子
        p = G->vertices[w].firstarc;
        // now为当前访问顶点
        now = vertices[v];
        // p表示出队节点w关联的各条连边/节点
        // v的所有未访问邻点入队
        while (p != NULL) {
            k = p->adjvex;
            if (!visited[k]) {
                // visit k
                visited[k] = true;
                ptr = vertices[k];
                if (q == NULL)
                    now->firstchild = ptr;
                else
                    q->nextsibling = ptr;
                q = ptr;
                Q.push(k);  // k入队
            }
            p = p->nextarc;
        }
    }
    return T;
}

//深度优先搜索遍历图时，在内存中构造生成森林
CSNode* DFSforest(ALGraph* G, int v) {
    //初始化
    CSNode *T, *ptr, *q, *vertices[MAX_VERTEX_NUM] = {nullptr};
    CSNode* now;  //增加now指针指向构造的树当前层的第一个顶点
    ArcNode* p;

    //先将G的所有顶点建立相应的树结点
    for (int i = 0; i < G->vexnum; i++) {
        vertices[i] = (CSNode*)malloc(sizeof(CSNode));
        if (vertices[i] == nullptr) {
            printf("Not Enough Space.\n");
            return nullptr;
        }
        vertices[i]->data = G->vertices[i].data;
        vertices[i]->firstchild = nullptr;
        vertices[i]->nextsibling = nullptr;
    }

    //标记相应点是否已访问
    bool visited[MAX_VERTEX_NUM] = {false};
    stack<int> Q;
    int w, k;

    // visit v
    visited[v] = true;  //标记起始点v已访问
    T = vertices[v];    //根节点
    Q.push(v);          // v入队

    //生成树
    while (!Q.empty()) {
        w = Q.top();
        Q.pop();
        q = NULL;  //孩子-兄弟表示， 理解标记Q非常重要
        // p的所有邻点为兄弟，均为w的孩子
        p = G->vertices[w].firstarc;
        // now为当前访问顶点
        now = vertices[v];
        // p表示出队节点w关联的各条连边/节点
        // v的所有未访问邻点入队
        while (p != NULL) {
            k = p->adjvex;
            if (!visited[k]) {
                // visit k
                visited[k] = true;
                ptr = vertices[k];
                if (q == NULL)
                    now->firstchild = ptr;
                else
                    q->nextsibling = ptr;
                q = ptr;
                Q.push(k);  // k入队
            }
            p = p->nextarc;
        }
    }
    return T;
}

//求最小生成树：普里姆算法
typedef struct {
    VexType adjvex;
    WType lowcost;  // 0:已经加入U； 无穷大:无直接连边
} Closedge[MAX_VERTEX_NUM];
int minimum(Closedge closedge) {
    int k = 0;
    int min = INFINITY;
    for (int i = 1; i < MAX_VERTEX_NUM; i++) {
        int low = closedge[i].lowcost;
        if (low != 0 && min > low) {
            k = i;
            min = low;
        }
    }
    return k;
}
void MiniSpanTree_PRIM(MGraph G, int u) {
    //初始化
    Closedge closedge;
    for (int i = 0; i < MAX_VERTEX_NUM; i++) {
        closedge[i].adjvex = u;
        closedge[i].lowcost = G.adj[u][i].w;
    }

    int k;
    for (int i = 0; i < G.vexnum && i != u; ++i) {
        k = minimum(closedge);  //非0最小权值的下标
        // printf(closedge[k].adjvex, G.vexs[k]);
        closedge[k].lowcost = 0;            // k并入U集
        for (int j = 0; j < G.vexnum; ++j)  //调整辅助数组
            if (G.adj[k][j].w < closedge[j].lowcost)
                closedge[j] = {G.vexs[k], G.adj[k][j].w};
    }  //各边有相同权值时，因选择的随意性，生成树可能不唯一
}  //各边的权值不相同时，产生的生成树是唯一的

//拓扑排序的实现
void count_indegree(ALGraph2* g) {
    int k;
    ArcNode2* p;
    for (k = 0; k < g->vexnum; k++)
        g->vertices[k].degree = 0;
    for (k = 0; k < g->vexnum; k++) {
        p = g->vertices[k].firstarc;
        while (p != nullptr) {
            g->vertices[p->adjvex].degree++;
            p = p->nextarc;
        }
    }
}
bool Topologic_Sort(ALGraph2* g, int topol[MAX_VERTEX_NUM]) {
    int k, now, vex_now, top = 0, count = 0;
    bool boolean = 1;
    int stack[MAX_VERTEX_NUM];
    ArcNode2* p;

    //初始化
    count_indegree(g);
    for (k = 0; k < g->vexnum; k++)  //入度为零的点入栈
        if (g->vertices[k].degree == 0)
            stack[top++] = g->vertices[k].id;

    do {
        if (top == 0)
            boolean = false;
        else {
            now = stack[top--];    //出栈
            topol[count++] = now;  //记录顶点序列
            //补充打印输出代码
            p = g->vertices[now].firstarc;
            while (p != nullptr)  //删除以顶点为尾的弧
            {
                vex_now = p->adjvex;
                g->vertices[vex_now].degree--;
                if (g->vertices[vex_now].degree == 0)
                    stack[top++] = vex_now;
                p = p->nextarc;
            }
        }
    } while (boolean);
    if (count < g->vexnum)
        return false;
    else
        return true;
}

//关键路径
void critical_path(ALGraph2* g) {
    int j, k, m;
    int topol[MAX_VERTEX_NUM];
    int ve[MAX_VERTEX_NUM] = {0};  //事件最早发生时间
    int vl[MAX_VERTEX_NUM];        //事件最晚发生时间
    ArcNode2* p;
    if (Topologic_Sort(g, topol) == false)
        printf("AOE网中存在回路，错误！\n");
    else {
        //遍历拓扑序列中第m个顶点的边链表
        //更新被指向节点的ve(k)，求最大值
        //从拓扑有序序列的第一个开始， 依次
        //计算每个事件的最早发生时间ve值
        for (m = 0; m < g->vexnum; m++) {
            j = topol[m];
            p = g->vertices[j].firstarc;
            for (; p != nullptr; p = p->nextarc) {
                k = p->adjvex;
                if (ve[j] + p->w > ve[k])
                    ve[k] = ve[j] + p->w;
            }
        }

        //初始化vl
        for (j = 0; j < g->vexnum; j++)
            vl[j] = ve[j];
        //遍历拓扑序列中第m个顶点的边链表
        //更新被指向节点的vl(k)，求最小值
        //从拓扑有序序列的最后一个开始，
        //依次计算每个事件的最早发生时间vl值
        for (m = g->vexnum - 1; m >= 0; m--) {
            j = topol[m];
            p = g->vertices[j].firstarc;
            for (; p != nullptr; p = p->nextarc) {
                k = p->adjvex;
                if (vl[k] - p->w < vl[j])
                    vl[j] = vl[k] - p->w;
            }
        }
        //注意更新ve和vl时，方法不完全相同
        // ve更新的是ve[k]，是j指向的顶点
        // vl更新的是vl[j]，是当前访问的顶点
        //这种差异主要由数据结构导致，数据只存储了顶点所指向的点，而未存储指向顶点的点
        //因此更新ve时，由前驱+边权，更便于更新ve[k]，而vl由后继-边权，更便于更新vl[j]
        for (m = 0; m < g->vexnum; m++) {
            p = g->vertices[m].firstarc;
            for (; p != nullptr; p = p->nextarc) {
                k = p->adjvex;
                if ((ve[m] + p->w) == vl[k])
                    printf("<%d, %d>", m, k);
            }
        }
        //注意，这里搜索的是边，而非顶点
        //否则，下面的代码就足够了
        /*
        for (m = 0; m < g->vexnum; m++)
            if (ve[m] == vl[m])
                printf("%d, ", m);
        */
    }
}
