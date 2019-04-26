/*
 * @描述: 选择排序
 * @作者: 李天红
 * @Github: https://github.com/Celint/Algorithm-experiment-
 * @Date: 2019-04-26
 */
#include <iostream>
// #include <fstream>
using namespace std;
void SelectSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] > arr[j])
            {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
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
    SelectSort(arr, n);
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
    system("pause");
    return 0;
}