#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100 // 存储空间初始分配量

typedef int Status; // Status是函数的类型,其值为函数结果状态代码

/* ************************用于构造二叉树 ************************ */
// 作用str[0]字符串长度,str[1]~str[MAXSIZE-1]字符串,如输入AB#D##C##等
int index_num = 1;
typedef char String[24]; // 0号单元存放串的长度
String str;

Status StrAssign(String T, char *chars)
{
    int i;
    if (strlen(chars) > MAXSIZE)
        return ERROR;
    else
    {
        T[0] = strlen(chars);
        for (i = 1; i <= T[0]; i++)
            T[i] = *(chars + i - 1);
        return OK;
    }
}

/* ************************************************************* */

typedef char TElemType;
TElemType Nil = ' '; // 字符型以空格符为空

Status visit(TElemType e)
{
    printf("%c", e);
    return OK;
}

// 结点结构
typedef struct BiTNode
{
    TElemType data; // 结点数据
    struct BiTNode *lchild, *rchild; // 左右孩子指针
} BiTNode, *BiTree;

typedef BiTree QElemType; // 设队列元素为二叉树的指针类型

// 链式队列结点,包括一个数据域和一个指针域,数据域为二叉树的指针类型
typedef struct QNode
{
    QElemType data; // 只保存这个结点的指针即可,这样可以减少空间的消耗
    struct QNode *next;
} QNode, *QueuePtr;

typedef struct
{
    QueuePtr front, rear; // 队头队尾指针
} LinkQueue;

// 构造空二叉树
Status InitBiTree(BiTree *T)
{
    // 初始为NULL说明此时他是一颗空树
    *T = NULL;
    return OK;
}

// 按前序输入二叉树中结点的值(一个字符)
// #表示空树,构造二叉链表表示二叉树T
void CreateBiTree(BiTree *T)
{
    TElemType ch;

    // scanf("%c", &ch);
    ch = str[index_num++];

    // 使用递归创建二叉树
    if (ch == '#')
        *T = NULL;
    else
    {
        *T = (BiTree) malloc(sizeof(BiTNode));
        if (!*T)
            exit(OVERFLOW);
        (*T)->data = ch;
        CreateBiTree(&(*T)->lchild); // 构造左子树
        CreateBiTree(&(*T)->rchild); // 构造右子树
    }
}

// 构造一个空队列Q
Status InitQueue(LinkQueue *Q)
{
    (*Q).front = (*Q).rear = (QueuePtr) malloc(sizeof(QNode));
    if (!(*Q).front)
        exit(OVERFLOW);
    (*Q).front->next = NULL;

    return OK;
}

// 插入元素e为Q的新的队尾元素
Status EnQueue(LinkQueue *Q, QElemType e)
{
    QueuePtr p = (QueuePtr) malloc(sizeof(QNode));
    if (!p) // 存储分配失败
        exit(OVERFLOW);
    p->data = e;
    p->next = NULL;
    (*Q).rear->next = p;
    (*Q).rear = p;

    return OK;
}

// 若Q为空队列,则返回TRUE,否则返回FALSE
Status QueueEmpty(LinkQueue Q)
{
    if (Q.front == Q.rear)
        return TRUE;
    else
        return FALSE;
}

// 若队列不空,删除Q的队头元素,用e返回其值,并返回OK,否则返回ERROR
Status DeQueue(LinkQueue *Q, QElemType *e)
{
    QueuePtr p;
    if ((*Q).front == (*Q).rear)
        return ERROR;

    p = (*Q).front->next;
    *e = p->data;
    (*Q).front->next = p->next;
    if ((*Q).rear == p)
        (*Q).rear = (*Q).front;
    free(p);
    return OK;
}

// 初始条件:二叉树T存在
// 操作结果:销毁二叉树T
void DestroyBiTree(BiTree *T)
{
    if (*T)
    {
        if ((*T)->lchild) // 有左孩子
            DestroyBiTree(&(*T)->lchild); // 销毁左孩子子树
        if ((*T)->rchild) // 有右孩子
            DestroyBiTree(&(*T)->rchild); // 销毁右孩子子树
        free(*T); // 释放根结点
        *T = NULL; // 空指针赋0
    }
}

#define ClearBiTree DestroyBiTree

// 初始条件:二叉树T存在
// 操作结果:若T为空二叉树,则返回TRUE,否则FALSE
Status BiTreeEmpty(BiTree T)
{
    if (T)
        return FALSE;
    else
        return TRUE;
}

