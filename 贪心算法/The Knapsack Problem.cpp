/*
 * @描述: 贪婪算法解背包问题
 * @作者: 李天红
 * @Github: https://github.com/Celint/Algorithm-experiment-
 * @Date: 2019-05-07
 */
#include <iostream>
#include <fstream>
using namespace std;
int main()
{
    ifstream in("knapsack.txt");
    int n;
    in >> n;
    int value[100], weight[100];
    for (int i = 0; i < 100; i++)
        in >> value[i];
    for (int i = 0; i < 100; i++)
        in >> weight[i];
    cout << "背包大小为：" << n << endl;
    cout << "价值为：" << endl;
    for (int i = 0; i < 100; i++)
        cout << value[i] << " ";
    cout << "\n重量分别为：" << endl;
    for (int i = 0; i < 100; i++)
        cout << weight[i] << " ";
    cout << "\n每件物品的单位价值高低分别为：" << endl;
    double eachValue[100];
    for (int i = 0; i < 100; i++)
    {
        eachValue[i] = double(value[i]) / double(weight[i]);
        cout << eachValue[i] << " ";
    }
    cout << endl;
    //冒泡排序对物品进行从大到小排序
    int m = 100;
    while (m != 0)
    {
        for (int i = 0; i < m - 1; i++)
        {
            if (eachValue[i] < eachValue[i + 1])
            {
                int temp = eachValue[i];
                eachValue[i] = eachValue[i + 1];
                eachValue[i + 1] = temp;
                temp = value[i];
                value[i] = value[i + 1];
                value[i + 1] = temp;
                temp = weight[i];
                weight[i] = weight[i + 1];
                weight[i + 1] = temp;
            }
        }
        m--;
    }
    //排序后
    cout << "\n排序后：\n";
    cout << "价值为：" << endl;
    for (int i = 0; i < 100; i++)
        cout << value[i] << " ";
    cout << "\n重量分别为：" << endl;
    for (int i = 0; i < 100; i++)
        cout << weight[i] << " ";
    cout << "\n每件物品的单位价值高低分别为：" << endl;
    for (int i = 0; i < 100; i++)
    {
        eachValue[i] = double(value[i]) / double(weight[i]);
        cout << eachValue[i] << " ";
    }
    cout << endl;
    int i = 0;
    //装包, 先把前面的揽走
    int totalWeight = 0, totalValue = 0;
    while (n - weight[i] >= 0)
    {
        totalWeight += weight[i];
        totalValue += value[i];
        n -= weight[i];
        i++;
    }

    cout << endl
         << i << " " << n << endl;
    //后面还可以装下，把能装下的装下
    for (int j = i; j < 100; j++)
    {
        if (n - weight[j] >= 0)
        {
            totalWeight += weight[j];
            totalValue += value[j];
            n -= weight[j];
            cout << j << " " << n << ", ";
        }
    }
    cout << "\n最终装包：大小为" << totalWeight << ", 价值为" << totalValue << endl;
    system("pause");
    return 0;
}