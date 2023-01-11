///
///@file 5.cpp
///@author Zero (email:2405549856@qq.com)
///@brief c++ primer 5th chapter theme:语句
///@date 2023-01-11
///
#include <D:\C in vsocde\c++ primer\c++ primer\header\variety.h>
#include <stdc++.h>
using namespace std;

int main()
{
    // 空语句:在某些循环中,空语句可以实现特殊的功能(例如循环输入)
    // 例如:while(cin>>s&&s!=sought);
    // 复合语句/块,用{}括起来的语句,一个块就是一个作用域,在块内声明的变量的生命周期就在此块中

    // switch特性:由于switch-case可能会跳过某些标签,而这些标签可能有一些变量的定义和初始化,没有跳过的标签可能用到这些变量
    // 因此c++规定不能跨过含有变量初始化的语句直接跳转到该变量作用域另一个位置
    int opt = 0;
    cout << "输入opt测试switch特性\n";
    cin >> opt;
    switch (opt) // 报错:控制传输跳过的实例化:
    {
    case 1:
        // string file_name;//错误：隐式初始化为空
        // int ival = 0;//错误：显式初始化ival
        int jval; // 正确：没有初始化
        break;
    case 0:
        jval = 0;
        cout << "jval= " << jval;
        // cout<<" ival = " << ival << endl;
        // cout << file_name.empty() << endl;
    default: {
    } // 就算没有default要做的事,也要加上default告诉读者已经考虑了这种情况
    }

    // 解决方案:把变量的定义放在块内,这样可以保证后面的case都在变量作用域外
    switch (opt) // 报错:控制传输跳过的实例化:
    {
    case 1: {
        // 变量定义在块中就不会crossing initialization(跨过初始化)
        string file_name;
        int ival = 0;
        int jval;
        break;
    }
    case 0: {
        int jval = 0;
        cout << "jval= " << jval;
    }
    default:; // 就算没有default要做的事,也要加上default告诉读者已经考虑了这种情况
    }

    // break：break将会跳出离它最近的while(do while),for,switch语句,并在跳出的语句之后的第一个语句开始执行

    // 异常处理：throw与try：异常指的是程序在运行时遇到的反常行为，这些行为超出了函数本身的范围，此时就需要异常处理
    // throw表达式：异常检测部分使用throw表达式来表示遇到无法处理的问题
    // try语句块：异常处理部分使用try语句块，以try开始，以一个或者多个catch子句结束。代码抛出（throw）的异常通常被某个catch语句处理

    // throw:1 格式: throw 抛出的异常类型;
    int int_1 = 1, int_2 = 2;
    if (int_1 + int_2 == 3)
    {
        throw runtime_error("Sum is 3"); // 还有一种是cerr<<"Sum is 3"<<endl;
        // 真实程序中对象相加和用户交互代码应该是分开的,因此建议使用throw抛出异常而不是cerr输出错误信息
    }

    /*
    try语句格式：
    try{
        //异常处理的信息:处理什么,怎么处理等
    }catch(异常声明){
        //处理代码
    }catch(异常声明){
        //处理代码
    }
    */
    // try当选中某个catch的语句处理异常后，执行对应块的内容，然后调到最后一个catch语句并执行对应块的代码

    /*
    标准异常：定义在<stdexcept>
    exception   最常见的问题
    runtime_error   运行时才检测到的问题
    range_error     运行时错误:生成超出有意义的值域范围
    overflow_error  运行时错误:计算上溢出
    underflow_error  运行时错误:计算下溢出
    logic_error        逻辑错误
    domain_error        对应参数的结果值不存在
    invalid_argument    无效参数
    length_error        试图创建一个超出该类型最大长度的对象
    out_of_range        使用阳光长处有效范围的值
    */

    // END
    return 0;
}