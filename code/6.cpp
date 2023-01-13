///
///@file 6.cpp
///@author Zero (email:2405549856@qq.com)
///@brief C++ primer chapter 6:函数
///@date 2023-01-12
///
#include <E:\C in vsocde\c++ primer\c++ primer\header\Chapter6.h>
#include <stdc++.h>
using namespace std;

int count_calls(); // 函数声明(函数原型)
int fact(int val);

int test_refer_f1(int &i) // 引用类型直接修改实参,调用时不用加&(因为加了代表指针)
{
    i = 0;
    return i;
}

// 使用引用传递来返回多个值:原理就是引用会直接改变对象本身的值,可以用引用来从函数中获得信息
string::size_type find_char(const string &s, char c, string::size_type &occurs)
{
    auto ret = s.size();                          // 记录第一次出现的位置(如果有)
    occurs = 0;                                   // 该字符出现的次数
    for (decltype(ret) i = 0; i != s.size(); ++i) // 由于要用到位置，因此不用range for
    {
        if (s[i] == c) // 找到字符
        {
            if (ret == s.size()) // 判断是否是第一次出现
            {
                ret = i;
            }
            ++occurs; // 出现次数++
        }
    }
    return ret + 1;
}

// 数组与形参:实际上转化为指针来操作,因此为了安全还需要传入大小
void f1(const int *beg, const int *end) // 调用时f1(begin(array),end(array))
{
    while (beg != end)
    {
        cout << *beg++ << " ";
    }
    cout << endl;
}

void f2(int array[], size_t size) // 显式传入大小
{
    for (size_t i = 0; i < size; ++i)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}

// initializer_list可变参数函数例子
void error_meg(initializer_list<string> il) // 调用时必须用{}来传递参数
{
    for (auto beg = il.begin(); beg != il.end(); ++beg)
    {
        cout << *beg << " ";
        cout << endl;
    }
}
// 调用:error_msg({"function","OK","Allright"})

// 如果返回类似是引用,则可以作为左值
char &get_val(string &str, string::size_type i)
{
    return str[i];
}

// 列表返回值
vector<string> process(const string &s1, const string &s2)
{
    if (s1.size() == s2.size())
        return {"They are right"};
    else if (s1.size() > s2.size())
    {
        return {"It's", "s1 = ", s1};
    }
    else
        return {"It's", "s2 = ", s2};
}

// 7 返回数组指针:可以采用typedef或者using
typedef int int_array_10[10];
using int_array_10 = int[10];
int_array_10 *f_return_arra_pointer1(void);
// 也可以通过声明的优先级来写（详见C专家编程第三章）
int (*f_return_array_pointer2(void))[10];

// 使用尾置返回类型
auto test_f1(void) -> int (*)[10];

// 用const_cast重载函数
const string &shoterString(const string &s1, const string &s2)
{
    // 初始版本，参数和返回类型是常量引用
    return s1.size() < s2.size() ? s1 : s2;
}

string &shoterString(string &s1, string &s2)
{
    // 当我们不需要常量引用时，可以用const_cast重载初始版本的shoterString
    auto &r = shoterString(const_cast<const string &>(s1), const_cast<const string &>(s2));
    return const_cast<string &>(r);
}

