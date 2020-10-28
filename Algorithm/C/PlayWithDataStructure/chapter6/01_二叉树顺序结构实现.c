/*
 * 二叉树顺序存储结构: 用一组地址连续的存储单元依次自上而下、自左而右存储完全二叉树上的
 * 结点元素,即将完全二叉树上编号为i的结点元素存储在定义为一维数组中下标为i-1的分量中.
 * 这种存储结构仅适用于完全二叉树
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAX_TREE_SIZE 15 // 二叉树的最大结点数

typedef int Status; // Status是函数的了类型,其值是函数结果状态代码
typedef int TElemType; // 树结点的数据类型,目前暂定为整型
typedef TElemType SqBiTree[MAX_TREE_SIZE]; // 0号单元存储根结点

typedef struct
{
    int level, order; // 结点的层,本层序号(按满二叉树计算)
} Position;

TElemType Nil = 0; // 设整形以0为空

// 构造空二叉树T,因为T是固定数组,不会改变,故不需要&
Status InitBiTree(SqBiTree T)
{
    int i;
    for (i = 0; i < MAX_TREE_SIZE; i++)
        T[i] = Nil; // 初值为空

    return OK;
}

// 在顺序存储结构中,两函数完全一样
// 清空二叉树
#define ClearBiTree InitBiTree

// 按层序次序输入二叉树中结点的值(字符型或整形),构造顺序存储的二叉树T
Status CreateBiTree(SqBiTree T)
{
    int i = 0;
    printf("请按层序输入结点的值(整型),0表示空结点,输999结束.结点数<=%d:\n", MAX_TREE_SIZE);

    while (i < 10)
    {
        T[i] = i + 1;

        if (i != 0 && T[(i + 1) / 2 - 1] == Nil && T[i] != Nil)
        {
            printf("出现无双亲的非根结点%d\n", T[i]);
            exit(ERROR);
        }
        i++;
    }

    while (i < MAX_TREE_SIZE)
    {
        T[i] = Nil; // 将空赋值给T的后面的结点
        i++;
    }

    return OK;
}

// 初始条件: 二叉树T存在
// 操作结果: 若T为空二叉树,则返回TRUE,否则FALSE
Status BiTreeEmpty(const SqBiTree T)
{
    if (T[0] == Nil) // 根结点为空,则树空
        return TRUE;
    else
        return FALSE;
}

// 由于顺序存储的二叉树是按序存在数组中的,数组元素位序等于数组下标-1,
// 所以应该先找到最后一个结点才能计算总共的深度(2^x >= n,x为解)
// 初始条件:二叉树T存在
// 操作结果:返回T的深度
int BiTreeDepth(const SqBiTree T)
{
    int i;
    int j = 1; // 用来存深度
    // 遍历获得最后一个结点
    for (i = MAX_TREE_SIZE - 1; i >= 0; i--)
    {
        if (T[i] != Nil)
            break;
    }
    // 由于树结点是从数组0位置开始存的(根结点),所以此时数组中的元素个数为i+1
    i++;

    // 第n层的满二叉树共有2^n -1个结点
    // 1层: 2^1-1=1
    // 2层: 2^2-1=3
    // 3层: 2^3-1=7
    // 当2^j-1 < i时,是装不下i个元素的
    while (powl(2, j) - 1 < i)
    {
        j++;
    }

    return j;
}

// 初始条件:二叉树T存在
// 操作结果:当T不空,用e返回T的根,返回OK;否则返回ERROR,e无定义
Status Root(SqBiTree T, TElemType *e)
{
    if (BiTreeEmpty(T)) // T空
        return ERROR;
    else
    {
        *e = T[0];
        return OK;
    }
}

// 初始条件:二叉树T存在,e是T中某个结点(的位置)
// 操作结果:返回处于位置e(层,本层序号)的结点的值
TElemType Value(SqBiTree T, Position e)
{
    // T[i]是第i+1个元素, T[0] = 根结点,即1号元素
    // e.level-1表示e的上一层
    // 第3层第3个元素为T[5],即 2^(3-1)+3-2=5 => powl(2, e.level-1)+e,order-2
    return T[(int) powl(2, e.level - 1) + e.order - 2];
}

// 初始条件:二叉树T存在,e是T中某个结点(的位置)
// 操作结果:给处于位置e(层,本层序号)的结点赋新值value
Status Assign(SqBiTree T, Position e, TElemType value)
{
    // 将层、本层序号转为矩阵的序号
    int i = (int) powl(2, e.level - 1) + e.order - 2;

    // T[i]对应第i+1个元素
    // 不能赋值的情况
    // 1.给叶子结点赋非空值,但是它双亲结点为空
    // (i+1)/2为叶子结点的双亲,在数组中对应T[(i+1)/2-1]
    if (value != Nil && T[(i + 1) / 2 - 1] == Nil)
        return ERROR;
    // 2.给双亲结点赋空值,但是它叶子结点不为空
    // (i+1)*2为左孩子, (i+1)*2-1为对应数组元素
    // (i+1)*2+1为右孩子, (i+1)*2+1-1为对应的数组元素
    if (value == Nil && (T[2 * i + 1] != Nil || T[2 * i + 2] != Nil))
        return ERROR;

    // 将值赋给T[i]
    T[i] = value;
    return OK;
}

// 初始条件:二叉树T存在,e是T中某个结点
// 操作结果:若e是T的非根结点,则返回它的双亲,否则返回空
TElemType Parent(SqBiTree T, TElemType e)
{
    int i;
    // 空树
    if (T[0] == Nil)
        return Nil;

    // 非空树,由于e是非根结点,则从第二个元素开始遍历
    for (i = 1; i <= MAX_TREE_SIZE - 1; i++)
        if (T[i] == e)
            return T[(i + 1) / 2 - 1];

    return Nil;
}

// 初始条件:二叉树T存在,e是T中某个结点
// 操作结果:返回e的左孩子,若e无左孩子,则返回空
TElemType LeftChild(SqBiTree T, TElemType e)
{
    int i;
    // 空树
    if (T[0] == Nil)
        return ERROR;

    // 非空树
    for (i = 1; i <= MAX_TREE_SIZE - 1; i++)
        if (T[i] == e)
        {
            if (2 * i + 1 >= MAX_TREE_SIZE)
                return Nil;
            else
                return T[2 * i + 1];
        }

    return Nil;
}

// 初始条件:二叉树T存在,e是T中某个结点
// 操作结果:返回e的右孩子.若e无右孩子,则返回空
TElemType RightChild(SqBiTree T, TElemType e)
{
    int i;
    // 空树
    if (T[0] == Nil)
        return ERROR;

    // 非空树
    for (i = 1; i <= MAX_TREE_SIZE - 1; i++)
        if (T[i] == e)
        {
            if (2 * i + 2 >= MAX_TREE_SIZE)
                return Nil;
            else
                return T[2 * i + 2];
        }
    return Nil;
}

// 初始条件:二叉树T存在,e是T中某个结点
// 操作结果:返回e的左兄弟.若e是T的左孩子或无左兄弟,则返回空
TElemType LeftSibling(SqBiTree T, TElemType e)
{
    int i;

    // 空树
    if (T[0] == Nil)
        return Nil;

    // 非空树
    for (i = 1; i <= MAX_TREE_SIZE - 1; i++)
        // 左孩子是偶数,所以左孩子在数组中的索引应该为奇数
        // 右孩子是奇数,所以右孩子在数组中的索引应该为偶数
        if (T[i] == e && i % 2 == 0)
            return T[i - 1];

    return Nil;
}

// 初始条件:二叉树T存在,e是T中某个结点
// 操作结果:返回e的右兄弟.若e是T的右孩子或无右兄弟,则返回空
TElemType RightSibling(SqBiTree T, TElemType e)
{
    int i;
    // 空树
    if (T[0] == Nil)
        return Nil;

    for (i = 1; i <= MAX_TREE_SIZE - 1; i++)
        // 左孩子是偶数,所以左孩子在数组中的索引应该为奇数
        // 右孩子是奇数,所以右孩子在数组中的索引应该为偶数
        if (T[i] == e && i % 2)
        {
            if (i + 1 >= MAX_TREE_SIZE)
                return Nil;
            else
                return T[i + 1];
        }

    return Nil;
}

/*
 * 二叉树性质5
 * 如果对一颗有n个结点的完全二叉树(其深度为log2n+1,取下整)的结点按层序编号,对任一结点i
 * 有如下:
 * 1.如果2i>n,则结点i无左孩子(结点i为叶子结点),否则其左孩子是结点2i
 * 2.如果2i+1>n,则结点i无左孩子,否则其右孩子是结点2i+1
 */
