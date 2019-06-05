/*
 * @描述: 距离矢量路由算法实验
 * @作者: 李天红
 * @Date: 2019-06-03
 */
#include <iostream>
#include <fstream>
using namespace std;
#define MAX_DISTANCE 65535 //最大距离，无穷远
typedef char destination;
typedef char nextjump;
typedef int spend;
char node[8];    //结点
spend map[8][8]; //网络拓扑图
typedef struct RouterTable
{
    destination dest;
    nextjump jump;
    spend spen;
    RouterTable *next;
} * RouterList;
/**
 * @描述: 1.初始化网络拓扑图
 */
void saveG()
{
    ifstream in("routerG.txt");
    for (int i = 0; i < 8; i++)
        in >> node[i];
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            in >> map[i][j];
        }
    }
}
/**
 * @描述: 2.为每个网络节点初始化并保存一张路由表
 */
RouterList Init(int n)
{
    RouterList l = (RouterList)malloc(sizeof(RouterList));
    RouterList p = l;
    p->next = NULL;
    for (int i = 7; i >= 0; i--)
    {
        if (map[n][i] != MAX_DISTANCE)
        {
            RouterList q = (RouterList)malloc(sizeof(RouterList));
            q->dest = node[i];
            q->jump = node[i];
            q->spen = map[n][i];
            q->next = p->next;
            p->next = q;
        }
    }
    return l;
}
int main()
{
    // 1.保存网络拓扑图
    saveG();
    // 2.为每个网络节点初始化并保存一张路由表
    RouterList routers[8][8];
    // 初始化
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            routers[i][j] = (RouterList)malloc(sizeof(RouterList));
    // 初始路由表
    for (int i = 0; i < 8; i++)
        routers[0][i] = Init(i);
    // 3.给每个网络节点一次执行距离矢量路由更新的机会
    // 更新次数
    int updateCount = 0;
    // 是否更新
    bool updated = false;
    int c = 1;
update:
    // 遍历所有的表
    for (int i = 0; i < 8; i++)
    {
        // 先把前一张表复制过来
        RouterList p = routers[c][i];
        RouterList q = routers[c - 1][i];
        while (q->next)
        {
            q = q->next;
            RouterList r = (RouterList)malloc(sizeof(RouterList));
            r->dest = q->dest;
            r->jump = q->jump;
            r->spen = q->spen;
            p->next = r;
            p = p->next;
        }
        p->next = NULL;
        // 访问邻居结点
        RouterList t = routers[0][i];
        while (t->next)
        {
            t = t->next;
            if (t->spen == 0)
                continue;
            else
            {
                for (int j = 0; j < 8; j++)
                {
                    if (t->dest == node[j])
                    {
                        RouterList r = routers[c - 1][j];
                        while (r->next)
                        {
                            r = r->next;
                            // 比较自己的表与邻居的表
                            RouterList s = routers[c][i];
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
                            // 如果找到了，就比较
                            if (find)
                            {
                                // 如果新的路径更短，就更新
                                if (s->spen > r->spen + t->spen)
                                {
                                    s->spen = r->spen + t->spen;
                                    s->jump = t->dest;
                                    updated = true;
                                }
                            }
                            // 如果没找到，就更新进去
                            else
                            {
                                RouterList o = (RouterList)malloc(sizeof(RouterList));
                                o->next = NULL;
                                o->dest = r->dest;
                                o->jump = t->dest;
                                o->spen = r->spen + t->spen;
                                s->next = o;
                                updated = true;
                            }
                        }
                    }
                }
            }
        }
    }
    // 如果更新过，就再次更新
    if (updated && c < 7)
    {
        updateCount++;
        c++;
        updated = false;
        goto update;
    }
    // 4.输出一个节点从初始到稳定的所有路由表数据以及更新次数
    cout << "一共更新了" << updateCount << "次\n";
    for (int i = 0; i <= updateCount; i++)
    {
        cout << "第" << i << "次：\n\n";
        for (int j = 0; j < 8; j++)
        {
            RouterList p = routers[i][j];
            cout << node[j] << "号表：\n";
            while (p->next)
            {
                p = p->next;
                cout << p->dest << ", " << p->jump << ", " << p->spen << endl;
            }
            cout << endl;
        }
        cout << "=========" << endl;
    }
    system("pause");
    return 0;
}