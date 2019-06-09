/*
 * @描述: 回溯法求八皇后问题
 * @作者: 李天红
 * @Github: https://github.com/Celint/Algorithm-experiment-
 * @Date: 2019-05-21
 */
#include <iostream>
#include <fstream>
using namespace std;
int c = 1, q, count = 0;
/**
 * @描述: 回溯查找
 */
void Search(int c[], int cur)
{
    if (cur == q)
    {
        cout << "可能的解为：" << endl;
        for (int i = 0; i < q; i++)
        {
            cout << c[i] << " ";
        }
        cout << endl;
        count++;
    }
    else
    {
        for (int i = 0; i < q; i++)
        {
            int yes = 1;
            c[cur] = i;
            for (int j = 0; j < cur; j++)
            {
                if (c[j] == c[cur] || c[j] + cur - j == c[cur] || c[j] - cur + j == c[cur])
                {
                    yes = 0;
                    break;
                }
            }
            if (yes)
                Search(c, cur + 1);
        }
    }
}
int main()
{
    int n;
    ifstream in("Queen.txt");
    in >> n;
    int c[n];
    q = n;
    Search(c, 0);
    cout << "一共有" << count << "种解法" << endl;
    system("pause");
    return 0;
}
