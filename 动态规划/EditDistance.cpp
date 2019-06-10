/*
 * @描述: 比对
 * @作者: 李天红
 * @Github: https://github.com/Celint/Algorithm-experiment-
 * @Date: 2019-06-10
 */
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
/**
 * @描述: 查看这两个字符串是否匹配
 */
int differ(char a, char b)
{
    if (a == b)
        return 0;
    else
        return 1;
}
/**
 * @描述: 计算不匹配的字符串长度
 */
int DPEditDis(string a, string b)
{
    int m = a.length(), n = b.length();
    int e[m + 1][n + 1];
    for (int i = 0; i <= m; i++)
        e[i][0] = i;
    for (int i = 0; i <= n; i++)
        e[0][i] = i;
    for (int i = 0; i <= m; i++)
        for (int j = 0; j <= n; j++)
            e[i][j] = min(min(e[i - 1][j] + 1, e[i][j - 1] + 1), e[i - 1][j - 1] + differ(a[i], b[j]));
    return e[m][n];
}
int main()
{
    string a, b;
    cout << "要比对的串为：\n";
    ifstream in1("ED1.txt");
    while (getline(in1, a))
        cout << a;
    cout << endl;
    ifstream in2("ED2.txt");
    while (getline(in2, b))
        cout << b;
    cout << endl;
    cout << "The Length of Mismatch is " << DPEditDis(a, b) << endl;
    system("pause");
    return 0;
}