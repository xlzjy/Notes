#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 10 /* 用于要排序数组个数最大值,可根据需要修改 */

typedef int Status;

typedef struct
{
//    int r[100000 + 1];
    int r[MAXSIZE + 1]; /* 用于存储要排序数组,r[0]用作哨兵或临时变量 */
    int length; /* 用于记录顺序表的长度 */
} SqList;

/* 交换L中数组r的下标为i和j的值 */
void swap(SqList *L, int i, int j)
{
    int temp = L->r[i];
    L->r[i] = L->r[j];
    L->r[j] = temp;
}

/* 打印 */
void print(SqList L)
{
    int i;
    for (i = 1; i < L.length; i++)
        printf("%d,", L.r[i]);
    printf("%d", L.r[i]);
    printf("\n");
}

/*
 * 冒泡排序(Bubble Sort)基本思想
 * 两两比较相邻记录的关键字,如果反序则交换,直到没有反序的记录为止
 */
/* 对顺序表L作交换排序(冒泡排序初级版) */
void BubbleSort0(SqList *L)
{
    int i, j;
    for (i = 1; i < L->length; i++)
    { /* i=1开始,即顺序表第1个元素,第0个元素不放值,一共要排n-1次 */

        for (j = i + 1; j <= L->length; j++)
        { /* i前面的元素已经排好,每次只需要从i+1的元素到末尾分别与第i个元素比较 */
            if (L->r[i] > L->r[j])
            { /* 如果前面元素比后面元素大,那么交换 */
                swap(L, i, j); /* 最终从小到大排序 */
            }
        }
    }
}

/* 对顺序表L作冒泡排序 */
void BubbleSort(SqList *L)
{
    int i, j;
    for (i = 1; i < L->length; i++)
    {
        for (j = L->length - 1; j >= i; j--) /* 注意j是从后往前循环 */
        {
            if (L->r[j] > L->r[j + 1]) /* 若前者大于后者(改进) */
            {
                swap(L, j, j + 1); /* 交换L->r[j]与L->r[j+1]的值 */
            }
        }
    }
}

/* 对顺序表L作改进冒泡算法(改进:可以避免因已经有序的情况下的无意义循环判断) */
void BubbleSort2(SqList *L)
{
    int i, j;
    Status flag = TRUE; /* flag用来作为标记 */

    for (i = 1; i < L->length && flag; i++) /* 若flag为TRUE则退出循环 */
    {
        flag = FALSE; /* 初始为FALSE */
        for (j = L->length - 1; j >= i; j--)
        {
            if (L->r[j] > L->r[j + 1])
            {
                swap(L, j, j + 1); /* 交换L->r[j]与L->r[j+1]的值 */
                flag = TRUE; /* 如果有数据交换,则flag为TRUE */
            }
            /* 如果循环内没有发生交换,那么flag始终为TRUE,同时说明剩余元素已经有序,排序结束 */
        }
    }
}

/*
 * 简单选择排序(Simple Selection Sort)
 * 简单选择排序就是通过n-i次关键字间的比较,从n-i+1个记录中选出最小的记录,并和第i(1 <= i <= n)个记录交换之
 */
void SelectSort(SqList *L)
{
    int i, j, min;

    for (i = 1; i < L->length; i++)
    {
        min = i; /* 将当前下标定义为最小值下标 */

        for (j = i + 1; j <= L->length; j++) /* 循环之后的数据 */
        {
            if (L->r[min] > L->r[j]) /* 如果有小于当前最小值的关键字 */
                min = j; /* 将此关键字的下标赋值给min */
        }

        if (i != min) /* 若min不等于i,说明找到最小值,交换 */
            swap(L, i, min); /* 交换L->r[i]与L->r[min]的值 */
    }
}

/*
 * 直接插入排序(Straight Insertion Sort)
 * 将一个记录插入到已经排好序的有序表中,从而得到一个新的、记录数增1的有序表
 */
void InsertSort(SqList *L)
{
    int i, j;

    for (i = 2; i <= L->length; i++) /* 依次将2～n的元素插入到已排序序列 */
    {
        if (L->r[i] < L->r[i - 1]) /* 若当前关键码小于其前驱,需将L->r[i]插入有序子表 */
        {
            L->r[0] = L->r[i]; /* 设置哨兵 */

            for (j = i - 1; L->r[j] > L->r[0]; j--) /* 从后向前查找待插入位置 */
                L->r[j + 1] = L->r[j]; /* 记录后移 */

            L->r[j + 1] = L->r[0]; /* 插入到正确位置 */
        }
    }
}

