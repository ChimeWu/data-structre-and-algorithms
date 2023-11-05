//构造一个链式队列，实现入队、出队、遍历等操作

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int data;
    struct node *next;
} Node;

typedef struct queue
{
    Node *front;
    Node *rear;
    int size;
} Queue;

void init(Queue *queue)
{
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
}

void push(Queue *queue, int value)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = value;
    node->next = NULL;
    if (queue->front == NULL)
    {
        queue->front = node;
        queue->rear = node;
    }
    else
    {
        queue->rear->next = node;
        queue->rear = node;
    }
    queue->size++;
}

void pop(Queue *queue)
{
    if (queue->front == NULL)
    {
        return;
    }
    Node *node = queue->front;
    queue->front = queue->front->next;
    free(node);
    queue->size--;
}

int front(Queue *queue)
{
    if (queue->front == NULL)
    {
        return -1;
    }
    return queue->front->data;
}

int back(Queue *queue)
{
    if (queue->rear == NULL)
    {
        return -1;
    }
    return queue->rear->data;
}

int size(Queue *queue)
{
    return queue->size;
}

bool empty(Queue *queue)
{
    return queue->size == 0;
}

void clear(Queue *queue)
{
    while (queue->front != NULL)
    {
        Node *node = queue->front;
        queue->front = queue->front->next;
        free(node);
    }
    queue->rear = NULL;
    queue->size = 0;
}

void output(Queue *queue)
{
    Node *temp = queue->front;
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    init(queue);
    push(queue, 1);
    push(queue, 2);
    push(queue, 3);
    output(queue);
    pop(queue);
    output(queue);
    printf("%d\n", front(queue));
    printf("%d\n", back(queue));
    printf("%d\n", size(queue));
    printf("%d\n", empty(queue));
    clear(queue);
    printf("%d\n", size(queue));
    printf("%d\n", empty(queue));
    return 0;
}
