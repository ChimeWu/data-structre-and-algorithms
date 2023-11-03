//用邻接多重表法实现一个无向图，实现其创建、插入、删除、查找、遍历等操作。定义一个最小生成树函数、一个最短路径函数。

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int data;
    struct node *next;
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
    if (index == 0)
    {
        node->next = graph->nodes;
        graph->nodes = node;
    }
    else if (index == graph->size)
    {
        Node *temp = graph->nodes;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = node;
    }
    else
    {
        Node *temp = graph->nodes;
        for (int i = 0; i < index - 1; i++)
        {
            temp = temp->next;
        }
        node->next = temp->next;
        temp->next = node;
    }
    graph->size++;
}

void removeNode(Graph *graph, int data)
{
    Node *temp = graph->nodes;
    if (temp->data == data)
    {
        graph->nodes = temp->next;
        free(temp);
        graph->size--;
        return;
    }
    while (temp->next != NULL)
    {
        if (temp->next->data == data)
        {
            Node *node = temp->next;
            temp->next = temp->next->next;
            free(node);
            graph->size--;
            return;
        }
        temp = temp->next;
    }
}

int indexOf(Graph *graph, int data)
{
    Node *temp = graph->nodes;
    int index = 0;
    while (temp != NULL)
    {
        if (temp->data == data)
        {
            return index;
        }
        temp = temp->next;
        index++;
    }
    return -1;
}

void print(Graph *graph)
{
    Node *temp = graph->nodes;
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void dfs(Graph *graph, int data)
{
    int index = indexOf(graph, data);
    if (index == -1)
    {
        printf("data not found\n");
        return;
    }
    bool *visited = (bool *)malloc(sizeof(bool) * graph->size);
    for (int i = 0; i < graph->size; i++)
    {
        visited[i] = false;
    }
    Node *temp = graph->nodes;
    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }
    dfs2(temp, visited);
    printf("\n");
}

void dfs2(Node *node, bool *visited)
{
    if (visited[node->data])
    {
        return;
    }
    visited[node->data] = true;
    printf("%d ", node->data);
    Node *temp = node->next;
    while (temp != NULL)
    {
        dfs2(temp, visited);
        temp = temp->next;
    }
}

void bfs(Graph *graph, int data)
{
    int index = indexOf(graph, data);
    if (index == -1)
    {
        printf("data not found\n");
        return;
    }
    bool *visited = (bool *)malloc(sizeof(bool) * graph->size);
    for (int i = 0; i < graph->size; i++)
    {
        visited[i] = false;
    }
    Node *temp = graph->nodes;
    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }
    bfs2(temp, visited);
    printf("\n");
}

void bfs2(Node *node, bool *visited)
{
    if (visited[node->data])
    {
        return;
    }
    visited[node->data] = true;
    printf("%d ", node->data);
    Node *temp = node->next;
    while (temp != NULL)
    {
        bfs2(temp, visited);
        temp = temp->next;
    }
}

