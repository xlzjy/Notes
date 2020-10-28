#include <stdio.h>

typedef char ElemType;

// 线索二叉树结点
// tag == 0,表示指针指向孩子
// tag == 1,表示指针是线索
typedef struct ThreadNode
{
    ElemType data;
    struct ThreadNode *lchild, *rchild;
    int ltag, rtag; // 左右线索标志
} ThreadNode, *ThreadTree;

// 全局变量pre,指向当前访问结点的前驱
ThreadNode *pre = NULL;

void visitIn(ThreadNode *q)
{
    if (q->lchild == NULL) // 左子树为空,建立前驱线索
    {
        q->lchild = pre;
        q->ltag = 1;
    }
    if (pre != NULL && pre->rchild == NULL)
    {
        pre->rchild = q; // 建立前驱结点的后继线索
        pre->rtag = 1;
    }
    pre = q;
}

// 中序遍历二叉树,一边遍历一边线索化
void InThread(ThreadTree T)
{
    if (T != NULL)
    {
        InThread(T->lchild); // 中序遍历左子树
        visitIn(T); // 访问根结点
        InThread(T->rchild); // 中序遍历右子树
    }
}

// 中序线索化二叉树T
void CreateInThread(ThreadTree T)
{
    pre = NULL; // pre初始为NULL

    // 非空二叉树才能线索化
    if (T != NULL)
    {
        InThread(T); // 中序线索化二叉树
        if (pre->rchild == NULL)
            pre->rtag = 1; // 处理遍历的最后一个结点
    }
}

void visitPre(ThreadNode *q)
{
    if (q->lchild == NULL) // 左子树为空,建立前驱线索
    {
        q->lchild = pre;
        q->ltag = 1;
    }

    if (pre != NULL && pre->rchild == NULL)
    {
        pre->rchild = q; // 建立前驱结点的后继线索
        pre->rtag = 1;
    }

    pre = q;
}

// 先序遍历二叉树,一边遍历一边线索化
void PreThread(ThreadTree T)
{
    if (T != NULL)
    {
        visitPre(T); // 先处理根结点
        if (T->ltag == 0) // lchild不是前驱线索
            PreThread(T->lchild);
        PreThread(T->rchild);
    }
}

// 先序线索化二叉树T
void CreatePreThread(ThreadTree T)
{
    pre = NULL; // pre初始为NULL
    if (T != NULL) // 非空二叉树才能线索化
    {
        PreThread(T); // 先序线索化二叉树
        if (pre->rchild == NULL)
            pre->rtag = 1; // 处理遍历的最后一个结点
    }
}

void visitPost(ThreadNode *q)
{
    if (q->lchild == NULL) // 左子树为空,建立前驱线索
    {
        q->lchild = pre;
        q->ltag = 1;
    }
    if (pre != NULL && pre->rchild == NULL)
    {
        pre->rchild = q; // 建立前驱结点的后继线索
        pre->rtag = 1;
    }
    pre = q;
}

// 后序遍历二叉树,一边遍历一边线索化
void PostThread(ThreadTree T)
{
    if (T != NULL)
    {
        PostThread(T->lchild); // 后序遍历左子树
        PostThread(T->rchild); // 后序遍历右子树
        visitPost(T); // 访问根结点
    }
}

// 后序线索化二叉树T
void CreatePostThread(ThreadTree T)
{
    pre = NULL; // pre初始为NULL
    if (T != NULL) // 非空二叉树才能线索化
    {
        PostThread(T); // 后序线索化二叉树
        if (pre->rchild == NULL)
            pre->rtag = 1; // 处理遍历的最后一个结点
    }
}

/* ********************************************************** */
// 找到以p为根的子树中,第一个被中序遍历的结点
ThreadNode *Firstnode(ThreadNode *p)
{
    // 循环找到最左下的结点(不一定是叶子结点)
    while (p->ltag == 0) p = p->lchild;
    return p;
}

// 在中序线索二叉树中找到结点p的后继结点
ThreadNode *Nextnode(ThreadNode *p)
{
    // 右子树中最左下结点
    if (p->rtag == 0)
        return Firstnode(p->rchild);
    else
        return p->rchild; // rtag==1直接返回后继线索
}

// 通过Firstnode, Nextnode可以很方便对中序线索二叉树进行中序遍历
// 利用线索实现的非递归算法
// 空间复杂度为O(1)
void Inorder(ThreadNode *T)
{
    for (ThreadTree *p = Firstnode(T); p != NULL; p = Nextnode(p))
    {
        // 然后访问p
        // visit (p);
    }
}

// 找到以p为根的子树中,最后一个被中序遍历的结点
ThreadNode *Lastnode(ThreadNode *p)
{
    // 循环找到最右下结点(不一定是叶子结点)
    while (p->rtag == 0)
        p = p->rchild;
    return p;
}

// 在中序线索二叉树中找到结点p的前驱结点
ThreadNode *Prenode(ThreadNode *p)
{
    // 左子树中的最右下结点
    if (p->ltag == 0)
        return Lastnode(p->lchild);
    else
        return p->lchild; // ltag==1直接返回前驱线索
}

// 对中序线索二叉树进行逆向中序遍历
void RevInorder(ThreadNode *T)
{
    for (ThreadNode *p = Lastnode(T); p != NULL; p = Prenode(p))
    {
        // visit(p);
    }
}

