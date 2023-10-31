//实现一个顺序栈及其基本操作
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 50

typedef struct stack
{
    int top;
    int array[MAX_SIZE];
} Stack;

Stack* createStack(int size)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->top = -1;
    return stack;
}

//判断栈是否为空
bool isEmpty(Stack *stack)
{
    return stack->top == -1;
}

//判断栈是否已满
bool isFull(Stack *stack)
{
    return stack->top == MAX_SIZE - 1;
}

//入栈
void push(Stack *stack, int data)
{
    if (isFull(stack))
    {
        printf("stack is full\n");
        return;
    }
    stack->array[++stack->top] = data;
}

//出栈
int pop(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("stack is empty\n");
        return -1;
    }
    return stack->array[stack->top--];
}

//获取栈顶元素
int peek(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("stack is empty\n");
        return -1;
    }
    return stack->array[stack->top];
}

//打印栈
void printStack(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("stack is empty\n");
        return;
    }
    for (int i = stack->top; i >= 0; i--)
    {
        printf("%d ", stack->array[i]);
    }
    printf("\n");
}

//销毁栈
void destroyStack(Stack *stack)
{
    free(stack);
}

int main()
{
    Stack *stack = createStack(MAX_SIZE);
    push(stack, 1);
    push(stack, 2);
    push(stack, 3);
    push(stack, 4);
    printStack(stack);
    printf("peek: %d\n", peek(stack));
    printf("pop: %d\n", pop(stack));
    printStack(stack);
    destroyStack(stack);
    return 0;
}