Status visit(TElemType c)
{
    printf("%d ", c);
    return OK;
}

// 访问的T[2*e+1]元素,它必须要初始化过,如果未初始化会发生问题
// 因为需要判断2*e+1 是否 >= MAX_TREE_SIZE
void PreTraverse(SqBiTree T, int e)
{
    if (e >= MAX_TREE_SIZE)
        return;

    visit(T[e]); // 访问根结点
    // T[e]对应e+1个元素,其左子树对应为2*(e+1),数组序号为T[2*(e+1)-1]
    if (T[2 * e + 1] != Nil) // 左子树不空
        PreTraverse(T, 2 * e + 1);
    if (T[2 * e + 2] != Nil)
        PreTraverse(T, 2 * e + 2);
}

// 初始条件:二叉树存在
// 操作结果:先序遍历T
// 需要函数: PreTraverse()函数
Status PreOrderTraverse(SqBiTree T)
{
    // 树空返回错误
    if (BiTreeEmpty(T))
        return ERROR;

    PreTraverse(T, 0);
    printf("\n");

    return OK;
}

// 访问的T[2*e+1]元素,它必须要初始化过,如果未初始化会发生问题
// 因为需要判断2*e+1 是否 >= MAX_TREE_SIZE
void InTraverse(SqBiTree T, int e)
{
    if (e >= MAX_TREE_SIZE)
        return;

    if (T[2 * e + 1] != Nil) // 左子树不空
        InTraverse(T, 2 * e + 1);
    visit(T[e]);
    if (T[2 * e + 2] != Nil) // 右子树不空
        InTraverse(T, 2 * e + 2);
}

