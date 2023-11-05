//用十字链表法构造一个有向图，实现图的基本操作

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int data;
    struct node *next;
    struct node *prev;
} Node;

typedef struct graph
{
    Node *nodes;
    int size;
} Graph;

void init(Graph *graph)
{
    graph->nodes = NULL;
    graph->size = 0;
}

void add(Graph *graph, int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    if (graph->nodes == NULL)
    {
        graph->nodes = node;
    }
    else
    {
        Node *temp = graph->nodes;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = node;
        node->prev = temp;
    }
    graph->size++;
}

void insert(Graph *graph, int index, int data)
{
    if (index < 0 || index > graph->size)
    {
        printf("index error\n");
        return;
    }
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    if (index == 0)
    {
        node->next = graph->nodes;
        graph->nodes->prev = node;
        graph->nodes = node;
    }
    else
    {
        Node *temp = graph->nodes;
        for (int i = 0; i < index - 1; i++)
        {
            temp = temp->next;
        }
        node->next = temp->next;
        node->prev = temp;
        temp->next->prev = node;
        temp->next = node;
    }
    graph->size++;
}

void remove(Graph *graph, int index)
{
    if (index < 0 || index >= graph->size)
    {
        printf("index error\n");
        return;
    }
    Node *node = graph->nodes;
    if (index == 0)
    {
        graph->nodes = graph->nodes->next;
        graph->nodes->prev = NULL;
    }
    else if (index == graph->size - 1)
    {
        for (int i = 0; i < index - 1; i++)
        {
            node = node->next;
        }
        node->next = NULL;
    }
    else
    {
        for (int i = 0; i < index - 1; i++)
        {
            node = node->next;
        }
        node->next = node->next->next;
        node->next->prev = node;
    }
    graph->size--;
}

void print(Graph *graph)
{
    Node *node = graph->nodes;
    while (node != NULL)
    {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

void addEdge(Graph *graph, int i, int j)
{
    if (i < 0 || i >= graph->size || j < 0 || j >= graph->size)
    {
        printf("index error\n");
        return;
    }
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = j;
    node->next = NULL;
    node->prev = NULL;
    if (graph->nodes == NULL)
    {
        graph->nodes = node;
    }
    else
    {
        Node *temp = graph->nodes;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = node;
        node->prev = temp;
    }
}

void insertEdge(Graph *graph, int i, int j, int data)
{
    if (i < 0 || i >= graph->size || j < 0 || j >= graph->size)
    {
        printf("index error\n");
        return;
    }
    Node *node = graph->nodes;
    while (node->data != i)
    {
        node = node->next;
    }
    Node *edge = (Node *)malloc(sizeof(Node));
    edge->data = j;
    edge->next = NULL;
    edge->prev = NULL;
    if (node->next == NULL)
    {
        node->next = edge;
        edge->prev = node;
    }
    else
    {
        Node *temp = node->next;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = edge;
        edge->prev = temp;
    }
}

void removeEdge(Graph *graph, int i, int j)
{
    if (i < 0 || i >= graph->size || j < 0 || j >= graph->size)
    {
        printf("index error\n");
        return;
    }
    Node *node = graph->nodes;
    while (node->data != i)
    {
        node = node->next;
    }
    if (node->next->data == j)
    {
        node->next = node->next->next;
        node->next->prev = node;
    }
    else
    {
        Node *temp = node->next;
        while (temp->data != j)
        {
            temp = temp->next;
        }
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
    }
}

void printEdge(Graph *graph, int i)
{
    if (i < 0 || i >= graph->size)
    {
        printf("index error\n");
        return;
    }
    Node *node = graph->nodes;
    while (node->data != i)
    {
        node = node->next;
    }
    node = node->next;
    while (node != NULL)
    {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