/*
 * 折半插入排序
 * 先用折半查找找到应该插入的位置,再移动元素
 */
void InsertSort_Half(SqList *L)
{
    int i, j, low, high, mid;

    for (i = 2; i <= L->length; i++) /* 依次将L[2]~L[n]插入前面的已排序序列 */
    {
        L->r[0] = L->r[i]; /* 将A[i]暂存到A[0] */
        low = 1;
        high = i - 1; /* 设定折半查找的范围 */

        while (low <= high) /* 折半查找(默认递增有序) */
        {
            mid = (low + high) / 2; /* 取中间点 */
            if (L->r[mid] > L->r[0]) /* 保证稳定性 */
                high = mid - 1; /* 查找左半子表 */
            else
                low = mid + 1; /* 查找右半子表 */
        }

        for (j = i - 1; j >= high + 1; j--) /* high+1为比插入元素大的第一个元素 */
            L->r[j + 1] = L->r[j]; /* 统一后移元素,空出插入位置 */

        L->r[high + 1] = L->r[0]; /* 插入操作 */
    }
}

/*
 * 希尔排序
 * 先追求表中元素部分有序,再逐渐逼近全局有序
 * 先将待排序表分割成若干形如L[i, i+d, i+2d, ..., i+kd]的"特殊"子表,对各个子表
 * 分别进行直接插入排序,缩小增量d,重复上述过程,直到d=1为止
 */
/* 对顺序表L作希尔排序(王道) */
void ShellSort1(SqList *L)
{
    int d, i, j, k = 0; /* d为增量 */
    /* A[0]只是暂存单元,不是哨兵,当j<=0时,插入位置已到 */
    for (d = L->length / 2; d >= 1; d = d / 2) /* 步长变化 */
    {
        /*
         * 每次轮流处理不同的子表,当然也可以对处于同一个子表的元素一个一个处理
         * 完之后再切换到下一个列表.
         * 其中d+1为当前子表中的第二个元素,不需要从第一个元素开始,直接从第二个
         * 元素和第一个元素比较开始.
         */
        for (i = d + 1; i <= L->length; i++)
        {
            if (L->r[i] < L->r[i - d]) /* 需要将A[i]插入有序增量子表 */
            {
                L->r[0] = L->r[i]; /* 暂存在A[0] */
                for (j = i - d; j > 0 && L->r[0] < L->r[j]; j -= d)
                { /* 在当前子列表中检查当前这个元素前面的元素是否比这个元素大 */
                    L->r[j + d] = L->r[j]; /* 记录右移,查找插入的位置 */
                }
                L->r[j + d] = L->r[0]; /* 插入 */
            }
        }
        printf("   第%d趟排序结果为: ", ++k);
        print(*L);
    }
}

/* 对顺序表L作希尔排序(大话) */
void ShellSort2(SqList *L)
{
    int i, j, k = 0;
    int increment = L->length;

    do
    {
        increment = increment / 3 + 1; /* 增量序列 */
        for (i = increment + 1; i <= L->length; i++)
        {
            if (L->r[i] < L->r[i - increment]) /* 需将L->r[i]插入有序增量子表 */
            {
                L->r[0] = L->r[i]; /* 暂存在L->r[0] */
                for (j = i - increment; j > 0 && L->r[0] < L->r[j]; j -= increment)
                    L->r[j + increment] = L->r[j]; /* 记录后移,查找插入位置 */
                L->r[j + increment] = L->r[0]; /* 插入 */
            }
        }
        printf("   第%d趟排序结果为: ", ++k);
        print(*L);
    } while (increment > 1);
}

/* **********************堆排序********************** */
/*
 * 堆是具有下列性质的完全二叉树:每个节点的值都大于或等于其左右孩子节点的值
 * 称为大顶堆;或者每个节点的值都小于或等于其左右孩子的值,称为小顶堆
 * 堆排序(Heap Sort)
 * 将待排序的序列构造成一个大顶堆.此时,整个序列的最大值就是堆顶的根节点.
 * 将它移走(起始就是将其与堆数据的末尾元素交换,此时末尾元素就是最大值),
 * 然后将剩余的n-1各序列重新构造成一个堆,这样就会得到n各元素中的次大值.
 * 如此反复执行,便能得到一个有序序列了.
 */
