#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status; // Status是函数的类型,其值是函数结果状态代码,如OK
typedef int ElemType; // ElemType类型根据实际情况而定,这里假设为int

typedef struct Node
{
    // 数据域
    ElemType data;
    // 指针域
    struct Node *next;
} Node;

// 定义LinkList
typedef struct Node *LinkList;

// 初始化顺序线性表
Status InitList(LinkList *L)
{
    // 产生头节点,并使L指向此头节点
    *L = (LinkList) malloc(sizeof(Node));
    // 存储分配失败
    if (!(*L))
        return ERROR;
    // 指针域为空

    (*L)->next = NULL;

    return OK;
}

// 初始条件:顺序线性表L已存在
// 操作结果:若L为空表,则返回TRUE,否则返回FALSE
Status ListEmpty(LinkList L)
{
    if (L->next == NULL)
        return TRUE;

    return FALSE;
}

// 初始条件:顺序线性表L已存在
// 操作结果:将L重置为空表
Status ClearList(LinkList *L)
{
    LinkList p, q;
    // p指向第一个结点
    p = (*L)->next;

    while (p)
    {
        q = p->next;
        free(p);
        // 让p指向q
        p = q;
    }

    (*L)->next = NULL; // 头结点指针域为空,一定不能忘

    return OK;
}

// 初始条件:顺序线性表L已存在
// 操作结果:返回L中数据元素个数
int ListLength(LinkList L)
{
    int i = 0;
    LinkList p = L->next;
    while (p)
    {
        i++;
        p = p->next;
    }

    return i;
}

// 初始条件:顺序线性表L已存在, 1 <= i <= ListLength(L)
// 操作结果:用e返回L中第i个数据元素的值
Status GetElem(LinkList L, int i, ElemType *e)
{
    int j = 1;
    // 用来标识p在第一个数据元素
    LinkList p;

    // 让p指向链表L的第一个节点
    p = L->next;

    while (p && j < i)
    {
        // 让p指向下一个节点
        p = p->next;
        j++;
    }

    if (!p || j > i)
        return ERROR;
    // 取出第i个元素的数据
    *e = p->data;

    return OK;
}

// 初始条件:顺序线性表L已存在
// 操作结果:返回L中第1个与e满足关系的数据元素的位序
// 若这样的数据元素不存在,则返回值为0
int LocateElem(LinkList L, ElemType e)
{
    int i = 0;
    LinkList p;
    p = L->next;

    while (p)
    {
        i++;
        if (p->data == e)
            return i;

        p = p->next;
    }

    return 0;
}

// 初始条件:顺序线性表L已存在,1 <= i <= ListLength(L)
// 操作结果:在L中第i个位置之前插入新的数据元素e,L的长度加1
Status ListInsert(LinkList *L, int i, ElemType e)
{
    int j = 1;
    LinkList p, q;

    p = *L;

    // 寻找第i个节点
    while (p && j < i)
    {
        p = p->next;
        j++;
    }

    // 第i个元素不存在
    if (!p || j > i)
        return ERROR;

    // 将p的后继节点赋值给s的后继
    q = (LinkList) malloc(sizeof(Node));
    q->data = e;
    q->next = p->next;
    // 将s赋值给p的后继
    p->next = q;

    return OK;
}

// 初始条件:顺序线性表L已存在,1 <= i <= ListLength(L)
// 操作结果:删除L的第i个数据元素,并用e返回其值,L的长度减1
Status ListDelete(LinkList *L, int i, ElemType *e)
{
    LinkList p, q;
    int j = 1;
    p = *L;

    // 遍历寻找第i个元素
    while (p->next && j < i) // 这里填p->next && j < i结果相同
    {
        p = p->next;
        j++;
    }

    // 第i个元素不存在
    // 为什么p->next,因为如果是p,如果i是最后一个元素的后一个元素,在这里不会返回错误
    // 导致下方q = p->next造成溢出,因此需要用p->next来判断
    if (!(p->next) || j > i)
        return ERROR;

    q = p->next;
    // 将q的后继赋值给p的后继
    p->next = q->next;
    // 将q结点中的数据给e
    *e = q->data;
    // 释放内存
    free(q);

    return OK;
}

