/*
 * @描述: 快速排序算法
 * @作者: 李天红
 * @Github: https://github.com/Celint/Algorithm-experiment-
 * @Date: 2019-04-18
 */
#include <iostream>
// #include <fstream>
using namespace std;
/**
 * @描述: 快速排序
 */
void QuickSort(int arr[], int left, int right)
{
    if (left > right)
        return;
    int i = left, j = right, flag = arr[left];
    while (i != j)
    {
        while (i < j && arr[j] >= flag)
            j--;
        while (i < j && arr[i] <= flag)
            i++;
        if (i < j)
        {
            int t = arr[i];
            arr[i] = arr[j];
            arr[j] = t;
        }
    }
    arr[left] = arr[i];
    arr[i] = flag;
    QuickSort(arr, left, i - 1);
    QuickSort(arr, i + 1, right);
}
int main()
{
    //为了调试方便，将待输入的数据存放到一个text文件里面
    // ifstream in("quick.txt");
    // int n;
    // in >> n;
    // int arr[n];
    // for (int i = 0; i < n; i++)
    //     in >> arr[i];
    int n;
    cin >> n;
    int arr[n];
    QuickSort(arr, 0, n - 1);
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
    system("pause");
    return 0;
}