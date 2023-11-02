//实现一个栈，要求用链式存储结构，且实现入栈、出栈、取栈顶元素、判断栈空、判断栈满等操作。

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int data;
    struct node *next;
} Node;

typedef struct stack
{
    Node *top;
    int size;
} Stack;

//初始化栈
void init(Stack *stack)
{
    stack->top = NULL;
    stack->size = 0;
}

//入栈
void push(Stack *stack, int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = stack->top;
    stack->top = node;
    stack->size++;
}

int pop(Stack *stack)
{
    if (stack->size == 0)
    {
        printf("stack is empty\n");
        return -1;
    }
    Node *node = stack->top;
    int data = node->data;
    stack->top = node->next;
    free(node);
    stack->size--;
    return data;
}

int peek(Stack *stack)
{
    if (stack->size == 0)
    {
        printf("stack is empty\n");
        return -1;
    }
    return stack->top->data;
}

bool isEmpty(Stack *stack)
{
    return stack->size == 0;
}

bool isFull(Stack *stack)
{
    return false;
}

void print(Stack *stack)
{
    Node *node = stack->top;
    while (node != NULL)
    {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

