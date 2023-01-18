///
///@file 7.cpp
///@author Zero (email:2405549856@qq.com)
///@brief C++ primer chapter 7 :类.
///  用一串///隔开类的声明，函数的定义和类的一些特性说明
///@date 2023-01-14
///

#include <stdc++.h>
using namespace std;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class person // 创建一个类
{
    // class能控制访问权限,默认为私有(struct默认为公有)
  public:                               // 访问控制符:公有，可以整个程序中访问
    typedef std::string::size_type pos; // 我们可以来类中定义其他类型的别名,这个同样存在访问限制
    // 自定义的类型必须先定义后使用,这和普通的成员不一样 (普通成员不受顺序的影响).因此类型成员通常出现在类的开头

    person &add(const person &rhs); // 类内函数,相当于+=
    // 一般类内函数,只是声明,也可以重载
    const person &show() const; // 显式数据,在参数列表后面加const后,该函数里的this指针指向常量
    void input_data(void);      // 输入数据
    person(); // 默认构造函数:没有参数和返回类型,名字和类名一样.(没有参数是默认构造函数的特点)
    // 创建默认构造函数的对象时,不需要加(),也就是person test;就可以直接创建一个默认构造函数的对象
    // person()=default;//default可以使构造函数的形式成为合成默认构造函数(由编译器创建的构造函数)
    // person(pos x = 3, string s = "#", int y = 1) : name(s), roll(y), pos_x(y){};
    // 上面的这个语句是自定义的默认构造函数,由于存在默认实参,因此当调用构造函数但是不输入给实参时使用的就是这个
    // 默认构造函数只能有一个
    // 注意:对于有的类(尤其是需要额外内存资源的函数),编译器不能合成默认构造函数,因此最好自己定义一个默认构造函数

    person(string c_name, int c_roo); // 自定义构造函数，类似函数重载.但是也没有返回类型
    person(string s1, pos x, int y);
    // 由于编译器在编译时先编译名字再编译函数体，这意味着函数和变量的顺序不会影响函数使用变量

    // 委托构造函数:用所属类的其他构造函数来初始化.和其他构造函数一样，一个委托构造函数也有一个成员初始值的列表和一个函数体。
    // 和其他成员初始值一样，类名后面紧跟圆括号括起来的参数列表，参数列表必须与类中另外一个构造函数匹配。
    person(pos y, pos x) : person("delegating", 3)
    {
        // 该委托构造函数委托上面的person(string c_name,int c_roo)来执行部分初始化
        // 如果参数列表为空,则是默认构造函数,也可以使用委托
        // 委托的函数也可以是委托构造函数,
        this->pos_x = y;
    }

    // 转换构造函数:只接受一个参数,定义了其他类型转化为该类型的隐式转换规则
    person(pos x) : pos_x(x)
    {
        // 接受一个pos x,可以用 = 把其他类型转换为 pos
        // 例如person test; test=3.14;
        // 此时就会调用转换构造函数,使用其定义的转换规则,把double的3.14转换为pos x赋值给pos_x
        this->name = "tansfer";
        this->roll = 4;
        this->unfold_data = 4;
        // 如果要抑制转换构造函数的隐式类型转换,可以在声明前加关键字explicit(显式类型转换加了explicit关键字后依然可以使用)
        // 关键字explicit只对一个实参的构造函数有效。需要多个实参的构造函数不能用于执行隐式转换(也就不能使用explicit关键字)
        // 只能在类内声明构造函数时使用explicit关键字，在类外部定义时不应重复
        // 此外explicit构造函数也不能用于拷贝初始化,test=initialization;可以直接初始化,test(initialization)
        // vector接受一个参数的构造函数就是explicit,而string的转换构造函数不是explicit
        // explicit转换构造函数依旧可以使用转换构造函数来显式类型转换,test.person(data)
    }

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
    // 如果友元函数在类中定义，那么它们将是隐式内联的(inline)
    // 除了类外函数以外，还可以把之前定义过的类（类的函数）定义为友元
    // 友元类的成员函数可以访问包括私有成员在内的所有成员
    // 但是友元不存在传递性
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
person::person() // 默认构造函数
{
    // this指针，指向调用这个函数的对象，可以访问这个对象的成员
    this->name = "undefined"; // 初始化
    this->roll = 1;
    this->unfold_data;     // 默认初始化为0
    this->unfold_data = 1; // 赋值
    // 有时我们可以忽略数据成员初始化和赋值之间的差异，但并非总能这样。
    // 如果成员是const或者是引用的话，必须将其初始化。因为构造函数是唯一可以初始化的const与引用的时机
    // 类似的，当成员属于某种类类型且该类没有定义默认构造函数时，也必须将这个成员初始化
    // 还有一点是初始化的效率比先默认初始化再赋值要高
    // 初始化的顺序是由定义时的顺序决定的,而不是构造函数里的顺序
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
    return *this;
    // 由于this指针指向调用这个函数的对象,因此解引用得到的就是这个对象
    // 如果返回类型是引用,那么*this返回的就是这个对象本身,如果不是,则返回这个对象的副本
}

// 构造函数列表初始值:在参数列表后跟一个 : ,后面是成员名字,用()来包含初始值,每个成员之间用 , 隔开
// 最后跟一个{}作为构造函数的函数体。如果初始列表没有包含某些成员，那么他们将要执行合成默认构造函数
person::person(int x, string y) : name(y), roll(x * x)
{
    this->unfold_data = 4;
    // 如果没有this->unfold——data，那么这个数据将执行默认初始化，为0
};

// 一般而言，this指针是一个指向这个对象的指针常量，而有的时候我们需要底层const
const person &person::show() const // 在参数列表后面加上const就可以使得这个函数的this指针指向常量类型
{
    cout << "id = " << name << "  "
         << "roll = " << roll << endl;
    return *this; // 返回的也是常量引用,意味着在此后不能进行.访问（也就是不能test.show().input_data)
}

// 类内函数
void person::input_data()
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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class screen;
// screen的友元类.但是友元不存在传递性,如果person是window_mgr的友元类，person也不能访问screen的私有成员
class window_mgr
{
  private:
    // 一组窗口
    std::vector<screen> screens;

  public:
    using screen_index = std::vector<screen>::size_type; // 窗口编号
    void clear(screen_index i);                          // 把所选编号的窗口设置为空
    window_mgr();
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
        // 定义在类内的函数被隐式的设为内联函数(隐式内联函数)
    }
    inline char get(pos ht, pos wd) const;    // 显式内联函数
    screen &move(pos r, pos c);               // 移动光标
    inline screen &set(char c);               // 设定光标位置的字符
    inline screen &set(pos x, pos y, char c); // 设定x,y处的字符
    void some_merbers() const;                // 测试mutable关键字
    friend class window_mgr; // 友元类:其中的成员函数可以访问screen的所有成员,包括私有
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
    pos cursor = 0, /*光标位置*/
        height /*窗口长*/ = 0, width /*窗口宽*/ = 0;
    string contents = " ";
    // mutable关键字修饰的变量永远可变，即是在const(this指向const)中也可以修改
    mutable size_t access_ctr = 0;   // access_ctr是可变数据成员
    void do_display(ostream &) const // 负责显示内容
    {
        cout << contents;
        // 这个函数是在类内定义的，隐式地被设为内联函数，因此调用do_display不会带来额外的开销
        // 定义这个函数在类规模扩大时，display的操作可能更加复杂，此时把相应的操作写在一个函数里会更好
        // 在实践中，设计良好的C++代码常常包含大量类似于do_display的小函数，通过调用这些函数,可以完成一组其他函数的“实际”工作。
    }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline screen &screen::move(pos r, pos c)
{
    pos row = r * this->width; // 计算行的位置
    this->cursor = row + c;    // 行内光标移动到指定的列
    return *this;              // 作为左值返回
}

inline char screen::get(pos r, pos c) const // 在类内中声明为inline函数
{
    pos row = r * width;
    return contents[row + c];
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
// 此外,在类外部的作用域里,类的对象名字被隐藏了
// 因此在类外部定义函数时要加上类作用域符,把作用域转到类中,并且不用在对其他成员授权
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 名字查找：声明一个对象时，名字查找会先在该 块中这条语句以上查找，如果没有再向块外的上面查找
// 如果也没有，那么编译器就会报错
// 类中的名字查找有点不同,其会查找类中所以成员,包括private,而不是只查找该条语句上面的语句
// 因此，如果类中有成员和全局变量同名，那么类中定义的函数使用的是类中的成员而不是全局变量
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 一般来说，内层作用域可以重新定义外层作用域中的名字，即使该名字已经在内层作用域中使用过。
// 然而在类中，如果成员使用了外层作用域中的某个名字，
// 而该名字代表一种类型，则类不能在之后重新定义该名字,也是typedef和using
typedef double Money;
Money bal = 4.14;
class Accout1
{
  public:
    Money roll; // roll是double
    Money balance()
    {
        // 测试类的名字查找
        return bal; // 返回的是下面的这个int类型的bal
    }
    typedef int Money;
    // 错误:不能重新定义Money,(但是编译器不报错!)
    Money bal; // bal是int类型
    // ...
};
// 需要特别注意的是，即使Accout1中定义的Money类型与外层作用域一致，上述代码仍然是错误的。
// 尽管重新定义类型名字是一种错误的行为，但是编译器并不为此负责。一些编译器仍将顺利通过这样的代码，而忽略代码有错的事实。
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 聚合类:所有成员都是public的,没有定义任何构造函数。没有类内初始值,没有基类(15章介绍)。
struct Data
{
    int val; // 没有类内初始值
    string s;
    int array[3];
    // 没有构造函数
};
// 我们可以提供一个花括号括起来的成员初始值列表，并用它初始化聚合类的数据成员
// 初始值的顺序必须与声明的顺序一致，也就是说，第一个成员的初始值要放在第一个，然后是第二个
// 如果要数组,那么初始化的数组元素要用{}括起来,而且元素必须小于数组长度,如果小于,那么后面的值将会被值初始化
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 字面值类:数据成员都是字面值类型的聚合类(并且字面值类的成员都是隐式const).如果一个类不是聚合类，但它符合下述要求，则它也是一个字面值常量类:
// 1 数据成员都必须是字面值类型。2 类必须至少含有一个constexpr构造函数。
// 3 如果一个数据成员含有类内初始值，则内置类型成员的初始值必须是一条常量表达式;
// 3 或者如果成员属于某种类类型，则初始值必须使用成员自己的constexpr构造函数。
// 4 类必须使用析构函数的默认定义，该成员负责销毁类的对象
// constexpr构造函数:由于构造函数不能有返回值但是constexpr函数要求有且只有一个返回,因此综合来看,constexpr构造函数的函数体应该是空
class constexpr_class
{
  private:
    bool io;
    bool hw;
    bool other;

  public:
    constexpr constexpr_class(bool c_io) : io(c_io), hw(c_io), other(c_io){};
    constexpr constexpr_class(bool c_io, bool c_hw, bool c_other) : io(c_io), hw(c_hw), other(c_other){};
    // constexpr构造函数的函数体为空,初始化只能用 : 来初始化成员变量
    constexpr_class() = default;
    // 当然也可以是default,但是声明不能有constexpr,因为合成构造函数的隐式声明没有constexpr
    ~constexpr_class();
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 类的静态成员:有时候我们需要类的成员和类本身相关,而不是和类的对象相关,而且该成员储存方式希望是类的对象共同享有.
// 当该成员改变时,所有对象的该成员都改变.例如银行利率
// 使用:在定义类时在需要的成员声明加static即可实现静态成员,成员可以是private或者是public,类型可以是引用,指针或者是类类型
// 该关键字只能出现在类的内部声明中,在外部定义静态成员时不能重复static关键字
class Accout2
{
  private:
    std::string owner;
    double amount;
    static double initRate;     // 静态成员变量 汇率
    static double interestRate; // 静态成员变量 利率
  public:
    static int accout_count;          // 一般静态成员变量不能在类内初始化
    static constexpr int peroid = 30; // 但是加上const或者constexpr就可以
    Accout2(string s1, double d1) : owner(s1), amount(d1)
    {
        ++accout_count;
    }
    void calculate()
    {
        amount += amount * interestRate;
        // 成员函数可以不通过::就能直接访问静态成员
    }
    static ostream &show_rate() // 静态成员函数:返回利率
    {
        cout << interestRate << endl;
        return cout; // 静态成员函数没有this指针,因此返回的只能是静态成员
        // 由于该函数是所有对象共享,因此调用该函数:  Accout2::show_rate();
    }
    static void change_rate(double);
    // 在某些非静态数据成员可能非法的场合，静态成员却可以正常地使用(静态成员变量不属于任何对象)
    // 举个例子，静态数据成员可以是不完全类型(编译器没有为其分配内存)(也就是可以在类中声明指向类的指针或者是类对象)
    // 特别的，静态数据成员的类型可以就是它所属的类类型。而非静态数据成员则受到限制，只能声明成它所属类的指针或引用
    static Accout2 test; // 静态成员可以是不完全类型
    Accout2 *p;          // 指针实际上在机器上已经定义了大小,所有指针的大小都是一样的
    // 非静态成员变量不能作为默认实参的(因为本身就是对象的一部分),静态成员变量可以
};
// 静态成员位于所有对象之外,对象中不包含静态成员,静态成员被所有对象共享
// 类似的,静态成员函数也不和对象绑定在一起,因此没有this指针(显式调用和隐式调用都不行),也不能声明为const
// 由于静态成员不存在于对象之中(他们不是在对象被创建时定义的),因此不能使用构造函数来初始化静态成员
// 因此类的静态成员只能在类外部定义并初始化,而且只能定义一次.类似全局变量,静态成员变量一直存在于整个程序的生命周期
// 静态成员函数也可以定义在类外,但是在类外定义时不能重复static关键字,该关键字只能出现在类内部声明时.
void Accout2::change_rate(double new_rate)
{
    // 类外定义静态成员函数时不能在前加static,只能在类内声明时使用static
    interestRate = new_rate;
}
// 在全局区定义静态成员:类型 类名::成员名字
double Accout2::interestRate = 1.1;
int Accout2::accout_count = 0;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    person one;               // 默认构造函数:创建默认构造函数的对象时,不需要加()
    person two("li", 1);      // 自定义构造函数
    person three(2, "zhang"); // 构造函数列表初始值
    cout << "please input unfold_data\n";
    read(cin, one);
    cout << "one : ";
    one = 3.141; // 调用转换构造函数,把3.141转换为pos类型赋给pos_x
    // 如果在转换构造函数声明的前加上explicit关键字(抑制转换),那么上面这条语句将会报错
    print(cout, one);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    screen myscreen;
    myscreen.move(3, 3).set('#');
    // 相当于(但是有区别)
    myscreen.move(3, 3);
    myscreen.set('#');
    // 由于move返回的是screen&为左值,因此可以继续使用.来使用set函数
    // 如果move返回是screen，那么实际上的move返回的是myscrenn的副本,set函数并没有实际改变myscreen
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 测试名字查找
    Accout1 test;
    test.roll = 3.14;
    test.bal = 3.14;
    cout << "roll=" << test.roll << " bal=" << test.bal << " balance return = " << test.balance() << endl;
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 聚合类
    struct Data test_data;
    test_data.s = "Yes";
    test_data.val = 1;                                           // 拷贝初始化
    test_data = {0, "No", {1, 1} /*还有一个将会被值初始化为0*/}; // 列表初始化,顺序必须和定义的一致
    for (auto i : test_data.array)
    {
        cout << i << " ";
        // 输出1 1 0,没有被列表初始化的元素被值初始化为0
    }
    cout << endl;
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 静态成员
    //  使用静态成员
    //  虽然静态成员不属于类的某个对象，但是我们仍然可以使用类的对象、引用或者指针来访问静态成员
    Accout2 one1("one", 100.0);
    Accout2 two2("tow", 200.0);
    cout << "使用对象的点操作符:";
    one1.show_rate();                                     // 使用某个对象的点操作符来访问静态成员
    cout << "对象数量:" << Accout2::accout_count << endl; // 也可以直接用 {类名::静态成员来} 访问
    cout << "旧利率:";
    Accout2::show_rate(); // 使用静态成员函数
    Accout2::change_rate(1.3);
    cout << "新利率:";
    Accout2::show_rate();
    // system("pause");
    // 没有析构函数?确实奇怪
    // END
    return 0;
}