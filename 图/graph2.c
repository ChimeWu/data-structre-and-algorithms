//用邻接表法构造一个图，实现其基本操作

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct arcnode
{
    int adjvex;
    struct arcnode *next;
} ArcNode;

typedef struct vnode
{
    int data;
    ArcNode *first;
} VNode;

typedef struct graph
{
    VNode *vnodes;
    int size;
} Graph;

void init(Graph *graph)
{
    graph->vnodes = NULL;
    graph->size = 0;
}

void add(Graph *graph, int data)
{
    VNode *vnodes = (VNode *)malloc(sizeof(VNode) * (graph->size + 1));
    for (int i = 0; i < graph->size; i++)
    {
        vnodes[i] = graph->vnodes[i];
    }
    ArcNode *arcnode = (ArcNode *)malloc(sizeof(ArcNode));
    arcnode->adjvex = graph->size;
    arcnode->next = NULL;
    VNode vnode;
    vnode.data = data;
    vnode.first = arcnode;
    vnodes[graph->size] = vnode;
    graph->size++;
    graph->vnodes = vnodes;
}

void insert(Graph *graph, int i, int j)
{
    if (i < 0 || i >= graph->size || j < 0 || j >= graph->size)
    {
        printf("index error\n");
        return;
    }
    ArcNode *arcnode = (ArcNode *)malloc(sizeof(ArcNode));
    arcnode->adjvex = j;
    arcnode->next = NULL;
    if (graph->vnodes[i].first == NULL)
    {
        graph->vnodes[i].first = arcnode;
    }
    else
    {
        ArcNode *temp = graph->vnodes[i].first;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = arcnode;
    }
}

void remove(Graph *graph, int i, int j)
{
    if (i < 0 || i >= graph->size || j < 0 || j >= graph->size)
    {
        printf("index error\n");
        return;
    }
    ArcNode *temp = graph->vnodes[i].first;
    ArcNode *prev = NULL;
    while (temp != NULL)
    {
        if (temp->adjvex == j)
        {
            if (prev == NULL)
            {
                graph->vnodes[i].first = temp->next;
            }
            else
            {
                prev->next = temp->next;
            }
            free(temp);
            break;
        }
        prev = temp;
        temp = temp->next;
    }
}

void print(Graph *graph)
{
    for (int i = 0; i < graph->size; i++)
    {
        printf("%d: ", graph->vnodes[i].data);
        ArcNode *temp = graph->vnodes[i].first;
        while (temp != NULL)
        {
            printf("%d ", temp->adjvex);
            temp = temp->next;
        }
        printf("\n");
    }
}

//深度优先遍历
void dfs(Graph *graph, int i, bool *visited)
{
    printf("%d ", graph->vnodes[i].data);
    visited[i] = true;
    ArcNode *temp = graph->vnodes[i].first;
    while (temp != NULL)
    {
        if (!visited[temp->adjvex])
        {
            dfs(graph, temp->adjvex, visited);
        }
        temp = temp->next;
    }
}

void dfsTraverse(Graph *graph)
{
    bool *visited = (bool *)malloc(sizeof(bool) * graph->size);
    for (int i = 0; i < graph->size; i++)
    {
        visited[i] = false;
    }
    for (int i = 0; i < graph->size; i++)
    {
        if (!visited[i])
        {
            dfs(graph, i, visited);
        }
    }
    printf("\n");
}

//广度优先遍历
void bfs(Graph *graph, int i, bool *visited)
{
    int *queue = (int *)malloc(sizeof(int) * graph->size);
    int front = 0;
    int rear = 0;
    queue[rear++] = i;
    visited[i] = true;
    while (front != rear)
    {
        int index = queue[front++];
        printf("%d ", graph->vnodes[index].data);
        ArcNode *temp = graph->vnodes[index].first;
        while (temp != NULL)
        {
            if (!visited[temp->adjvex])
            {
                queue[rear++] = temp->adjvex;
                visited[temp->adjvex] = true;
            }
            temp = temp->next;
        }
    }
}

void bfsTraverse(Graph *graph)
{
    bool *visited = (bool *)malloc(sizeof(bool) * graph->size);
    for (int i = 0; i < graph->size; i++)
    {
        visited[i] = false;
    }
    for (int i = 0; i < graph->size; i++)
    {
        if (!visited[i])
        {
            bfs(graph, i, visited);
        }
    }
    printf("\n");
}