// 初始条件:二叉树存在
// 操作结果:中序遍历T
// 需要函数:InTraverse()
Status InOrderTraverse(SqBiTree T)
{
    // 树空返回错误
    if (BiTreeEmpty(T))
        return ERROR;

    InTraverse(T, 0);
    printf("\n");

    return OK;
}

// 访问的T[2*e+1]元素,它必须要初始化过,如果未初始化会发生问题
// 因为需要判断2*e+1 是否 >= MAX_TREE_SIZE
void PostTraverse(SqBiTree T, int e)
{
    if (e >= MAX_TREE_SIZE)
        return;

    if (T[2 * e + 1] != Nil) // 左子树不空
        PostTraverse(T, 2 * e + 1);
    if (T[2 * e + 2] != Nil) // 右子树不空
        PostTraverse(T, 2 * e + 2);
    visit(T[e]);
}

// 初始条件:二叉树T存在
// 操作结果:后序遍历T
Status PostOrderTraverse(SqBiTree T)
{
    // 树空返回错误
    if (BiTreeEmpty(T))
        return ERROR;

    PostTraverse(T, 0);
    printf("\n");

    return OK;
}

// 层序遍历二叉树
/*
 * 1.倒序查找最后一个不为空的元素,这个元素为最后一个叶子结点
 * 2.然后从根结点逐个输出到这个结点
 */
void LevelOrderTraverse(SqBiTree T)
{
    int i = MAX_TREE_SIZE - 1, j;

    // 找到最后一个元素在数组中的下标值
    while (i)
    {
        if (T[i] != Nil)
            break;
        i--;
    }

    // 从根结点起,按层序遍历二叉树
    for (j = 0; j <= i; j++)
        if (T[j] != Nil)
            visit(T[j]); // 只遍历非空的结点

    printf("\n");
}

// 逐层、按本层序号输出二叉树
void Print(SqBiTree T)
{
    int j, k;
    Position p;
    TElemType e;

    // 按层遍历
    for (j = 1; j <= BiTreeDepth(T); j++)
    {
        printf("第%d层: ", j);
        // 第1层最多2^0个;第2层最多2^1个;第3层最多2^2;...;第n层最多2^(n-1)
        for (k = 1; k <= powl(2, j - 1); k++)
        {
            p.level = j;
            p.order = k;
            e = Value(T, p);
            if (e != Nil)
                printf("%d:%d ", k, e);
        }
        printf("\n");
    }
}

SqBiTree Q;

void Copy(const SqBiTree T, SqBiTree P)
{
    for (int i = 0; i <= MAX_TREE_SIZE - 1; i++)
    {
        P[i] = T[i];
    }
}


int main(void)
{
    Status i;
    Position p;
    TElemType e;
    SqBiTree T;
    InitBiTree(T);
    CreateBiTree(T);

    Copy(T, Q);
    printf("建立二叉树后,树空否?%d(1:是 0:否) 树的深度=%d\n", BiTreeEmpty(T), BiTreeDepth(T));
    i = Root(T, &e);
    if (i)
        printf("二叉树的根为: %d\n", e);
    else
        printf("树空, 无根\n");

    printf("层序遍历二叉树:\n");
    LevelOrderTraverse(T);
    printf("前序遍历二叉树:\n");
    PreOrderTraverse(T);
    printf("中序遍历二叉树:\n");
    InOrderTraverse(T);
    printf("后序遍历二叉树:\n");
    PostOrderTraverse(T);

    printf("接下来将修改层号3本层序号为2的元素\n");
    p.level = 3;
    p.order = 2;
    e = Value(T, p);
    printf("待修改结点的的原值为%d,修改成%d\n", e, 50);
    e = 50;
    Assign(T, p, e);

    printf("前序遍历二叉树:\n");
    PreOrderTraverse(T);

    printf("结点%d的双亲为%d, 左右孩子分别为", e, Parent(T, e));
    printf("%d, %d ", LeftChild(T, e), RightChild(T, e));
    printf("左右兄弟分别为: %d, %d\n", LeftSibling(T, e), RightSibling(T, e));

    Print(T); // 按层按序打印二叉树

    ClearBiTree(T);
    printf("清楚二叉树后,树空否? %d(1:是 0:否) 树的深度=%d\n", BiTreeEmpty(T), BiTreeDepth(T));
    i = Root(T, &e);

    if (i)
        printf("二叉树的根为:%d\n", i);
    else
        printf("树空,无根\n");

    return 0;
}