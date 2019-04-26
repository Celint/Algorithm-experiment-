/*
 * @描述: 归并排序
 * @作者: 李天红
 * @Github: https://github.com/Celint/Algorithm-experiment-
 * @Date: 2019-04-18
 */
#include <iostream>
// #include <fstream>
using namespace std;
/**
 * @描述: 归并排序
 */
void MergeSort(int arr[], int left, int right)
{
    //当分得足够小时
    if (right - left < 2)
    {
        if (arr[left] > arr[right])
        {
            int temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
        }
        return;
    }
    MergeSort(arr, left, (right + left) / 2);
    MergeSort(arr, (left + right) / 2 + 1, right);
    //合并
    int t[right - left + 1]; //临时数组
    int x = 0, i = left, j = (left + right) / 2 + 1;
    while (i <= (right + left) / 2 && j <= right)
    {
        if (arr[i] <= arr[j])
            t[x++] = arr[i++];
        else
            t[x++] = arr[j++];
    }
    while (i <= (right + left) / 2 && j > right)
        t[x++] = arr[i++];
    while (i > (right + left) / 2 && j <= right)
        t[x++] = arr[j++];
    for (int y = 0; y <= right - left; y++) //把t数组复制到arr数组
        arr[y + left] = t[y];
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
    MergeSort(arr, 0, n - 1);
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    system("pause");
    return 0;
}