///
///@file 7.cpp
///@author Zero (email:2405549856@qq.com)
///@brief C++ primer chapter 7 :类.
///  用一串///隔开类的声明，函数的定义和类的一些特性说明
///@date 2023-01-14
///

#include <stdc++.h>
using namespace std;
/////////////////////////////////////////////////////////////////////////////////
class person // 创建一个类
{
    // class能控制访问权限,默认为私有(struct默认为公有)
  public:                               // 访问控制符:公有，可以整个程序中访问
    typedef std::string::size_type pos; // 我们可以来类中定义其他类型的别名,这个同样存在访问限制
    // 自定义的类型必须先定义后使用,这和普通的成员不一样 (普通成员不受顺序的影响).因此类型成员通常出现在类的开头

    person &add(const person &rhs); // 类内函数,相当于+=
    // 一般类内函数,只是声明,也可以重载
    const person &show() const; // 显式数据,在参数列表后面加const后,该函数里的this指针指向常量
    void cin(void);             // 输入数据
    person(); // 默认构造函数:没有参数和返回类型,名字和类名一样.(没有参数是默认构造函数的特点)
    // person()=default;//default可以使构造函数的形式成为合成默认构造函数(由编译器创建的构造函数)
    // 注意:对于有的类(尤其是需要额外内存资源的函数),编译器不能合成默认构造函数,因此最好自己定义一个默认构造函数
    person(string c_name, int c_roo); // 自定义构造函数，类似函数重载.但是也没有返回类型
    // 由于编译器在编译时先编译名字再编译函数体，也就是函数和变量的顺序不会影响函数使用变量
    int unfold_data;         // 公有数据，可以用test.unfold_data来访问
    person(int x, string y); // 构造函数初始值列表

  private: // 访问控制符:私有，只能从类内部函数访问,不能用类代码访问(也就是test.id)
    string name{"none"}; // 类内初始化必须用=或者{}
    int roll = 1;
    pos pos_x = 1; // pos是在public定义的string的别名(如果在private中定义则在pubilc中不能使用)

    // 友元:有的时候我们需要设置类外函数,通过这个函数来访问类中私有的数据,这时就要用到友元friend
    // 在类内添加一个前面加上friend的声明即可.一般在类开头或者结束集中声明友元函数
    // 由于友元函数只是授予了访问权限，不是真正的函数声明，因此还需要在类外在进行一次函数声明(有的编译器没有强制要求)
    // 一般而言，友元函数和类写在同一个头文件中，并且要在类内类外都要声明
    // 如果要使用一组重载函数,那么必须对每一个都要进行friend声明
    friend ostream &print(ostream &os, const person &item);
    friend istream &read(istream &is, person &item);
    // 如果友元函数在类中定义，那么它们将是隐式内联的
    // 除了类外函数以外，还可以把之前定义过的类（类的函数）定义为友元
    // 友元类的成员函数可以访问包括私有成员在内的所有成员
    // 但是友元不存在传递性
};
/////////////////////////////////////////////////////////////////////////////////
person::person() // 默认构造函数
{
    // this指针，指向调用这个函数的对象，可以访问这个对象的成员
    this->name = "undefined";
    this->roll = 1;
    this->unfold_data = 1;
}

person::person(string c_name, int c_roll) // 一般自定义的构造函数，类似重载
{
    this->name = c_name;
    this->roll = c_roll;
}

// 返回this解引用
person &person::add(const person &rhs)
{
    name += rhs.name;
    roll += rhs.roll;
    return *this; // 由于this指针指向调用这个函数的对象,因此解引用得到的就是这个对象
}

// 构造函数列表初始值:在参数列表后跟一个 : ,后面是成员名字,用()来包含初始值,每个成员之间用 , 隔开
// 最后跟一个{}作为构造函数的函数体。如果初始列表没有包含某些成员，那么他们将要执行合成默认构造函数
person::person(int x, string y) : name(y), roll(x * x)
{
    this->unfold_data = 4;
};

// 一般而言，this指针是一个指向这个对象的指针常量，而有的时候我们需要底层const
const person &person::show() const // 在参数列表后面加上const就可以使得这个函数的this指针指向常量类型
{
    cout << "id = " << name << "  "
         << "roll = " << roll << endl;
    return *this; // 返回的也是常量引用,意味着在此后不能进行.访问
}

// 类内函数
void person::cin()
{
    int x, y;
    std::cin >> x >> y;
    this->name = x;
    this->roll = y;
}

// 两个友元函数,可以在例外访问私有数据
//  返回一个输出流数据(必须是引用类型)
ostream &print(ostream &os, const person &item)
{
    os << "name=" << item.name << "  roll=" << item.roll << "  unfold_data=" << item.unfold_data << endl;
    return os;
}
// 返回输入流数据(必须是引用类型)
istream &read(istream &is, person &item)
{
    cout << "please input name,roll and unfold_data" << endl;
    cin >> item.name >> item.roll >> item.unfold_data;
    return is;
}
/////////////////////////////////////////////////////////////////////////////////
class screen;
// screen的友元类.但是友元不存在传递性,如果person是window_mgr的友元类，person也不能访问screen的私有成员
class window_mgr
{
  private:
    // 一组窗口
    std::vector<screen> screens; // 类内初始化必须用=或者{}
  public:
    using screen_index = std::vector<screen>::size_type; // 窗口编号
    void clear(screen_index i);                          // 把所选编号的窗口设置为空
    window_mgr();
};
/////////////////////////////////////////////////////////////////////////////////
class screen
{

