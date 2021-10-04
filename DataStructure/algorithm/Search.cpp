#include <stdlib.h>
#include <stdio.h>

typedef int KeyType;

typedef struct
{
    KeyType key;
} ElemType;

/**********静态查找表**********/
//顺序查找表、有序查找表
typedef struct
{
    ElemType *elem;
    int length;
} SSTable;

//顺序查找
int Search_Seq(SSTable *st, KeyType key)
{
    st->elem[0].key = key; //设置哨兵
    for (int i = st->length; st->elem[i].key != key; i--)
        return i;
}

//折半查找-有序表
int Search_Bin(SSTable *st, KeyType key)
{
    int low = 1;
    int high = st->length;
    int mid = (low + high) / 2;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (st->elem[mid].key == key) //找到目标
            return mid;
        else if (st->elem[mid].key > key) //当前数据比待查数据大，则向左查找
            high = mid - 1;
        else //当前数据比待查数据小，则向右查找
            low = mid + 1;
    }
    return 0; //未搜索到
}

//斐波那契查找-有序查找表
#define MAX 20
int Fabonacci[MAX] = {0, 1, 0};      //存储斐波那契数列
void FaboCreat(int Fabon[], int len) //生成斐波那契数列
{
    int x = Fabon[0];
    for (int i = 2; i < len - 1; i++)
    {
        Fabon[i] = Fabon[i - 1] + x;
        x = Fabon[i - 1];
    }
}
int Search_Fabon(int Fabon[], int len, SSTable *st, KeyType key)
{
    if (st->elem[st->length].key < key || st->elem[0].key > key)
        return -1;
    //假设数据个数为斐波那契数
    //先找到数据个数对应的斐波那契数
    int i = 0;
    for (; i < len; i++)
    {
        if (Fabon[i] == st->length)
            break;
    }
    i--;
    int mid = Fabon[i - 1];
    while (!((st->elem[mid].key < key && st->elem[mid + 1].key > key) ||
             (st->elem[mid].key > key && st->elem[mid - 1].key < key)))
    {
        if (st->elem[mid].key == key)
            return mid;
        else if (st->elem[mid].key > key)
        {
            i--;
            mid = Fabon[i];
        }
        else if (st->elem[mid].key < key)
        {
            i++;
            mid = Fabon[i];
        }
    }
    return -1;
}

//插值查找-数据线性性较好-有序表
int Search_Insert(SSTable *st, KeyType key)
{
    int high = st->length - 1;
    int low = 0;
    int mid = (key - st->elem[low].key) / (st->elem[high].key - st->elem[low].key) * (high - low);
    while (high >= low)
    {
        if (st->elem[mid].key == key)
            return mid;
        else if (st->elem[mid].key > key)
        {
            high = mid - 1;
            mid = (key - st->elem[low].key) / (st->elem[high].key - st->elem[low].key) * (high - low);
        }
        else if (st->elem[mid].key < key)
        {
            low = mid + 1;
            mid = (key - st->elem[low].key) / (st->elem[high].key - st->elem[low].key) * (high - low);
        }
    }
    return -1;
}

//索引表
typedef struct
{
    KeyType maxkey; //块内最大关键字
    int startpos;   //块起始位置
} Index;

//索引查找
int Block_Search(ElemType *st, Index *ind, int n, int b, KeyType key)
{
    //在分块索引表中查找关键字位key的记录，表长n，块数b
    int i = 0;
    int j, k;
    while ((i < b) && (key > ind[i].maxkey))
        i++;
    if (i >= b)
    {
        printf("No Found!\n");
        return 0;
    }
    j = ind[i].startpos;
    while ((j < n) && (st[j].key <= ind[i].maxkey)) //前一个j < n是用于防止在最后一个索引表中查找时，数据溢出
    {
        if (st[j].key == key)
            break;
        j++;
    }
    if ((j >= n) || (st[j].key != key))
    {
        j = 0;
        printf("No Found.\n");
    }
    return j;
}

