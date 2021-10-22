#include "D:\WorkSpace\Visual Studio Code\review\Types\Stack_Queue.cpp"

//数值转换-10转k
void conversion(int N, int k) {
    SqStack* s;
    Initial(s, STACK_INIT_SIZE);  //初始化一个栈
    while (N != 0) {
        Insert(s, N % k);
        N = N / k;
    }
    SqElemType e;
    while (isEmpty(s) != 0) {
        Remove(s, &e);
        printf("%d", e);
    }
}

//行编辑器
void LineEdit() {
    SqStack* s;
    Initial(s, STACK_INIT_SIZE);  //初始化一个栈
    char ch = getchar();
    while (ch != EOF) {
        while (ch != EOF && ch != '\n') {
            switch (ch) {
                case '#':
                    Remove(s, (SqElemType*)(&ch));
                    break;
                case '@':
                    ClearStack(s);
                    break;
                default:
                    Insert(s, (SqElemType)ch);
                    break;
            }
            ch = getchar();
        }
        ClearStack(s);
        if (ch != EOF) ch = getchar();
    }
    DestroyStack(s);
}

//表达式求值
enum COMPARE { LOW, EQUAL, HIGH };
//比较算符优先级
COMPARE Precede(char a, char b) {
    switch (a) {
        case '+':
            switch (b) {
                case '+':
                    return HIGH;
                case '-':
                    return HIGH;
                case '*':
                    return LOW;
                case '/':
                    return LOW;
                case '(':
                    return LOW;
                case ')':
                    return HIGH;
                case '#':
                    return HIGH;
            }
        case '-':
            switch (b) {
                case '+':
                    return HIGH;
                case '-':
                    return HIGH;
                case '*':
                    return LOW;
                case '/':
                    return LOW;
                case '(':
                    return LOW;
                case ')':
                    return HIGH;
                case '#':
                    return HIGH;
            }
        case '*':
            switch (b) {
                case '+':
                    return HIGH;
                case '-':
                    return HIGH;
                case '*':
                    return HIGH;
                case '/':
                    return HIGH;
                case '(':
                    return LOW;
                case ')':
                    return HIGH;
                case '#':
                    return HIGH;
            }
        case '/':
            switch (b) {
                case '+':
                    return HIGH;
                case '-':
                    return HIGH;
                case '*':
                    return HIGH;
                case '/':
                    return HIGH;
                case '(':
                    return LOW;
                case ')':
                    return HIGH;
                case '#':
                    return HIGH;
            }
        case '(':
            switch (b) {
                case '+':
                    return LOW;
                case '-':
                    return LOW;
                case '*':
                    return LOW;
                case '/':
                    return LOW;
                case '(':
                    return LOW;
                case ')':
                    return EQUAL;
                case '#':
                    return LOW;
            }
        case ')':  //似乎用不上？
            switch (b) {
                case '+':
                    return HIGH;
                case '-':
                    return HIGH;
                case '*':
                    return HIGH;
                case '/':
                    return HIGH;
                case '(':
                    return HIGH;
                case ')':
                    return HIGH;
                case '#':
                    return HIGH;
            }
        case '#':
            switch (b) {
                case '+':
                    return LOW;
                case '-':
                    return LOW;
                case '*':
                    return LOW;
                case '/':
                    return LOW;
                case '(':
                    return LOW;
                case ')':
                    return LOW;
                case '#':
                    return EQUAL;
            }
    }
}
//运算
SqElemType Operate(SqElemType a, SqElemType theta, SqElemType b) {
    switch (theta) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        default:
            break;
    }
}
//处理表达式
int EvaluateExpression() {
    //算术表达式求值的算符优先算法。
    //设OPTR和OPND分别为运算符栈和运算数栈，OP为运算符集合
    SqStack* OPTR;
    SqStack* OPND;
    Initial(OPTR, STACK_INIT_SIZE);
    Insert(OPTR, (SqElemType)'#');
    Initial(OPND, STACK_INIT_SIZE);
    char ch = getchar();
    SqElemType e;
    SqElemType a;
    SqElemType b;
    SqElemType theta;
    GetTop(OPTR, &e);
    while (ch != '#' || e != '#') {
        //不是运算符则入栈
        if (ch != '(' && ch != ')' && ch != '+' && ch != '-' && ch != '*' &&
            ch != '/' && ch != '#') {
            Insert(OPND, (SqElemType)ch);
            ch = getchar();
        } else {
            switch (Precede(e, ch)) {
                case LOW:  //栈顶元素优先级低
                    Insert(OPTR, (SqElemType)ch);
                    ch = getchar();
                    GetTop(OPTR, &e);
                    break;
                case EQUAL:  //脱括号并接收下一字符
                    Remove(OPTR, &e);
                    ch = getchar();
                    GetTop(OPTR, &e);
                    break;
                case HIGH:  //出栈并将运算结果入栈
                    Remove(OPTR, &theta);
                    Remove(OPND, &b);
                    Remove(OPND, &a);
                    Insert(OPND, Operate(a, theta, b));
                    GetTop(OPTR, &e);
                    break;
            }
        }
    }
    SqElemType x;
    GetTop(OPND, &x);
    return x;
}
