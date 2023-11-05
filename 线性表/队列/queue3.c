//构造一个双端队列，实现队列的基本操作

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 100

typedef struct deque
{
    int data[MAXSIZE];
    int front;
    int rear;
} Deque;

void init(Deque *deque)
{
    deque->front = 0;
    deque->rear = 0;
}

bool push_front(Deque *deque, int value)
{
    if ((deque->rear + 1) % MAXSIZE == deque->front)
    {
        return false;
    }
    deque->front = (deque->front - 1 + MAXSIZE) % MAXSIZE;
    deque->data[deque->front] = value;
    return true;
}

bool push_back(Deque *deque, int value)
{
    if ((deque->rear + 1) % MAXSIZE == deque->front)
    {
        return false;
    }
    deque->data[deque->rear] = value;
    deque->rear = (deque->rear + 1) % MAXSIZE;
    return true;
}

bool pop_front(Deque *deque)
{
    if (deque->front == deque->rear)
    {
        return false;
    }
    deque->front = (deque->front + 1) % MAXSIZE;
    return true;
}

bool pop_back(Deque *deque)
{
    if (deque->front == deque->rear)
    {
        return false;
    }
    deque->rear = (deque->rear - 1 + MAXSIZE) % MAXSIZE;
    return true;
}

int front(Deque *deque)
{
    if (deque->front == deque->rear)
    {
        return -1;
    }
    return deque->data[deque->front];
}

int back(Deque *deque)
{
    if (deque->front == deque->rear)
    {
        return -1;
    }
    return deque->data[(deque->rear - 1 + MAXSIZE) % MAXSIZE];
}

int main()
{
    Deque deque;
    init(&deque);
    push_front(&deque, 1);
    push_back(&deque, 2);
    push_front(&deque, 3);
    push_back(&deque, 4);
    printf("%d\n", front(&deque));
    printf("%d\n", back(&deque));
    pop_front(&deque);
    pop_back(&deque);
    printf("%d\n", front(&deque));
    printf("%d\n", back(&deque));
    return 0;
}
