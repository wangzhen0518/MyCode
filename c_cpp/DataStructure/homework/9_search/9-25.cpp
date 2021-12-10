#include <iostream>

typedef int KeyType;

typedef struct
{
    KeyType key;
} ElemType;

//顺序查找表、有序查找表
typedef struct
{
    ElemType *elem;
    int length;
} SSTable;

//哨兵放在高位
int Search(SSTable *s, KeyType key)
{
    s->elem[s->length].key = key;
    for (int n = 0; n <= s->length; n++)
        if (s->elem[n].key == key)
            return n;
}