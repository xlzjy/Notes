#include <stdio.h>
#include <stdlib.h>
#include "BTree.h"

void Test2()
{
    int i, k;
    system("color 70");
    BTree t = NULL;
    Result s; // 设定查找结果

    while (1)
    {
        printf("此时的B树: \n");
        PrintBTree(t);
        printf("\n");
        printf("=============Operation Table=============\n");
        printf("   1.Init     2.Insert    3.Delete    \n");
        printf("   4.Destroy  5.Exit      \n");
        printf("=========================================\n");
        printf("Enter number to choose operation:_____\b\b\b");
        scanf("%d", &i);

        switch (i)
        {
            case 1:
            {
                InitBTree(&t);
                printf("InitBTree successfully.\n");
                break;
            }
            case 2:
            {
                printf("Enter number to InsertBTree: _____ \b\b\b");
                scanf("%d", &k);
                s = SearchBTree(t, k);
                InsertBTree(&t, s.i, k, s.pt);
                printf("InsertBTree successfully.\n");
                break;
            }
            case 3:
            {
                printf("Enter number to DeleteBTree: ____ \b\b\b");
                scanf("%d", &k);
//                BTreeDelete(&t, k);
                printf("\n");
                printf("DeleteBTree successfully.\n");
                break;
            }
            case 4:
            {
//                DestroyBTree(&t);
                printf("DestroyBTree successfully.\n");
                break;
            }
            case 5:
            {
                exit(0);
            }
            default:
                break;
        }
    }
}

int main(void)
{
    Test2();
    return 0;
}