// 初始条件:二叉树T存在
// 操作结果:返回T的深度(两种方法:递归方法 非递归方法)
/*
 * 递归方法
 * 1.如果一颗树只有一个结点,它的深度为1
 * 2.如果根结点只有左子树而没有右子树,那么树的深度应该是其左子树的深度加1;
 * 同样如果根结点只有右子树,那么树的深度应该是其右子树的深度加1
 * 3.如果既有左子树又有右子树,那该树的深度就是其左、右子树深度的较大值再加1
 */
int BiTreeDepth(BiTree T)
{
    int l, r; // 左子树和右子树的深度

    // 空树
    if (T == NULL)
        return 0; // 步骤1
    else
    {
        l = BiTreeDepth(T->lchild); // 步骤2
        r = BiTreeDepth(T->rchild); // 步骤3
        return l > r ? l + 1 : r + 1; // 步骤4
    }
}

// 非递归方法

// 初始条件:二叉树T存在
// 操作结果:返回T的根
TElemType Root(BiTree T)
{
    if (BiTreeEmpty(T))
        return Nil;
    else
        return T->data;
}

// 初始条件:二叉树T存在,p指向T中某个结点
// 操作结果:返回p所指结点的值
TElemType Value(BiTree p)
{
    return p->data;
}

// 给p所指结点赋值为value
void Assign(BiTree p, TElemType value)
{
    p->data = value;
}

// 初始条件:二叉树T存在
// 操作结果:前序递归遍历T
void PreOrderTraverse(BiTree T)
{
    if (T == NULL)
        return;
    printf("%c", T->data); // 显示结点数据,可以更改为其他对结点的操作
    PreOrderTraverse(T->lchild); // 再先序遍历左子树
    PreOrderTraverse(T->rchild); // 最后先序遍历右子树
}

// 初始条件:二叉树T存在
// 操作结果:中序递归遍历T
void InOrderTraverse(BiTree T)
{
    if (T == NULL)
        return;
    InOrderTraverse(T->lchild); // 中序遍历左子树
    printf("%c", T->data); // 显示结点数据,可以更改为其他结点操作
    InOrderTraverse(T->rchild); // 最后中序遍历右子树
}

// 初始条件:二叉树T存在
// 操作结果:后续递归遍历T
void PostOrderTraverse(BiTree T)
{
    if (T == NULL)
        return;
    PostOrderTraverse(T->lchild); // 先后序遍历左子树
    PostOrderTraverse(T->rchild); // 再后序遍历右子树
    printf("%c", T->data); // 显示结点数据,可以更改为其他对结点的操作
}

// 初始条件:二叉树T存在
// 操作结果:层序遍历T
/*
 * 思想:
 * 1.初始化一个辅助队列
 * 2.根结点入队
 * 3.若队列非空,则队头结点出队,访问该结点,并将其左、右孩子插入队尾(如果有的话)
 * 4.重复3直至队列为空
 */
void LevelOrderTraverse(BiTree T)
{
    LinkQueue q;
    QElemType e;

    if (T)
    {
        InitQueue(&q);
        EnQueue(&q, T);
        while (!QueueEmpty(q))
        {
            DeQueue(&q, &e);
            visit(e->data);
            if (e->lchild)
                EnQueue(&q, e->lchild);
            if (e->rchild)
                EnQueue(&q, e->rchild);
        }
    }
}

/* ********************************** */
// 参考网址 https://blog.csdn.net/wangrunmin/article/details/7852996

// 初始条件:二叉树T存在,e是T中的某个结点
// 操作结果:若e是T的非根结点,则返回它的双亲,否则返回空
TElemType Parent(BiTree T, TElemType e)
{
    LinkQueue q;
    QElemType a;

    if (T) // 非空树
    {
        InitQueue(&q); // 初始化队列
        EnQueue(&q, T); // 树根入队

        while (!QueueEmpty(q)) // 队不空
        {
            DeQueue(&q, &a); // 出队,队列元素赋给a
            if ((a->lchild && a->lchild->data == e) || (a->rchild && a->rchild->data == e))
                // 找到e(是其左或右孩子)
                return a->data;
            else
            {
                // 没找到e,则入队其左右孩子指针(如果非空)
                if (a->lchild)
                    EnQueue(&q, a->lchild);
                if (a->rchild)
                    EnQueue(&q, a->rchild);
            }
        }
    }
    return Nil;
}