/**********动态查找表**********/
typedef ElemType TElemType;
//二叉排序树-二叉链表
typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;
//二叉排序树的搜索
bool Search_BiT(BiTree t, KeyType key, BiTNode **p, BiTNode **f)
{
    if (!t) //递归结束条件
    {
        *p = *f;
        return false;
    }
    if (t->data.key == key)
    {
        *p = t;
        return true;
    }
    if (t->data.key > key)
    {
        *f = t;
        return Search_BiT(t->lchild, key, p, f);
    }
    else
    {
        *f = t;
        return Search_BiT(t->rchild, key, p, f);
    }
}

//二叉排序树的插入
bool Insert_BiT(BiTree *t, KeyType e)
{
    BiTNode *p = NULL;
    BiTNode *f = NULL;
    if (Search_BiT(*t, e, &p, &f) == false)
    {
        BiTNode *q = (BiTNode *)malloc(sizeof(BiTNode));
        if (q == NULL)
        {
            printf("Not Enough Space!\n");
            return false;
        }
        q->data.key = e;
        q->lchild = q->rchild = NULL;
        if (p == NULL) //树为空
            *t = q;
        else if (p->data.key > e)
            p->lchild = q;
        else
            p->rchild = q;
        return true;
    }
    else
        return false;
}

//二叉排序树的删除
bool Delete_BiT(BiTree t, KeyType key)
{
    BiTNode *p = NULL;
    BiTNode *f = NULL;
    if (Search_BiT(t, key, &p, &f) == true)
    {
        if ((p->lchild == NULL) && (p->rchild == NULL))
        {
            if (f->lchild == p)
                f->lchild = NULL;
            else
                f->rchild = NULL;
            free(p);
        }
        else if (p->lchild == NULL)
        {
            if (f->lchild == p)
                f->lchild = p->rchild;
            else
                f->rchild = p->rchild;
            free(p);
        }
        else if (p->rchild == NULL)
        {
            if (f->lchild == p)
                f->lchild = p->lchild;
            else
                f->rchild = p->lchild;
            free(p);
        }
        else
        {
            BiTNode *s = p->lchild;
            while (s->rchild != NULL)
                s = s->rchild;
            s->rchild = p->rchild;
            if (f->lchild == p)
                f->lchild = p->lchild;
            else
                f->rchild = p->lchild;
            free(p);
        }
        return true;
    }
    else
        return false;
}

//平衡二叉排序树
//平衡二叉排序树-二叉链表
typedef struct BBSTNode
{
    TElemType data;
    int Bfactor; //平衡因子
    struct BBSTNode *lchild, *rchild, *parent;
} BBSTNode, *BBSTree;

//平衡二叉排序树的搜索
bool Search_BBST(BBSTree t, KeyType key, BBSTNode **p, BBSTNode **f)
{
    if (!t) //递归结束条件
    {
        *p = *f;
        return false;
    }
    if (t->data.key == key)
    {
        *p = t;
        return true;
    }
    if (t->data.key > key)
    {
        *f = t;
        return Search_BBST(t->lchild, key, p, f);
    }
    else
    {
        *f = t;
        return Search_BBST(t->rchild, key, p, f);
    }
}

//平衡二叉排序树的插入
BBSTNode *Insert_BBST(BBSTree *t, KeyType e)
{
    BBSTNode *p = NULL;
    BBSTNode *f = NULL;
    if (Search_BBST(*t, e, &p, &f) == false)
    {
        BBSTNode *q = (BBSTNode *)malloc(sizeof(BiTNode));
        if (q == NULL)
        {
            printf("Not Enough Space!\n");
            return false;
        }
        q->data.key = e;
        q->lchild = q->rchild = NULL;
        q->parent = p;
        p->Bfactor = 0;
        if (p == NULL) //树为空
            *t = q;
        else if (p->data.key > e)
            p->lchild = q;
        else
            p->rchild = q;
        f = q;

        //处理平衡因子
        while (p != *t)
        {
            if (q == p->lchild)
                p->Bfactor++;
            else
                p->Bfactor--;
            q = p;
            p = p->parent;
        }
        //处理根的平衡因子
        if (q == p->lchild)
            p->Bfactor++;
        else
            p->Bfactor--;
        return f;
    }
    else
        return NULL;
}

