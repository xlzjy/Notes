#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define OK 1
#define ERROR 0

typedef int Status; // Status是函数的类型,状态代码
typedef char TElemType;
// Link==0表示指向左右孩子指针
// Thread==1表示指向前驱或后继的线索
typedef enum
{
    Link, Thread
} PointerTag;

// 二叉线索存储结点结构
typedef struct BiThrNode
{
    TElemType data; // 结点数据
    struct BiThrNode *lchild, *rchild; // 左右孩子指针
    PointerTag LTag; // 左标志
    PointerTag RTag; // 右标志
} BiThrNode, *BiThrTree;

TElemType Nil = '#'; // 字符型以#为空

/*
 按前序输入二叉线索树中结点的值,构造二叉线索树T
 0(整型)/#表示空结点
 */
Status CreateBiThrTree(BiThrTree *T)
{
    TElemType input; // 用户输入的字符
    scanf("%c", &input);

    // 当各层递归返回后,直到第一层,如果用户输入了#,那么这棵树创建完毕
    if (input == Nil) // 即input == '#
        *T = NULL; // 用户输入#代表当前子树T为空
    else
    {
        // 当前T开辟一个新的结点
        *T = (BiThrTree) malloc(sizeof(BiThrNode));
        if (!*T) // 内存申请失败
            exit(OVERFLOW);
        (*T)->data = input; // 生成根结点,将用户输入给当前树结点

        CreateBiThrTree(&(*T)->lchild); // 递归构造左子树
        if ((*T)->lchild) // 有左孩子
            (*T)->LTag = Link;

        CreateBiThrTree(&(*T)->rchild); // 递归构造右子树
        if ((*T)->rchild) // 有右孩子
            (*T)->RTag = Link;
    }

    return OK;
}

// 全局变量,始终指向刚刚访问过的结点
BiThrTree pre;

// 中序遍历进行中序线索化
// 线索化的过程就是在遍历中修改空指针的过程
void InThreading(BiThrTree p)
{
    if (p)
    {
        InThreading(p->lchild); // 递归左子树线索化

        if (!p->lchild) // 如果p没有左孩子
        {
            p->LTag = Thread; // 前驱线索
            p->lchild = pre; // 左孩子指针指向前驱
        }

        if (!pre->rchild) // 前驱没有右孩子
        {
            pre->RTag = Thread; // 后继线索
            pre->rchild = p; // 前驱右孩子指针指向后继(当前结点p)
        }
        pre = p; // 保持pre指向p的前驱
        InThreading(p->rchild); // 递归右子树线索化
    }
}
// ABD###CE#F###
// 中序遍历二叉树T,并将其中序线索化,Thrt指向头结点
Status InOrderThreading(BiThrTree *Thrt, BiThrTree T)
{
    *Thrt = (BiThrTree) malloc(sizeof(BiThrNode));
    if (!*Thrt)
        exit(OVERFLOW);

    /*
     * 建立头结点(初始化)
     * 若T树不空,则头结点的左孩子=根结点,且LTag=0
     * 头结点的右指针回指
     */
    (*Thrt)->LTag = Link;
    (*Thrt)->RTag = Thread;
    (*Thrt)->rchild = *Thrt; // 右指针回指
    if (!T) // 若二叉树空,则左指针回指
    {
        (*Thrt)->lchild = *Thrt;
    } else
    {
        (*Thrt)->lchild = T;
        pre = (*Thrt);
        InThreading(T); // 中序遍历进行中序线索化
        // 此时pre指向T的最后一个结点
        pre->rchild = *Thrt;
        pre->RTag = Thread; // 最后一个结点线索化
        (*Thrt)->rchild = pre;
    }

    return OK;
}

// 打印函数
Status visit(TElemType e)
{
    printf("%c", e);
    return OK;
}

// 中序遍历二叉线索树T(头结点)的非递归算法
Status InOrderTraverse_Thr(BiThrTree T)
{
    BiThrTree p;
    p = T->lchild; // p指向根结点,第一个结点
    // 空树或遍历结束时, p==T
    while (p != T)
    {
        // 当LTag==0是循环到中序序列的第一个结点
        while (p->LTag == Link)
            p = p->lchild;

        // 打印结点,若结点为空,则返回ERROR
        if (!visit(p->data))
            return ERROR;

        while (p->RTag == Thread && p->rchild != T)
        {
            p = p->rchild;
            visit(p->data); // 访问后继结点
        }

        p = p->rchild; // p进至其右子树根
    }

    return OK;
}

int main(void)
{
    BiThrTree H, T;
    printf("请按前序输入二叉树(如:'ABDH##I##EJ###CF##G##')\n");
    CreateBiThrTree(&T); /* 按前序产生二叉树 */
    InOrderThreading(&H, T); /* 中序遍历,并中序线索化二叉树 */
    printf("中序遍历(输出)二叉线索树:\n");
    InOrderTraverse_Thr(H); /* 中序遍历(输出)二叉线索树 */
    printf("\n");

    return 0;
}