/* 已知L->r[s...m]中记录的关键字除L->r[s]之外满足堆的定义 */
/* 本函数调整L->r[s]的关键字,使L->r[s...m]称为一个大顶堆 */
void HeapAdjust(SqList *L, int s, int m)
{
    int j;
    L->r[0] = L->r[s]; /* 用L[0]暂存元素 */
    for (j = 2 * s; j <= m; j *= 2) /* 沿关键字较大的孩子节点向下筛选 */
    {
        if (j < m && L->r[j] < L->r[j + 1])
            j++; /* j为关键字中较大的记录的下标 */
        if (L->r[0] >= L->r[j])
            break; /* rc应插入在位置s上 */
        else
        {
            L->r[s] = L->r[j];
            s = j;
        }
    }
    L->r[s] = L->r[0]; /* 插入 */
}

/* 对顺序表L进行堆排序 */
void HeapSort(SqList *L)
{
    int i;
    /* 第一个for循环将现在待排序序列构建成一个大顶堆,从分支节点的最后一个节点开始建堆 */
    for (i = L->length / 2; i > 0; i--) /* 把L中的r构建成一个大顶堆 */
        HeapAdjust(L, i, L->length);

    /* 第二个for循环逐步将每个最大值的根节点与末尾元素交换,并且再调整其成为大顶堆 */
    for (i = L->length; i > 1; i--)
    {
        swap(L, 1, i); /* 将堆顶记录和当前未经排序子序列的最后一个记录交换 */
        HeapAdjust(L, 1, i - 1); /* 将L->r[1...i-1]重新调整为大顶堆 */
    }
}
/* ************************************************* */

/* **********************归并排序********************* */
/*
 * 归并排序(Mergeing Sort)
 * 利用归并的思想实现:假设初始序列含有n个记录,则可以看成是n个有序的子序列,
 * 每个子序列的长度为1,然后两两归并,得到[n/2]([x]表示不小于x的最小整数)个长度
 * 为2或1的有序子序列;再两两归并,....,如此重复,直至得到一个长度为n的有序序列为止,
 * 这种排序方法称为2路归并排序
 */
/* 将有序的SR[i...m]和SR[m+1...n]归并为有序的TR[i...n] */
void Merge(const int SR[], int TR[], int i, int m, int n)
{
    int j, k, l;
    for (j = m + 1, k = i; i <= m && j <= n; k++) /* 将SR中记录由小到大归并入TR */
    { /* 最后i或j超出范围就退出循环 */
        if (SR[i] < SR[j])
            TR[k] = SR[i++];
        else
            TR[k] = SR[j++];
    }

    if (i <= m) /* 左边还没归并完 */
    {
        for (l = 0; l <= m - i; l++)
            TR[k + l] = SR[i + l]; /* 将剩余的SR[i...m]赋值到TR */
    }
    if (j <= n) /* 右边还没归并完 */
    {
        for (l = 0; l <= n - j; l++)
            TR[k + l] = SR[j + l]; /* 将剩余的SR[j...n]复制到TR */
    }
}

/* 递归法 */
/* 将SR[s...t]归并排序为TR1[s...t] */
void MSort(int SR[], int TR1[], int s, int t)
{
    int m;
    int TR2[MAXSIZE + 1]; /* 辅助数组TR2 */
    if (s == t) /* 如果归并中只剩一个元素,那么它就已经排好序了 */
        TR1[s] = SR[s];
    else
    {
        m = (s + t) / 2; /* 将SR[s...t]平分为SR[s...m]和SR[m+1...t] */
        MSort(SR, TR2, s, m); /* 递归将SR[s...m]归并为有序的TR2[s...m] */
        MSort(SR, TR2, m + 1, t); /* 递归将SR[m+1...t]归并为有序TR2[m+1...t] */
        Merge(TR2, TR1, s, m, t); /* 将TR2[s...m]和TR2[m+1...t]归并到TR1[s...t] */
    }
}

/* 对顺序表L作归并排序 */
void MergeSort(SqList *L)
{
    MSort(L->r, L->r, 1, L->length);
}

