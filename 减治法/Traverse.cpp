/*
 * @描述: 深度广度优先遍历算法
 * @作者: 李天红
 * @Github: https://github.com/Celint/Algorithm-experiment-
 * @Date: 2019-06-04
 */
#include <iostream>
#include <fstream>
using namespace std;
/**
 * @描述: 图的邻接表存储表示
 */
#define MAX_VERTEX_NUM 30 //最大顶点数
typedef int InfoType;
typedef struct ArcNode
{                            //弧结点
    int adjvex;              //该弧指向的顶点的位置
    struct ArcNode *nextarc; //指向下一条弧的指针
} ArcNode;
typedef int VertexType;
typedef struct VNode
{                      //表头结点
    InfoType data;     //顶点信息
    ArcNode *firstarc; //指向第一条依附该定点的弧的指针
} VNode, AdjList[MAX_VERTEX_NUM];
typedef struct
{                       //图结构定义
    AdjList vertices;   //表头结点数，表头向量
    int vexnum, arcnum; //图的当前顶点数和弧数
} ALGraph;
int visited[MAX_VERTEX_NUM]; //访问标志数组初始化
int Locate(ALGraph G, int n)
{
    for (int i = 0; i < G.vexnum; i++)
    {
        if (n == G.vertices[i].data)
            return i;
    }
}
/**
 * @描述: 创建图
 */
void CreateGraph(ALGraph &G)
{
    ifstream in("G.txt");
    in >> G.vexnum; //边数
    in >> G.arcnum; //节点数
    // 每个结点的值。初始化边矩阵
    for (int i = 0; i < G.arcnum; i++)
    {
        in >> G.vertices[i].data;
        G.vertices[i].firstarc = NULL;
    }
    // 与边相关联两点的序号
    for (int i = 0; i < G.arcnum; i++)
    {
        int a, b;
        int x, y;
        ArcNode *p, *q;
        in >> a;
        in >> b;
        x = Locate(G, a);
        y = Locate(G, b);
        p = (ArcNode *)malloc(sizeof(ArcNode));
        p->adjvex = x;
        p->nextarc = NULL; //初始化
        p->nextarc = G.vertices[y].firstarc;
        G.vertices[y].firstarc = p;
        q = (ArcNode *)malloc(sizeof(ArcNode));
        q->adjvex = y;
        q->nextarc = NULL; //初始化
        q->nextarc = G.vertices[x].firstarc;
        G.vertices[x].firstarc = q;
    }
}
/**
 * @描述: 深度优先遍历
 */
void DFS(ALGraph G, int v)
{
    visited[v] = 1;
    cout << G.vertices[v].data << " ";
    for (int w = 0; w < G.vexnum; w++)
    {
        if (G.vertices[w].firstarc != NULL && !visited[w])
            DFS(G, w);
    }
}
/**
 * @描述: 深度优先遍历
 */
void DFSTraverse(ALGraph G)
{
    for (int i = 0; i < G.vexnum; i++)
        visited[i] = 0;
    for (int i = 0; i < G.vexnum; i++)
        if (!visited[i])
            DFS(G, i);
}
/**
 * @描述: 打印邻接表
 */
void Print(ALGraph G)
{
    for (int i = 0; i < G.vexnum; i++)
    {
        ArcNode *p;
        p = G.vertices[i].firstarc;
        printf("%d", G.vertices[i].data);
        while (p != NULL)
        {
            printf("->%d", p->adjvex);
            p = p->nextarc;
        }
        printf("\n");
    }
}
/**
 * @描述: 广度优先遍历
 */
void BFSTraverse(ALGraph G)
{
    for (int i = 0; i < G.vexnum; i++)
        visited[i] = 0;
    for (int i = 0; i < G.vexnum; i++)
    {
        if (!visited[i])
        {
            printf("%d ", G.vertices[i].data);
            visited[i] = 1;
            for (int j = 0; G.vertices[j].firstarc != NULL && !visited[j]; j++)
            {
                printf("%d ", G.vertices[j].data);
                visited[j] = 1;
            }
        }
    }
}
int main()
{
    ALGraph G;
    CreateGraph(G);
    cout << "打印邻接表：\n";
    Print(G);
    cout << "深度优先遍历顺序为：\n";
    DFSTraverse(G);
    cout << endl;
    cout << "广度优先遍历顺序为：\n";
    BFSTraverse(G);
    cout << endl;
    system("pause");
    return 0;
}