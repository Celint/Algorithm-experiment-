/*
 * @描述: 程序实现循环赛日程表安排问题
 * @作者: 李天红
 * @Github: https://github.com/Celint/Algorithm-experiment-
 * @Date: 2019-04-16
 */
#include <iostream>
using namespace std;
#define MAX 1024
int tour[MAX][MAX];
/**
 * @描述: 生成日程表的函数
 */
void Tournament(int n, int m)
{
    if (n == 2)
    { //先填完第1、2行
        tour[m][0] = m + 1;
        tour[m + 1][1] = m + 1;
        tour[m][1] = m + 2;
        tour[m + 1][0] = m + 2;
    }
    else
    {
        Tournament(n / 2, m);
        Tournament(n / 2, m + n / 2);
        for (int i = m; i < m + n / 2; i++)
        { //填左下角
            for (int j = n / 2; j < n; j++)
            {
                tour[i][j] = tour[i + n / 2][j - n / 2];
            }
        }
        for (int i = m + n / 2; i < m + n; i++)
        { //填右下角
            for (int j = n / 2; j < n; j++)
            {
                tour[i][j] = tour[i - n / 2][j - n / 2];
            }
        }
    }
}
int main()
{
    int k;
    cout << "请输入2^k位选手中k的值，k = ";
    do
    {
        cin >> k;
    } while (k < 0 || k > 15);
    int n = 0x1 << k; //左移k位，表示2^k
    Tournament(n, 0);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%3d", tour[i][j]);
        }
        cout << endl;
    }
    system("pause");
    return 0;
}