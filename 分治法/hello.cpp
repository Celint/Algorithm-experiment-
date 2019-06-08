/*
 * @描述: 寻找第k小的数
 * @作者: 李天红
 * @Github: https://github.com/Celint/Algorithm-experiment-
 * @参考博客: https://segmentfault.com/a/1190000008322873?utm_source=tuicool&utm_medium=referral&tdsourcetag=s_pctim_aiomsg
 * @Date: 2019-04-28
 */
#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;

int InsertSort(int array[], int left, int right);
int GetPivotIndex(int array[], int left, int right);
int Partition(int array[], int left, int right, int pivot_index);
int BFPRT(int array[], int left, int right, int k);

int main()
{
    ifstream in("k-th.txt");
    int n, k;
    in >> k;
    in >> n;
    int array[n], a[n];
    for (int i = 0; i < n; i++)
    {
        in >> array[i];
        // a[i] = arr[i];
    }
    // 因为是以 k 为划分，所以还可以求出第 k 小值
    cout << "数组大小为：" << n << ", 第 " << k << " 小值为：" << array[BFPRT(array, 0, n, k)] << endl;
    system("pause");
    return 0;
}

/**
 * 对数组 array[left, right] 进行插入排序，并返回 [left, right]
 * 的中位数。
 */
int InsertSort(int array[], int left, int right)
{
    int temp;
    int j;

    for (int i = left + 1; i <= right; i++)
    {
        temp = array[i];
        j = i - 1;
        while (j >= left && array[j] > temp)
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = temp;
    }

    return ((right - left) >> 1) + left;
}

/**
 * 数组 array[left, right] 每五个元素作为一组，并计算每组的中位数，
 * 最后返回这些中位数的中位数下标（即主元下标）。
 *
 * @attention 末尾返回语句最后一个参数多加一个 1 的作用其实就是向上取整的意思，
 * 这样可以始终保持 k 大于 0。
 */
int GetPivotIndex(int array[], int left, int right)
{
    if (right - left < 5)
        return InsertSort(array, left, right);

    int sub_right = left - 1;

    // 每五个作为一组，求出中位数，并把这些中位数全部依次移动到数组左边
    for (int i = left; i + 4 <= right; i += 5)
    {
        int index = InsertSort(array, i, i + 4);
        swap(array[++sub_right], array[index]);
    }

    // 利用 BFPRT 得到这些中位数的中位数下标（即主元下标）
    return BFPRT(array, left, sub_right, ((sub_right - left + 1) >> 1) + 1);
}

/**
 * 利用主元下标 pivot_index 进行对数组 array[left, right] 划分，并返回
 * 划分后的分界线下标。
 */
int Partition(int array[], int left, int right, int pivot_index)
{
    swap(array[pivot_index], array[right]); // 把主元放置于末尾

    int partition_index = left; // 跟踪划分的分界线
    for (int i = left; i < right; i++)
    {
        if (array[i] < array[right])
        {
            swap(array[partition_index++], array[i]); // 比主元小的都放在左侧
        }
    }

    swap(array[partition_index], array[right]); // 最后把主元换回来

    return partition_index;
}

/**
 * 返回数组 array[left, right] 的第 k 小数的下标
 */
int BFPRT(int array[], int left, int right, int k)
{
    int pivot_index = GetPivotIndex(array, left, right);              // 得到中位数的中位数下标（即主元下标）
    int partition_index = Partition(array, left, right, pivot_index); // 进行划分，返回划分边界
    int num = partition_index - left + 1;

    if (num == k)
        return partition_index;
    else if (num > k)
        return BFPRT(array, left, partition_index - 1, k);
    else
        return BFPRT(array, partition_index + 1, right, k - num);
}