#include <stdio.h>
#include <stdlib.h>

typedef int Status;    /* Status是函数的类型,其值是函数结果状态代码，如OK等 */

#define MAXEDGE 15
#define MAXVEX 9
#define INFINITY 65535

typedef struct
{
    int arc[MAXVEX][MAXVEX];
    int numVertexes, numEdges;
} MGraph;

typedef struct
{
    int begin;
    int end;
    int weight;
} Edge;   /* 对边集数组Edge结构的定义 */

/* 构件图 */
void CreateMGraph(MGraph *G)
{
    int i, j;

    /* printf("请输入边数和顶点数:"); */
    G->numEdges = 15;
    G->numVertexes = 9;

    for (i = 0; i < G->numVertexes; i++)/* 初始化图 */
    {
        for (j = 0; j < G->numVertexes; j++)
        {
            if (i == j)
                G->arc[i][j] = 0;
            else
                G->arc[i][j] = G->arc[j][i] = INFINITY;
        }
    }

    G->arc[0][1] = 10;
    G->arc[0][5] = 11;
    G->arc[1][2] = 18;
    G->arc[1][8] = 12;
    G->arc[1][6] = 16;
    G->arc[2][8] = 8;
    G->arc[2][3] = 22;
    G->arc[3][8] = 21;
    G->arc[3][6] = 24;
    G->arc[3][7] = 16;
    G->arc[3][4] = 20;
    G->arc[4][7] = 7;
    G->arc[4][5] = 26;
    G->arc[5][6] = 17;
    G->arc[6][7] = 19;

    for (i = 0; i < G->numVertexes; i++)
    {
        for (j = i; j < G->numVertexes; j++)
        {
            G->arc[j][i] = G->arc[i][j];
        }
    }

}

/* 交换权值 以及头和尾 */
void Swapn(Edge *edges, int i, int j)
{
    int temp;
    temp = edges[i].begin;
    edges[i].begin = edges[j].begin;
    edges[j].begin = temp;
    temp = edges[i].end;
    edges[i].end = edges[j].end;
    edges[j].end = temp;
    temp = edges[i].weight;
    edges[i].weight = edges[j].weight;
    edges[j].weight = temp;
}

/* 对权值进行排序,冒泡排序 */
void sort(Edge edges[], MGraph *G)
{
    int i, j;
    // 比较n个数,只要比较n-1次
    for (i = 0; i < G->numEdges - 1; i++)
    {
        // 前一个数和邻接的下一个数比较,一共比较(n-1)-(i+1)-1次,既n-i-1次
        for (j = i + 1; j < G->numEdges; j++)
        {
            if (edges[i].weight > edges[j].weight)
            {
                Swapn(edges, i, j);
            }
        }
    }
    printf("权排序之后的为:\n");
    // 打印所有的边
    for (i = 0; i < G->numEdges; i++)
    {
        printf("(%d, %d) %d\n", edges[i].begin, edges[i].end, edges[i].weight);
    }
}

// 查找连接顶点的尾部下标
int Find(const int *parent, int f)
{
    while (parent[f] > 0)
    {
        f = parent[f];
    }

    return f;
}

/* 生成最小生成树 */
void MiniSpanTree_Kruskal(MGraph G)
{
    int i, j;
    int k = 0; // edges数据下标
    Edge edges[MAXEDGE];/* 定义边集数组,edge的结构为begin,end,weight,均为整型 */

    /* 用来构建边集数组并排序********************* */
    for (i = 0; i < G.numVertexes - 1; i++)
    {
        for (j = i + 1; j < G.numVertexes; j++)
        {
            /*
             * i=0,j=1; i=1,j=2; i=2,j=3;... 这代表了邻接矩阵的右上三角,不包含对角线
             * 邻接矩阵右上三角中不等于INFINITY的,就是有效的权重,包含了所有的边
             * 所以只要对右上三角进行操作就能取出邻接矩阵中的所有边
             */
            if (G.arc[i][j] < INFINITY)
            {
                edges[k].begin = i;
                edges[k].end = j;
                edges[k].weight = G.arc[i][j];
                k++;
            }
        }
    }
    sort(edges, &G);
    /* ******************************************* */

    int n, m;
    int parent[MAXVEX];/* 定义一数组用来判断边与边是否形成环路 */

    for (i = 0; i < G.numVertexes; i++)
        parent[i] = 0; // 初始化数组值为0

    printf("打印最小生成树: \n");

    for (i = 0; i < G.numEdges; i++) // 循环每一条边
    {
        n = Find(parent, edges[i].begin);
        m = Find(parent, edges[i].end);

        if (n != m) // 假如n与m不等,说明此边没有与现有的生成树形成环路
        {
            parent[n] = m; // 将此边的结尾顶点放入下标为起点的parent中,表示此顶点已经在生成树集合中
            printf("(%d, %d) %d\n", edges[i].begin, edges[i].end, edges[i].weight);
        }
    }
}

int main(void)
{
    MGraph G;
    CreateMGraph(&G);
    MiniSpanTree_Kruskal(G);
    return 0;
}