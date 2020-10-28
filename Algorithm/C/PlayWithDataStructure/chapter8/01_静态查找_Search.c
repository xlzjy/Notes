#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100 // 存储空间初始分配量

/* 顺序查找(无哨兵模式),a为数组,n为要查找的数组长度,key为要查找的关键字 */
int Sequential_Search(const int *a, int n, int key)
{
    int i;
    for (i = 1; i <= n; i++)
    {
        if (a[i] == key)
            return i;
    }

    return 0;
}

/* 有哨兵顺序查找 */
int Sequential_Search2(int *a, int n, int key)
{
    int i;
    a[0] = key; // 设置a[0]为关键字值,称之为哨兵
    i = n; // 循环从数组尾部开始

    while (a[i] != key)
    {
        i--;
    }

    return i; // 返回0则说明查找失败
}

/* 折半查找 */
int Binary_Search(const int *a, int n, int key)
{
    int low, high, mid;
    low = 1; // 定义最低下标为记录首位
    high = n; // 定义最高下标为记录末位

    while (low <= high)
    {
        mid = (low + high) / 2; // 折半
        if (key < a[mid]) // 若查找值比中值小
            high = mid - 1; // 最高下标调整到中位下标小一位
        else if (key > a[mid]) // 若查找值比中值大
            low = mid + 1; // 最低下标调整到中位下标大一位
        else
        {
            return mid;
        }
    }
    return 0;
}

/* 插值查找 */
int Interpolation_Search(const int *a, int n, int key)
{
    int low, high, mid;
    low = 1; // 定义最低下标为记录首位
    high = n; // 定义最高下标为记录末尾
    while (low <= high)
    {
        mid = low + (high - low) * (key - a[low]) / (a[high] - a[low]); // 插值
        if (key < a[mid]) // 若查找值比插值小
            high = mid - 1; // 最高下标调整到插值下标小一位
        if (key > a[mid]) // 若查找值比插值大
            low = mid + 1; // 最低下标调整到插值下标大一位
        else
            return mid; // 若相等则说明mid即为查找到的位置
    }
    return 0;
}

int F[100]; // 斐波那契数列

/* 斐波那契查找 */
int Fibonacci_Search(int *a, int n, int key)
{
    int low, high, mid, i, k;
    low = 1; // 定义最低下标为记录首位
    high = n; // 定义最高下标为记录末位
    k = 0;

    while (n > F[k] - 1) // 计算n位于斐波那契数列的位置
        k++;

    for (i = n; i < F[k] - 1; i++) // 将不满的数值补全,避免比较的时候对应的空位上没有值导致比较失败
        a[i] = a[n]; // 将a[n-1]后续的值补为a[n]

    while (low <= high)
    {
        mid = low + F[k - 1] - 1; // 计算当前分隔的下标
        if (key < a[mid]) // 若查找记录小于当前分割记录
        {
            high = mid - 1; // 最高下标调整到分隔下标mid-1处
            k = k - 1; // 斐波那契数列下标减一位
        } else if (key > a[mid])
        {
            low = mid + 1; // 最低下标调整到分隔下标mid+1处
            k = k - 2; // 斐波那契数列下标减两位
        } else
        {
            if (mid <= n)
                return mid; // 若相等则说明mid即为查找到的位置
            else
                return n; // 若mid>n说明是补全数值,返回n
        }
    }

    return 0;
}

int main(void)
{
    int a[MAXSIZE + 1], i, result;

    for (i = 0; i <= MAXSIZE; i++)
    {
        a[i] = i;
    }

    result = Sequential_Search(a, MAXSIZE, MAXSIZE);
    printf("Sequential_Search: %d\n", result);
    result = Sequential_Search2(a, MAXSIZE, 1);
    printf("Sequential_Search2: %d\n", result);

    int arr[MAXSIZE] = {0, 1, 16, 24, 35, 47, 59, 62, 73, 88, 99};

    result = Binary_Search(arr, 10, 62);
    printf("Binary_Search: %d \n", result);

    result = Interpolation_Search(arr, 10, 62);
    printf("Interpolation_Search: %d\n", result);

    F[0] = 0;
    F[1] = 1;
    for (i = 2; i < 100; i++)
    {
        F[i] = F[i - 1] + F[i - 2];
    }
    result = Fibonacci_Search(arr, 10, 62);
    printf("Fibonacci_Search: %d\n", result);

    return 0;
}