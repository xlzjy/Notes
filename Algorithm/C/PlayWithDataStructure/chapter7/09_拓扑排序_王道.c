#include <stdio.h>
#include <stdbool.h>

#define MaxVertexNum 100 // 图中顶点数目的最大值
#define MAXSIZE 100
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;
typedef int SElemType; // SElemType类型根据实际情况而定,这里假设为int
typedef int VertexType;

typedef struct ArcNode // 边表节点
{
    int adjvex; // 该弧所指向的顶点的位置
    struct ArcNode *nextarc; // 指向下一条弧的指针
    // InfoType info; // 网的边权值
} ArcNode;

typedef struct VNode // 顶点表结点
{
    VertexType data; // 顶点信息
    ArcNode *firstarc; // 指向第一条依附该顶点的弧的指针
} VNode, AdjList[MaxVertexNum];

typedef struct
{
    AdjList vertices; // 邻接表
    int vexnum, arcnum; // 图的顶点数和弧数
} Graph; // Graph是易邻接表存储的图类型

// 顺序栈结构
typedef struct
{
    SElemType data[MAXSIZE];
    int top; // 用于栈顶指针
} SqStack;

Status visit(SElemType c)
{
    printf("%d ", c);
    return OK;
}

// 构造一个空栈S
Status InitStack(SqStack *S)
{
    S->top = -1; // 空栈
    return OK;
}

// 把S置为空栈
Status ClearStack(SqStack *S)
{
    S->top = -1;
    return OK;
}

// 若栈S为空栈,则返回TRUE,否则返回FALSE
Status StackEmpty(SqStack S)
{
    if (S.top == -1)
        return TRUE;

    return FALSE;
}

// 返回S的元素个数,即栈的长度
int StackLength(SqStack S)
{
    return S.top + 1;
}

// 若栈不空,则用e返回S的栈顶元素,并返回OK,否则返回ERROR
Status GetTop(SqStack S, SElemType *e)
{
    if (S.top == -1)
        return ERROR;

    *e = S.data[S.top];

    return OK;
}

// 插入元素e为新的栈顶元素
Status Push(SqStack *S, SElemType e)
{
    if (S->top == MAXSIZE - 1)
        return ERROR;

    S->data[++S->top] = e; // 将新元素插入到栈顶空间

    return OK;
}

// 若栈不空,则删除S的栈顶元素,用e返回其值,并返回OK,否则返回ERROR
Status Pop(SqStack *S, SElemType *e)
{
    if (S->top == -1)
        return ERROR;

    *e = S->data[S->top--]; // 将要删除的栈顶元素赋值给e

    return OK;
}

// 从栈底到栈顶一次对栈中每个元素显示
Status StackTraverse(SqStack S)
{
    int i = 0;
    while (i <= S.top)
    {
        visit(S.data[i++]);
    }

    printf("\n");

    return OK;
}

bool TopologicalSort(Graph G, int *indegree, int *print)
{
    SqStack S;
    InitStack(&S); // 初始化栈,存储入度为0的顶点

    for (int i = 0; i < G.vexnum; i++)
        if (indegree[i] == 0)
            Push(&S, i); // 将所有入度为0的顶点进栈

    int count = 0; // 计数,记录当前已经输出的顶点数
    while (!StackEmpty(S)) // 栈不空,则存在入度为0的顶点
    {
        SElemType top;
        Pop(&S, &top); // 栈顶元素出栈,这里的top为栈顶的变量
        print[count++] = top; // 输出顶点i

        ArcNode *p;
        for (p = G.vertices[top].firstarc; p; p = p->nextarc)
        {
            // 将所有i指向的顶点的入度减1,并且将入度减为0的顶点压入栈S
            int v = p->adjvex;
            if (!(--indegree[v])) // --一定会执行
                Push(&S, v); // 入度为0,则入栈
        }
    }

    if (count < G.vexnum)
        return FALSE; // 排序失败,有向图中有回路
    else
        return TRUE; // 拓扑排序成功
}

int main(void)
{
    Graph G;
    G.vexnum = 5;
    G.arcnum = 5;
    int inDegree[MaxVertexNum] = {0, 1, 0, 2, 2}; // 当前顶点入度
    int print[MaxVertexNum] = {-1, -1, -1, -1, -1}; // 记录拓扑序列

    TopologicalSort(G, inDegree, print);
}