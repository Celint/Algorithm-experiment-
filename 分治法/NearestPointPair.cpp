/*
 * @描述: 最近点对问题，分别用蛮力法和分治法
 * @作者: 李天红
 * @Github: https://github.com/Celint/Algorithm-experiment-
 * @Date: 2019-05-09
 */
#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
using namespace std;
#define MAx_DISTANCE 512.0
/**
 * @描述: 快速排序算法
 */
void QuickSort(double arr[], int left, int right)
{
    if (left > right)
        return;
    int i = left, j = right;
    double flag = arr[left];
    while (i != j)
    {
        while (i < j && arr[j] >= flag)
            j--;
        while (i < j && arr[i] <= flag)
            i++;
        if (i < j)
        {
            double t = arr[i];
            arr[i] = arr[j];
            arr[j] = t;
        }
    }
    arr[left] = arr[i];
    arr[i] = flag;
    QuickSort(arr, left, i - 1);
    QuickSort(arr, i + 1, right);
}
/**
 * @描述: 蛮力法求最近点对问题
 */
void BruteForce(int arr[][2], int n)
{
    double result[n * (n - 1) / 2], flag;
    int c = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int x = pow(arr[j][0] - arr[i][0], 2);
            int y = pow(arr[j][1] - arr[i][1], 2);
            result[c] = pow(double(x) + double(y), 0.5);
            if (c == 0)
                flag = result[0];
            // cout << "点 " << i + 1 << " 与点 " << j + 1 << " 的距离为：" << result[c] << endl;
            if (result[c] < flag)
                flag = result[c];
            c++;
        }
    }
    cout << "蛮力法求最近点对距离为：" << flag;
    QuickSort(result, 0, c - 1);
    // for (int i = 0; i < c; i++)
    //     cout << result[i] << " ";
    // cout << endl;
}
/**
 * @描述: 归并排序，按点的x坐标进行排序
 */
void MergeSort(int arr[][2], int left, int right, int a)
{
    //当分得足够小时
    if (right - left < 2)
    {
        if (arr[left][a] > arr[right][a])
        {
            int temp = arr[left][0];
            arr[left][0] = arr[right][0];
            arr[right][0] = temp;
            temp = arr[left][1];
            arr[left][1] = arr[right][1];
            arr[right][1] = temp;
        }
        return;
    }
    MergeSort(arr, left, (right + left) / 2, a);
    MergeSort(arr, (left + right) / 2 + 1, right, a);
    //合并
    int t[right - left + 1][2]; //临时数组
    int x = 0, i = left, j = (left + right) / 2 + 1;
    while (i <= (right + left) / 2 && j <= right)
    {
        if (arr[i][a] <= arr[j][a])
        {
            t[x][0] = arr[i][0];
            t[x++][1] = arr[i++][1];
        }
        else
        {
            t[x][0] = arr[j][0];
            t[x++][1] = arr[j++][1];
        }
    }
    while (i <= (right + left) / 2 && j > right)
    {
        t[x][0] = arr[i][0];
        t[x++][1] = arr[i++][1];
    }
    while (i > (right + left) / 2 && j <= right)
    {
        t[x][0] = arr[j][0];
        t[x++][1] = arr[j++][1];
    }
    for (int y = 0; y <= right - left; y++)
    { //把t数组复制到arr数组
        arr[y + left][0] = t[y][0];
        arr[y + left][1] = t[y][1];
    }
}
/**
 * @描述: 分治法
 */
double NearestPoints(int arr[][2], int left, int right)
{
    if (right - left == 0)
    {
        return MAx_DISTANCE;
    }
    else if (right - left == 1)
    {
        int x = pow(arr[right][0] - arr[left][0], 2);
        int y = pow(arr[right][1] - arr[left][1], 2);
        return pow(double(x) + double(y), 0.5);
    }
    double minLeft = NearestPoints(arr, left, (right + left) / 2);
    double minRight = NearestPoints(arr, (right + left) / 2 + 1, right);
    double minPair = minLeft > minRight ? minRight : minLeft;
    double mid = (arr[(right + left) / 2][0] + arr[(right + left) / 2 + 1][0]) / 2.0;
    int a = left, b = (right + left) / 2;
    while (arr[a++][0] < mid - minPair)
        ;
    if (arr[a][0] > mid)
        return minPair;
    while (arr[b++][0] < mid + minPair)
        ;
    if (b == (right + left) / 2 + 1 && arr[b][0] >= mid + minPair)
        return minPair;
    MergeSort(arr, a, b, 1); //对于在mid - minPair到mid + minPair范围的点对y轴排序
    for (int i = a; i < b; i++)
    {
        int x = pow(arr[i][0] - arr[i + 1][0], 2);
        int y = pow(arr[i][1] - arr[i + 1][1], 2);
        double result = pow(double(x) + double(y), 0.5);
        if (result < minPair)
            minPair = result;
    }
    return minPair;
}
int main()
{
    clock_t start, finish;
    double totaltime;
    ifstream in("points.txt");
    int n;
    in >> n;
    int arr[n][2], a[n][2];
    cout << "一共有" << n << "个点\n";
    for (int i = 0; i < n; i++)
    {
        in >> arr[i][0];
        in >> arr[i][1];
        // cout << arr[i][0] << " " << arr[i][1] << endl;
        a[i][0] = arr[i][0];
        a[i][1] = arr[i][1];
    }
    // 蛮力法：
    start = clock();
    BruteForce(a, n);
    finish = clock();
    totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
    cout << ", 耗时为" << totaltime << endl;
    // 分治法：  按x轴坐标进行排序
    start = clock();
    MergeSort(arr, 0, n - 1, 0);
    cout << "分治法求最近点对距离为：" << NearestPoints(arr, 0, n - 1);
    finish = clock();
    totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
    cout << ", 耗时为" << totaltime << endl;
    system("pause");
    return 0;
}