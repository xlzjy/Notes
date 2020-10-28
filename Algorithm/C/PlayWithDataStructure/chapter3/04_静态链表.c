#include <stdio.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 10 // 存储空间初始分配量

typedef int Status; // Status是函数的类型,其值是函数结果状态代码,如OK
typedef char ElemType; // ElemType类型根据实际情况而定,这里假设为char

Status visit(ElemType c)
{
    printf("%c ", c);
    return OK;
}

// 线性表的静态链表存储结构
struct Node
{
    ElemType data;
    // 游标,为0时表示无指向
    int cur;
};
typedef struct Node Component;
typedef Component StaticLinkList[MAXSIZE];

// 将一维数组space中各分量链成一个备用链表,space[0].cur为头指针,"0"表示空指针
Status InitList(StaticLinkList space)
{
    int i;
    for (i = 0; i < MAXSIZE - 1; i++)
        space[i].cur = i + 1;

    // 目前静态链表为空,最后一个元素的cur为0
    space[MAXSIZE - 1].cur = 0;

    return OK;
}

// 若备用空间链表为空,则返回分配的结点下标,否则返回0
int Malloc_SSL(StaticLinkList space)
{
    // 当前数组第一个元素的cur存的值,就是要返回的第一个备用空闲的下标
    int i = space[0].cur;
    // 由于要拿出一个分量来使用了,所以就要把它下一个分量用来做备用
    if (space[0].cur)
        space[0].cur = space[i].cur;

    return i;
}

// 将下标为k的空闲结点回收到备用链表
void Free_SSL(StaticLinkList space, int i)
{
    // 把第一个元素的cur值赋给要删除的分量
    space[i].cur = space[0].cur;
    // 把要删除的分量下标赋值给第一个元素的cur
    space[0].cur = i;
}

// 初始条件:静态链表L已存在
// 操作结果:返回L中数据元素个数
int ListLength(StaticLinkList L)
{
    // 存放第一个数据元素的下标
    int i = L[MAXSIZE - 1].cur;
    int j = 0;

    while (i)
    {
        i = L[i].cur;
        j++;
    }

    return j;
}

// 在L中第i个元素之前插入新的数据元素e
Status ListInsert(StaticLinkList L, int i, ElemType e)
{
    // 注意k首先是最后一个元素的下标
    int k = MAXSIZE - 1;

    if (i < 1 || i > ListLength(L) + 1) // 1 <= i <= 链表长度+尾结点
        return ERROR;

    // 获得空闲分量的下标
    int j = Malloc_SSL(L);

    int l;

    if (j)
    {
        // 将数据赋值给此分量的data
        L[j].data = e;

        // 找到第i个元素之前的位置
        for (l = 1; l <= i - 1; l++)
            k = L[k].cur;

        // 把第i个元素之前的cur赋值给新元素的cur
        L[j].cur = L[k].cur;

        // 把新元素的下标赋值给第i个元素之前元素的cur
        L[k].cur = j;

        return OK;
    }

    return ERROR;
}

// 删除在L中第i个数据元素
Status ListDelete(StaticLinkList L, int i)
{
    int j, k;
    k = MAXSIZE - 1;

    if (i < 1 || i > ListLength(L))
        return ERROR;

    for (j = 1; j <= i - 1; j++)
        k = L[k].cur;

    j = L[k].cur;

    L[k].cur = L[j].cur;

    Free_SSL(L, j);

    return OK;
}

Status ListTraverse(StaticLinkList L)
{
    int j = 0;
    int i = L[MAXSIZE - 1].cur;

    while (i)
    {
        visit(L[i].data);
        i = L[i].cur;
        j++;
    }
    return OK;
}

int main(void)
{
    StaticLinkList L;
    Status i;
    i = InitList(L);
    printf("初始化L后：L.length=%d\n", ListLength(L));

    i = ListInsert(L, 1, 'F');
    i = ListInsert(L, 1, 'E');
    i = ListInsert(L, 1, 'D');
    i = ListInsert(L, 1, 'B');
    i = ListInsert(L, 1, 'A');

    printf("\n在L的表头依次插入FEDBA后：\nL.data=");
    ListTraverse(L);

    i = ListInsert(L, 3, 'C');
    printf("\n在L的“B”与“D”之间插入“C”后：\nL.data=");
    ListTraverse(L);

    i = ListDelete(L, 1);
    printf("\n在L的删除“A”后：\nL.data=");
    ListTraverse(L);

    printf("\n");

    return 0;
}

