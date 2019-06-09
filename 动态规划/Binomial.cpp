/*
 * @描述: 二项式系数算法
 * @作者: 李天红
 * @Github: https://github.com/Celint/Algorithm-experiment-
 * @Date: 2019-06-09
 */
#include <iostream>
#include <fstream>
using namespace std;
/**
 * @描述: 求二项式系数
 */
int Binomial(int n, int k)
{
    int c[n + 1][k + 1];
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= min(i, k); j++)
        {
            if (j == 0 || j == n)
                c[i][j] = 1;
            else
                c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
        }
    }
    return c[n][k];
}
int main()
{
    int n, k;
    ifstream in("Binomial.txt");
    in >> k >> n;
    cout << "C[" << n << "," << k << "] = " << Binomial(n, k) << endl;
    system("pause");
    return 0;
}