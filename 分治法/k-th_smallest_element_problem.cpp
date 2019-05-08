/*
 * @描述: 寻找第k小的值
 * @作者: 李天红
 * @Github: https://github.com/Celint/Algorithm-experiment-
 * @Date: 2019-04-27
 */
#include <iostream>
#include <fstream>
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
int select(int arr[], int left, int right, int key)
{
    if (right - left < 75)
    {
        MergeSort(arr, left, right);
        return arr[left + key];
    }
    // 将数组分为n/5组，取每组的中位数
    int M[(right - left + 1) / 5], i;
    for (int i = 0; i < (right - left + 1) / 5; i++)
    {
        MergeSort(arr, i * 5, i * 5 + 4);
        M[i] = arr[i * 5 + 2];
    }
    // 把中位数数组的中位数存在x变量中
    int x = select(M, 0, i, i / 2);
    // 将比x小的放在数组S1，比x大的放在S2数组
    int S1[right - left + 1], S2[right - left + 1], s1 = 0, s2 = 0;
    for (int i = left; i <= right; i++)
    {
        if (arr[i] <= x)
            S1[s1++] = arr[i];
        else
            S2[s2++] = arr[i];
    }
    if (s1 >= key)
        return select(S1, 0, s1 - 1, key);
    else
        return select(S2, 0, s2 - 1, key - s1);
}
int main()
{
    ifstream in("k-th.txt");
    int n, k;
    in >> k;
    in >> n;
    int arr[n], a[n];
    for (int i = 0; i < n; i++)
    {
        in >> arr[i];
        a[i] = arr[i];
    }
    cout << "找第" << k << "小的数, 数组的大小为: " << n << endl;
    MergeSort(a, 0, n - 1);
    cout << "归并排序查找第" << k << "小的数为：" << a[k - 1] << endl;
    // for (int i = 0; i < n; i++)
    //     cout << a[i] << " ";
    // cout << endl;
    cout << "BFPR查找第" << k << "小的数为：" << select(arr, 0, n - 1, k - 1) << endl;
    system("pause");
    return 0;
}
