//各种图实现的定义

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTEX_NUM 20
#define INFINITY 65535


//顶点类型
typedef int VertexType;

//边上权值类型
typedef int EdgeType;

//边上权值类型
typedef int InfoType;


//邻接矩阵法
typedef struct {
    VertexType vexs[MAX_VERTEX_NUM]; //顶点表
    EdgeType arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; //邻接矩阵
    int vexnum, arcnum; //图的当前顶点数和弧数
} MGraph;

//邻接表法
typedef struct ArcNode {
    int adjvex; //该弧所指向的顶点的位置
    struct ArcNode *next; //指向下一条弧的指针
    InfoType *info; //该弧相关信息的指针
} ArcNode;

typedef struct VNode {
    VertexType data; //顶点信息
    ArcNode *first; //指向第一条依附该顶点的弧的指针
} VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {
    AdjList vertices; //邻接表
    int vexnum, arcnum; //图的当前顶点数和弧数
} ALGraph;

//十字链表法
typedef struct ArcNode2 {
    int tailvex, headvex; //该弧的尾和头顶点的位置
    struct ArcNode2 *hlink, *tlink; //分别指向弧头相同和弧尾相同的弧的指针
    InfoType *info; //该弧相关信息的指针
} ArcNode2;

typedef struct VNode2 {
    VertexType data; //顶点信息
    ArcNode2 *firstin, *firstout; //分别指向该顶点第一条入弧和出弧
} VNode2, AdjList2[MAX_VERTEX_NUM];

typedef struct {
    AdjList2 xlist; //邻接表
    int vexnum, arcnum; //图的当前顶点数和弧数
} GLGraph;

//邻接多重表法
typedef struct ArcNode3 {
    bool mark; //访问标记
    int ivex, jvex; //该边依附的两个顶点的位置
    struct ArcNode3 *ilink, *jlink; //分别指向依附这两个顶点的下一条边
    InfoType *info; //该边相关信息的指针
} ArcNode3;

typedef struct VNode3 {
    VertexType data; //顶点信息
    ArcNode3 *firstedge; //指向第一条依附该顶点的边的指针
} VNode3, AdjList3[MAX_VERTEX_NUM];

typedef struct {
    AdjList3 adjmulist; //邻接表
    int vexnum, arcnum; //图的当前顶点数和弧数
} AMLGraph;

//边集数组法
typedef struct {
    VertexType vexs[MAX_VERTEX_NUM]; //顶点表
    EdgeType edges[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; //邻接矩阵
    int vexnum, arcnum; //图的当前顶点数和弧数
} MGraph2;

