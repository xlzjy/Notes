#include <stdio.h>
#include <stdbool.h>

#define TRUE 1
#define FALSE 0
#define MAXVEX 10 /* 最大顶点数,由用户定义 */
#define INFINITY 65535 /* 用65535来代表无穷 */

typedef int VertexType; /* 顶点类型应由用户定义 */
typedef int EdgeType; /* 边上的权值类型应由用户定义 */

typedef struct
{
    VertexType vexs[MAXVEX]; /* 顶点表 */
    EdgeType arc[MAXVEX][MAXVEX]; /* 邻接矩阵,可看作边表 */
    int numVertexes, numEdges; /* 图中当前的顶点数和边数 */
} MGraph;

bool visited[MAXVEX]; /* 访问标记数组,初始化为false */

void visit(VertexType v)
{
    printf("%c", v);
}

// 从顶点v除法,深度优先遍历图G
void DFS(MGraph G, int v)
{
    visit(v); // 访问顶点v
    visited[v] = TRUE; // 设为已访问标记

    for (w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w))
    {
        // w为u的尚未访问的邻接顶点
        if (!visited[w])
        {
            DFS(G, w);
        }
    }
}

// 对图G进行深度优先遍历
void DFSTraverse(MGraph G)
{
    for (v = 0; v < G.numVertexes; v++)
        visited[v] = FALSE; // 初始化已访问标记数据

    // 本代码中是从v=0开始遍历
    for (v = 0; v < G.numVertexes; v++)
        if (!visited[v])
            DFS(G, v);
}