//构造平衡二叉排序树
void Balance(BBSTNode *q, BBSTree r) //插入新结点后，对树进行平衡
{
    while (q != r)
    {
        //找出不平衡的结点
        while (q->Bfactor != 2 && q->Bfactor != -2)
            q = q->parent;
        //根据不同不平衡类型，进行平衡处理
        //LL型
        if (q->Bfactor == 2 && q->lchild->Bfactor == 1)
        {
            BBSTNode *t = q->lchild;
            if (q == q->parent->lchild)
            {
                q->parent->lchild = t;
                t->parent = q->parent;
            }
            else
            {
                q->parent->rchild = t;
                t->parent = q->parent;
            }
            //处理孩子
            q->lchild = t->rchild;
            t->rchild = q;
            //处理双亲
            q->parent = t;
            q->lchild->parent = q;
            //处理平衡因子
            q->Bfactor = t->Bfactor = 0;
            q = t;
        }
        //LR型
        else if (q->Bfactor == 2 && q->lchild->Bfactor == -1)
        {
            BBSTNode *t = q->lchild;
            if (q == q->parent->lchild)
            {
                q->parent->lchild = t->rchild;
                t->rchild->parent = q->parent;
            }
            else
            {
                q->parent->rchild = t->rchild;
                t->rchild->parent = q->parent;
            }
            //处理孩子
            q->lchild = t->rchild->rchild;
            t->rchild->rchild = q;
            q = t->rchild;
            t->rchild = q->lchild;
            q->lchild = t;
            //处理双亲
            q->lchild->rchild->parent = q->lchild;
            q->rchild->lchild->parent = q->rchild;
            q->lchild->parent = q;
            q->rchild->parent = q;
            //处理平衡因子
            if (q->Bfactor == 1)
            {
                q->lchild->Bfactor = 0;
                q->rchild->Bfactor = -1;
            }
            else if (q->Bfactor == -1)
            {
                q->lchild->Bfactor = 1;
                q->rchild->Bfactor = 0;
            }
            else
            {
                q->lchild->Bfactor = 0;
                q->rchild->Bfactor = 0;
            }
            q->Bfactor = 0;
        }
        //RL型
        else if (q->Bfactor == -2 && q->rchild->Bfactor == 1)
        {
            BBSTNode *t = q->rchild;
            if (q == q->parent->lchild)
            {
                q->parent->lchild = t->lchild;
                t->lchild->parent = q->parent;
            }
            else
            {
                q->parent->rchild = t->lchild;
                t->lchild->parent = q->parent;
            }
            //处理孩子
            q->rchild = t->lchild->lchild;
            t->lchild->lchild = q;
            q = t->lchild;
            t->lchild = q->rchild;
            q->rchild = t;
            //处理双亲
            q->lchild->rchild->parent = q->lchild;
            q->rchild->lchild->parent = q->rchild;
            q->lchild->parent = q;
            q->rchild->parent = q;
            //处理平衡因子
            if (q->Bfactor == 1)
            {
                q->lchild->Bfactor = 0;
                q->rchild->Bfactor = -1;
            }
            else if (q->Bfactor == -1)
            {
                q->lchild->Bfactor = 1;
                q->rchild->Bfactor = 0;
            }
            else
            {
                q->lchild->Bfactor = 0;
                q->rchild->Bfactor = 0;
            }
            q->Bfactor = 0;
        }
        //RR型
        else if (q->Bfactor == 2 && q->rchild->Bfactor == -1)
        {
            BBSTNode *t = q->lchild;
            if (q == q->parent->lchild)
            {
                q->parent->lchild = t;
                t->parent = q->parent;
            }
            else
            {
                q->parent->rchild = t;
                t->parent = q->parent;
            }
            //处理孩子
            q->rchild = t->lchild;
            t->lchild = q;
            //处理双亲
            q->parent = t;
            q->rchild->parent = q;
            //处理平衡因子
            q->Bfactor = t->Bfactor = 0;
            q = t;
        }
    }
}
bool Creat_BBSTree(BBSTree t, KeyType key[], int len)
{
    BBSTNode *q;
    for (int i = 0; i < len; i++)
    {
        if ((q = Insert_BBST(&t, key[i])) == NULL)
            return false;
        Balance(q, t);
    }
    return true;
}

