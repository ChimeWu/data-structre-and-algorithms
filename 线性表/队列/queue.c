//构造一个顺序队列，实现其基本操作

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 100

typedef struct queue
{
    int data[MAXSIZE];
    int front;
    int rear;
} Queue;

void init(Queue *queue)
{
    queue->front = 0;
    queue->rear = 0;
}

bool push(Queue *queue, int value)
{
    if ((queue->rear + 1) % MAXSIZE == queue->front)
    {
        return false;
    }
    queue->data[queue->rear] = value;
    queue->rear = (queue->rear + 1) % MAXSIZE;
    return true;
}

bool pop(Queue *queue)
{
    if (queue->front == queue->rear)
    {
        return false;
    }
    queue->front = (queue->front + 1) % MAXSIZE;
    return true;
}

int front(Queue *queue)
{
    if (queue->front == queue->rear)
    {
        return -1;
    }
    return queue->data[queue->front];
}

int back(Queue *queue)
{
    if (queue->front == queue->rear)
    {
        return -1;
    }
    return queue->data[(queue->rear - 1 + MAXSIZE) % MAXSIZE];
}

int main()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    init(queue);
    push(queue, 1);
    push(queue, 2);
    push(queue, 3);
    printf("%d\n", front(queue));
    printf("%d\n", back(queue));
    pop(queue);
    printf("%d\n", front(queue));
    printf("%d\n", back(queue));
    pop(queue);
    printf("%d\n", front(queue));
    printf("%d\n", back(queue));
    pop(queue);
    printf("%d\n", front(queue));
    printf("%d\n", back(queue));
    return 0;
}
