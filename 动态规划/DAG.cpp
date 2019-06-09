/*
 * @描述: 有向加权图中的最长路径
 * @作者: 李天红
 * @Github: https://github.com/Celint/Algorithm-experiment-
 * @Date: 2019-06-09
 */
#include <iostream>
#include <fstream>
#define MAX_V 65535
using namespace std;
char Nodes[6]; //结点数组
int map[6][6]; //网络拓扑图
typedef struct DAG
{
    char dest;
    int spent;
    DAG *next;
} * DAGList;
/**
 * @描述: 初始化网络拓扑图
 */
void saveG()
{
    ifstream in("DAG.txt");
    for (int i = 0; i < 6; i++)
        in >> Nodes[i];
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++)
            in >> map[i][j];
}
/**
 * @描述: 初始化结点
 */
DAGList Init(int n)
{
    DAGList d = (DAGList)malloc(sizeof(DAGList));
    DAGList p = d;
    for (int i = 0; i < 6; i++)
    {
        if (map[n][i] != MAX_V)
        {
            DAGList q = (DAGList)malloc(sizeof(DAGList));
            q->dest = Nodes[i];
            q->spent = map[n][i];
            q->next = NULL;
            p->next = q;
            p = q;
        }
    }
    p->next = NULL;
    return d;
}
int main()
{
    saveG();
    DAGList vex[6][6];
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++)
            vex[i][j] = (DAGList)malloc(sizeof(DAGList));
    for (int i = 0; i < 6; i++)
        vex[0][i] = Init(i);
    int count = 0;
    bool updated = false;
    int c = 1;
update:
    for (int i = 0; i < 6; i++)
    {
        DAGList p = vex[c][i];
        DAGList q = vex[c - 1][i];
        while (q->next)
        {
            q = q->next;
            DAGList r = (DAGList)malloc(sizeof(DAGList));
            r->dest = q->dest;
            r->spent = q->spent;
            p->next = r;
            p = p->next;
        }
        p->next = NULL;
        DAGList t = vex[0][i];
        while (t->next)
        {
            t = t->next;
            for (int j = 0; j < 6; j++)
            {
                if (t->dest = Nodes[j])
                {
                    DAGList r = vex[c][i];
                    while (r->next)
                    {
                        r = r->next;
                        DAGList s = vex[c][i];
                        bool find = false;
                        while (s->next)
                        {
                            s = s->next;
                            if (s->dest == r->dest)
                            {
                                find = true;
                                break;
                            }
                        }
                        if (find && s->spent < r->spent + t->spent)
                        {
                            s->spent = r->spent + t->spent;
                            updated = true;
                        }
                        else if (!find)
                        {
                            DAGList o = (DAGList)malloc(sizeof(DAGList));
                            o->dest = r->dest;
                            o->spent = r->spent + t->spent;
                            o->next = NULL;
                            s->next = o;
                            updated = true;
                        }
                    }
                    break;
                }
            }
        }
    }
    if (updated && c < 5)
    {
        count++;
        c++;
        updated = false;
        goto update;
    }
    DAGList p = vex[count][0];
    int mx;
    while (p->next)
    {
        p = p->next;
        mx = p->spent;
    }
    cout << "S -> E的最长距离是：" << mx << endl;
    system("pause");
    return 0;
}