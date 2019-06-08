/*
 * @描述: 寻找强连通子图
 * @作者: 李天红
 * @Github: https://github.com/Celint/Algorithm-experiment-
 * @Date: 2019-06-04
 */
#include <iostream>
#include <fstream>
using namespace std;
char nodes[9]; // 结点
int map[9][9]; // 网络拓扑图
typedef struct Graph
{
    char dest;   // 目的结点
    Graph *next; // 下一个邻居
} * GraphList;
/**
 * @描述: 初始化网络拓扑图
 */
void saveG()
{
    ifstream in("scs.txt");
    for (int i = 0; i < 9; i++)
    {
        in >> nodes[i];
        for (int j = 0; j < 9; j++)
            in >> map[i][j];
    }
}
GraphList Init(int c)
{
    GraphList l = (GraphList)malloc(sizeof(GraphList));
    GraphList p = l;
    p->next = NULL;
    for (int i = 8; i >= 0; i--)
    {
        if (map[c][i] == 1)
        {
            GraphList q = (GraphList)malloc(sizeof(GraphList));
            q->dest = nodes[i];
            q->next = p->next;
            p->next = q;
        }
    }
    return l;
}
int main()
{
    // 保存网络拓扑图
    saveG();
    // 初始化
    GraphList vex[9][9];
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            vex[i][j] = (GraphList)malloc(sizeof(GraphList));
    cout << "各结点的邻居结点分别为：\n";
    for (int i = 0; i < 9; i++)
    {
        vex[0][i] = Init(i);
        GraphList p = vex[0][i];
        cout << nodes[i] << ": ";
        while (p->next)
        {
            p = p->next;
            cout << p->dest << " ";
        }
        cout << endl;
    }
    // 列出每个结点能访问的所有结点
    // 更新链表次数
    int updateCount = 0;
    // 是否更新
    bool updated = false;
    int c = 1;
update:
    // 遍历所有表
    for (int i = 0; i < 9; i++)
    {
        // 先把前一张表复制过来
        GraphList p = vex[c][i];
        GraphList q = vex[c - 1][i];
        while (q->next)
        {
            q = q->next;
            GraphList r = (GraphList)malloc(sizeof(GraphList));
            r->dest = q->dest;
            p->next = r;
            p = p->next;
        }
        p->next = NULL;
        // 访问邻居结点
        GraphList t = vex[0][i];
        while (t->next)
        {
            t = t->next;
            for (int j = 0; j < 9; j++)
            {
                if (t->dest == nodes[j])
                {
                    GraphList r = vex[c - 1][j];
                    while (r->next)
                    {
                        r = r->next;
                        // 比较自己的表和邻居的表
                        GraphList s = vex[c][i];
                        // 查找邻居表有的，我的表是否有
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
                        // 如果没找到就更新进去
                        if (!find)
                        {
                            GraphList o = (GraphList)malloc(sizeof(GraphList));
                            o->next = NULL;
                            o->dest = r->dest;
                            s->next = o;
                            updated = true;
                        }
                    }
                }
            }
        }
    }
    // 如果更新过，就再次更新
    if (updated && c < 8)
    {
        updateCount++;
        c++;
        updated = false;
        goto update;
    }
    // 每个结点输出它能访问的所有结点
    cout << "每个结点能访问的所有结点是：\n";
    for (int i = 0; i < 9; i++)
    {
        GraphList p = vex[updateCount][i];
        cout << nodes[i] << ": ";
        while (p->next)
        {
            p = p->next;
            cout << p->dest << ", ";
        }
        cout << endl;
    }
    cout << "强连通子图分别为：\n";
    bool flag[9] = {false};
    for (int i = 0; i < 9; i++)
    {
        char svex[9];
        int a = 0;
        if (flag[i] == false)
        {
            flag[i] = true;
            svex[a++] = nodes[i];
            GraphList p = vex[updateCount][i];
            while (p->next)
            {
                p = p->next;
                for (int j = 0; j < 9; j++)
                {
                    if (nodes[j] == p->dest)
                    {
                        GraphList q = vex[updateCount][j];
                        while (q->next)
                        {
                            q = q->next;
                            if (q->dest == nodes[i] && flag[j] == false)
                            {
                                flag[j] = true;
                                svex[a++] = nodes[j];
                                break;
                            }
                        }
                    }
                }
            }
        }
        for (int j = 0; j < a; j++)
            cout << svex[j] << " ";
        cout << endl;
    }
    cout << endl;
    system("pause");
    return 0;
}