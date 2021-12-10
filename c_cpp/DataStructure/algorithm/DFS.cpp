#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 20

//邻接表
typedef struct ArcNode {
    int adjvex;               //该弧所指向的顶点的位置
    struct ArcNode* nextarc;  //指向下一条弧的位置
    int w;                    //弧的权
} ArcNode;
typedef struct VexNode {
    int id;
    int degree;         //顶点的(出度)度
    int w;              //顶点的权
    ArcNode* firstarc;  //指向第一条依附于该顶点的弧
} VexNode, AdjList[MAX_VERTEX_NUM];
typedef struct {
    AdjList vertices;
    int vexnum, arcnum;  //顶点数和边数
    bool directional;    // t：有向图，f：无向图
    bool weighted;       // t：带权图，f：等权图
} ALGraph;

/*****栈的定义*****/
//顺序栈
#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 10
typedef VexNode* SqElemType;
typedef struct SqStack {
    SqElemType* base;  //栈底
    SqElemType* top;   //栈顶
    int stacksize;     //当前已分配空间
} SqStack;

//初始化栈
void Initial(SqStack* s, int len) {
    s->base = (SqElemType*)malloc(sizeof(SqElemType) * len);
    if (!s->base) {
        printf("内存不够！\n");
        exit(-1);
    }
    s->top = s->base;
    s->stacksize = len;
}

//判断栈是否为空
int isEmpty(SqStack* s) {
    if (s->top == s->base)
        return 1;
    else
        return 0;
}

//插入新元素
void Insert(SqStack* s, SqElemType e) {
    if (s->top - s->base >= s->stacksize) {
        SqElemType* q;
        q = (SqElemType*)realloc(
            s->base, sizeof(SqElemType) * (s->stacksize + STACK_INCREMENT));
        if (!q) {
            printf("内存不够！\n");
            exit(-1);
        }
        s->top = s->base + s->stacksize;
        s->stacksize += STACK_INCREMENT;
    }
    *(s->top) = e;
    s->top++;
}

//删除元素
void Remove(SqStack* s, SqElemType* e) {
    if (isEmpty(s) == 0) {
        *e = *(s->top - 1);
        s->top--;
    } else {
        printf("栈为空！\n");
        return;
    }
}

// BFS
typedef struct {
    VexNode* vexs[MAX_VERTEX_NUM];
    int len;
} Path;

Path SearchOnGraph_BFS(ALGraph* G, int id1, int id2,
                       int (*Goal)(VexNode* v, int id)) {
    VexNode* s;
    //初始化访问数组
    int visit[MAX_VERTEX_NUM] = {0};

    //初始化路径
    Path path;  // path中的每个成员指向图中的一个顶点
    for (int i = 0; i < MAX_VERTEX_NUM; i++)
        path.vexs[i] = NULL;
    path.vexs[0] = &G->vertices[id1];
    path.len = 1;
    int lastvex
        [MAX_VERTEX_NUM];  // lastvexs记录每一个顶点的上一个顶点在path.vexs中的下标
    for (int i = 0; i < MAX_VERTEX_NUM; i++)
        lastvex[i] = -1;

    //初始化fringe
    SqStack fringe;
    Initial(&fringe, MAX_VERTEX_NUM);
    if ((*Goal)(&G->vertices[id1], id2) == 1)  // G->vertices[0]就是目标顶点
        return path;
    Insert(&fringe, &G->vertices[id1]);
    visit[id1] = 1;

    int i = 0;
    while (!isEmpty(&fringe)) {
        Remove(&fringe, &s);
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
                    while (k < MAX_VERTEX_NUM)
                        path.vexs[k++] = NULL;
                    return path;
                } else
                    Insert(&fringe, &G->vertices[w->adjvex]);
            }
        }
    }
    printf("No Goal!\n");
    exit(-1);  //未找到目标
}
