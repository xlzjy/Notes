#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * 平衡二叉排序树查找时间复杂度O(logn)
 * 插入和删除也为O(logn)
 */

#define TRUE 1
#define FALSE 0

typedef int Status; // 函数的返回状态
typedef int TElemType;

// 二叉树的二叉链表结点结构定义
typedef struct BiTNode // 结点结构
{
    TElemType data; // 结点数据
    int bf; // 结点的平衡因子
    struct BiTNode *lchild, *rchild; // 左右孩子指针
} BiTNode, *BiTree;

/*
 * 对以P为根的二叉排序树作右旋处理
 * 处理之后P指向新的树根结点,即旋转处理之前的左子树的根结点
 */
void R_Rotate(BiTree *P)
{
    BiTree L; // L -> Left
    L = (*P)->lchild; // L指向P的左子树根结点
    (*P)->lchild = L->rchild; // L的右子树挂接为P的左子树
    L->rchild = *P;
    *P = L;
}

/*
 * 对以p为根的二叉排序树左旋处理
 * 处理之后P指向新的树根结点,即旋转处理之前的右子树的根结点0
 */
void L_Rotate(BiTree *P)
{
    BiTree R; // R -> Right
    R = (*P)->rchild; // R指向P的右子树根结点
    (*P)->rchild = R->lchild; // R的左子树挂接为P的右子树
    R->lchild = *P;
    *P = R; // P指向新的根结点
}

#define LH +1 /* 左高 Left High */
#define EH 0  /* 等高 Equal Height*/
#define RH -1 /* 右高 Right High*/

/*
 * 对以指针T所指结点为根的二叉树作左平衡旋转处理
 * 本算法结束时,指针T指向新的根结点
 * 函数被调用,传入一个需要调整平衡性的子树T.由于LeftBalance函数被调用时,其实是已经确认当前子树
 * 是不平衡状态,且左子树的高度大于右子树的高度.即此时T的根结点是平衡因子大于1的数
 */
void LeftBalance(BiTree *T)
{ // 左平衡只有左边重的时候才会使用
    BiTree L, Lr; // L左子树,Lr左子树的右子树
    L = (*T)->lchild; // L指向T的左子树根结点
    switch (L->bf) // 检查T的左子树的平衡度,并作相应平衡处理
    {

        case LH: // 新结点插入在T的左孩子的左子树上,要作单右旋处理
            /*
             * 当L的平衡因子为LH,表明它与根结点的BF值符号相同,因此将根结点与L的平衡因子改为0并进行右旋操作
             */
            (*T)->bf = L->bf = EH;
            R_Rotate(T);
            break;

        case RH: // 新结点插入在T的左孩子的右子树上,要作双旋处理
            /*
             * 当L的平衡因子为RH,表明它与根结点的BF值符号相反,此时需要左双旋处理
             */
            Lr = L->rchild;
            switch (Lr->bf) // 修改T及其左孩子的平衡因子
            {
                case LH:
                    (*T)->bf = RH;
                    L->bf = EH;
                    break;
                case EH: // ?
                    (*T)->bf = L->bf = EH;
                    break;
                case RH:
                    (*T)->bf = EH;
                    L->bf = LH;
                    break;
            }
            Lr->bf = EH; // 不管怎么样,Lr结点经过旋转后会变成当前子树的根结点,此时是平衡的,所以Lr->bf = EH
            L_Rotate(&(*T)->lchild); // 对T的左子树作左旋平衡处理
            R_Rotate(T); // 对T作右旋平衡处理
    }
}

/*
 * 对以指针T所指结点为根的二叉树作左平衡旋转处理
 * 本算法结束时,指针T指向新的根结点
 */
void RightBalance(BiTree *T)
{ // 右平衡只有右边重的时候才会使用
    BiTree R, Rl;
    R = (*T)->rchild; // R指向T的右子树根结点
    switch (R->bf) // 检查T的右子树的平衡度,并作相应平衡处理
    {
        case RH: // 新结点插入在T的右孩子的右子树上,要作单左旋处理
            (*T)->bf = R->bf = EH;
            L_Rotate(T);
            break;
        case LH: // 新结点插入在T的右孩子的左子树上,要作双旋处理
            Rl = R->lchild; // Rl指向T的右孩子的左子树根
            switch (Rl->bf) // 修改T及右孩子的平衡因子
            {
                case RH:
                    (*T)->bf = LH;
                    R->bf = EH;
                    break;
                case EH:
                    (*T)->bf = R->bf = EH;
                    break;
                case LH:
                    (*T)->bf = EH;
                    R->bf = RH;
                    break;
            }
            Rl->bf = EH;
            R_Rotate(&(*T)->rchild); // 对T的右子树作右旋平衡处理
            L_Rotate(T); // 对T作左旋平衡处理
    }
}

