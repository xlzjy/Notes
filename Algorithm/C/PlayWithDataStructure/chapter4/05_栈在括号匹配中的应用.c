#include <stdio.h>
#include <stdbool.h>

/*
 * 用栈实现括号匹配:
 * 依次扫描所有字符,遇到左括号入栈,遇到右括号则弹出栈顶元素检查是否匹配
 * 匹配失败情况:
 * 1.左括号单身
 * 2.右括号单身
 * 3.左右括号不匹配
 */

#define MAXSIZE 10 // 定义栈中元素的最大个数
typedef struct
{
    char data[MAXSIZE]; // 静态数组存放栈中元素
    int top; // 栈顶指针
} SqStack;

// 初始化栈
void InitStack(SqStack *S);
// 判断栈是否为空
bool StackEmpty(SqStack S);
// 新元素入栈
bool Push(SqStack *S, char x);
// 栈顶元素出栈,用x返回
bool Pop(SqStack *S, char *x);

bool bracketCheck(char str[], int length)
{
    SqStack s;
    InitStack(&s); // 初始化一个栈

    for (int i = 0; i < length; i++)
    {
        if (str[i] == '(' || str[i] == '[' || str[i] == '{')
        {
            Push(&s, str[i]); // 扫描到左括号,入栈
        } else
        {
            if (StackEmpty(s)) // 扫描到右括号,且当前栈空
                return false;

            char topElem;
            Pop(&s, &topElem); // 栈顶元素出栈
            if (str[i] == ')' && topElem != '(')
                return false;
            if (str[i] == ']' && topElem != '[')
                return false;
            if (str[i] == '}' && topElem != '{')
                return false;
        }
    }

    return StackEmpty(s); // 检索完全部括号后,栈空说明匹配成功
}