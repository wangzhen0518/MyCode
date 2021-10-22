#include <stdio.h>
#include <stdlib.h>
/********************队列********************/
/*****队列定义*****/
typedef int QElemType;
//循环队列
typedef struct {
    QElemType* base;
    int front;
    int rear;
    int size;
} SqQueue;

//链队列
typedef struct Qnode {
    QElemType data;
    struct Qnode* next;
} Qnode, *QueuePtr;
typedef struct {
    QueuePtr rear, front;
} LinkQueue;

/*****队列ADT*****/
//初始化队列
void Initial(SqQueue* Q, int len) {
    if (len <= 0) {
        printf("Wrong Input.\n");
        exit(-1);
    }
    Q->size = len;
    Q->base = (QElemType*)malloc(sizeof(QElemType) * len);
    if (!Q->base) {
        printf("Not Enough Space.\n");
        exit(-1);
    }
    Q->front = Q->rear = 0;
}

//插入新元素
void Insert(SqQueue* Q, QElemType v) {
    if ((Q->rear + 1) % Q->size == Q->front) {
        printf("The queue is full.\n");
        exit(-1);
    }
    Q->base[Q->rear] = v;
    Q->rear = (Q->rear + 1) % Q->size;
}

//移出元素
void Remove(SqQueue* Q, QElemType* v) {
    if (Q->front == Q->rear) {
        printf("The queue is empty.\n");
        exit(-1);
    }
    *v = Q->base[Q->front];
    Q->front = (Q->front + 1) % Q->size;
}

//判断队列是否为空
int isEmpty(const SqQueue* Q) {
    if (Q->rear == Q->front)
        return 1;
    else
        return 0;
}

/********************栈********************/
/*****栈的定义*****/
//顺序栈
#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 10
//二叉链表
typedef struct BiTnode {
    TElemType data;
    struct BiTnode *lchild, *rchild;
} BiTNode, *BiTree;

typedef BiTNode* SqElemType;
typedef struct SqStack {
    SqElemType* base;  //栈底
    SqElemType* top;   //栈顶
    int stacksize;     //当前已分配空间
} SqStack;

//链栈
typedef int StackData;
typedef struct node {
    StackData data;     //结点
    struct node* link;  //链指针
} StackNode;
typedef struct {
    StackNode* top;  //栈顶指针
} LinkStack;

/*****栈ADT*****/
//初始化栈
void Initial(SqStack* s, int len) {
    if (len <= 0) {
        printf("Wrong Input.\n");
        exit(-1);
    }
    s->base = (SqElemType*)malloc(sizeof(SqElemType) * len);
    if (!s->base) {
        printf("内存不够！\n");
        exit(-1);
    }
    s->top = s->base;
    s->stacksize = len;
}
void Initial(LinkStack* s) {
    s->top = NULL;
}

//判断栈是否为空
bool isEmpty(const SqStack* s) {
    if (s->top == s->base)
        return true;
    else
        return false;
}
bool isEmpty(const LinkStack* s) {
    return s->top == NULL;
}

//取栈顶元素
void GetTop(const SqStack* s, SqElemType* e) {
    if (s->top == s->base) {
        printf("栈空!\n");
        return;
    }
    *e = *(s->top - 1);
}
void GetTop(const LinkStack* s, StackData* e) {
    if (isEmpty(s)) {
        printf("栈空!\n");
        return;
    } else
        *e = s->top->data;
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
    (s->top)++;
}
void Insert(LinkStack* s, StackData e) {
    StackNode* p = (StackNode*)malloc(sizeof(StackData));
    if (p == NULL) {
        printf("内存不够!\n");
        return;
    } else {
        p->data = e;
        p->link = s->top;
        s->top = p;
    }
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
void Remove(LinkStack* s, StackData* e) {
    if (isEmpty(s)) {
        printf("栈空!\n");
        return;
    } else {
        StackNode* p = s->top;
        *e = p->data;
        s->top = p->link;
        free(p);
    }
}

//清空栈
void ClearStack(SqStack* s) {
    s->top = s->base;
}

//销毁栈
void DestroyStack(SqStack* s) {
    free(s->base);
    s->stacksize = 0;
}
