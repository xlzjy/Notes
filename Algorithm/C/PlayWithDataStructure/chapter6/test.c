#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef int Status;
typedef int TElemType;

typedef struct BiTNode
{
    TElemType data;
    int bf;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

#define LH +1
#define EH 0
#define RH -1

// 右旋
void R_Rotate(BiTree *P)
{
    BiTree L;
    L = (*P)->lchild;
    (*P)->lchild = L->rchild;
    L->rchild = *P;
    *P = L;
}

// 左旋
void L_Rotate(BiTree *P)
{
    BiTree R;
    R = (*P)->rchild;
    (*P)->rchild = R->lchild;
    R->lchild = *P;
    *P = R;
}

void LeftBalance(BiTree *T)
{
    BiTree L, Lr;
    L = (*T)->lchild; // L指向T的左子树根结点
    switch (L->bf) // 检查T的左子树的平衡度,并作相应平衡处理
    {
        case LH: // 新结点插入在T的左孩子的左子树上,要作单右旋处理
            (*T)->bf = L->bf = EH;
            R_Rotate(T);
            break;
        case RH: // 新结点插入在T的左孩子的右子树上,要作双旋处理
            Lr = L->rchild;
            switch (Lr->bf) // 修改T及其左孩子的平衡因子
            {
                case LH:
                    (*T)->bf = RH; // 画图理解,详见双向旋转图先左后右图c
                    L->bf = EH;
                    break;
                case EH:
                    (*T)->bf = L->bf = EH;
                    break;
                case RH:
                    (*T)->bf = EH;
                    L->bf = LH;
                    break;
            }
            Lr->bf = EH;
            L_Rotate(&(*T)->lchild); // 对T的左子树作左旋平衡处理
            R_Rotate(T); // 对T作右旋平衡处理
    }
}

void RightBalance(BiTree *T)
{
    BiTree R, Rl;
    R = (*T)->rchild; // R指向T的右子树根结点

    switch (R->bf) // 检查T的右子树的平衡度,并作相应平衡调整
    {
        case RH: // 新结点插入在T的右孩子的右子树上,要作单左旋处理
            (*T)->bf = R->bf = EH;
            L_Rotate(T);
            break;
        case LH: // 新结点插入在T的右孩子的左子树上,要作双旋处理
            Rl = R->lchild;
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

                    break;
            }
            Rl->bf = EH;
            R_Rotate(&(*T)->rchild); // 对T的右子树作右旋平衡处理
            L_Rotate(T); // 对T作左旋平衡处理
    }
}

Status InsertAVL(BiTree *T, int e, Status *taller)
{
    if (!*T)
    {
        *T = (BiTree) malloc(sizeof(BiTNode));
        (*T)->data = e;
        (*T)->lchild = (*T)->rchild = NULL;
        (*T)->bf = EH;
        *taller = TRUE;
    } else
    {
        if (e == (*T)->data)
        {
            *taller = FALSE;
            return FALSE;
        }
        if (e < (*T)->data)
        {
            if (!InsertAVL(&(*T)->lchild, e, taller))
                return FALSE;

            if (*taller) // 已插入到T的左子树中且左子树长高
            {
                switch ((*T)->bf)
                {
                    case LH: // 原本左子树比右子树高,需要作左平衡处理
                        LeftBalance(T);
                        *taller = FALSE;
                        break;
                    case EH: // 原本左右子树等高,先因左子树增高而树增高
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
            if (InsertAVL(&(*T)->rchild, e, taller)) // 插入失败
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

int main(void)
{
    int i;
    int a[10] = {3, 2, 1, 4, 5, 6, 7, 10, 9, 8};
    BiTree T = NULL;
    Status taller;

    for (i = 0; i < 10; i++)
    {
        InsertAVL(&T, a[i], &taller);
    }

    return 0;
}