//B-树
#define M 5 //B-树阶数
typedef struct B_TNode
{
    int keynum;             //关键字个数
    KeyType key[M];         //关键字列表, key[0]不使用
    struct B_TNode *ptr[M]; //指向子树
    TElemType *recptr[M];   //关键字对应的位置，recptr[0]不使用
} B_TNode, *B_Tree;

//B-树查找
int SearchB_T(B_Tree t, KeyType key, B_TNode *&p)
{
    //在B-树中查找关键字key, 查找成功返回在结点中的位置
    //及结点指针p；否则返回0及最后一个结点指针
    B_TNode *q;
    int n;
    p = q = t;
    while (q != NULL)
    {
        p = q;
        q->key[0] = key;
        for (n = q->keynum; key <= q->key[n]; n--)
            if (n > 0 && q->key[n] == key)
                return n;
        q = q->ptr[n];
    }
    return 0;
}

//B-树插入
bool InsertB_T(B_Tree *t, KeyType key, B_TNode *q, int i)
{
    //在M阶B-树t的结点q的key[i]与key[i+1]之间插入关键字key
    //若引起结点过大，则眼双亲链进行必要的结点分裂调整，使t仍是M阶B-树

    //以下是书上的伪代码，有许多前面未定义的函数，我实在是不晓得怎么补全了
    /*
    x = key;
    ap = NULL;
    finished = false;
    while (q && !finished)
    {
        Insert(q, i, x, ap);    //将x和ap分别插入到q->key[i+1]和q->ptr[i+1]
        if (q->keynum < M ) finished =true;
        else
        {
            s=supint(M/2);  //对M取上整
            split( q, ap);
            x = q->key[s];
            //将q->key[s+1..m], q->ptr[s..m]和q->recptr[s+1..m]移入新结点*ap
            q = q->parent;
            if(q)
                i = Search(q, x);   //在双亲结点*q中查找x的插入位置
        }
    }
    if(!finished)   //t是空树 (参数q初值为NULL) 或者根节点已分裂为结点*q和*qp
        NewRoot(t, q, x, ap);   //生成含信息(t, x, ap)的新的根节点*t, 原t和ap为子树指针
    */
}

//B+树
typedef enum
{
    branch,
    leaf
} NodeType;
typedef struct BPNode
{
    NodeType tag;          //结点标志
    int keynum;            //结点中关键字的个数
    struct BPNode *parent; //指向父结点的指针
    KeyType key[M + 1];    //关键字数组，key[0]未用
    union pointer
    {
        struct BPNode *ptr[M + 1]; //子树指针向量
        TElemType *recptr[M + 1];  //recptr[0]未用
    } ptrType;                     //用联合体定义子树指针和记录指针
} BPNode, *BPTree;

//B+树查找
int SearchBPT(BPTree t, KeyType key, BPNode *p)
{
    //在B+树中查找关键字key, 查找成功返回在结点中的位置
    //及结点指针p；否则返回0及最后一个结点指针
    BPNode *q;
    int n;
    p = q = t;
    while (q != NULL)
    {
        p = q;
        q->key[0] = key;
        for (n = q->keynum; key < q->key[n]; n--)
            ;
        if (q->tag == branch)
            q = q->ptrType.ptr[n];
        else if (n > 0 && q->tag == leaf && q->key[n] == key)
            return n;
    }
    return 0;
}

//哈希表-基于拉链法处理冲突的实现
typedef struct node
{
    KeyType key;
    struct node *link;
} HNode;

//哈希函数
int h(KeyType key)
{
    /*code*/
}

//哈希查找
HNode *Search_Hash(HNode *t[], KeyType key)
{
    HNode *p;
    int i;
    i = h(key);
    if (t[i] == NULL)
        return NULL;
    p = t[i];
    while (p != NULL)
    {
        if (p->key == key)
            return p;
        else
            p = p->link;
    }
    return NULL;
}