// constexpr函数
constexpr int new_size() // 参数必须是字面值类型
{
    typedef int *int_ptr; // 里面可以有其他语句,但是这些语句不能执行操作.例如可以有using 声明,typedef,
    return 42;            // 有且只有一条return ,返回类型必须是字面值类型
}
// constexpr函数不一定返回常量表达式
constexpr int scale(size_t cnt)
{
    return new_size() * cnt;
}
int main()
{
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

    // 指针形参也不能修改指针本身,只能通过解引用修改指向的地址上的值
    // 而引用可以直接改变它所绑定的对象的值
    int i = 1;
    cout << test_refer_f1(i) << endl;
    // 输入为0
    // 由于有的容器不支持拷贝（值传递0），或者是容器内存很大，此时使用引用传递可以避免这些情况
    // 使用引用传递来返回多个值:原理就是引用会直接改变对象本身的值,可以用引用来从函数中获得信息
    string::size_type occurs = 0;
    string::size_type ret = 0;
    ret = find_char("ABBCCC", 'C', occurs);
    cout << "该字符第一次出现在" << ret << "个位置\n"
         << "该字符出现了" << occurs << "次" << endl;

    // const与参数
    // c++中用实参初始化形参时会忽略形参的顶层const,此时用常量和变量初始化形参都行,因此f(const int)和f(int)是一样的

    // 尽量使用常量引用(const 数据类型 &):1 可以不用拷贝 2 不会改变原有的数据3 可以传递字面值常量
    // 还有一点是,如果其他的参数是常量引用,并且这个函数还调用了一个参数表示常量引用的函数,那么被调用的函数将无法实现(类型冲突)

    // 如果不修改参数,建议使用const
    // 如果要修改数组，可以使用数组引用(int (&refer_array)[])

    // main函数的参数:int argc,char *argv[]
    // argv是一个字符串数组,argc是指字符串的数量
    //  一般由用户输入,而系统会自动统计字符串数目赋值给argc.例如 prog -d -o dfile data(),那么argv[0]="prog"...

    // 可变参数:1 标准库中的initializer_list 2 省略符形参
    {
        // initializer_list用于参数数量未知但是参数类型全部相同(这也是一种模板类型),该模板中的对象中的值只能是常量(对应的成员函数返回的指针也是常量指针)
        initializer_list<int> lst1;          // 执行默认初始化
        initializer_list<int> lst2{1, 2, 3}; // 执行列表初始化,初始值和列表中数目一致,列表中元素是const
        initializer_list<int> lst3(lst1); // 拷贝初始化,拷贝后二者共享元素
        lst1 = lst3;                      // 赋值初始化,二者共享元素
        lst1.size();                      // 元素数量
        auto beg = lst1.begin();          // 返回指向lst1中首元素的指针(这里是const int*),lst1.end()同理
        void error_meg(initializer_list<string> il);
        error_meg({"OK", "NO", "YYYY"});
        // 用range for遍历initializer_list时,声明加上&,这样自动推断的结果才是const int&
        for (auto &i : lst1)
        {
            cout << i << "i";
        }
        cout << endl;
    }

    // return
    // 1 return会把控制权交给主调函数，因此对于有返回类型的函数无论是否返回值都要加上return来交付控制权
    // 2 返回值实际上是通过创建临时变量并且初始化，然后把它赋值给其他变量来实现的
    // 3 如果是返回类型是引用，那么返回的是这个引用绑定的对象本身
    // 4 不要返回局部对象的引用或者指针或者临时常量,因为函数结束后这些内存就不可用了
    // 5 如果返回类型是引用类型,则是左值,
    { // 测试返回类型为引用，则可以作为左值
        string str("a string");
        cout << str << endl;
        char &get_val(string & str, string::size_type i);
        get_val(str, 0) = 'A';
        cout << str << endl;
    }
    // 6 可以用列表初始化返回值:就像列表初始化一样,返回值的类型由定义的决定
    {
        vector<string> process(const string &s1, const string &s2);
        for (auto i : process("Y", "N"))
        {
            cout << i << " ";
        }
        cout << endl;
    }
    // 7 返回数组指针:可以采用typedef或者using
    typedef int int_array_10[10];
    using int_array_10 = int[10];
    int_array_10 *f_return_array_pointer1(void);
    int(*f_return_array_pointer2(void))[10];

    // 使用尾置返回类型:在本应该出现返回类型的地方放个auto,之后在参数列表后面用->连接到实际的返回类型
    auto test_f1(void)->int(*)[10];

    // 也可以使用decltype,注意decltype不会把数组转化为指针,因此要返回数组指针还要加一个*
    int array[10] = {0};
    decltype(array) *test_f2(void);

    // 函数重载：在同一个作用域内，函数的名字相同，但是除了返回类型外参数列表也不同。此时就可以通过参数来调用对应的函数
    int look_up(const string &Accout);
    int look_up(const int(&Phone)[9]);
    int look_up(const char &Name);
    // 注意,不允许两个函数除了返回类型外其他的所有要素都相同
    // 参数列表有名字和没名字是一样的，此外类型别名(typedef,using)也是一样的
    int look_up(const string &Accout);
    // bool look_up(const string &name);//报错：无法重载仅按返回类型区分的函数
    // 由于函数传入参数时会忽略形参的顶层const，因此有const和无const无法重载
    int test_f2(const int);
    int test_f2(int); // 报错:重复定义test_f2

    // 无法重载函数的情况:1 除了返回类型其他要素都相同
    // 2 参数列表中顶层const与无顶层const类型(底层const可以重载.当传入非常量时编译器会优先选择非常量函数版本)
    // 3 参数列表中 别名(typedef 和 using)
    // 4 局部变量会隐藏全局变量,因此与全局函数同名的局部变量(函数)会掩盖前者,在局部中就无法重载全局函数(子作用域同理)

    // 关于重载的建议：只重载操作非常相似的函数

    // const_cast与重载:有时候我们定义了一个返回类型和和参数都是常量引用,当我们传入非常量实参时返回类型依然时常量引用,但是我们需要的时非常量引用
    // 此时就可以使用const_cast
    const string &shoterString(const string &s1, const string &s2);
    string &shoterString(string & s1, string & s2);

    /*
    重载确定(函数匹配):当调用的函数有重载时,编译器会找到与实参最佳匹配(参数类型,数量与实参的类型,数量)的函数进行调用
    如果无法找到匹配的函数，或者是有多个匹配的重载函数（例如一个函数的参数是const
    int而另一个是int，由于传参会忽略顶层const，这两个实际上是一样的），编译器就会报错
    */

    /*
    全局函数,局部变量与重载:
    由于局部会隐藏全局,因此局部变量（函数）与全局函数同名时,无法重载全局函数
    因为C++中调用函数时名字检查发生在类型检查之前，检查名字时检测到是局部定义的而不是全局定义的，因此局部第一次定义的函数不是全局函数的重载，第二次定义时就是局部函数的重载
    而如果是变量与全局函数同名时，调用函数会直接报错，无法检测到与它同名的全局函数。
    如果没有定义同名，那么在局部中可以重载全局函数
    */

    // 特殊用途的语言特性
    // 默认实参：有时我们需要默认参数的值，当调用函数时没有传递参数，此时就采用默认参数。例如Windows窗口默认大小
    using sz = string::size_type;
    string screen(sz ht = 24, sz wid = 80, char bg = ' ');
    screen();       // 相当于screen(24,80,' ');
    screen(30);     // 相当于screen(30,80,' ');
    screen(30, 70); // 相当于screen(30,70,' ');
    screen(30, 70, '!');
    screen('?'); // 由于'?'是char类型而screen的第一个参数sz,char可以转化为sz,ascii是63,因此相当于screen(63);
    // 多次（重复）声明中只能添加默认实参，不能修改已经确定的默认实参
    string screen_2(sz ht, sz wid, char bg = ' ');
    string screen_2(sz ht = 25, sz wid = 85, char bg); // 添加默认实参,注意最后的只能是char bg,不能是char bg=' '
    // string screen_2(sz ht , sz wid , char bg = '*');//报错,已经存在默认实参
    // 局部变量不能作为默认实参，如果表达式能转化为形参所需类型，如果表达式的值就能作为默认实参
    {
        // 这个作用域可以是其他函数的定义
        char def = '*';
        sz wd = 100;
        screen(); // 调用screen(24,80,' ');
    }

    // 对于一些操作封装为函数有以下优点:1 便于理解 2 行为统一 3 易于修改 4 重复利用,避免重复造轮子
    //  内联函数:一般的函数调用会产生较大的开销,而内联函数(inline)是在调用点内联展开。在函数返回类型前加上关键字inline即可将函数设置为内联函数
    // 一般规模小，流程直接，调用频繁的函数可以设置为内联函数，但是很多编译器不支持递归内联函数，而大于75行的函数也不太可能展开
    // 例如shoterString
    inline const string &shoterString(const string &s1, const string &s2);
    string s1 = "OK", s2 = "Yes";
    cout << shoterString(s1, s2) << endl;
    // 在编译时就会展开为类似下面这种形式
    cout << (s1.size() < s2.size() ? s1 : s2) << endl;
    // 从而节省了开支

    // constexpr函数:可以用来返回常量表达式,给constexpr变量初始化.
    // constexpr函数的返回值和传入的参数都必须是字面值
    constexpr int new_size(); // 编译器会把constexpr函数调用换成结果值，因此constexpr被隐式设定为内联函数
    // constexpr函数不一定返回常量表达式
    constexpr int scale(size_t cnt); // return new_size()*cnt
    // 内联函数和constexpr函数由于要展开，因此把二者定义直接写到头文件中

    // 调试帮助
    // 1
    // assert(exprssion):定义在cassert中,这是一个宏,类似内联函数展开.如果expression为0,则输出信息终止程序,否则什么也不做
    // assert用于检测不能发生的情况,比如,输入文本可能要求每个单词都要大于一定的阈值,因此用assert(word.size()>threshod)
    // 如果用户输入没有大于这个阈值,则expression为0,输出信息并终止程序
    // 2 NDEBUG:assert的实现依赖于NDEBUG的宏,如果定义了NDEBUG则assert就什么也不做
    // 此外NDEBUG还可以用于实现自动

    // 函数匹配:
    // 候选函数：与被调用函数同名，声明在调用点可见的重载函数集合
    // 可行函数：通过实参从候选函数中选出来的函数，特征：1 形参数量和调用提高的实惨数量相等 2
    // 实参类型和形参相同，或者是可以转化为形参的类型
    // 最终确定调用的版本：通过比对实参的类型和形参的类型，类型越接近，匹配越好，调用匹配最好的函数（如果没有则报错）
    // 匹配成功标准:1 该函数每个实参的匹配都不劣于其他可行函数的匹配 2 至少有一个实参的匹配犹豫其他可行函数的匹配
    // 如果没有可行函数脱颖而出，那么编译器会报错二义性的信息
    // 匹配等级：1 精确匹配，包括相同，或者数组（函数）转化为对应的指针，添加或者删除顶层const
    // 2 通过const转化(非常量的指针,引用转化为常量指针,常量引用)
    // 3 类型 提升
    // 4 算数类型匹配
    // 5 类 类型转换

    // const与重载：如果两个重载函数的区别在于指针（引用）的指向类型是否为const，那么编译器会根据实参是否为const来选择

    // 函数指针
    int test_refer_f1(int &i); // 之前定义的函数
    int (*func_ptr)(int &i);   // 定义函数指针
    func_ptr = &test_refer_f1; //&可选
    int i = 1;
    cout << func_ptr(i) << endl; // 调用，也可以是(*func_ptr)(i)
    // 指向不同函数类型的指针之间不存在转换规则,但是可以赋值为nullptr
    // 重载函数也可以用指针指向,但是要明确所指向函数的参数,返回值
    // 函数指针作为形参时，(*)也是可选的
    void undefined_func_1(int f1(int &)); // 也可以是int (*f1)(int&)
    // 返回函数指针:可以像返回数组指针一样,通过using,typedef来操作
    using function_ptr = int (*)(int a, int b);
    typedef int (*function_ptr)(int a, int b);
    function_ptr undefined_func_2(void);
    int (*undefined_func_3(void))(int a, int b);        // 直接声明
    auto undefined_func_3(void)->int (*)(int a, int b); // 尾置返回类型
    int undefined_func_4(int a, int b);                 // 某个函数
    decltype(undefined_func_4) *undefined_func_6();     // 用decltype来返回函数，再用*来创建函数指针

    // vscode分离编译确实需要cmake/makefile，有时间在搞
    // END
    return 0;
}