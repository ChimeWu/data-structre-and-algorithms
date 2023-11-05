//用邻接矩阵法构造一个图，实现图的基本操作

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

typedef struct graph
{
    char vex[MAX];
    int edge[MAX][MAX];
    int vexnum, edgenum;
}Graph;

void init(Graph *graph)
{
    graph->vexnum = 0;
    graph->edgenum = 0;
}

void add(Graph *graph, char data)
{
    graph->vex[graph->vexnum] = data;
    graph->vexnum++;
}

void insert(Graph *graph, int i, int j, int data)
{
    if (i < 0 || i >= graph->vexnum || j < 0 || j >= graph->vexnum)
    {
        printf("index error\n");
        return;
    }
    graph->edge[i][j] = data;
    graph->edge[j][i] = data;
    graph->edgenum++;
}

void remove(Graph *graph, int i, int j)
{
    if (i < 0 || i >= graph->vexnum || j < 0 || j >= graph->vexnum)
    {
        printf("index error\n");
        return;
    }
    graph->edge[i][j] = 0;
    graph->edge[j][i] = 0;
    graph->edgenum--;
}

void print(Graph *graph)
{
    printf("vexnum: %d\n", graph->vexnum);
    printf("edgenum: %d\n", graph->edgenum);
    printf("vex: ");
    for (int i = 0; i < graph->vexnum; i++)
    {
        printf("%c ", graph->vex[i]);
    }
    printf("\n");
    printf("edge:\n");
    for (int i = 0; i < graph->vexnum; i++)
    {
        for (int j = 0; j < graph->vexnum; j++)
        {
            printf("%d ", graph->edge[i][j]);
        }
        printf("\n");
    }
}

//深度优先遍历
void dfs(Graph *graph, int i, bool *visited)
{
    printf("%c ", graph->vex[i]);
    visited[i] = true;
    for (int j = 0; j < graph->vexnum; j++)
    {
        if (graph->edge[i][j] != 0 && !visited[j])
        {
            dfs(graph, j, visited);
        }
    }
}

void dfs2(Graph *graph, int i)
{
    bool *visited = (bool *)malloc(sizeof(bool) * graph->vexnum);
    for (int j = 0; j < graph->vexnum; j++)
    {
        visited[j] = false;
    }
    dfs(graph, i, visited);
    printf("\n");
}

void dfs3(Graph *graph)
{
    bool *visited = (bool *)malloc(sizeof(bool) * graph->vexnum);
    for (int i = 0; i < graph->vexnum; i++)
    {
        visited[i] = false;
    }
    for (int i = 0; i < graph->vexnum; i++)
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
    int queue[MAX];
    int front = 0;
    int rear = 0;
    queue[rear++] = i;
    while (front != rear)
    {
        int index = queue[front++];
        printf("%c ", graph->vex[index]);
        visited[index] = true;
        for (int j = 0; j < graph->vexnum; j++)
        {
            if (graph->edge[index][j] != 0 && !visited[j])
            {
                queue[rear++] = j;
            }
        }
    }
}

void bfs2(Graph *graph, int i)
{
    bool *visited = (bool *)malloc(sizeof(bool) * graph->vexnum);
    for (int j = 0; j < graph->vexnum; j++)
    {
        visited[j] = false;
    }
    bfs(graph, i, visited);
    printf("\n");
}

void bfs3(Graph *graph)
{
    bool *visited = (bool *)malloc(sizeof(bool) * graph->vexnum);
    for (int i = 0; i < graph->vexnum; i++)
    {
        visited[i] = false;
    }
    for (int i = 0; i < graph->vexnum; i++)
    {
        if (!visited[i])
        {
            bfs(graph, i, visited);
        }
    }
    printf("\n");
}

//图的连通性
bool connected(Graph *graph)
{
    bool *visited = (bool *)malloc(sizeof(bool) * graph->vexnum);
    for (int i = 0; i < graph->vexnum; i++)
    {
        visited[i] = false;
    }
    dfs(graph, 0, visited);
    for (int i = 0; i < graph->vexnum; i++)
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
    int lowcost[MAX];
    int adjvex[MAX];
    bool visited[MAX];
    for (int i = 0; i < graph->vexnum; i++)
    {
        lowcost[i] = graph->edge[0][i];
        adjvex[i] = 0;
        visited[i] = false;
    }
    visited[0] = true;
    for (int i = 1; i < graph->vexnum; i++)
    {
        int min = 0x7fffffff;
        int index = 0;
        for (int j = 0; j < graph->vexnum; j++)
        {
            if (lowcost[j] < min && !visited[j])
            {
                min = lowcost[j];
                index = j;
            }
        }
        printf("%c %c\n", graph->vex[adjvex[index]], graph->vex[index]);
        visited[index] = true;
        for (int j = 0; j < graph->vexnum; j++)
        {
            if (graph->edge[index][j] < lowcost[j] && !visited[j])
            {
                lowcost[j] = graph->edge[index][j];
                adjvex[j] = index;
            }
        }
    }
}

//最小生成树Kruskal算法
typedef struct edge
{
    int u;
    int v;
    int w;
}Edge;

void swap(Edge *edge1, Edge *edge2)
{
    Edge temp = *edge1;
    *edge1 = *edge2;
    *edge2 = temp;
}

void sort(Edge *edges, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < size; j++)
        {
            if (edges[j].w < edges[min].w)
            {
                min = j;
            }
        }
        swap(&edges[i], &edges[min]);
    }
}

int find(int *parent, int index)
{
    while (parent[index] > 0)
    {
        index = parent[index];
    }
    return index;
}

