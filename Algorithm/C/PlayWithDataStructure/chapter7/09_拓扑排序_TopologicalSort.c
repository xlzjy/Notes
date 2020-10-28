#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXEDGE 20
#define MAXVEX 14
#define INFINITY 65535

typedef int Status; // 函数的类型

// 邻接矩阵结构
typedef struct
{
    int vexs[MAXVEX];
    int arc[MAXVEX][MAXVEX];
    int numVertexes, numEdges;
} MGraph;

// 邻接表结构
typedef struct EdgeNode
{
    int adjvex; // 邻接点域,存储该顶点对应的下标
    int weight; // 用于存储权值,对于非网图可以不需要
    struct EdgeNode *next; // 链域,指向下一个邻接点
} EdgeNode;

typedef struct VertexNode
{
    int in; // 顶点入度
    int data; // 顶点域,存储顶点信息
    EdgeNode *firstedge; // 边表头指针
} VertexNode, AdjList[MAXVEX];

typedef struct
{
    AdjList adjList;
    int numVertexes, numEdges; // 图中的当前顶点数和边数
} graphAdjList, *GraphAdjList;


void CreateMGraph(MGraph *G)
{
    int i, j;

    G->numVertexes = MAXVEX;
    G->numEdges = MAXEDGE;

    for (i = 0; i < G->numVertexes; i++) // 初始化图
    {
        G->vexs[i] = i;
    }

    for (i = 0; i < G->numVertexes; i++) // 初始化图
    {
        for (j = 0; j < G->numVertexes; j++)
        {
            G->arc[i][j] = 0;
        }
    }

    G->arc[0][4] = 1;
    G->arc[0][5] = 1;
    G->arc[0][11] = 1;
    G->arc[1][2] = 1;
    G->arc[1][4] = 1;
    G->arc[1][8] = 1;
    G->arc[2][5] = 1;
    G->arc[2][6] = 1;
    G->arc[2][9] = 1;
    G->arc[3][2] = 1;
    G->arc[3][13] = 1;
    G->arc[4][7] = 1;
    G->arc[5][8] = 1;
    G->arc[5][12] = 1;
    G->arc[6][5] = 1;
    G->arc[8][7] = 1;
    G->arc[9][10] = 1;
    G->arc[9][11] = 1;
    G->arc[10][13] = 1;
    G->arc[12][9] = 1;
}

// 利用邻接矩阵构建邻接表
void CreateALGraph(MGraph G, GraphAdjList *GL)
{
    int i, j;
    EdgeNode *e;

    *GL = (GraphAdjList) malloc(sizeof(graphAdjList));

    (*GL)->numVertexes = G.numVertexes;
    (*GL)->numEdges = G.numEdges;

    for (i = 0; i < G.numVertexes; i++) // 读入顶点信息,建立顶点表
    {
        (*GL)->adjList[i].in = 0;
        (*GL)->adjList[i].data = G.vexs[i];
        (*GL)->adjList[i].firstedge = NULL; // 将边表置为空表
    }

    for (i = 0; i < G.numVertexes; i++) // 建立边表
    {
        for (j = 0; j < G.numVertexes; j++)
        {
            if (G.arc[i][j] == 1)
            {
                e = (EdgeNode *) malloc(sizeof(EdgeNode));
                e->adjvex = j; // 邻接序号为j
                e->next = (*GL)->adjList[i].firstedge; // 将当前顶点上的指向的节点指针赋值给e
                (*GL)->adjList[i].firstedge = e; // 将当前顶点的指针指向e
                (*GL)->adjList[j].in++;
            }
        }
    }
}

/* 拓扑排序，若GL无回路，则输出拓扑排序序列并返回1，若有回路返回0。 */
// Debug查看指针的数组内容, *(int(*)[MAXVEX])(stack)
Status TopologicalSort(GraphAdjList GL)
{
    EdgeNode *e;
    int i, k, gettop;
    int top = 0; // 用于栈指针下标
    int count = 0; // 用于统计输出顶点的个数
    int *stack; // 建栈存储入度为0的顶点

    stack = (int *) malloc(sizeof(EdgeNode) * GL->numVertexes);

    for (i = 0; i < GL->numVertexes; i++)
        if (GL->adjList[i].in == 0)
            stack[++top] = i; // 将入度为0的顶点入栈

    while (top != 0)
    {
        gettop = stack[top--]; // 栈顶元素出栈,出栈的元素是邻接表元素下标

        if (count == GL->numVertexes - 1)
        {
            printf("%d", GL->adjList[gettop].data); // 最后一个节点
        } else if (count < GL->numVertexes - 1)
        {
            printf("%d -> ", GL->adjList[gettop].data); // 打印此节点
        }
        count++; // 打印了就统计输出顶点数

        for (e = GL->adjList[gettop].firstedge; e != NULL; e = e->next)
        {
            // 对此顶点弧表遍历
            k = e->adjvex; // 取出邻接点下标
            // 如果邻接点的入度为0,那么入栈
            if (!(--GL->adjList[k].in)) // 将k号顶点邻接点的入度减1
                stack[++top] = k; // 若未0则入栈,以便于下次循环输出
        }
    }

    printf("\n");

    if (count < GL->numVertexes) // 如果count小于顶点数,说明存在环
        return ERROR;
    else
        return OK;
}

int main(void)
{
    MGraph G;
    GraphAdjList GL;
    int result;

    CreateMGraph(&G);
    CreateALGraph(G, &GL);

    result = TopologicalSort(GL);
    printf("result: %s", result == 1 ? "拓扑排序成功" : "有回路,拓扑排序失败");

    return 0;
}
