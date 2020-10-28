#include <stdio.h>

typedef char ElemType;

// 线索二叉树结点
typedef struct BiTNode
{
    ElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

// 辅助全局变量,用于查找结点p的前驱
BiTNode *p; // p指向目标结点
BiTNode *pre = NULL; // 指向当前访问结点的前驱
BiTNode *final = NULL; // 用于记录最终结果

// 访问结点q
void visit(BiTNode *q)
{
    if (q == p) // 当前访问的结点刚好是结点p
        final = pre; // 找到p的前驱
    else
        pre = q; // pre指向当前访问的结点
}


// 中序遍历
void InOrderFindPre(BiTree T)
{
    if (T != NULL)
    {
        InOrderFindPre(T->lchild); // 递归遍历左子树
        visit(T);
        InOrderFindPre(T->rchild); // 递归遍历右子树
    }
}


