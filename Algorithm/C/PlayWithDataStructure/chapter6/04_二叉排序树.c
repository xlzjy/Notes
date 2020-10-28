#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

typedef int Status; // Status是函数的类型

// 二叉树的二叉链表结点结构定义
typedef struct BiTNode
{
    int data; // 结点数据
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

/*
 * 递归查找二叉排序树T中是否存在key
 * 指针f指向T的双亲,其初始调用值为NULL
 * 若查找成功,则指针p指向该数据元素结点,并返回TRUE
 * 否则指针p指向查找路径上访问的"最后一个结点"并返回FALSE
 */
Status SearchBST(BiTree T, int key, BiTree f, BiTree *p)
{
    /*
     * SearchBST函数是一个可递归运行的函数,参数T是一个二叉链表
     * 当T指向根结点是,f的初值就为NULL
     * 最后的参数p是为了查找成功后可以得到查找到的结点位置
     */
    if (!T) // 查找不成功,用来判断当前二叉树是否达到叶子结点
    {
        *p = f;
        return FALSE;
    } else if (key == T->data) // 查找成功
    {
        *p = T;
        return TRUE;
    } else if (key < T->data)
        return SearchBST(T->lchild, key, T, p); // 在左子树中继续查找
    else
        return SearchBST(T->rchild, key, T, p); // 在右子树中继续查找
}

/*
 * 当二叉排序树T中不存在关键字等于key的数据元素时,
 * 插入key并返回TRUE,否则返回FALSE
 */
Status InsertBST(BiTree *T, int key)
{
    BiTree p, s;
    if (!SearchBST(*T, key, NULL, &p))
    {
        s = (BiTree) malloc(sizeof(BiTNode));
        if (!s)
            exit(OVERFLOW);
        s->data = key;
        s->lchild = s->rchild = NULL;

        if (!p)
        {
            *T = s; // 插入s为新的根结点
        } else if (key < p->data)
            p->lchild = s; // 插入s为左孩子
        else
            p->rchild = s; // 插入s为右孩子
        return TRUE;
    } else
        return FALSE; // 树中已有关键字相同的结点,不再插入
}

// 从二叉排序树中删除结点p,并重接它的左或右子树
Status Delete(BiTree *p)
{
    BiTree q, s;
    if ((*p)->rchild == NULL) // 右子树空则只需要重接它的左子树(待删结点是叶子也走此分支)
    {
        q = *p;
        *p = (*p)->lchild;
        free(q);
    } else if ((*p)->lchild == NULL) // 只需重接它的右子树
    {
        q = *p;
        *p = (*p)->rchild;
        free(q);
    } else // 左右子树均不空
    {
        q = *p;
        s = (*p)->lchild;
        while (s->rchild) // 转左,然后向右到尽头(找待删结点的前驱)
        {
            q = s;
            s = s->rchild;
        }
        // 找到右孩子后,s就是最靠近p的结点
        (*p)->data = s->data; // s指向被删除结点的直接前驱(将被删除结点前驱的值取代被删除结点的值)

        if (q != *p)
            q->rchild = s->lchild; // 重接q的右子树
        else
            q->lchild = s->lchild; // 重接q的左子树
        free(s);
    }
    return TRUE;
}

/*
 * 若二叉排序T中存在关键字等于key的数据元素时,则删除该数据元素结点
 * 并返回TRUE;否则返回FALSE
 * 删除结点三种情况:
 * 1.叶子结点
 * 2.仅有左或右子树的结点
 * 3.左右子树都有的结点
 */
Status DeleteBST(BiTree *T, int key)
{
    if (!*T) // 不存在关键字等于key的数据元素
        return FALSE;
    else
    {
        if (key == (*T)->data) // 找到关键字等于key的数据元素
            return Delete(T);
        else if (key < (*T)->data)
            return DeleteBST(&(*T)->lchild, key);
        else
            return DeleteBST(&(*T)->rchild, key);
    }
}


int main(void)
{
    int i;
    int a[13] = {62, 88, 58, 47, 39, 38, 36, 35, 73, 51, 99, 37, 93};
    BiTree T = NULL;

    for (i = 0; i < 13; i++)
    {
        InsertBST(&T, a[i]);
    }

    DeleteBST(&T, 93);
    DeleteBST(&T, 47);

    return 0;
}