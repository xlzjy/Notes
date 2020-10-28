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
} Edge;

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

void sort(Edge edges[], MGraph *G)
{
    int i, j;

    for (i = 0; i < G->numEdges - 1; i++)
    {
        for (j = i + 1; j < G->numEdges; j++)
        {
            if (edges[i].weight > edges[j].weight)
            {
                Swapn(edges, i, j);
            }
        }
    }

    printf("权排序之后为:\n");

    for (i = 0; i < G->numEdges; i++)
    {
        printf("(%d, %d) %d\n", edges[i].begin, edges[i].end, edges[i].weight);
    }
}

int Find(const int *parent, int f)
{
    while (parent[f] > 0)
    {
        f = parent[f];
    }

    return f;
}

void MiniSpanTree_Kruskal(MGraph G)
{
    int i, j;
    int k = 0;
    Edge edges[MAXEDGE];

    for (i = 0; i < G.numVertexes - 1; i++)
    {
        for (j = i + 1; j < G.numVertexes; j++)
        {
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

    int n, m;
    int parent[MAXVEX];

    for (i = 0; i < G.numVertexes; i++)
        parent[i] = 0;

    printf("打印最小生成树\n");

    for (i = 0; i < G.numEdges; i++)
    {
        n = Find(parent, edges[i].begin);
        m = Find(parent, edges[i].end);

        if (n != m)
        {
            parent[n] = m;
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