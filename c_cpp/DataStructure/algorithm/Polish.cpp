#include <cstring>
#include <iostream>
#include <stack>

const int DELTA = 48;  // ASC||码和数字大小的偏移

using std::cout;
using std::endl;
using std::stack;

//中序表达式转逆波兰式
stack<char> NiPolish(char* str) {
    stack<char> out;
    stack<char> temp;

    int i = 0;
    char c = str[i];
    while (c != '\0') {
        switch (c) {
            case '*':
            case '/':
                while (!temp.empty() &&
                       (temp.top() == '*' || temp.top() == '/')) {
                    out.push(temp.top());
                    temp.pop();
                }
                temp.push(c);
                break;
            case '+':
            case '-':
                while (!temp.empty() && temp.top() != '(') {
                    out.push(temp.top());
                    temp.pop();
                }
                temp.push(c);
                break;
            case '(':
                temp.push(c);
                break;
            case ')':
                while (!temp.empty() && temp.top() != '(') {
                    out.push(temp.top());
                    temp.pop();
                }
                temp.pop();
                break;
            default:
                out.push(c);
                break;
        }
        c = str[++i];
    }
    while (!temp.empty()) {
        out.push(temp.top());
        temp.pop();
    }

    //将Out倒序入栈，以便后续运算
    while (!out.empty()) {
        temp.push(out.top());
        out.pop();
    }
    cout << std::endl;
    return temp;
}

//中序表达式转波兰式
stack<char> Polish(char* str) {
    stack<char> out;
    stack<char> temp;

    int i = strlen(str) - 1;
    char c = str[i];
    while (i >= 0) {
        switch (c) {
            case '*':
            case '/':
                while (!temp.empty() &&
                       (temp.top() == '*' || temp.top() == '/')) {
                    out.push(temp.top());
                    temp.pop();
                }
                temp.push(c);
                break;
            case '+':
            case '-':
                while (!temp.empty() && temp.top() != ')') {
                    out.push(temp.top());
                    temp.pop();
                }
                temp.push(c);
                break;
            case ')':
                temp.push(c);
                break;
            case '(':
                while (!temp.empty() && temp.top() != ')') {
                    out.push(temp.top());
                    temp.pop();
                }
                temp.pop();
                break;
            default:
                out.push(c);
                break;
        }
        c = str[--i];
    }
    while (!temp.empty()) {
        out.push(temp.top());
        temp.pop();
    }

    //将Out倒序入栈，以便后续运算
    while (!out.empty()) {
        temp.push(out.top());
        out.pop();
    }
    return temp;
}

//计算逆波兰式结果
int CalculateNiPolish(stack<char> s) {
    stack<int> count;
    char c;
    int temp1 = 0;
    int temp2 = 0;
    while (!s.empty()) {
        c = s.top();
        s.pop();
        switch (c) {
            //运算
            case '*':
            case '/':
            case '+':
            case '-':
                if (!count.empty()) {
                    temp1 = count.top();
                    count.pop();
                    temp2 = count.top();
                    count.pop();
                    switch (c) {
                        case '*':
                            temp1 = temp2 * temp1;
                            break;
                        case '/':
                            temp1 = temp2 / temp1;
                            break;
                        case '+':
                            temp1 = temp2 + temp1;
                            break;
                        case '-':
                            temp1 = temp2 - temp1;
                            break;
                    }
                    count.push(temp1);
                }
                break;
            //数字入栈
            default:
                count.push(int(c) - DELTA);
                break;
        }
    }
    return count.top();
}

//计算波兰式结果
int CalculatePolish(stack<char> s) {
    int temp1 = 0;
    int temp2 = 0;
    stack<int> count;
    char c;

    while (!s.empty()) {
        c = s.top();
        s.pop();
        switch (c) {
            //运算
            case '*':
            case '/':
            case '+':
            case '-':
                if (!count.empty()) {
                    temp1 = count.top();
                    count.pop();
                    temp2 = count.top();
                    count.pop();
                    switch (c) {
                        case '*':
                            temp1 = temp2 * temp1;
                            break;
                        case '/':
                            temp1 = temp2 / temp1;
                            break;
                        case '+':
                            temp1 = temp2 + temp1;
                            break;
                        case '-':
                            temp1 = temp2 - temp1;
                            break;
                    }
                    count.push(temp1);
                }
                break;
            //数字入栈
            default:
                count.push(int(c) - DELTA);
                break;
        }
    }
    return count.top();
}

int main() {
    char str[] = "1+2*(4-3)+6/2";
    // cout << "逆波兰式运算：" << CalculateNiPolish(NiPolish(str)) << endl;
    cout << "波兰式运算：" << CalculatePolish(NiPolish(str)) << endl;
    Polish(str);
}