  public:
    friend class window_mgr; // 友元类,一般写在最前面,该类中的成员函数可以访问screen的所有成员(包括私有)
    friend void window_mgr::clear(screen_index); // 除了把整个类声明为友元,还可以只声明类的成员函数
    using pos = std::string::size_type; // 我们可以来类中定义其他类型的别名,这个同样存在访问限制
    screen() = default;                 // 合成默认构造函数
    screen(pos ht, pos wd, char c)
        : height(ht), width(wd), contents(ht * wd, c) /*ht*wd个c字符的初始化*/
          {};
    char get() const // 读取光标处的字符
    {
        return contents[cursor];
        // 隐式内联函数(定义在类内的函数被隐式的设为内联函数)
    }
    inline char get(pos ht, pos wd) const;    // 显式内联函数
    screen &move(pos r, pos c);               // 移动光标
    inline screen &set(char c);               // 设定光标位置的字符
    inline screen &set(pos x, pos y, char c); // 设定x,y处的字符
    void some_merbers() const;                // 测试mutable关键字
    class window_mgr; // 友元类:其中的成员函数可以访问screen的所有成员,包括私有
    // 类内函数重载
    screen &display(ostream &os) // 非常量版本
    {
        do_display(os); // 调用do_display时,display的this指针会隐式地传递给do_display
        return *this;
    };
    const screen &display(ostream &os) const // 常量版本
    {
        do_display(os);
        return *this;
    }

  private:
    pos cursor /*光标位置*/
        = 0,
        height /*窗口长*/ = 0, width /*窗口宽*/ = 0;
    string contents = "";
    // mutable关键字修饰的变量永远可变，即是在const(this指向const)中也可以修改
    mutable size_t access_ctr = 0;   // access_ctr是可变数据成员
    void do_display(ostream &) const // 负责显示内容
    {
        cout << contents;
        // 这个函数是在类内定义的，隐式地被设为内联函数，因此调用do_display不会带来额外的开销
        // 定义这个函数在类规模扩大时，display的操作可能更加复杂，此时把相应的操作写在一个函数里会更好
        // 在实践中，设计良好的C++代码常常包含大量类似于do——display的小函数，通过调用这些函数,可以完成一组其他函数的“实际”工作。
    }
};
/////////////////////////////////////////////////////////////////////////////////
inline screen &screen::move(pos r, pos c)
{
    pos row = r * this->width; // 计算行的位置
    this->contents = row + c;  // 行内光标移动到指定的列
    return *this;              // 作为左值返回
}

inline char screen::get(pos r, pos c) const // 在类内中声明为inline函数
{
    pos row = r * width;
    return contents[row] + c;
}

void screen::some_merbers() const
{
    ++this->access_ctr;
    // const成员函数中this指向常量,但是access_ctr是mutable类型,可以一直被修改
}

inline screen &screen::set(char c)
{
    contents[cursor] = c;
    return *this;
}

inline screen &screen ::set(pos x, pos y, char ch)
// 引用类型意味着返回的是对象本身而不是对象的副本
{
    contents[x * width + y] = ch;
    return *this; // 返回对象本身而不是对象的副本
}

void window_mgr::clear(screen_index i)
{
    screen &s = screens[i];
    s.contents = string(s.height * s.width, ' ');
}

/////////////////////////////////////////////////////////////////////////////////
////友元与作用域
// 类和非成员函数的声明不是必须在它们的友元声明之前。
// 当一个名字第一次出现在一个友元声明中时，我们隐式地假定该名字在当前作用域中是可见的。
// 然而，友元本身不一定真的声明在当前作用域中
// 甚至就算在类的内部定义该函数，我们也必须在类的外部提供相应的声明从而使得函数可见。
// 换句话说，即使我们仅仅是用声明友元的类的成员调用该友元函数，它也必须是被声明过的
// void X();
// struct test
// {
//     friend void f(); // 假设f已经声明了
//     void X()
//     {
//         f(); // 未识别，实际上没有声明
//     }
// };
//此外,在类外部的作用域里,类的对象名字被隐藏了
//因此在类外部定义函数时要加上类作用域符,把作用域转到类中,并且不用在对其他成员授权
//nielianheishu
/////////////////////////////////////////////////////////////////////////////////
int main()
{
    person one;               // 默认构造函数
    person two("li", 1);      // 自定义构造函数
    person three(2, "zhang"); // 构造函数列表初始值
    cout << "please input unfold_data\n";
    read(cin, one);
    cout << "one : ";
    print(cout, one);
    screen myscreen;
    myscreen.move(3, 3).set('#');
    // 相当于(但是有区别)
    myscreen.move(3, 3);
    myscreen.set('#');
    // 由于move返回的是screen&为左值,因此可以继续使用.来使用set函数
    // 如果move返回是screen，那么实际上的move返回的是myscrenn的副本,set函数并没有实际改变myscreen
    return 0;
}