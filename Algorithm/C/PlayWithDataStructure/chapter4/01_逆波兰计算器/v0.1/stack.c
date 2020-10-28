#include "stack.h"

// 构造一个空栈
Status InitStack(SqStack *S)
{
    S->top = -1; // 空栈
    return OK;
}

// 插入元素e为新的栈顶元素
Status Push(SqStack *S, SElemType e)
{
    if (S->top == MAXSIZE - 1)
        return ERROR;

    S->data[++S->top] = e; // 将新元素插入到栈顶空间

    return OK;
}

// 若栈不空,则删除S的栈顶元素,用e返回其值,并返回OK,否则返回ERROR
Status Pop(SqStack *S, SElemType *e)
{
    if (S->top == -1)
        return ERROR;

    *e = S->data[S->top--]; // 将要删除的栈顶元素赋值给e

    return OK;
}

// 若栈不空,则用e返回S的栈顶元素,并返回OK,否则返回ERROR
Status GetTop(SqStack S, SElemType *e)
{
    if (S.top == -1)
        return ERROR;

    *e = S.data[S.top];

    return OK;
}

// 若栈S为空栈,则返回TRUE,否则返回FALSE
Status StackEmpty(SqStack S)
{
    if (S.top == -1)
        return TRUE;

    return FALSE;
}