/* 将SR[]中相邻长度为s的子序列两两归并到TR[] */
void MergePass(int SR[], int TR[], int s, int n)
{
    int i = 1; /* 从第一个元素开始,合并大小为s的相邻2段子数组 */
    int j;

    /* i+2*s-1要小于等于数组长度,也就是说未合并的元素个数要大于2*s */
    while (i + 2 * s - 1 <= n)
    {
        /* 两两归并,合并大小为s的相邻2段子数组 */
        Merge(SR, TR, i, i + s - 1, i + 2 * s - 1);
        i = i + 2 * s;
    } /* 此循环执行的次数: L.length / (2*s) */

    if (i + s - 1 < n) /* 归并最后两个序列 */
        Merge(SR, TR, i, i + s - 1, n);
    else /* 若最后只剩下单个子序列 */
        for (j = i; j <= n; j++)
            TR[j] = SR[j];
}

/* 对顺序表L作归并非递归排序 */
void MergeSort2(SqList *L)
{
    int *TR = (int *) malloc(L->length * sizeof(int)); /* 申请额外空间 */
    int k = 1;
    while (k < L->length) /* 这里不能为<= */
    {
        MergePass(L->r, TR, k, L->length); /* 将数组L->r 合并到 TR数组 */
        k = 2 * k; /* 子序列长度加倍 */
        MergePass(TR, L->r, k, L->length); /* 将数组TR 合并到 L->r */
        k = 2 * k; /* 子序列长度加倍 */
        /* 交替合并 */
    }
}
/* ************************************************* */

/* **********************快速排序********************* */
/*
 * 快速排序(Quick Sort)
 * 通过一趟排序将待排记录分割成独立的两部分,其中一部分记录的关键字均比另一部分记录的关键字小,
 * 则可分别对这两部分记录继续进行排序,以达到整个序列有序的目的
 */
/* 交换顺序表L中子表的记录,使枢轴记录到位,并返回其所在的位置 */
/* 此时在它之前(后)的记录均不大(小)于它 */
int Partition(SqList *L, int low, int high)
{
    int pivotkey;

    pivotkey = L->r[low]; /* 用子表的第一个记录作枢轴记录 */
    while (low < high) /* 从表的两端交替向中间扫描 */
    {
        while (low < high && L->r[high] >= pivotkey)
            high--;
        swap(L, low, high); /* 将比枢轴记录小的记录交换到低端 */

        while (low < high && L->r[low] <= pivotkey)
            low++;
        swap(L, low, high); /* 将比枢轴记录大的记录交换到高端 */
    }
    return low; /* 返回枢轴所在位置 */
}

/* 对顺序表L中的子序列L->r[low...high]作快速排序 */
void Qsort(SqList *L, int low, int high)
{
    int pivot;
    if (low < high)
    {
        pivot = Partition(L, low, high); /* 将L->r[low...high]一分为二,算出枢轴值pivot */
        Qsort(L, low, pivot - 1); /* 对低子表递归排序 */
        Qsort(L, pivot + 1, high); /* 对高子表递归排序 */
    }
}

/* 对顺序表L作快速排序 */
void QuickSort(SqList *L)
{
    Qsort(L, 1, L->length);
}

/* 优化版快速排序 */
/* Partition采用了三数取中优化 */
int Partition1(SqList *L, int low, int high)
{
    int pivotkey;

    /* 三数取中 */
    int m = low + (high - low) / 2; /* 计算数组中间的元素的下标 */
    if (L->r[low] > L->r[high])
        swap(L, low, high); /* 交换左端与右端数据,保证左端较小 */
    if (L->r[m] > L->r[high])
        swap(L, high, m); /* 交换中间与右端数据,保证中间较小 */
    if (L->r[m] > L->r[low])
        swap(L, m, low); /* 交换中间与左端数据,保证左端较小 */
    /* 此时L.r[low]已经为整个序列左中右三个关键字的中间值 */

    pivotkey = L->r[low]; /* 用子表的第一个记录作为枢轴记录 */
    L->r[0] = pivotkey; /* 将枢轴关键字备份到L->r[0] */

    while (low < high)
    {
        while (low < high && L->r[high] >= pivotkey)
            high--;
        L->r[low] = L->r[high]; /* 采用替换而不是交换的方式进行操作 */

        while (low < high && L->r[low] <= pivotkey)
            low++;
        L->r[high] = L->r[low]; /* 采用替换而不是交换的方式进行操作 */
    }

    L->r[low] = L->r[0]; /* 将枢轴数值替换会L.r[low] */

    return low;
}

