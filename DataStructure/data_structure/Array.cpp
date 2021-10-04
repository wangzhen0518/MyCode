#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

/**********数组**********/
typedef int ElemType;
typedef struct
{
    ElemType *base; //数组元素基地址
    int dim;        //数组维数
    int *bounds;    //数组维界基址
    int *constants; //数组映象函数常量基址
} Array;

//初始化
bool InitArray(Array *a, int dim, ...)
{
    a->dim = dim;
    a->bounds = (int *)malloc(dim * sizeof(int));
    if (a->bounds == NULL)
        return false;
    int elemtotal = 1;
    va_list ap;
    va_start(ap, dim);
    int i;
    for (i = 0; i < dim; i++)
    {
        a->bounds[i] = va_arg(ap, int);
        elemtotal *= a->bounds[i];
    }
    va_end(ap);
    a->base = (ElemType *)malloc(elemtotal * sizeof(ElemType));
    if (a->base == NULL)
        return false;
    //求映象函数的常数ci，并存入a.constants[i-1]
    a->constants = (int *)malloc(dim * sizeof(int));
    a->constants[dim - 1] = 1;
    if (a->constants == NULL)
        return false;
    for (i = dim - 2; i >= 0; i--)
        a->constants[i] = a->bounds[i + 1] * a->constants[i + 1];
    return true;
}

//映象函数
bool Locate(const Array *a, va_list ap, int *off)
{
    //根据ap指示的各下标值，求出对应元素相对地址off
    *off = 0;
    int i = 0;
    int ind = 0;
    for (i = 0; i < a->dim; i++)
    {
        ind = va_arg(ap, int);
        //用映象函数求和
        *off += a->constants[i] * ind;
    }
}

/**********稀疏矩阵**********/
//三元组表
#define MAXSIZE 12500
typedef struct
{
    int row, col; //非零元的行下标和列下标
    ElemType value;
} Triple;
typedef struct
{
    Triple data[MAXSIZE + 1];
    int mu, nu, tu; //矩阵行数、列数、非零元个数
} TSMatrix;

//链式存储-十字链表
typedef struct Clnode
{
    int row, col;   //行号和列号
    ElemType value; //元素值
    struct CLnode *down, *right;
} OLNode; //非0结点
typedef struct Clnode
{
    int rn; //矩阵行数
    int cn; //矩阵列数
    int tn; //非0元素个数
    OLNode **rhead;
    OLNode **chead;
} CrossList;

//矩阵转置
bool TransMatrix(const TSMatrix *a, TSMatrix *b)
{
    int p, q, col;
    b->mu = a->nu;
    b->nu = a->mu;
    b->tu = a->tu;
    if (b->tu == 0)
    {
        printf("The Matrix a is empty.\n");
        return false;
    }
    else
    {
        q = 0;
        for (col = 1; col <= a->nu; col++)
        {
            for (p = 0; p < a->tu; p++)
                if (a->data[p].col == col)
                {
                    b->data[q].row = a->data[p].col;
                    b->data[q].col = a->data[p].row;
                    b->data[q].value = a->data[p].value;
                    q++;
                }
        }
        return true;
    }
}
bool FastTransMatrix(const TSMatrix *m, TSMatrix *t)
{
    int col;
    int num[MAXSIZE + 1] = {0};
    int cpot[MAXSIZE + 1] = {0};
    t->mu = m->nu;
    t->nu = m->mu;
    t->tu = m->tu;
    if (t->tu == 0)
    {
        printf("The Matrix m is Empty.\n");
        return false;
    }
    else
    {
        for (int n = 0; n < m->tu; n++)
            num[m->data[n].col]++; //统计每列非零元素个数
        cpot[0] = 0;
        //求第col列中第一个非零元在t.data中的序号
        for (col = 1; col <= m->nu; col++)
            cpot[col] = cpot[col - 1] + num[col - 1];
        //转置
        for (int p = 0, q = 0; p < m->tu; p++)
        {
            col = m->data[p].col;
            q = cpot[col];
            t->data[q].col = m->data[p].row;
            t->data[q].row = m->data[p].col;
            t->data[q].value = m->data[p].value;
            cpot[col]++;
        }
    }
}

/**********广义表**********/
typedef struct GLNode
{
    bool tag; //标志域，1：表结点，0：原子结点
    union
    {
        ElemType value; //原子结点的值域
        struct
        {
            struct GLNode *hp, *tp;
        } ptr; //ptr和atom两成员共用
    } Gdata;
} GLNode;