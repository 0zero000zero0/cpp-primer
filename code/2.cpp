///
///@file 2.cpp
///@author Zero (email:2405549856@qq.com)
///@brief c++ primer chapter 2 :变量和基本类型
///@date 2023-01-11
///

#include <D:\C in vsocde\c++ primer\c++ primer\header\variety.h>
#include <bits/stdc++.h>
using namespace std;
int test_variety1 = 1;

int test_f1(void)
{
    cout << test_variety1 << endl;
    return 1;
}

int main()
{
    bool bool1 = 100;
    int a1 = bool1;
    cout << "a1= " << a1 << endl; // bool值在运算中只有0和1
    unsigned u = 10;
    int i1 = -42;
    cout << "u+i1= " << u + i1 << endl; // 在unsigned中由于没有负数，因此-32实际上是MAX_INT对32取模的值
    cout << "i1+i1=" << i1 + i1 << endl;
    unsigned u1 = 42, u2 = 10;
    cout << "u1-u2=" << u1 - u2 << endl;
    cout << "u2-u1=" << u2 - u1 << endl;
    cout << "\ta\tb\tc" << endl;            // 转义字符
    cout << "who goes with f\145rgus?\012"; // 泛化转义字符
    string str1("It's ok");                 // string类型：可变长度的字符串（字符数组）
    str1 = "It's no";
    cout << "str1=" << str1 << endl;
    extern int test_variety; // 声明外部变量
    test_variety = 1;
    cout << "test_variety= " << test_variety << endl;
    int test_variety1 = 2;
    cout << "inner test_variety1 =" << test_variety1 << endl; // 局部
    cout << "outer test_variety1 = " << ::test_variety1 << endl; // 当作用域符：：左边没有值时，就像全局区申请
    int &pa1 = a1;
    // 引用，实际上就是取个别名，引用必须初始化，实际上可以看作绑定
    // 对引用的操作实际上就是对引用的绑定对象进行操作
    // 二者地址相同，进一步说明引用实际上就是取别名
    int *pointer_pb = &pa1;
    int *pointer_a1 = &a1;
    printf("&a1=%#x\n&pa1=#%x\npointer_a1=%#x\npointer_pa1=%#x\n", &a1, &pa1, pointer_a1, pointer_pb);
    // %#X输出自带0x
    // 由于引用实际上只是取个别名，不是具体的对象,因此对指向引用的指针实际上就是指向引用所绑定的对象
    int *nuull_pointer = nullptr; // 初始化指针为0(NULL,nullptr )
    void *void_ptr = &a1;
    //*void_ptr = 3;
    // void*类型可以转化为任意类型的指针，但是我们不清楚该地址所存放的对象的类型，因此不能对void*指针进行解引用
    // 也就是说void*指针不能访问地址上的内容
    // void*类型可以：与其他指针比较，作为函数的输入和输出，赋值给另外一个void*指针
    cout << "void_ptr= " << void_ptr << endl;

    int *&test_refer_to_pointer = pointer_a1; // 指向指针的引用
    cout << "test_refer_to_pointer= " << test_refer_to_pointer << endl;

    // const关键字可以使得变量只读,并且只在该文件内可以访问
    // 由于只读的属性,const修饰的变量必须初始化
    // 如果要跨文件使用const修饰的变量，那么在定义，声明时都必须加上extern
    extern const int const_int;
    cout << "const_int = " << const_int << endl;
    const int a2 = 2;
    const int &r_a2 = a2; // 对常量的引用,可以用常量,变量(对应的类型)进行初始化
    /*常量引用是对引用的操作进行限定，也就是不能通过引用来修改值，即使引用绑定了一个变量也不行
    但是可以通过其他途径改变这个变量的值
*/
    cout << "r_a2= " << r_a2 << endl;
    const int &r1 = 3;
    // int &r2 = r_a2 * 2;//报错,因为r3是对int的引用而不是const int
    double dval = 3.14;
    const int &r3 = dval;
    cout << "r3= " << r3 << endl;
    // r3=3
    /*
    原理:由于r3是对const
    int的引用而dval是double,因此编译器为了能够使r3绑定一个整数 就把代码变成了
    const int temp=dval;
    const int &r3=temp;
    这个temp就是临时量对象
    */

    // 指针与const
    // 与引用类似，指向常量的指针(const int
    // *)也不能通过解引用来改变值，无论这个指针指向的是常量还是变量，但是指针的指向可以更改(常量指针)
    // 而指针常量(int
    // *const)定义时必须初始化,且之后不能改变指针的指向(值),不过可以通过解引用改变指向对象的值
    // 顶层const表示指针本身是常量,而底层const表示指针所指向的对象是常量
    // 更一般的概念，顶层可以表示这个数据本身是常量。而底层则表示引用，指针等复合类型对应的对象是常量
    int i = 0;
    int *const p1 = &i;  // p1是顶层const，本身是常量（指针常量）
    const int ci = 1;    // ci是顶层const，本身是常量
    const int *p2 = &ci; // p2是底层const，本身可以改变但是它指向的对象不能改变
    const int *const p3 = p2; // p3即是底层也是顶层const，并且p2是底层const，左边的操作符完全包含右边，可以初始化
    const int &r = ci; // 由于ci是顶层const而r是底层const，因此可以绑定
    // int *p = p3;//错误,因为p3包含底层const的操作符但是p没有
    p2 =
        p3; // 正确,虽然p2没有包括顶层const,但是对于赋值、拷贝而言,顶层const作为右值对于它本身没有什么影响(因为右值需要的是地址上内容而不是地址本身)
    p2 = &i; // int *可以转化为const int *
    // *p2 = 1;//但是不能通过p2改变i的值
    // int &r4 = ci;//错误,int&不能绑定到const
    // int上,因为前者可以改变它的值但是后者的定义不允许改变
    const int &r5 = i; // 正确,与指针类似
    // 存在string指针
    string s1 = "OK";
    string *p_s1 = &s1;
    cout << "*p_s1= " << *p_s1 << endl;

    // constexpr：c++11中允许声明一个constexpr变量，由编译器检查变量的值是否为常量表达式，且必须由常量表达式来初始化
    constexpr int mf = 20;
    constexpr int limit = mf + 1;
    // constexpr也可以是某个函数,此时函数的返回值可以初始化constexpr类型
    // constexpr也可以修饰指针和引用，但是它们的初始值必须是nullptr，0或者存储于某个固定地址的对象
    constexpr int *cpr1 = 0; // 实际上cpt是一个指针常量(int *const)
    constexpr int *cpr2 = nullptr;
    // using可以起到与typdef一样的作用
    typedef int *int_ptr;
    using int_ptr = int *;
    const int_ptr p4 = &i; // 实际上p4是一个指针常量
    *p4 = 3;
    // p4 = &ci;//报错,常量不允许改变值

    // auto :由编译器推断类型,但是连续声明时类型必须一致
    auto a3 = 1, *p_a3 = &a3;
    // auto a4 = 3.14, a5 = 3;//报错,前者默认为double而后者为int
    // auto会忽略顶层const(因为这对拷贝没有影响)但是会保留底层const
    auto a5 = ci; // a5是int(这书好像有些小问题,书上给的是const int
                  // 可能是因为我的是c++17)
    a5 = 3;       // 我实际操作下来是int,因为auto忽略顶层const
    // 如果要希望推断出的类型是顶层,那么就应该要用const auto
    const auto f1 = ci;
    // 复合类型依然适用
    auto &r6 = a1;
    // auto &r7 = 12;//报错,因为非常量引用不能绑定到字面值上
    const auto &r7 = 12; // 正确,常量引用可以绑定到字面值常量上

    // decltype函数,接受一个值,返回数据类型,类型包括顶层const和引用
    // 当希望从表达式推断出需要定义的变量的类型但是又不想用表达式的值来初始化变量
    decltype(1 + 2.1) b1 = dval;
    decltype(test_f1()) b2 = dval; // 编译器实际上不会调用里面的函数,只是读取它的返回类型
    cout << "b1= " << b1 << "\nb2= " << b2 << endl;

    // 前面已经声明const int a2=2
    const int &r8 = a2, *p5 = &a2;
    decltype(a2) c1 = 0;  // c1是const int
    decltype(a2) c2 = c1; // c2是const int & (有意思的是vscode识别为const int)?
    // 引用一直都是作为绑定的对象的同义词出现，只有在decltype例外
    // 如果希望结果是引用所绑定的类型,那么可以采用表达式计算结果来实现
    decltype(r8 + 0) c4 = 4; // c4是int类型
    // decltype(a2) c3;//报错，因为c3是const int  ，必须初始化
    // decltype对解引用的返回类型是引用，解引用可以获得指针所指向的对象，并且还能对其赋值
    decltype(*p2) c3 = a2; // c3类型是const int &
    // 还有一点是：如果给变量加上括号，编译器就会把他当做一个表达式，就会得到引用类型
    decltype((a1)) c5 = a3; // c5类型为int&
    struct stu
    {
        /* data */
        int a{0};
        double b = 1.1;
        // 不能使用（）进行初始化
    };
    struct stu one; // 默认初始化
    cout << "stu one.a = " << one.a << " stu one.b= " << one.b << endl;
//END
    return 0;
}