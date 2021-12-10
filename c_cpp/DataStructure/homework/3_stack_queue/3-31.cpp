//判断一个字符串是不是回文
#include <iostream>
#include <cstring>
#include <stack>

using std::stack;

bool Judge(const char *str)
{
    int len = strlen(str);
    int half = len / 2;

    stack<char> temp;
    //将str的前半部分入栈，再与后半部分比较
    int i = 0;
    for (; i < half; i++)
        temp.push(str[i]);
    if (len % 2 == 1) //串长为奇，i后移一位
        i = i + 1;
    for (; i < len; i++)
        if (temp.top() != str[i])
            return false;
        else
            temp.pop();
    return true;
}

int main()
{
    using std::cout;
    char str[] = "abdcdba";
    cout << Judge(str);
    return 0;
}