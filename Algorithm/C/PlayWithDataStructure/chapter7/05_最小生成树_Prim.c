#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXEDGE 20
#define MAXVEX 9
#define INFINITY 65535

typedef int Status; // Status是函数的类型,其值是函数结果状态代码

typedef struct
{
    int arc[MAXVEX][MAXVEX];
    int numVertexes, numEdges;
} MGraph;

void CreateMGraph(MGraph *G) // 构建图
{
    int i, j;

    // 输入边数和顶点数
    G->numEdges = 15;
    G->numVertexes = 9;

    for (i = 0; i < G->numVertexes; i++) // 初始化图
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
    G->arc[1][6] = 16;
    G->arc[1][8] = 12;
    G->arc[2][3] = 22;
    G->arc[2][8] = 8;
    G->arc[3][4] = 20;
    G->arc[3][6] = 24;
    G->arc[3][7] = 16;
    G->arc[3][8] = 21;
    G->arc[4][5] = 26;
    G->arc[4][7] = 7;
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

/* Prim算法生成最小生成树
 * 算法大概思路
 * 一、初始化步骤:
 * 1.主要需要定义两个数组 adjvex用来存当前每个位置的最小权值所对应的顶点下标 lowcost用来存各个位置的最小权值
 * 2.由于初始输入的点是v0,所以lowcost[0]=0(代表v0已经纳入生成树), adjvex[0]=0
 * 3.除了已有的v0位置,adjvex其余位置都应该置0,因为当前只有v0纳入生成树,从v0出发. lowcost除了v0位置,其他位置都应该是矩阵中v0行的对应元素,因为当前只有v0这个元素
 * 二、算法开始
 * 1.除了v0元素,应遍历剩下所有元素,需要做以下事:
 *   (1) 初始化:设置一个最小值min=65535, j=1从除了v0以外的元素开始, k=0
 *   (2) 用j当作索引,找到当前lowcost里面最小的权值lowcost[j],那么将j赋值给k,min最小值就为lowcost[j]
 *   (3) 打印出来(adjvex[k],k) (谁和k组成最小的权值,k)
 *   (4) lowcost[k]=0,此时k已经纳入生成树,因此将lowcost[k]置为0
 *   (5) 从j=1开始遍历所有顶点,如果lowcost本身等于0或者lowcost[j]<邻接矩阵中第k行对应的第j个元素,那么就更新lowcost[j],同时adjvex[j]=k,这样就新增了最小权值的顶点
 * 2.继续之前的循环
 */
void MiniSpanTree_Prim(MGraph G)
{
    /* *********************初始化********************* */

    /* min是为了之后找到一定范围内的最小权值 */
    /* j是用来做顶点下标循环的变量 */
    /* k是用来存储最小权值的顶点下标 */
    int min, i, j, k;

    /* lowcost,adjvex两个数组长度都为顶点个数9 */
    int adjvex[MAXVEX]; // 保存相关顶点下标
    int lowcost[MAXVEX]; // 保存相关顶点间边的权值

    /*
     * lowcost[0]=0就表示v0已经被纳入到最小生成树中,之后凡是lowcost数组中的
     * 值被设置为0就表示此下标的顶点被纳入最小生成树
     */
    lowcost[0] = 0; // 初始化第一个顶点下标为0
    adjvex[0] = 0; // 初始化第一个顶点下标为0

    /*
     * 读取邻接矩阵的第一行数据,将数值赋值给lowcost数组,所以此时lowcost数组值为
     * {0,10,65535,65535,65535,11,65535,65535,65535},而adjvex则全部为0
     * 此时已经完成了初始化操作
     */
    for (i = 1; i < G.numVertexes; i++)
    {
        lowcost[i] = G.arc[0][i]; // 将v0顶点与之有边的权值存入数组
        adjvex[i] = 0; // 初始化为v0的下标
    }

    /* *********************初始化结束********************* */

    /* *********************构造最小生成树********************* */
    for (i = 1; i < G.numVertexes; i++)
    {
        /* min设置为一个极大值,目的是为了之后找到一定范围内的最小权值 */
        min = INFINITY; // 初始化最小权值为无穷

        j = 1; // j是用来做顶点下标循环的变量
        k = 0; // k是用来存储最小权值的顶点下标

        /* 循环中不断修改min为当前lowcost数组中最小值,并用k保留此最小值的顶点下标 */
        while (j < G.numVertexes) // 循环全部顶点
        {
            if (lowcost[j] != 0 && lowcost[j] < min)
            { // 如果权值不为0且权值小于min,lowcost[j]!=0表示已经是生成树的顶点不参与最小权值的查找
                min = lowcost[j]; // 则让当前权值成为最小值
                k = j; // 将当前最小值的下标存入k
            }
            j++;
        }

        printf("(%d,%d) ", adjvex[k], k); // 打印当前顶点边中权值最小边
        /* 将当前顶点纳入最小生成树中 */
        lowcost[k] = 0; // 将当前顶点的权值设置为0,表示此顶点已经完成任务

        for (j = 1; j < G.numVertexes; j++) // 循环所有顶点
        {
            if (lowcost[j] != 0 && G.arc[k][j] < lowcost[j])
            {
                // 若下标为k顶点各边权值小于此前这些顶点未被加入生成树权值
                lowcost[j] = G.arc[k][j]; // 将较小的权值存入lowcost
                adjvex[j] = k; // 将下标为k的顶点存入adjvex
            }
        }
    }
}

int main(void)
{
    MGraph G;
    CreateMGraph(&G);
    MiniSpanTree_Prim(G);

    return 0;
}