//图的连通性
bool isConnected(Graph *graph)
{
    bool *visited = (bool *)malloc(sizeof(bool) * graph->size);
    for (int i = 0; i < graph->size; i++)
    {
        visited[i] = false;
    }
    dfs(graph, 0, visited);
    for (int i = 0; i < graph->size; i++)
    {
        if (!visited[i])
        {
            return false;
        }
    }
    return true;
}

//最小生成树Prim算法
void prim(Graph *graph)
{
    int *lowcost = (int *)malloc(sizeof(int) * graph->size);
    int *closest = (int *)malloc(sizeof(int) * graph->size);
    bool *s = (bool *)malloc(sizeof(bool) * graph->size);
    for (int i = 0; i < graph->size; i++)
    {
        lowcost[i] = 0;
        closest[i] = 0;
        s[i] = false;
    }
    s[0] = true;
    ArcNode *temp = graph->vnodes[0].first;
    while (temp != NULL)
    {
        lowcost[temp->adjvex] = temp->adjvex;
        closest[temp->adjvex] = 0;
        temp = temp->next;
    }
    for (int i = 1; i < graph->size; i++)
    {
        int min = 0;
        for (int j = 0; j < graph->size; j++)
        {
            if (!s[j] && lowcost[j] < lowcost[min])
            {
                min = j;
            }
        }
        printf("%d %d\n", closest[min], min);
        s[min] = true;
        temp = graph->vnodes[min].first;
        while (temp != NULL)
        {
            if (!s[temp->adjvex] && temp->adjvex != min && temp->adjvex < lowcost[temp->adjvex])
            {
                lowcost[temp->adjvex] = temp->adjvex;
                closest[temp->adjvex] = min;
            }
            temp = temp->next;
        }
    }
}

//最小生成树Kruskal算法
typedef struct edge
{
    int i;
    int j;
    int weight;
} Edge;

void swap(Edge *edges, int i, int j)
{
    Edge temp = edges[i];
    edges[i] = edges[j];
    edges[j] = temp;
}

void sort(Edge *edges, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < size; j++)
        {
            if (edges[j].weight < edges[min].weight)
            {
                min = j;
            }
        }
        swap(edges, i, min);
    }
}

int find(int *parent, int i)
{
    while (parent[i] > 0)
    {
        i = parent[i];
    }
    return i;
}

void kruskal(Graph *graph)
{
    Edge *edges = (Edge *)malloc(sizeof(Edge) * graph->size * graph->size);
    int index = 0;
    for (int i = 0; i < graph->size; i++)
    {
        ArcNode *temp = graph->vnodes[i].first;
        while (temp != NULL)
        {
            edges[index].i = i;
            edges[index].j = temp->adjvex;
            edges[index].weight = temp->adjvex;
            index++;
            temp = temp->next;
        }
    }
    sort(edges, index);
    int *parent = (int *)malloc(sizeof(int) * graph->size);
    for (int i = 0; i < graph->size; i++)
    {
        parent[i] = 0;
    }
    for (int i = 0; i < index; i++)
    {
        int pi = find(parent, edges[i].i);
        int pj = find(parent, edges[i].j);
        if (pi != pj)
        {
            printf("%d %d\n", edges[i].i, edges[i].j);
            parent[pi] = pj;
        }
    }
}

//最短路径Dijkstra算法
void dijkstra(Graph *graph, int i)
{
    int *dist = (int *)malloc(sizeof(int) * graph->size);
    int *path = (int *)malloc(sizeof(int) * graph->size);
    bool *s = (bool *)malloc(sizeof(bool) * graph->size);
    for (int i = 0; i < graph->size; i++)
    {
        dist[i] = 0;
        path[i] = 0;
        s[i] = false;
    }
    s[i] = true;
    ArcNode *temp = graph->vnodes[i].first;
    while (temp != NULL)
    {
        dist[temp->adjvex] = temp->adjvex;
        path[temp->adjvex] = i;
        temp = temp->next;
    }
    for (int i = 1; i < graph->size; i++)
    {
        int min = 0;
        for (int j = 0; j < graph->size; j++)
        {
            if (!s[j] && dist[j] < dist[min])
            {
                min = j;
            }
        }
        s[min] = true;
        temp = graph->vnodes[min].first;
        while (temp != NULL)
        {
            if (!s[temp->adjvex] && temp->adjvex != min && dist[min] + temp->adjvex < dist[temp->adjvex])
            {
                dist[temp->adjvex] = dist[min] + temp->adjvex;
                path[temp->adjvex] = min;
            }
            temp = temp->next;
        }
    }
    for (int i = 0; i < graph->size; i++)
    {
        printf("%d ", dist[i]);
    }
    printf("\n");
    for (int i = 0; i < graph->size; i++)
    {
        printf("%d ", path[i]);
    }
    printf("\n");
}