// 返回二叉树T中指向元素值为s的结点的指针
BiTree Point(BiTree T, TElemType s)
{
    LinkQueue q;
    QElemType a;
    if (T) /* 非空树 */
    {
        InitQueue(&q); /* 初始化队列 */
        EnQueue(&q, T); /* 根结点入队 */
        while (!QueueEmpty(q)) /* 队不空 */
        {
            DeQueue(&q, &a); /* 出队,队列元素赋给a */
            if (a->data == s)
                return a; // a为地址
            if (a->lchild) /* 有左孩子 */
                EnQueue(&q, a->lchild); /* 入队左孩子 */
            if (a->rchild) /* 有右孩子 */
                EnQueue(&q, a->rchild); /* 入队右孩子 */
        }
    }
    return NULL;
}

// 初始条件:二叉树T存在,e是T中的某个结点
// 操作结果:返回e的左孩子,若e无左孩子,则返回空
TElemType LeftChild(BiTree T, TElemType e)
{
    BiTree a;
    if (T) // 非空树
    {
        a = Point(T, e); // a是结点e的指针
        if (a && a->lchild) // T中存在结点e且e存在左孩子
            return a->lchild->data; // 返回e的左孩子的值
    }
    return Nil; // 其余情况返回空
}

// 初始条件:二叉树T存在,e是T中某个结点
// 操作结果:返回e的右孩子,若e无右孩子,则返回空
TElemType RightChild(BiTree T, TElemType e)
{
    BiTree a;
    if (T) // 非空树
    {
        a = Point(T, e); // a是结点e的指针
        if (a && a->rchild) // T中存在结点e且e存在右孩子
            return a->rchild->data; // 返回e的右孩子的值
    }
    return Nil; // 其余情况返回空
}

// 初始条件:二叉树T存在,e是T中某个结点
// 操作结果:返回e的左兄弟,若e是T的左孩子或无左兄弟,则返回空
TElemType LeftSibling(BiTree T, TElemType e)
{
    TElemType a;
    BiTree p;

    if (T) // 非空树
    {
        a = Parent(T, e); // a为e的双亲
        p = Point(T, a); // p为指向结点a的指针
        // 既然返回左兄弟,那么他是右边的结点
        if (p->lchild && p->rchild && p->rchild->data == e)
            return p->lchild->data; // 返回p的左孩子(e的左兄弟)
    }
    return Nil; // 树空或没找到e的左兄弟
}

// 初始条件:二叉树T存在,e是T中某个结点
// 操作结果:返回e的右兄弟,若e是T的右孩子或无右兄弟,则返回空
TElemType RightSibling(BiTree T, TElemType e)
{
    TElemType a;
    BiTree p;

    if (T) // 非空树
    {
        a = Parent(T, e); // a为e的双亲
        p = Point(T, a); // p为指向结点a的指针
        // 既然返回右兄弟,那么它是左边的结点
        if (p->lchild && p->rchild && p->lchild->data == e)
            return p->rchild->data; // 返回p的右孩子(e的右兄弟)
    }
    return Nil; // 树空或没找到e的右兄弟
}

int main()
{
    int i;
    BiTree T;
    TElemType e1, e2;
    InitBiTree(&T);

    StrAssign(str, "ABDH#K###E##CFI###G#J##");
    CreateBiTree(&T);

    printf("构造空二叉树后,树空否? %d(1:是 0:否) 树的深度=%d\n", BiTreeEmpty(T), BiTreeDepth(T));
    e1 = Root(T);
    printf("二叉树的根为: %c\n", e1);

    printf("\n前序遍历二叉树:");
    PreOrderTraverse(T);
    printf("\n中序遍历二叉树:");
    InOrderTraverse(T);
    printf("\n后序遍历二叉树:");
    PostOrderTraverse(T);
    printf("\n层序遍历二叉树:");
    LevelOrderTraverse(T);
    printf("\nF的双亲结点为 = %c", Parent(T, 'F'));
    printf("\nK结点的指针为 = %p", Point(T, 'A'));
    printf("\nF的左孩子结点为 = %c", LeftChild(T, 'F'));
    printf("\nG的右孩子结点为 = %c", RightChild(T, 'G'));
    printf("\nE的左兄弟结点为 = %c", LeftSibling(T, 'E'));
    printf("\nB的右兄弟结点为 = %c", RightSibling(T, 'B'));


    ClearBiTree(&T);
    printf("\n清除二叉树后,树空否? %d(1:是 0:否) 树的深度=%d\n", BiTreeEmpty(T), BiTreeDepth(T));
    i = Root(T);
    if (!T)
        printf("树空,无根\n");

    return 0;
}