#include "wrap.h"

int cal(int a, int b, char op)
{
    switch(op)
    {
    case '+':
        return a+b;
        break;
    case '-':
        return a-b;
        break;
    case '*':
        return a*b;
        break;
    case '/':
        return a/b;
        break;
    }

    return 0;
}

void arithmetic()
{
    cout << "请输入一个四则运算表达式：" << endl;
    string exp;
    cin >> exp;

    stack<int> s1; // 存放整数
    stack<char>s2; // 存放运算符

    for(unsigned int i=0; i<exp.length(); i++)
    {
        // 遇到数字一律入栈
        if(isdigit(exp[i]))
        {
            unsigned int j;
            for(j=i; j<exp.length()&&isdigit(exp[j]); j++);
            s1.push(atoi(exp.c_str()+i));
            i = j-1;
            continue;
        }

        // 遇到运算符视情况而定：
        // 1，若运算符栈不为空且栈顶元素优先级比较高，则循环出栈运算
        while(!s2.empty() && (s2.top() == '*' || s2.top() == '/'))
        {
            int b = s1.top();s1.pop();
            int a = s1.top();s1.pop();
            char op = s2.top();s2.pop();

            s1.push(cal(a, b, op));
        }

        // 2，若运算符栈为空或者栈顶元素优先级比较低，则入栈
        if(s2.empty() || s2.top() == '+' || s2.top() == '-')
        {
            s2.push(exp[i]);
        }
    }

    while(!s2.empty())
    {
        int b = s1.top();s1.pop();
        int a = s1.top();s1.pop();
        char op = s2.top();s2.pop();

        s1.push(cal(a, b, op));
    }

    cout << "答案：" << s1.top() << endl;
}
