/*
 * @描述: 找零问题：如何使用面值25、10、5、1美分的硬币兑换63美分使硬币总数最小？
 * @作者: 李天红
 * @Github: https://github.com/Celint/Algorithm-experiment-
 * @Date: 2019-05-07
 */
#include <iostream>
using namespace std;
int main()
{
    int n = 63, count = 0; //63美分
    //找25美分的
    int m = n / 25;
    cout << "找" << m << "个25美分的, ";
    while (m--)
    {
        count++;
        n -= 25;
    }
    //再找10美分的
    m = n / 10;
    cout << "再找" << m << "个10美分的, ";
    while (m--)
    {
        count++;
        n -= 10;
    }
    //再找5美分的
    m = n / 5;
    cout << "再找" << m << "个5美分的, ";
    while (m--)
    {
        count++;
        n -= 5;
    }
    //最后是1美分的；
    count += n;
    cout << "最后是" << n << "个1美分的" << endl
         << "总共用了" << count << "个硬币" << endl;
    system("pause");
    return 0;
}