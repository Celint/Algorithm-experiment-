/*
 * @描述: 多段图问题
 * @作者: 李天红
 * @Github: https://github.com/Celint/Algorithm-experiment-
 * @参考博客: https://blog.csdn.net/ncepuzhuang/article/details/8923790
 * @Date: 2019-06-07
 */
#include <iostream>
#include <fstream>
using namespace std;
int n, sta;
typedef struct MG
{
    int nabor;
    int spend;
    MG *next;
} * MGList;
struct nodes
{
    int state;
    int node;
};
/**
 * @描述: 最短花费路径
 */
int Cost(int state, int node, nodes nodes[], MGList vex[])
{
    for (int i = 0; i < n; i++)
    {
        if (nodes[i].node == node)
        {
            MGList p = vex[i];
            int spend[4];
            int c = 0;
            while (p->next)
            {
                p = p->next;
                if (state < 4)
                    spend[c++] = p->spend + Cost(state + 1, p->nabor, nodes, vex);
                else
                    spend[c++] = p->spend;
            }
            int min = spend[0];
            for (int j = 0; j < c; j++)
                if (min > spend[j])
                    min = spend[j];
            return min;
        }
    }
}
int main()
{
    ifstream in("MG.txt");
    in >> n >> sta;
    cout << "一共有" << n << "个结点，" << sta << "个阶段\n";
    // 初始化多段图
    nodes nodes[n];
    MGList vex[n];
    int c = 0;
    for (int i = 0; i < sta; i++)
    {
        int m;
        in >> m;
        for (int j = 0; j < m; j++)
        {
            nodes[c].state = i + 1;
            in >> nodes[c++].node;
        }
    }
    cout << "每个结点及其阶段：\n";
    for (int i = 0; i < n; i++)
        cout << "结点：" << nodes[i].node << ", 阶段：" << nodes[i].state << endl;
    for (int i = 0; i < n; i++)
    {
        int m;
        in >> m;
        vex[i] = (MGList)malloc(sizeof(MGList));
        MGList q = vex[i];
        for (int j = 0; j < m; j++)
        {
            MGList p = (MGList)malloc(sizeof(MGList));
            in >> p->nabor;
            in >> p->spend;
            p->next = NULL;
            q->next = p;
            q = p;
        }
        q->next = NULL;
    }
    cout << "\n多段图的邻接表为：\n";
    for (int i = 0; i < n; i++)
    {
        MGList p = vex[i];
        cout << nodes[i].node << ": ";
        while (p->next)
        {
            p = p->next;
            cout << " -> " << p->nabor << ", " << p->spend;
        }
        cout << endl;
    }
    cout << endl;
    cout << "最少花费为：" << Cost(1, 1, nodes, vex) << endl;
    system("pause");
    return 0;
}