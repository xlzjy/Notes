#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;
typedef int QElemType;

typedef struct QNode
{
    QElemType data;
    struct QNode *next;
} QNode, *QueuePtr;

typedef struct // 队列的链表结构
{
    QueuePtr front, rear; // 队头、队尾指针
} LinkQueue;

// 构造一个空队列Q
Status InitQueue(LinkQueue *Q)
{
    // 有头结点
    Q->front = Q->rear = (QueuePtr) malloc(sizeof(QNode));
    if (!Q->front)
        exit(OVERFLOW);

    Q->front->next = NULL; // 这一步可以使得Q->rear->next = NULL

    return OK;
}

// 清空队列Q(不包括头结点)
Status ClearQueue(LinkQueue *Q)
{
    if (Q == NULL)
        return ERROR;

    QueuePtr p;
    p = Q->front->next;

    // 用p结点在队头逐个删除结点
    while (p)
    {
        Q->front->next = p->next;
        free(p);
        p = Q->front->next;
    }

    // 将队尾指针指向队头指针
    Q->rear = Q->front;

    return OK;
}

// 销毁队列,头结点也不要
Status DestroyQueue(LinkQueue *Q)
{
    while (Q->front)
    {
        Q->rear = Q->front->next;
        free(Q->front);
        Q->front = Q->rear;
    }

    return OK;
}

// 若Q为空队列,则返回TRUE,否则返回FALSE
Status QueueEmpty(LinkQueue Q)
{
    if (Q.front == Q.rear)
        return TRUE;
    return FALSE;
}

// 求队列的长度
Status QueueLength(LinkQueue Q)
{
    int i = 0;
    QueuePtr p;
    p = Q.front;

    while (Q.rear != p)
    {
        i++;
        p = p->next;
    }

    return i;
}

// 若队列不空,则用e返回Q的队头元素,并返回OK,否则返回ERROR
Status GetHead(LinkQueue Q, QElemType *e)
{
    if (Q.front == Q.rear)
        return ERROR;

    QueuePtr p;

    p = Q.front->next;
    *e = p->data;

    return OK;
}

// 插入元素e为Q的新的队尾元素
Status EnQueue(LinkQueue *Q, QElemType e)
{
    QueuePtr s = (QueuePtr) malloc(sizeof(QNode));
    if (!s)
        return ERROR;

    s->data = e;

    // 偷梁换柱
    s->next = NULL; // 最后一个结点,必然指向NULL
    Q->rear->next = s; // 把拥有元素e的新结点s赋值给原队尾结点的后继
    Q->rear = s; // 把当前的s设置为队尾结点,rear指向s

    return OK;
}

// 若队列不空,删除Q的队头元素,用e返回其值,并返回OK,否则返回ERROR
Status DeQueue(LinkQueue *Q, QElemType *e)
{
    if (Q->front == Q->rear)
        return ERROR;

    QueuePtr p;
    p = Q->front->next; // 将欲删除的队头结点暂存给p
    *e = p->data; // 将欲删除的队头结点的值赋值给e
    Q->front->next = p->next; // 将原队头结点的后继p->next赋值给头结点后继

    if (p == Q->rear) // 若队头就是队尾,则删除后将rear指向头结点
        Q->rear = Q->front;

    free(p);

    return OK;
}

Status visit(QElemType p)
{
    printf("%d ", p);
    return OK;
}

// 将队头到队尾依次对队列Q中每个元素输出
Status QueueTraverse(LinkQueue Q)
{
    QueuePtr p;
    p = Q.front->next;

    while (p)
    {
        visit(p->data);
        p = p->next;
    }

    printf("\n");
    return OK;
}

int main(void)
{
    int i;
    QElemType d;
    LinkQueue q;
    i = InitQueue(&q);
    if (i)
        printf("成功地构造了一个空队列!\n");

    printf("是否空队列? %d(1:空 0:非空)\n", QueueEmpty(q));
    printf("队列的长度%d\n", QueueLength(q));

    EnQueue(&q, -5);
    EnQueue(&q, 5);
    EnQueue(&q, 10);
    printf("插入3个元素(-5,5,10)后,队列的长度为%d\n", QueueLength(q));
    printf("是否空队列? %d(1:空 0:否)\n", QueueEmpty(q));
    printf("队列的元素依次为: \n");
    QueueTraverse(q);

    i = GetHead(q, &d);
    if (i == OK)
        printf("队头元素是: %d\n", d);

    DeQueue(&q, &d);
    printf("删除了队头元素%d\n", d);

    i = GetHead(q, &d);
    if (i == OK)
        printf("新的队头元素是: %d\n", d);

    ClearQueue(&q);
    printf("清空队列后, q.front=%u q.read=%u q.front->next=%u q.rear->next"
           "=%u\n", q.front, q.rear, q.front->next, q.rear->next);

    DestroyQueue(&q);
    // 这时候指针指向NULL,因此没有后继结点
    printf("销毁队列后, q.front=%u q.rear=%u\n", q.front, q.rear);

    return 0;
}