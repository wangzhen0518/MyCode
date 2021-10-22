#include <stdio.h>
#include <stdlib.h>

#define ElemType int
#define LIST_INIT_SIZE 100  //线性表存储空间初始分配量
#define LIST_INCREMENT 10   //存储空间分配增量

//线性表定长顺序存储
typedef struct SqList {
    ElemType* elem;  //存储元素
    int length;      //当前元素个数
    int listsize;    //当前顺序表占用空间大小
} SqList;

//线性表链式存储，即链表
typedef struct Lnode {
    ElemType* elem;
    struct Lnode* next;
} Lnode, *LinkList;

// ADT
//初始化
void InitList_sq(SqList* L) {
    L->elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (L->elem == NULL) exit(-1);
    L->length = 0;
    L->listsize = LIST_INIT_SIZE;
}

//查找
int LocateElem(const SqList* L, ElemType x) {
    int i = 0;
    while (i < L->length) {
        if (L->elem[i] == x)
            return i;
        else
            i++;
    }
    return -1;
}

//求表长
int ListLength(const SqList* L) {
    return L->length;
}

//在表中提取第i个元素的值
void GetElem(const SqList* L, ElemType* e, int i) {
    if (i < 1 || i > L->length) {
        printf("参数范围错误！\n");
        exit(-1);
    } else
        *e = L->elem[i - 1];
}

//插入元素
void ListInsert_Sq(SqList* L, int i, ElemType e) {
    if (i < 1 || i > L->length) {
        printf("参数范围错误！\n");
        exit(-1);
    } else if (L->length == L->listsize) {
        ElemType* q = (ElemType*)realloc(
            L->elem, sizeof(ElemType) * (L->listsize + LIST_INCREMENT));
        if (q == NULL) {
            printf("内存不够！\n");
            exit(-1);
        } else {
            L->elem = q;
            L->listsize += LIST_INCREMENT;
        }
    }
    for (int k = L->length - 1; k >= i - 1; k--)
        L->elem[k + 1] = L->elem[k];
    L->elem[i - 1] = e;
    L->length++;
}

//删除元素
void ListDelete_Sq(SqList* L, int i, ElemType* e) {
    if (i < 1 || i > L->length) {
        printf("参数范围错误！\n");
        exit(-1);
    }
    *e = L->elem[i - 1];
    for (int k = i - 1; k < L->length - 1; k++)
        L->elem[k] = L->elem[k + 1];
    L->length--;
}

//集合相加
void Union(SqList* La, const SqList* Lb) {
    int n = ListLength(La);
    int m = ListLength(Lb);
    ElemType e;
    for (int i = 1; i <= m; i++) {
        GetElem(Lb, &e, i);
        if (LocateElem(La, e) == -1) ListInsert_Sq(La, i, e);
    }
}

//集合相减
void Intersection(SqList* La, const SqList* Lb) {
    int n = ListLength(La);
    int m = ListLength(Lb);
    ElemType e;
    int k;
    for (int i = 1; i <= m; i++) {
        GetElem(Lb, &e, i);
        if ((k = LocateElem(La, e)) != -1) ListDelete_Sq(La, k, &e);
    }
}

//集合的归并
void MergeList_Sq(const SqList* La, const SqList* Lb, SqList* Lc) {
    int n = ListLength(La);
    int m = ListLength(Lb);
    int i = 1, j = 1, k = 1;
    ElemType a;
    ElemType b;
    InitList_sq(Lc);
    while (i <= n && j <= m) {
        GetElem(La, &a, i);
        GetElem(Lb, &b, j);
        if (a < b) {
            ListInsert_Sq(Lc, k, a);
            i++;
        } else if (a == b) {
            ListInsert_Sq(Lc, k, a);
            i++;
            j++;
        } else {
            ListInsert_Sq(Lc, k, b);
            j++;
        }
        k++;
    }
    if (i == n + 1)  // La全部存入Lc
    {
        for (; j <= m; j++, k++) {
            GetElem(Lb, &b, j);
            ListInsert_Sq(Lc, k, b);
        }
    } else  // Lb全部存入Lc
    {
        for (; i <= n; i++, k++) {
            GetElem(Lb, &a, i);
            ListInsert_Sq(Lc, k, a);
        }
    }
}