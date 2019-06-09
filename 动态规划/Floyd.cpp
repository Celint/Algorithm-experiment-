/*
 * @描述: Floyd 所有点对最短路径算法
 * @作者: 李天红
 * @Github: https://github.com/Celint/Algorithm-experiment-
 * @Date: 2019-06-09
 */
#include <iostream>
#include <fstream>
#define MAXDISTANCE 65535
using namespace std;
int nodes[4];  //结点
int map[4][4]; //网络拓扑图
typedef struct FloydTable
{
    int dest;
    int spen;
    FloydTable *next;
} * FloydList;
/**
 * @描述: 初始化网络拓扑图
 */
void saveG()
{
    ifstream in("Floyd.txt");
    for (int i = 0; i < 4; i++)
        in >> nodes[i];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            in >> map[i][j];
}
/**
 * @描述: 初始化图
 */
FloydList Init(int n)
{
    FloydList f = (FloydList)malloc(sizeof(FloydList));
    FloydList p = f;
    for (int i = 0; i < 4; i++)
    {
        if (map[n][i] != MAXDISTANCE)
        {
            FloydList q = (FloydList)malloc(sizeof(FloydList));
            q->dest = nodes[i];
            q->spen = map[n][i];
            q->next = NULL;
            p->next = q;
            p = q;
        }
    }
    p->next = NULL;
    return f;
}
int main()
{
    saveG();
    FloydList floyd[4][4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            floyd[i][j] = (FloydList)malloc(sizeof(FloydList));
    for (int i = 0; i < 4; i++)
        floyd[0][i] = Init(i);
    int count = 0;
    bool updated;
    int c = 1;
update:
    for (int i = 0; i < 4; i++)
    {
        FloydList p = floyd[c][i];
        FloydList q = floyd[c - 1][i];
        while (q->next)
        {
            q = q->next;
            FloydList r = (FloydList)malloc(sizeof(FloydList));
            r->dest = q->dest;
            r->spen = q->spen;
            p->next = r;
            p = p->next;
        }
        p->next = NULL;
        FloydList t = floyd[0][i];
        while (t->next)
        {
            t = t->next;
            for (int j = 0; j < 4; j++)
            {
                if (t->dest == nodes[j])
                {
                    FloydList r = floyd[c - 1][j];
                    while (r->next)
                    {
                        r = r->next;
                        FloydList s = floyd[c][i];
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
                        if (find && s->spen > r->spen + t->spen)
                        {
                            s->spen = r->spen + t->spen;
                            updated = true;
                        }
                        else if (!find)
                        {
                            FloydList o = (FloydList)malloc(sizeof(FloydList));
                            o->dest = r->dest;
                            o->spen = r->spen + t->spen;
                            o->next = NULL;
                            updated = true;
                        }
                    }
                }
            }
        }
    }
    if (updated && c < 3)
    {
        count++;
        c++;
        updated = false;
        goto update;
    }
    for (int i = 0; i < 4; i++)
    {
        FloydList p = floyd[count][i];
        cout << nodes[i] << ": ";
        while (p->next)
        {
            p = p->next;
            cout << "到" << p->dest << "的距离为：" << p->spen << "    ";
        }
        cout << endl;
    }
    system("pause");
    return 0;
}