//最短路径Floyd算法
void floyd(Graph *graph)
{
    int **dist = (int **)malloc(sizeof(int *) * graph->size);
    int **path = (int **)malloc(sizeof(int *) * graph->size);
    for (int i = 0; i < graph->size; i++)
    {
        dist[i] = (int *)malloc(sizeof(int) * graph->size);
        path[i] = (int *)malloc(sizeof(int) * graph->size);
    }
    for (int i = 0; i < graph->size; i++)
    {
        for (int j = 0; j < graph->size; j++)
        {
            dist[i][j] = 0;
            path[i][j] = 0;
        }
    }
    for (int i = 0; i < graph->size; i++)
    {
        ArcNode *temp = graph->vnodes[i].first;
        while (temp != NULL)
        {
            dist[i][temp->adjvex] = temp->adjvex;
            path[i][temp->adjvex] = i;
            temp = temp->next;
        }
    }
    for (int k = 0; k < graph->size; k++)
    {
        for (int i = 0; i < graph->size; i++)
        {
            for (int j = 0; j < graph->size; j++)
            {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = k;
                }
            }
        }
    }
    for (int i = 0; i < graph->size; i++)
    {
        for (int j = 0; j < graph->size; j++)
        {
            printf("%d ", dist[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < graph->size; i++)
    {
        for (int j = 0; j < graph->size; j++)
        {
            printf("%d ", path[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

//拓扑排序
void topologicalSort(Graph *graph)
{
    int *indegree = (int *)malloc(sizeof(int) * graph->size);
    for (int i = 0; i < graph->size; i++)
    {
        indegree[i] = 0;
    }
    for (int i = 0; i < graph->size; i++)
    {
        ArcNode *temp = graph->vnodes[i].first;
        while (temp != NULL)
        {
            indegree[temp->adjvex]++;
            temp = temp->next;
        }
    }
    int *queue = (int *)malloc(sizeof(int) * graph->size);
    int front = 0;
    int rear = 0;
    for (int i = 0; i < graph->size; i++)
    {
        if (indegree[i] == 0)
        {
            queue[rear++] = i;
        }
    }
    while (front != rear)
    {
        int index = queue[front++];
        printf("%d ", graph->vnodes[index].data);
        ArcNode *temp = graph->vnodes[index].first;
        while (temp != NULL)
        {
            indegree[temp->adjvex]--;
            if (indegree[temp->adjvex] == 0)
            {
                queue[rear++] = temp->adjvex;
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

//关键路径
void criticalPath(Graph *graph)
{
    int *ve = (int *)malloc(sizeof(int) * graph->size);
    int *vl = (int *)malloc(sizeof(int) * graph->size);
    for (int i = 0; i < graph->size; i++)
    {
        ve[i] = 0;
        vl[i] = 0;
    }
    int *queue = (int *)malloc(sizeof(int) * graph->size);
    int front = 0;
    int rear = 0;
    for (int i = 0; i < graph->size; i++)
    {
        if (ve[i] == 0)
        {
            queue[rear++] = i;
        }
    }
    while (front != rear)
    {
        int index = queue[front++];
        ArcNode *temp = graph->vnodes[index].first;
        while (temp != NULL)
        {
            if (ve[index] + temp->adjvex > ve[temp->adjvex])
            {
                ve[temp->adjvex] = ve[index] + temp->adjvex;
            }
            if (--vl[index] == 0)
            {
                queue[rear++] = index;
            }
        }
    }
    for (int i = 0; i < graph->size; i++)
    {
        vl[i] = ve[graph->size - 1];
    }
    for (int i = graph->size - 2; i >= 0; i--)
    {
        ArcNode *temp = graph->vnodes[i].first;
        while (temp != NULL)
        {
            if (vl[temp->adjvex] - temp->adjvex < vl[i])
            {
                vl[i] = vl[temp->adjvex] - temp->adjvex;
            }
            temp = temp->next;
        }
    }
    for (int i = 0; i < graph->size; i++)
    {
        ArcNode *temp = graph->vnodes[i].first;
        while (temp != NULL)
        {
            int e = ve[i];
            int l = vl[temp->adjvex] - temp->adjvex;
            if (e == l)
            {
                printf("%d %d\n", i, temp->adjvex);
            }
            temp = temp->next;
        }
    }
}

