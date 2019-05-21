/*
 * @描述: 动态规划实现背包问题
 * @作者: 李天红
 * @Github: https://github.com/Celint/Algorithm-experiment-
 * @Date: 2019-05-16
 */
#include <iostream>
#include <fstream>
using namespace std;
/**
 * @描述: 物品的数据结构
 */
typedef struct thing
{
    int value;
    int weight;
};
int main()
{
    ifstream in("knapsack.txt");
    int n;
    in >> n;
    thing arr[100];
    for (int i = 0; i < 100; i++)
        in >> arr[i].value;
    for (int i = 0; i < 100; i++)
        in >> arr[i].weight;
    cout << "背包大小为：" << n << endl;
    cout << "\n每件物品的价值、重量分别为：" << endl;
    for (int i = 0; i < 100; i++)
    {
        cout << arr[i].value << "\t" << arr[i].weight << endl;
    }
    cout << endl;
    int d[100][n + 1];
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            d[i][j] = (i == 0 ? 0 : d[i - 1][j]);
            if (j >= arr[i].weight)
                d[i][j] = max(d[i][j], d[i - 1][j - arr[i].weight] + arr[i].value);
        }
    }
    cout << "最终装包价值为：" << d[99][n] << endl
         << endl;
    system("pause");
    return 0;
}