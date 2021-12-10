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

void Create(ALGraph &g)
{
    using std::cin;
    using std::cout;
    using std::endl;

    VexType data; //顶点数据信息

    cout << "请输入顶点个数：" << endl;
    cin >> g.vexnum;
    cout << "请输入弧个数：" << endl;
    cin >> g.arcnum;

    //处理顶点信息
    cout << endl;
    for (int i = 0; i < g.vexnum; i++)
    {
        g.vertices[i].id = i;
        g.vertices[i].firstarc = nullptr;
        cout << "请输入第" << i << "个顶点的数据：";
        cin >> g.vertices[i].data;
    }
    cout << endl;

    //处理边信息
    cout << endl;
    for (int i = 0; i < g.arcnum;i++)
    {
        int m, n;
        cout<<"请输入第"<<i<<"条弧的两个顶点：";
        cin >> m >> n;
        ArcNode *temp = new ArcNode;
        if(temp==nullptr)
        {
            cout << "内存不够！";
            exit(-1);
        }
        temp->adjvex=n;
        temp->info = nullptr;
        temp->nextarc = g.vertices[i].firstarc;
        g.vertices[i].firstarc = temp;
    }
}