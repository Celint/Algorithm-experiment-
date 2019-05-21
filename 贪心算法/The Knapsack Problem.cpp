/*
 * @描述: 贪婪算法解背包问题
 * @作者: 李天红
 * @Github: https://github.com/Celint/Algorithm-experiment-
 * @Date: 2019-05-07
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
    double eachValue;
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
    cout << "\n每件物品的价值、重量、单位价值分别为：" << endl;
    for (int i = 0; i < 100; i++)
    {
        arr[i].eachValue = double(arr[i].value) / double(arr[i].weight);
        cout << arr[i].value << ", " << arr[i].weight << ", " << arr[i].eachValue << endl;
    }
    cout << endl;
    //冒泡排序对物品单位价值进行从大到小排序
    int m = 100;
    while (m != 0)
    {
        for (int i = 0; i < m - 1; i++)
        {
            if (arr[i].eachValue < arr[i + 1].eachValue)
            {
                thing temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
            }
        }
        m--;
    }
    //排序后
    cout << "\n排序后：";
    cout << "\n每件物品的价值、重量、单位价值分别为：" << endl;
    for (int i = 0; i < 100; i++)
        cout << arr[i].value << "\t" << arr[i].weight << "\t" << arr[i].eachValue << endl;
    cout << endl;
    int i = 0;
    //装包, 先把前面的揽走
    thing total;
    total.value = 0;
    total.weight = 0;
    while (n - arr[i].weight >= 0)
    {
        total.weight += arr[i].weight;
        total.value += arr[i].value;
        n -= arr[i].weight;
        i++;
    }

    cout << endl;
    //后面还可以装下，把能装下的装下
    for (int j = i; j < 100; j++)
    {
        if (n - arr[j].weight >= 0)
        {
            total.weight += arr[j].weight;
            total.value += arr[j].value;
            n -= arr[j].weight;
        }
    }
    cout << "\n最终装包：大小为" << total.weight << ", 价值为" << total.value << endl;
    system("pause");
    return 0;
}