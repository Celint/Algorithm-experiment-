/*
 * @描述: 最小生成数的Prim算法
 * @作者: 李天红
 * @Github: https://github.com/Celint/Algorithm-experiment-
 * @Date: 2019-06-10
 */
#include <iostream>
#include <fstream>
#define MAX_SPEN 65535
using namespace std;
int n = 7;
int node[7];
int map[7][7];
typedef struct Prim
{
    int node;
    int dest;
    int spen;
    Prim *next;
} * PrimList;
/**
 * @描述: 初始化网络拓扑图
 */
void saveG()
{
    ifstream in("MST.txt");
    for (int i = 0; i < n; i++)
        in >> node[i];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            in >> map[i][j];
}
/**
 * @描述: 初始化树
 */
PrimList Init(int x)
{
    PrimList t = (PrimList)malloc(sizeof(PrimList));
    t->node = node[x];
    PrimList p = t;
    for (int i = 0; i < n; i++)
    {
        if (map[x][i] != 0 && map[x][i] != -1)
        {
            PrimList q = (PrimList)malloc(sizeof(PrimList));
            q->node = node[x];
            q->dest = node[i];
            q->spen = map[x][i];
            p->next = q;
            p = q;
        }
        p->next = NULL;
    }
    return t;
}
/**
 * @描述: 找出最小生成树
 */
PrimList MstNodes(PrimList tree[])
{
    PrimList mst = (PrimList)malloc(sizeof(PrimList));
    mst->next = NULL;
    mst->node = tree[0]->node;
    mst->dest = tree[0]->node;
    mst->spen = 0;
update:
    int dest, spen = MAX_SPEN, node;
    PrimList p = mst;
    while (true)
    {
        for (int i = 0; i < n; i++)
        {
            if (p->dest == tree[i]->node)
            {
                PrimList q = tree[i];
                while (q->next)
                {
                    q = q->next;
                    PrimList r = mst;
                    bool find = false;
                    while (true)
                    {
                        if (r->dest == q->dest)
                        {
                            find = true;
                            break;
                        }
                        if (r->next)
                            r = r->next;
                        else
                            break;
                    }
                    if (find)
                        continue;
                    else if (spen > q->spen)
                    {
                        node = q->node;
                        spen = q->spen;
                        dest = q->dest;
                    }
                }
                break;
            }
        }
        if (p->next)
            p = p->next;
        else
        {
            PrimList q = (PrimList)malloc(sizeof(PrimList));
            q->dest = dest;
            q->spen = spen;
            q->node = node;
            q->next = NULL;
            p->next = q;
            break;
        }
    }
    int count = 1;
    p = mst;
    while (p->next)
    {
        p = p->next;
        count++;
    }
    if (count < 7)
        goto update;
    return mst;
}
int main()
{
    saveG();
    PrimList tree[n];
    PrimList mst;
    cout << "每个结点的邻居结点为：\n";
    for (int i = 0; i < n; i++)
    {
        tree[i] = Init(i);
        PrimList p = tree[i];
        cout << p->node << ": ";
        while (p->next)
        {
            p = p->next;
            cout << " -> " << p->node << ", " << p->spen << ", " << p->dest;
        }
        cout << endl;
    }
    mst = MstNodes(tree);
    cout << "最小生成子图以" << mst->node << "为起点：\n";
    while (mst->next)
    {
        mst = mst->next;
        cout << "从" << mst->node << "到" << mst->dest << "花费" << mst->spen << endl;
    }
    system("pause");
    return 0;
}