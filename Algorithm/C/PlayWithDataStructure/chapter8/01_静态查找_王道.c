#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int ElemType;

/* 顺序查找部分 */
typedef struct // 查找表的数据结构(这里采用顺序表)
{
    ElemType *elem; // 动态数组基址
    int TableLen; // 表的长度
} SSTable_Seq;

// 顺序查找方法1
int Search_Seq1(SSTable_Seq ST, ElemType key)
{
    int i;
    for (i = 0; i < ST.TableLen && ST.elem[i] != key; i++);
    // 查找成功,则返回元素下标;查找失败,则返回-1
    return i == ST.TableLen ? -1 : i;
}

// 顺序查找方法2
int Search_Seq2(SSTable_Seq ST, ElemType key)
{
    ST.elem[0] = key; // 0号位置存哨兵
    // 优点:无需判断是否越界,效率更高,因为从尾向0递减,到0号元素一定会找到,就会退出循环
    int i;

    for (i = ST.TableLen; ST.elem[i] != key; i--); // 从后往前找
    return i; // 查找成功,则返回元素下标;查找失败,则返回0
}

void Search_Seq_Test()
{
    SSTable_Seq ssTable;
    ssTable.TableLen = 5;
    ssTable.elem = (int *) malloc(sizeof(int) * ssTable.TableLen);

    printf("非有序数组: ");
    ssTable.elem[0] = 20;
    ssTable.elem[1] = 25;
    ssTable.elem[2] = 5;
    ssTable.elem[3] = 15;
    ssTable.elem[4] = 7;

    printf("找到数字7的索引为: %d\n", Search_Seq1(ssTable, 7));
    printf("找到数字7的索引为: %d\n", Search_Seq2(ssTable, 7));
}

/* 折半查找部分 */
typedef struct // 查找表的数据结构(顺序表)
{
    ElemType *elem; // 动态数组基址
    int TableLen; // 表的长度
} SSTable_Half;

// 折半查找,又称二分查找,仅适用于有序的顺序表,因为顺序表用于随机访问的特性
// 而链表没有随机访问特性,所以不能通过链表来实现折半查找(即链表找到mid元素只能从头一个一个往后遍历)
// 折半查找
int Binary_Search(SSTable_Half L, ElemType key)
{
    int low = 0, high = L.TableLen - 1, mid;
    while (low <= high)
    {
        mid = (low + high) / 2; // 取中间位置
        if (L.elem[mid] == key)
            return mid; // 查找成功则返回所在位置
        else if (L.elem[mid] > key)
            high = mid - 1; // 从前半部分继续查找
        else
            low = mid + 1; // 从后半部分继续查找
    }

    return -1; // 查找失败,返回-1
}

/* 分块查找部分 */
// 索引表,索引表中保存每个分块的最大关键字和分块的存储区间
typedef struct
{
    ElemType maxValue;
    int low, high;
} Index;

// 顺序表存储实际元素
ElemType List[100];

int main(void)
{
    Search_Seq_Test();
    return 0;
}