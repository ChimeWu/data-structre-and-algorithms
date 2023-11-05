//用邻接矩阵法构造一个图，实现图的基本操作

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct graph
{
    int **matrix;
    int size;
} Graph;

void init(Graph *graph)
{
    graph->matrix = NULL;
    graph->size = 0;
}

void add(Graph *graph)
{
    int **matrix = (int **)malloc(sizeof(int *) * (graph->size + 1));
    for (int i = 0; i < graph->size + 1; i++)
    {
        matrix[i] = (int *)malloc(sizeof(int) * (graph->size + 1));
    }
    for (int i = 0; i < graph->size; i++)
    {
        for (int j = 0; j < graph->size; j++)
        {
            matrix[i][j] = graph->matrix[i][j];
        }
    }
    for (int i = 0; i < graph->size; i++)
    {
        matrix[i][graph->size] = 0;
    }
    matrix[graph->size][graph->size] = 0;
    graph->size++;
    graph->matrix = matrix;
}

void insert(Graph *graph, int i, int j, int data)
{
    if (i < 0 || i >= graph->size || j < 0 || j >= graph->size)
    {
        printf("index error\n");
        return;
    }
    graph->matrix[i][j] = data;
}

void remove(Graph *graph, int i, int j)
{
    if (i < 0 || i >= graph->size || j < 0 || j >= graph->size)
    {
        printf("index error\n");
        return;
    }
    graph->matrix[i][j] = 0;
}

void print(Graph *graph)
{
    for (int i = 0; i < graph->size; i++)
    {
        for (int j = 0; j < graph->size; j++)
        {
            printf("%d ", graph->matrix[i][j]);
        }
        printf("\n");
    }
}

