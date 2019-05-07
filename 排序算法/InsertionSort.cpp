/*
 * @描述: 插入排序
 * @作者: 李天红
 * @Github: https://github.com/Celint/Algorithm-experiment-
 * @Date: 2019-04-26
 */
#include <iostream>
// #include <fstream>
using namespace std;
/**
 * @描述: 插入排序
 */
void InsertionSort(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        int temp = arr[i];
        int j = i;
        //从右开始找，跟比最右边大的换位置
        while (j > 0 && temp < arr[j - 1])
        {
            arr[j] = arr[j - 1];
            j--;
        }
        //在循环结束的位置插入
        arr[j] = temp;
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
    InsertionSort(arr, n);
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
    system("pause");
    return 0;
}