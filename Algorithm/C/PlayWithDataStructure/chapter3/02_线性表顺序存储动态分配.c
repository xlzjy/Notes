#include <stdio.h>
#include <stdlib.h>

#define InitSize 10 // 默认的最大长度

typedef struct
{
    int *data; // 指示动态分配数组的指针
    int MaxSize; // 顺序表的最大容量
    int length; // 顺序表的当前长度
} SeqList;

void InitList(SeqList *L)
{
    // 用malloc函数申请一片连续的存储空间
    L->data = (int *) malloc(InitSize * sizeof(int));
    L->length = 0;
    L->MaxSize = InitSize;
}

// 增加动态数组的长度
void IncreaseSize(SeqList *L, int len)
{
    int *p = L->data; // p指针和data指针都指向同样的数据块,data[0]处
    L->data = (int *) malloc((L->MaxSize + len) * sizeof(int));

    for (int i = 0; i < L->length; i++)
    {
        L->data[i] = p[i]; // 将数据复制到新区域(时间开销大)
    }
    L->MaxSize = L->MaxSize + len; // 顺序表最大长度增加len
    free(p); // 释放原来的内存空间,因为p指向了原先的动态分配数据,将其释放,太秒了
}

int main(void)
{
    SeqList L; // 声明一个顺序表
    InitList(&L); // 初始化顺序表
    // ...往顺序表中随便插入几个元素...
    IncreaseSize(&L, 5);

    return 0;
}