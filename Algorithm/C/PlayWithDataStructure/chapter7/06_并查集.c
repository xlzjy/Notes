#include <stdio.h>
#include <stdlib.h>

/*
 * 并查集
 * https://www.bilibili.com/video/BV13t411v7Fs?from=search&seid=18363496798023302179
 * 目的:通过并查集来判断一个图中是否有环
 */

#define VERTICES 6

void initialise(int parent[], int rank[])
{
    int i;
    for (i = 0; i < VERTICES; i++)
    {
        parent[i] = -1;
        rank[i] = 0;
    }
}

// 寻找x的根节点
int find_root(int x, const int parent[])
{
    // 如果parent[x]为-1,说明x本身就是根节点
    int x_root = x; // 假设x为根节点

    while (parent[x_root] != -1)
    {
        x_root = parent[x_root];
    }

    return x_root;
}

// 函数返回1表示合并成功
// 返回0表示合并失败
int union_vertices(int x, int y, int parent[], int rank[])
{
    int x_root = find_root(x, parent);
    int y_root = find_root(y, parent);

    if (x_root == y_root)
        return 0;
    else
    {
        if (rank[x_root] > rank[y_root]) // x高度比y高度高
        {
            parent[y_root] = x_root;
        } else if (rank[y_root] > rank[x_root]) // y高度比x高度高
        {
            parent[x_root] = y_root;
        } else // 两边高度一样
        {
            parent[x_root] = y_root;
            rank[y_root]++;
        }
        return 1;
    }
}

int main(void)
{
    int parent[VERTICES] = {0};
    int rank[VERTICES] = {0};
    int edges[5][2] = {
            {0, 1},
            {1, 2},
            {1, 3},
//            {2, 4},
            {3, 4},
            {2, 5}
    };
    initialise(parent, rank);

    int i;

    for (i = 0; i < 5; i++)
    {
        int x = edges[i][0];
        int y = edges[i][1];

        if (union_vertices(x, y, parent, rank) == 0)
        {
            printf("Cycle detected!");
            exit(0);
        }
    }

    printf("No cycles found.\n");

    return 0;
}