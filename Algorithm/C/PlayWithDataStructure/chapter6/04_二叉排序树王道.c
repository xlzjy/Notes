#include <stdio.h>
#include <stdlib.h>

// 二叉排序树结点
typedef struct BSTNode
{
    int key;
    struct BSTNode *lchild, *rchild;
} BSTNode, *BSTree;

/*
 * 查找思路:
 * 若树非空,目标值与根结点的值比较:
 * 若小于根结点,则在左子树上查找,否则在右子树上查找
 * 查找成功,返回结点指针;查找失败返回NULL
 */

// 在二叉排序树中查找值为key的结点(非递归实现)
// 最坏空间复杂度O(1)
BSTNode *BST_Search(BSTree T, int key)
{
    while (T != NULL && key != T->key) // 若树空或等于根结点值,则结束循环
    {
        if (key < T->key) // 小于,则在左子树上查找
            T = T->lchild;
        else  // 大于,则在右子树上查找
            T = T->rchild;
    }

    return T;
}

// 在二叉排序树中查找值为key的结点(递归实现)
// 最坏空间复杂度O(h),h为树的高度
BSTNode *BSTSearch(BSTree T, int key)
{
    if (T == NULL)
        return NULL; // 查找失败
    if (key == T->key)
        return T;
    else if (key < T->key)
        return BSTSearch(T->lchild, key); // 在左子树中找
    else
        return BSTSearch(T->rchild, key); // 在右子树中找
}

/*
 * 插入思路:
 * 若原二叉排序树为空,则直接插入结点;否则,若关键字k小于根结点值,
 * 则插入到左子树,若关键字k大于根结点值,则插入到右子树
 */

// 在二叉排序树插入关键字为k的新结点(递归实现)
int BST_Insert(BSTree *T, int k)
{
    if (*T == NULL) // 原树为空,新插入的结点为根结点
    {
        *T = (BSTree) malloc(sizeof(BSTNode));
        (*T)->key = k;
        (*T)->lchild = (*T)->rchild = NULL;
        return 1; // 返回1,插入成功
    } else if (k == (*T)->key) // 树中存在相同关键字的结点,插入失败
        return 0;
    else if (k < (*T)->key) // 插入到T的左子树
        return BST_Insert(&(*T)->lchild, k);
    else // 插入到T的右子树
        return BST_Insert(&(*T)->rchild, k);
}

// 在二叉排序树插入关键字为k的新结点(非递归实现)
int BSTInsert(BSTree *T, int k)
{
    BSTree p;
    if (*T == NULL) // 如果树为空
    {
        *T = (BSTree) malloc(sizeof(BSTNode));
        (*T)->key = k;
        (*T)->lchild = (*T)->rchild = NULL;
        return 1;
    } else // 如果树不空,有两种情况,里面有k或者里面没k
    {
        // p如果找到了,就是k所在结点;如果没找到就是NULL
        p = BST_Search(*T, k);
        if (p == NULL) // 如果没有k
        {
            *T = (BSTree) malloc(sizeof(BSTNode));
            (*T)->key = k;
            (*T)->lchild = (*T)->rchild = NULL;
            return 1;
        } else
        {
            return 0; // 有重复的k
        }
    }
}