void kruskal(Graph *graph)
{
    Edge edges[MAX];
    int size = 0;
    for (int i = 0; i < graph->vexnum; i++)
    {
        for (int j = i + 1; j < graph->vexnum; j++)
        {
            if (graph->edge[i][j] != 0)
            {
                edges[size].u = i;
                edges[size].v = j;
                edges[size].w = graph->edge[i][j];
                size++;
            }
        }
    }
    sort(edges, size);
    int parent[MAX];
    for (int i = 0; i < graph->vexnum; i++)
    {
        parent[i] = 0;
    }
    for (int i = 0; i < size; i++)
    {
        int u = find(parent, edges[i].u);
        int v = find(parent, edges[i].v);
        if (u != v)
        {
            printf("%c %c\n", graph->vex[edges[i].u], graph->vex[edges[i].v]);
            parent[u] = v;
        }
    }
}

//最短路径Dijkstra算法
void dijkstra(Graph *graph, int i)
{
    int dist[MAX];
    int path[MAX];
    bool visited[MAX];
    for (int j = 0; j < graph->vexnum; j++)
    {
        dist[j] = graph->edge[i][j];
        path[j] = i;
        visited[j] = false;
    }
    visited[i] = true;
    for (int j = 1; j < graph->vexnum; j++)
    {
        int min = 0x7fffffff;
        int index = 0;
        for (int k = 0; k < graph->vexnum; k++)
        {
            if (dist[k] < min && !visited[k])
            {
                min = dist[k];
                index = k;
            }
        }
        visited[index] = true;
        for (int k = 0; k < graph->vexnum; k++)
        {
            if (graph->edge[index][k] + dist[index] < dist[k] && !visited[k])
            {
                dist[k] = graph->edge[index][k] + dist[index];
                path[k] = index;
            }
        }
    }
    for (int j = 0; j < graph->vexnum; j++)
    {
        printf("%c ", graph->vex[j]);
    }
    printf("\n");
    for (int j = 0; j < graph->vexnum; j++)
    {
        printf("%d ", dist[j]);
    }
    printf("\n");
    for (int j = 0; j < graph->vexnum; j++)
    {
        printf("%c ", graph->vex[path[j]]);
    }
    printf("\n");
}

//最短路径Floyd算法
void floyd(Graph *graph)
{
    int dist[MAX][MAX];
    int path[MAX][MAX];
    for (int i = 0; i < graph->vexnum; i++)
    {
        for (int j = 0; j < graph->vexnum; j++)
        {
            dist[i][j] = graph->edge[i][j];
            path[i][j] = j;
        }
    }
    for (int k = 0; k < graph->vexnum; k++)
    {
        for (int i = 0; i < graph->vexnum; i++)
        {
            for (int j = 0; j < graph->vexnum; j++)
            {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = path[i][k];
                }
            }
        }
    }
    for (int i = 0; i < graph->vexnum; i++)
    {
        for (int j = 0; j < graph->vexnum; j++)
        {
            printf("%d ", dist[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < graph->vexnum; i++)
    {
        for (int j = 0; j < graph->vexnum; j++)
        {
            printf("%c ", graph->vex[path[i][j]]);
        }
        printf("\n");
    }
}

//拓扑排序
void topologicalSort(Graph *graph)
{
    int indegree[MAX];
    for (int i = 0; i < graph->vexnum; i++)
    {
        indegree[i] = 0;
    }
    for (int i = 0; i < graph->vexnum; i++)
    {
        for (int j = 0; j < graph->vexnum; j++)
        {
            if (graph->edge[i][j] != 0)
            {
                indegree[j]++;
            }
        }
    }
    int queue[MAX];
    int front = 0;
    int rear = 0;
    for (int i = 0; i < graph->vexnum; i++)
    {
        if (indegree[i] == 0)
        {
            queue[rear++] = i;
        }
    }
    while (front != rear)
    {
        int index = queue[front++];
        printf("%c ", graph->vex[index]);
        for (int i = 0; i < graph->vexnum; i++)
        {
            if (graph->edge[index][i] != 0)
            {
                indegree[i]--;
                if (indegree[i] == 0)
                {
                    queue[rear++] = i;
                }
            }
        }
    }
    printf("\n");
}

//关键路径
void criticalPath(Graph *graph)
{
    int ve[MAX];
    int vl[MAX];
    for (int i = 0; i < graph->vexnum; i++)
    {
        ve[i] = 0;
    }
    int queue[MAX];
    int front = 0;
    int rear = 0;
    for (int i = 0; i < graph->vexnum; i++)
    {
        if (ve[i] == 0)
        {
            queue[rear++] = i;
        }
    }
    while (front != rear)
    {
        int index = queue[front++];
        for (int i = 0; i < graph->vexnum; i++)
        {
            if (graph->edge[index][i] != 0)
            {
                if (ve[index] + graph->edge[index][i] > ve[i])
                {
                    ve[i] = ve[index] + graph->edge[index][i];
                }
                if (--vl[i] == 0)
                {
                    queue[rear++] = i;
                }
            }
        }
    }
    for (int i = 0; i < graph->vexnum; i++)
    {
        vl[i] = ve[graph->vexnum - 1];
    }
    for (int i = graph->vexnum - 2; i >= 0; i--)
    {
        for (int j = 0; j < graph->vexnum; j++)
        {
            if (graph->edge[i][j] != 0)
            {
                if (vl[j] - graph->edge[i][j] < vl[i])
                {
                    vl[i] = vl[j] - graph->edge[i][j];
                }
            }
        }
    }
    for (int i = 0; i < graph->vexnum; i++)
    {
        for (int j = 0; j < graph->vexnum; j++)
        {
            if (graph->edge[i][j] != 0)
            {
                int e = ve[i];
                int l = vl[j] - graph->edge[i][j];
                if (e == l)
                {
                    printf("%c %c\n", graph->vex[i], graph->vex[j]);
                }
            }
        }
    }
}