Status visit(ElemType e)
{
    printf("%d ", e);
    return OK;
}

// 初始条件:顺序线性表L已存在
// 操作结果:依次对L的每个数据元素输出
Status ListTraverse(LinkList L)
{
    LinkList p;
    p = L->next;

    while (p)
    {
        visit(p->data);
        p = p->next;
    }

    printf("\n");
    return OK;
}

// 随机产生n个元素的值,建立带表头结点的单链线性表L(头插法)
void CreateListHead(LinkList *L, int n)
{
    int i;
    // 先建立一个带头节点的单链表
    *L = (LinkList) malloc(sizeof(Node));
    LinkList p;
    // 初始化随机种子
    srand(time(0));

    (*L)->next = NULL; // 极其重要不能漏

    for (i = 0; i < n; i++)
    {
        // 生成新节点
        p = (LinkList) malloc(sizeof(Node));
        // 随机生成100以内的数字
        p->data = rand() % 100 + 1;
        // 插入到表头
        p->next = (*L)->next;
        (*L)->next = p;
    }
}

// 随机产生n个元素的值,建立带表头结点的单链线性表L(尾插法)
void CreateListTail(LinkList *L, int n)
{
    LinkList p, r;
    int i;
    // 初始化随机数种子
    srand(time(0));

    // L为整个线性表
    *L = (LinkList) malloc(sizeof(Node));
    // r为指向尾部的结点
    r = *L;

    for (i = 0; i < n; i++)
    {
        // 生成新节点

        p = (LinkList) malloc(sizeof(Node));
        // 随机生成100以内的数字
        p->data = rand() % 100 + 1;
        // 将表尾终端节点的指针指向新结点
        r->next = p;
        // 将当前的新节点定义为表尾终端的结点
        r = p;
    }

    // 表示当前链表结束
    r->next = NULL;
}

int main(void)
{
    LinkList L;
    ElemType e;
    Status i;
    int j, k;
    i = InitList(&L);
    printf("初始化后: ListLength(L) = %d\n", ListLength(L));

    for (j = 1; j <= 5; j++)
        i = ListInsert(&L, 1, j);
    printf("在L的表头依次插入1~5后: L.data=");
    ListTraverse(L);

    printf("ListLength(L)=%d \n", ListLength(L));
    i = ListEmpty(L);
    printf("L是否空: i=%d(1:是 0:否)\n", i);

    i = ClearList(&L);
    printf("清空L后：ListLength(L)=%d\n", ListLength(L));
    i = ListEmpty(L);
    printf("L是否空：i=%d(1:是 0:否)\n", i);

    for (j = 1; j <= 10; j++)
        ListInsert(&L, j, j);
    printf("在L的表尾依次插入1～10后：L.data=");
    ListTraverse(L);

    printf("ListLength(L)=%d \n", ListLength(L));

    GetElem(L, 5, &e);
    printf("第5个元素的值为：%d\n", e);

    for (j = 3; j <= 4; j++)
    {
        k = LocateElem(L, j);
        if (k)
            printf("第%d个元素的值为%d\n", k, j);
        else
            printf("没有值为%d的元素\n", j);
    }

    k = ListLength(L); /* k为表长 */
    for (j = k + 1; j >= k; j--)
    {
        i = ListDelete(&L, j, &e); /* 删除第j个数据 */
        if (i == ERROR)
            printf("删除第%d个数据失败\n", j);
        else
            printf("删除第%d个的元素值为：%d\n", j, e);
    }
    printf("依次输出L的元素：");
    ListTraverse(L);

    j = 9;
    ListDelete(&L, j, &e); /* 删除第5个数据 */
    printf("删除第%d个的元素值为：%d\n", j, e);

    printf("依次输出L的元素：");
    ListTraverse(L);

    i = ClearList(&L);
    printf("\n清空L后：ListLength(L)=%d\n", ListLength(L));
    CreateListHead(&L, 20);
    printf("整体创建L的元素(头插法)：");
    ListTraverse(L);

    i = ClearList(&L);
    printf("\n删除L后：ListLength(L)=%d\n", ListLength(L));
    CreateListTail(&L, 20);
    printf("整体创建L的元素(尾插法)：");
    ListTraverse(L);

    return 0;
}
