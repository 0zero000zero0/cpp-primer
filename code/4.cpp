///
///@file 4.cpp
///@author Zero (email:2405549856@qq.com)
///@brief C++primer 第四章 :表达式
///@date 2023-01-09
///

#include <stdc++.h>
using namespace std;

int main()
{
    // 左值与右值：当对象被作为左值（例如在赋值=左边）时，使用的是这个对象的身份（在内存中的位置）；当对象被作为右值时，使用的是对象的内容（地址上的值）
    // 有的运算符需要左值但是返回的是右值（取地址&），有的需要右值返回也是右值。
    // 需要右值的地方可以用左值代替（这时使用的就是对象的内容而不是地址），但是需要左值的地方不能用右值来代替
    // 需要左值的运算符:=的左边(结果仍然是左值),取地址符&(返回一个指向该对象的指针,为右值)
    // 返回左值：解引用和下标，++，--
    // decltype返回类型:如果是左值,那么返回类型是引用.例如int *p,由于解引用*p得到的是左值(int),因此decltype返回的是int&
    // 如果是右值,那么返回的是指针,例如decltype(&p),&p返回的是右值(指针),因此decltype返回类型是int **
    int a1 = 1;
    int *p = &a1;
    decltype(*p) r1 = a1;   // int& r1
    decltype(&p) p_p1 = &p; // int **p_p1

    // 处理复合表达式的经验:1 拿不准优先级时用()来强制让表达式的组合关系符合需求
    // 2 如果一个表达式改变了某个对象的值,那么在这个表达式中不要在使用这个对象的值.
    // 第二条有个例外：当一个表达式是另一个表达式的子表达式时无效。例如：*p++
    // 由于*优先级高于++,因此该表达式会先解引用p，在把p向后移动一个位置

    // 一元运算符可以作用于bool值和指针，作用于指针时返回对象值的一个(提升后)副本
    bool bool_1 = false;
    bool_1 = -bool_1;
    cout << "bool_1= " << bool_1 << endl; // bool_1=0

    // 赋值:赋值语句左边必须是可修改的左值(例如const就不是),返回值也是左值
    // 此外赋值 满足右结合律，当有多条赋值语句时，从右到左开始执行
    // 只有当右边对象的类型可以转化为左边时才能执行
    int int_1, *int_ptr;
    // int_1 = int_ptr 1= 0;//0赋值给指针,但是int*不能转化为int
    string s1, s2;
    s1 = s2 = "OK"; // 字面值常量"OK"可以转化为string类型,然后给s1和s2赋值
    // 赋值的优先级低于 != 和==,因此while,if等条件判断时要在赋值=的语句加上()

    // 关于++和--：前置版本将对象本身作为左值返回，而后置版本则返回的是对象原来的值的副本。因此除了*p++外（也就是不使用对象本身的值），使用前置的++性能更好
    // 由于++和--会改变这个对象的值，因此如果一个表达式用到了某个对象而且子表达式也用到了这个对象，不要在子表达式中使用++和--

    // 由于?:的优先级很低,因此在使用时最好加上括号
    cout << ((s1 != "OK") ? "Yes" : "NO") << endl;

    // sizeof特性：sizeof实际上并不会调用里面的表达式,因此可以直接求某个类型,未初始化的指针(以及它的解引用类型)的大小
    int *p1;
    cout << "size of p1 = " << sizeof(p1) << endl;   // 8
    cout << "size of *p1 = " << sizeof(*p1) << endl; // 4
    // 如果是引用，则返回引用的类型的大小
    // 如果是数组名，则返回是整个数组所占空间的大小，并不会把数组名转化为指针.sizeof(array)/sizeof(*array)可以用来计算数组大小
    // 如果是string，vector，则返回该类型的固定大小，不会计算对象的元素占用的空间
    vector<int> v1;
    for (int i = 0; i < 10; i++)
        v1.push_back(i);
    cout << "size of vector int = " << sizeof(vector<int>) << endl; // 24
    cout << "size of v1 = " << sizeof(v1) << endl;                  // 24

    // 显示类型转换cast-name<type>(expression),其中type是转换的目标类型,expression是待转换的表达式,cast-name是根据情况选以下的实际类型
    // 1 :
    // static_cast:任何明确定义的类型转换，只要不包含底层cosnst(指向的类型是const),都可以使用.当把较大类型转换为较小类型时,static_cast可以使得编译器不发出精度损失的警告
    int int_1 = 1, int_2 = 3;
    double double_1 = static_cast<double>(int_1) / int_2;
    // static_cast 还可以把void*转换成对应类型的指针
    void *void_ptr = &double_1;
    double *double_ptr_1 = static_cast<double *>(void_ptr); // 注意转换结果要与原始地址的类型相等,不然undefined
    // 2 :
    // const_cast:只能适用于改变运算对象的底层const,实际上const_cast是擦出掉const属性,此时编译器不再阻止我们改变这个值。对常量使用const_cast没什么问题，对变量使用undefined
    const char *p2;
    char *p3 = const_cast<char *>(p2);
    // const_cast<string>(p2);//报错,const_cast只能擦出const属性,因此类型只能是对应的指针,引用

    // END

    return 0;
}