/*
 * @描述: 冒泡排序
 * @作者: 李天红
 * @Github: https://github.com/Celint/Algorithm-experiment-
 * @Date: 2019-04-26
 */
#include <iostream>
// #include <fstream>
using namespace std;
/**
 * @描述: 冒泡排序
 */
void BubbleSort(int arr[], int n)
{
    while (n != 0)
    {
        for (int i = 0; i < n - 1; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
            }
        }
        n--;
    }
}
int main()
{
    // ifstream in("sort.txt");
    // int n;
    // in >> n;
    // int arr[n];
    // for (int i = 0; i < n; i++)
    // {
    //     in >> arr[i];
    //     cout << arr[i] << " ";
    // }
    // cout << endl;
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    BubbleSort(arr, n);
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
    system("pause");
    return 0;
}