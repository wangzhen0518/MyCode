#include "D:\WorkSpace\Visual Studio Code\review\Types\String.cpp"
#include <string.h>

/**********串的模式匹配算法**********/
//暴力匹配
int IndexString(const StringType *s, const StringType *t)
{
    int k = 0, j = 0; //k: 主串, j: 子串
    while ((k < s->length) && (j < t->length))
    {
        if (s->str[k] == t->str[j])
        {
            k++;
            j++;
        }
        else
        {
            k = k - j + 1;
            j = 0;
        }
    }
    if (j == t->length)
        return k - j;
    else
        return -1;
}

//KMP算法
int next[MAX_STRLEN] = {-1};
//穷举法
int next1(const StringType *t, int j)
{
    //借助改进的基本操作subString(), 返回值改用return
    //char *subString(s,startpos,len)
    //求next[]数组， 需要对不同的j， 调用next1(j)
    if (j <= 0 || j >= t->length)
    {
        printf("Wrong input.\n");
        return -1;
    }
    StringType str1, str2;
    int k = j;
    do
    {
        k--;
        SubString(t, 0, k, &str1);
        SubString(t, j - k, k, &str2);
        while (k && strncmp(str1.str, str2.str, k))
        {
            if (k == 0)
                return 0;
            else
                return k;
        }
    } while (k >= 0);
}
//改进穷举法
int next2(const StringType *t, int j)
{
    if (j <= 0 || j >= t->length)
    {
        printf("Wrong input.\n");
        return -1;
    }
    int k = j - 2;
    for (; k >= 0; k--)
    {
        //即先找到和t[j-1]相同的字符，再比较子串是否相同
        if (t->str[k] == t->str[j - 1])
            if (strncmp(t->str, &t->str[j - k - 1], k + 1) == 0)
                return k + 1;
    }
    return 0;
}
//伪递归算法
void next3(const StringType *t, int next[])
{
    int k, j = 2;
    next[0] = -1;
    next[1] = 0;
    while (j < t->length)
    {
        k = next[j - 1];
        while (k > 0 && t->str[k] != t->str[j - 1])
            k = next[k];
        if (k <= 0)
        {
            if (t->str[0] == t->str[j - 1])
                next[j] = 1;
            else
                next[j] = 0;
        }
        else
            next[j] = k + 1;
        j++;
    }
}
int KMP_Index(const StringType *s, const StringType *t)
{
    //s、t分别是主串和模式串
    int i = 0, j = 0;
    while ((i < s->length) && (j < t->length))
    {
        if ((j == -1) || (s->str[i] == t->str[j]))
        {
            i++;
            j++;
        }
        else
            j = next[j];
    }
    if (j == t->length)
        return i - j;
    else
        return -1;
}

