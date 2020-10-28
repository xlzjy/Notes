// 线性表顺序存储

#include <stdio.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
// 存储空间初始分配量
#define MAXSIZE 20

// ElemType元素类型根据实际情况而定,这里假设为int
typedef int ElemType;
// Status是函数的类型,其值是函数结果状态代码,如OK等
typedef int Status;

typedef struct
{
    // 数组存储数据元素,最大值为MAXSIZE
    ElemType data[MAXSIZE];
    // 线性表当前长度
    int length;
} SqList;

// 初始化顺序线性表
Status InitList(SqList *L)
{
    L->length = 0;
    return OK;
}

// 初始条件:顺序线性表L已存在
// 操作结果:若L为空表,则返回TRUE,否在返回FALSE
Status ListEmpty(SqList L)
{
    if (L.length == 0)
        return TRUE;
    else
        return FALSE;
}

// 初始条件:顺序线性表L已存在
// 操作结果:将L重置为空表
Status ClearList(SqList *L)
{
    L->length = 0;
    return OK;
}

// 初始条件:顺序线性表L已存在
// 操作结果:返回L中数据元素个数
int ListLength(SqList L)
{
    return L.length;
}

// 初始条件:顺序线性表L已存在,1 <= i <= ListLength(L)
// 操作结果:用e返回L中第i个数据元素的值,注意i是指位置,第1个位置的数组是从0开始
Status GetElem(SqList L, int i, ElemType *e)
{
    if (L.length == 0 || i < 1 || i > L.length)
        return ERROR;

    *e = L.data[i - 1]; // e用指针传回去
    return OK;
}

// 初始条件:顺序线性表L已存在
// 操作结果:返回L中第1个与e满足关系的数据元素的位序
// 若这样的数据元素不存在,则返回值为0
int LocateElem(SqList L, ElemType e)
{
    int i;
    if (L.length == 0)
        return 0;

    for (i = 0; i < L.length; i++)
    {
        if (L.data[i] == e)
            break;
    }

    if (i >= L.length)
        return 0;

    return i + 1;
}

// 初始条件:顺序线性表L已存在, 1 <= i <= ListLength(L)
// 操作结果:在L中第i个位置之前插入新的数据元素e,L的长度加1
Status ListInsert(SqList *L, int i, ElemType e)
{
    int k;
    // 顺序线性表已经满
    if (L->length == MAXSIZE)
        return ERROR;
    // 当i比第一位置小或者比最后一位之后一位还要大时
    if (i < 1 || i > L->length + 1)
        return ERROR;
    // 若插入数据位置不在表尾,要将后续数据全部往后移一位
    if (i <= L->length)
    {
        for (k = L->length - 1; k >= i - 1; k--)
        {
            L->data[k + 1] = L->data[k];
        }

    }
    // 新元素插入
    L->data[i - 1] = e;

    // 表长度加一
    L->length++;

    return OK;
}

// 初始条件:顺序线性表L已存在, 1 <= i <= ListLength(L)
// 操作结果:删除L的第i个数据元素,并用e返回值,L的长度减1
Status ListDelete(SqList *L, int i, ElemType *e)
{
    int k;
    // 线性表为空
    if (L->length == 0)
        return ERROR;
    // 删除位置不正确
    if (i < 1 || i > L->length)
        return ERROR;

    // 取出需要删除的元素
    *e = L->data[i - 1];

    // 如果删除不是最后位置
    if (i < L->length)
    {
        for (k = i; k < L->length; k++)
        {
            // 将删除位置后继元素前移
            L->data[k - 1] = L->data[k];
        }
    }
    L->length--;

    return OK;
}

// 打印元素
Status VisitElement(ElemType c)
{
    printf("%d ", c);
    return OK;
}

// 初始条件:顺序线性表L已存在
// 操作结果:依次对L的每个数据元素输出
Status ListTraverse(SqList L)
{
    if (L.length == 0)
        return ERROR;

    int i;
    for (i = 0; i < L.length; i++)
        VisitElement(L.data[i]);

    printf("\n");

    return OK;
}

// 将B中A中没有的元素并到A中
void unionL(SqList *La, SqList Lb)
{
    int k;
    int La_len = La->length;
    int Lb_len = Lb.length;
    ElemType e;

    for (k = 1; k <= Lb_len; k++)
    {
        GetElem(Lb, k, &e);
        if (!LocateElem(*La, e))
            ListInsert(La, ++La_len, e);
    }
}

int main(void)
{
    SqList L;
    SqList Lb;

    ElemType e; // 数组元素
    Status i; // 函数结果
    int j, k;

    i = InitList(&L);
    printf("初始化L后: L.length=%d\n", L.length); // L.length=0

    for (j = 1; j <= 5; j++)
        i = ListInsert(&L, 1, j); // 插入的位置是1
    printf("在L的表头依次插入1~5后: L.data=");
    ListTraverse(L); // 5 4 3 2 1

    printf("L.length=%d \n", L.length); // L.length=5

    i = ListEmpty(L); // 判断是否为空
    printf("L是否空: i=%d(1:是 0:否)\n", i); // L是否空: i=0(1:是 0:否)

    i = ClearList(&L);
    printf("清空L后: L.length=%d \n", L.length); // 清空L后: L.length=0

    i = ListEmpty(L);
    printf("L是否空: i=%d(1:是 0:否)\n", i); // L是否空: i=1(1:是 0:否)

    for (j = 1; j <= 10; j++)
        ListInsert(&L, j, j);
    printf("在L的表尾依次插入1~10后: L.data=");
    ListTraverse(L); // 1 2 3 4 5 6 7 8 9 10

    printf("L.length=%d \n", L.length); // L.length=10

    ListInsert(&L, 1, 0);
    printf("在L的表头插入0后: L.data=");

    ListTraverse(L); // 0 1 2 3 4 5 6 7 8 9 10
    printf("L.length=%d\n", L.length); // L.length=11

    ListInsert(&L, 1, 0);
    printf("在L的表头插入0后: L.data=");
    ListTraverse(L); // 0 0 1 2 3 4 5 6 7 8 9 10
    printf("L.length=%d\n", L.length); // L.length=12

    GetElem(L, 5, &e);
    printf("第5个元素的值为：%d\n", e); // 3
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

    j = 5;
    ListDelete(&L, j, &e); /* 删除第5个数据 */
    printf("删除第%d个的元素值为：%d\n", j, e);

    printf("依次输出L的元素：");
    ListTraverse(L);

    //构造一个有10个数的Lb
    i = InitList(&Lb);
    for (j = 6; j <= 15; j++)
        i = ListInsert(&Lb, 1, j);

    unionL(&L, Lb);

    printf("依次输出合并了Lb的L的元素：");
    ListTraverse(L);

    return 0;

}



