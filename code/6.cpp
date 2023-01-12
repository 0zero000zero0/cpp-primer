///
///@file 6.cpp
///@author Zero (email:2405549856@qq.com)
///@brief C++ primer chapter 6:函数
///@date 2023-01-12
///
#include <D:\C in vsocde\c++ primer\c++ primer\header\Chapter6.h>
#include <stdc++.h>
using namespace std;

int count_calls(); // 函数声明(函数原型)
int count_calls();
int main()
{
    // 函数
    cout << fact(5) << endl;
    // C++中如果函数定义时的参数列表为空，则该函数不要参数(C语言是待定推测)
    // C++中每个参数都要有声明的类型,不能用f(int
    // one,two)这种形式,函数中最外层的作用域中的局部变量不能使用和函数形参一样的名字
    // 局部静态变量staitc执行时该变量都是上一次执行的值,直到程序结束才会被释放.局部外不可见,如果不初始化那么就执行默认初始化
    for (size_t i = 0; i < 10; i++)
    {
        /* code */
        cout << count_calls() << endl;
    }

    return 0;
}