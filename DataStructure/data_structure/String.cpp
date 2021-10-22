#include <stdio.h>
#include <stdlib.h>

//定长顺序存储
#define MAX_STRLEN 256
typedef struct {
    char str[MAX_STRLEN];
    int length;
} StringType;

//串的堆分配存储方式
typedef struct {
    char* ch;
    int length;
} HString;

//串的块链存储方式的实现
#define BLOCK_SIZE 4
typedef struct Blstrtype {
    char data[BLOCK_SIZE];
    struct Blstrtype* next;
} BNODE;  //块结点
typedef struct {
    BNODE* head;
    int strlen;
} Blstring;  //块链串

//连接串
void StrConcat(StringType* s, const StringType* t) {
    int i;
    if ((s->length + t->length) > MAX_STRLEN) {
        printf("长度溢出!\n");
        return;
    }
    for (i = 0; i < t->length; i++)
        s->str[s->length + i] = t->str[i];
    s->length += t->length;
}
void StrConcat(HString* t, const HString* s1, const HString* s2) {
    if (t->ch != NULL) free(t->ch);
    t->length = s1->length + s2->length;
    t->ch = (char*)malloc(sizeof(char) * t->length);
    if (t->ch == NULL) {
        printf("内存不够!\n");
        t->length = 0;
        return;
    }
    int i = 0;
    for (; i < s1->length; i++)
        t->ch[i] = s1->ch[i];
    for (int k = 0; k < s2->length; i++, k++)
        t->ch[i] = s2->ch[k];
}

//求主串给定起点和长度的子串
void SubString(const StringType* s, int pos, int len, StringType* sub) {
    int k, j;
    if (pos < 0 || pos > s->length) {
        printf("范围错误!\n");
        return;
    }
    sub->length = len;
    for (j = 0, k = pos; j < len; j++, k++)
        sub->str[j] = s->str[k];
}
