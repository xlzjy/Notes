#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * 广度优先遍历(Breadth-First-Search, BFS) 步骤:
 * 1.找到与一个顶点相邻的所有顶点
 * 2.标记哪些顶点被访问过
 * 3.需要一个辅助队列
 * 使用到两个函数
 * FirstNeighbor(G,x): 求图G中顶点x的第一个邻接点,若有则返回顶点号;若x没有邻接点
 *   或图中不存在x,则返回-1
 * NextNeighbor(G,x,y): 假设图G中顶点y是顶点x的一个邻接点,返回除y之外顶点x的下一个
 *   邻接点的顶点号,若y是x的最后一个邻接点,则返回-1
 */

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
    printf("%d ", v);
}

// 广度优先遍历
void BFS(MGraph G, int v) // 从顶点v出发,广度优先遍历图G
{
    visit(v); // 访问初始顶点v
    visited[v] = TRUE; // 对v做已访问标记
    Enqueue(Q, v); // 顶点v入队列Q

    while (!isEmpty(Q))
    {
        DeQueue(Q, v); // 顶点v出队列
        for (w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w))
        {
            // 检测v所有邻接点
            if (!visited[w]) // w为v的尚未访问的邻接结点
            {
                visit(w); // 访问顶点w
                visited[w] = TRUE; // 对w做已访问标记
                Enqueue(Q, w); // 顶点w入队列
            }
        }
    }
}

// 需要广度优先遍历图G的所有连通分量
void BFSTraverse(MGraph G) // 对图G进行广度优先遍历
{
    for (int i = 0; i < G.numVertexes; i++)
    {
        visited[i] = FALSE; // 访问标记数组初始化
    }

    InitQueue(Q); // 初始化辅助队列Q

    for (int i = 0; i < G.numVertexes; i++) // 从0号顶点开始遍历
    {
        if (!visited[i]) // 对每个连通分量调用一次BFS
            BFS(G, i); // vi未访问过,从vi开始BFS
    }

}