#define MAX_LENGTH_INSERT_SORT 7 /* 数组长度阈值 */

/* 对顺序表L中的子序列L.r[low...high]作快速排序 */
void QSort1(SqList *L, int low, int high)
{
    int pivot;
    /* 当high-low大于常数时用快速排序 */
    if ((high - low) > MAX_LENGTH_INSERT_SORT)
    { /* 当high-low大于常数时用快速排序 */
        while (low < high)
        {
            pivot = Partition1(L, low, high); /* 将L.r[low...high]一分为二,算出枢轴值pivot */

            QSort1(L, low, pivot - 1); /* 对低子表递归排序 */
            low = pivot + 1; /* 尾递归 */
        }
    } else /* 当high-low小于等于常数时用直接插入排序 */
        InsertSort_Half(L);
}

void QuickSort1(SqList *L)
{
    QSort1(L, 1, L->length);
}
/* ************************************************* */

#define N 9

/* 恢复未排序前 */
void recovery(const int src[], SqList *L)
{
    L->length = 0;
    L->r[0] = 0;

    for (int i = 0; i < N; i++)
    {
        L->r[i + 1] = src[i];
        L->length++;
    }
}

/* 大数据性能测试 */
void MegaDataSort()
{
    srand(time(0));
    int Max = 100000;
    int d[100000];
    int i;
    SqList L;
    L.length = 0;

    for (i = 0; i < Max; i++)
        d[i] = rand() % Max + 1;

    for (i = 0; i < Max / 3; i++)
    {
        L.r[i + 1] = d[i];
        L.length++;
    }

    {
        clock_t start, end;
        start = clock();
        // xxSort(&L);
        end = clock();
        printf("time: %f s\n", ((double) (end - start)) / CLOCKS_PER_SEC / N);
    }
}

int main(void)
{
    int i, j;
    int unsorted[N] = {50, 10, 90, 30, 70, 40, 80, 60, 20};
    SqList L;

    {
        recovery(unsorted, &L);
        printf("原序为:\n");
        print(L);
        printf("初级冒泡排序:\n");
        BubbleSort0(&L);
        print(L);
        printf("\n");
    }

    {
        recovery(unsorted, &L);
        printf("原序为:\n");
        print(L);
        printf("冒泡排序:\n");
        BubbleSort(&L);
        print(L);
        printf("\n");
    }

    {
        recovery(unsorted, &L);
        printf("原序为:\n");
        print(L);
        printf("改进冒泡排序:\n");
        BubbleSort2(&L);
        print(L);
        printf("\n");
    }

    {
        recovery(unsorted, &L);
        printf("原序为:\n");
        print(L);
        printf("简单选择排序:\n");
        SelectSort(&L);
        print(L);
        printf("\n");
    }

    {
        recovery(unsorted, &L);
        printf("原序为:\n");
        print(L);
        printf("直接插入排序:\n");
        InsertSort(&L);
        print(L);
        printf("\n");
    }

    {
        recovery(unsorted, &L);
        printf("原序为:\n");
        print(L);
        printf("折半插入排序:\n");
        InsertSort_Half(&L);
        print(L);
        printf("\n");
    }

    {
        recovery(unsorted, &L);
        printf("原序为:\n");
        print(L);
        printf("希尔排序1:\n");
        ShellSort1(&L);
        printf("\n");
    }

    {
        recovery(unsorted, &L);
        printf("原序为:\n");
        print(L);
        printf("希尔排序2:\n");
        ShellSort2(&L);
        printf("\n");
    }

    {
        recovery(unsorted, &L);
        printf("原序为:\n");
        print(L);
        printf("堆排序:\n");
        HeapSort(&L);
        print(L);
        printf("\n");
    }

    {
        recovery(unsorted, &L);
        printf("原序为:\n");
        print(L);
        printf("归并排序:\n");
        MergeSort(&L);
        print(L);
        printf("\n");
    }

    {
        recovery(unsorted, &L);
        printf("原序为:\n");
        print(L);
        printf("归并排序非递归改进:\n");
        MergeSort2(&L);
        print(L);
        printf("\n");
    }

    {
        recovery(unsorted, &L);
        printf("原序为:\n");
        print(L);
        printf("快速排序:\n");
        QuickSort(&L);
        print(L);
        printf("\n");
    }

    /* Mega Data Sort */
//    MegaDataSort();

    return 0;
}