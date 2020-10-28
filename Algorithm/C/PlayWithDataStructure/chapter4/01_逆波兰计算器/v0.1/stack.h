#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define InputMaxSize 100 // 用户输入大小
#define MAXSIZE 20 // 数组容量

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status; // 返回结果
typedef char SElemType; // 栈中数据的类型

typedef struct
{
    SElemType data[MAXSIZE];
    int top;
} SqStack;

int Input_Array(char *ar, int n);

char *generate_expression(const char *array, int length);

Status InitStack(SqStack *S);

Status Push(SqStack *S, SElemType e);

Status Pop(SqStack *S, SElemType *e);

Status GetTop(SqStack S, SElemType *e);

Status StackEmpty(SqStack S);