/*
 * 若在平衡的二叉排序树T中不存在和e右相同关键字的结点,则插入一个数据元素为e的新结点
 * 并返回1,否则返回0.若因插入而使二叉排序树失去平衡,则作平衡旋转处理,布尔变量taller
 * 反映T长高与否
 */
/*
 * 伪代码
 * 如果找不到含e的子树,那么就新建一个结点,同时结点值为新插入的值,结点的左右孩子应该为NULL,平衡因子为0,同时树长高,因此置taller为TRUE
 * 否则三种情况
 *    1.找到了结点值为e的结点,那就返回错误
 *    2.若e<当前子树的结点值,则进入它的左子树继续进行插入判断操作
 *    3.若e>当前子树的结点值,则进入它的右子树继续进行插入判断操作
 */
Status InsertAVL(BiTree *T, int e, Status *taller)
{
    if (!*T) // 如果找不到e,则插入
    {
        // 插入新结点,树长高,置taller为TRUE
        *T = (BiTree) malloc(sizeof(BiTNode));
        (*T)->data = e;
        (*T)->lchild = (*T)->rchild = NULL;
        (*T)->bf = EH;
        *taller = TRUE;

    } else
    {
        // 树中已存在和e有相同关键字的结点则不再插入
        if (e == (*T)->data)
        {
            *taller = FALSE;
            return FALSE;
        }

        // 当新结点e小于T的根结点值时,应继续在T的左子树中进行搜索,如果在最后一层找到e与元素相等,那么插入失败
        if (e < (*T)->data)
        {
            // 递归调用本函数,直到找到则返回false,否则说明插入结点成功
            if (!InsertAVL(&(*T)->lchild, e, taller)) // 未插入
                return FALSE;

            /*
             * 当taller为TRUE时,说明插入了结点,此时需要判断T的平衡因子,如果是LH,说明左子树高于右子树,需要调用LeftBalance函数进行左平衡旋转处理
             * 如果是0或-1,则说明新插入结点没有让整棵二叉排序树失去平衡性,只需修改相关的BF值即可
             */
            if (*taller) // 已插入到T的左子树中且左子树长高
            {
                switch ((*T)->bf) // 检查T的平衡度
                {
                    case LH: // 原本左子树比右子树高,需要作左平衡处理
                        LeftBalance(T);
                        *taller = FALSE;
                        break;
                    case EH: // 原本左右子树等高,现因左子树增高而树增高
                        (*T)->bf = LH;
                        *taller = TRUE;
                        break;
                    case RH: // 原本右子树比左子树高,现左右子树等高
                        (*T)->bf = EH;
                        *taller = FALSE;
                        break;
                }
            }
        } else
        {
            // 应继续在T的右子树中进行搜索
            if (!InsertAVL(&(*T)->rchild, e, taller)) // 未插入
                return FALSE;

            if (*taller) // 已插入到T的右子树且右子树长高
            {
                switch ((*T)->bf) // 检查T的平衡度
                {
                    case LH: // 原本左子树比右子树高,现左右子树等高
                        (*T)->bf = EH;
                        *taller = FALSE;
                        break;
                    case EH: // 原本左右子树等高,现因右子树增高而树增高
                        (*T)->bf = RH;
                        *taller = TRUE;
                        break;
                    case RH: // 原本右子树比左子树高,需要作右平衡处理
                        RightBalance(T);
                        *taller = FALSE;
                        break;
                }

            }

        }
    }

    return TRUE;
}

// 判断现有平衡二叉树中是否已经具有数据域为e的结点
bool FindNode(BiTree T, TElemType e, BiTree *pos)
{
    BiTree p = T;
    *pos = NULL;

    while (p)
    {
        if (p->data == e)
        {
            // 找到结点,pos指向该结点并返回true
            *pos = p;
            return true;
        } else if (e < p->data)
        {
            p = p->lchild;
        } else
        {
            p = p->rchild;
        }
    }
    return false;
}

// 中序遍历平衡二叉树
void InOrderTraverse(BiTree T)
{
    if (T->lchild)
        InOrderTraverse(T->lchild);
    printf("%d ", T->data);
    if (T->rchild)
        InOrderTraverse(T->rchild);
}

int main(void)
{
    int i;
    int a[10] = {3, 2, 1, 4, 5, 6, 7, 10, 9, 8};
    BiTree T = NULL;
    BiTree pos;
    Status taller;

    for (i = 0; i < 10; i++)
    {
        InsertAVL(&T, a[i], &taller);
    }

    // 中序遍历输出
    InOrderTraverse(T);
    printf("\n");

    // 判断平衡二叉树中是否含有数据域为8的数据
    if (FindNode(T, 8, &pos))
        printf("%d\n", pos->data);
    else
        printf("Not find this Node\n");

    // 判断平衡二叉树中是否含有数据域为11的数据
    if (FindNode(T, 11, &pos))
        printf("%d\n", pos->data);
    else
        printf("Not find this Node\n");

    return 0;
}
