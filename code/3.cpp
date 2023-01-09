///
///@file 3.cpp
///@author Zero (2405549856@qq.com)
///@brief 个人学习c++ primer时的代码,主要用于复习
///@date 2023-01-09
///

#include <bits/stdc++.h>
#include <D:\C in vsocde\c++ primer\c++ primer\header\variety.h>
#include <string>
using namespace std;
// 使用命名空间(名字空间)
// 注意必须以分号结尾
// 头文件中不应该包含using声明，因为头文件的内容会被拷贝到到引用它的文件，这样可能会造成冲突

int main()
{

    auto a = "ok";
    // string：要使用string，必须先包含<string>和,使用std::string
    string s1;        // 默认初始化为空字符串
    string s2 = s1;   // S2也是空,或者是string s2(s1)也可以初始化
    string s(3, 'a'); // s3为aaa
    cout << s << endl;
    // 用 = 进行初始化实际上是拷贝初始化,把右边的字符串复制到左边
    // 而()是直接初始化,当初始值有多个时,用()

    // string操作
    //  os << s;//把s写入到输出流中,返回s的值
    //  is >> s1;//从is中读取字符串给s，以空白为分隔符，返回is
    // 这里空白指的是空白符号:空格,换行,制表符等
    //  getline(cin, s1), ; // 从istream(cin)中读取一行给s，返回is
    s.empty(); // 判断s是否为空，若为空则返回ture，否则返回false
    s.size();  // 返回s字符数目
    // 实际上empty和size是string的成员函数
    s[2];        // 返回第3个字符
    s2 = s1 + s; // 把s连接到s1末尾,返回s1与 s连接的结果
    // 如果混用字面值字符（‘a'），那么必修确保每一个+的两侧对象至少有一个是string
    s1 = s2;  // 用s2的副本代替s1原来的字符串
    s1 == s2; // 判断s1与s2是否相等，此外!=,>=,<=,>,<也可以用于字符串判断,根据字符在字典中顺序来判断
    // 比较规则 :1:如果两个字符串长度不同但是较短的字符串的对应字符与较长的相同,那么结果就是较长的大
    // 2：只要根据字典顺序，如果有一个字符串的对应位置的字符大，那么这个字符串就是比较大的，不管二者长度
    cout << "测试输入字符串,请输入s1c" << endl;
    cin >> s1;                     // string对象会忽略开头的空白,并从第一个真正的字符开始读取,直到遇到下一个空白
    cout << "s1 = " << s1 << endl; // 如果输入为“   ok  ”，实际输出就是“ok”，没有前后的空白
    // cout << "测试while输入字符串" << endl;
    // while(cin>>s2)//读取时会检测流是否到文件末尾或者是遇到非法输入
    //     cout << s2 << endl;
    // 如果要在string输入中包含空格,那么可以使用getline函数,该函数以换行符为结束标志
    // 换行符也被读取进去getline中，但是不写入到string里，如果第一个就是换行符，那么这个字符串就是空
    // 使用endl会结束当前行并且刷新 显示缓冲区
    // cout << "测试getline函数" << endl;
    // while (getline(cin,s))
    // {
    //     if(!s.empty())
    //     {
    //         cout << s << "  字符串长度为 "<<s.size()<<endl;
    //     }else
    //         cout << " 字符串长度 " << s.size() << endl;
    // }
    // string::size_type:这是成员函数size()返回结果的类型,是一种unsigned
    // 如果表达式中有sieze函数，那么就不要在使用int，避免混用int与unsigned可能带来的问题
    string s4 = "test " + s + "\n";
    cout << s4;
    // string s5 = "hello" + "\n";//报错
    // 处理string对象的字符,cctype头文件,虽然cctype与ctype.h一致,但是前者更符合c++命名规则

    // 范围for(range for):用于遍历某个序列来执行某种操作
    // for(declaration : expression)  statement
    s4 = "It's ok!";
    decltype(s4.size()) n1 = 0; // decltype返回数据类型
    for (auto c1 : s4)
        if (isalpha(c1))
            ++n1;
    cout << "n1= " << n1 << endl;
    // 如果要通过range for来改变字符串中的字符，就必须使用引用来进行
    for (auto &c2 : s4)   // 自动推断为相应的引用类型
        c2 = toupper(c2); // 转换为大写
    cout << "s4 = " << s4 << endl;

    // 用range for遍历二维数组:除了最内层的遍历循环,其他的所以循环都应该是引用类型
    int arrayx[2][2] = {1, 2, 3, 4};
    for (int(&row)[2] : arrayx) // 需要用引用才能进行
    {
        for (int &col : row) // 如果使用auto 也要加上&
            cout << col << " ";
        cout << endl;
    }
    //
    // 案例 转16进制
    const string hex_digits = "0123456789ABCDEF";
    string result;
    string::size_type n2 = 0;
    string test;
    cout << "输入要转为16进制的数字 " << endl;
    while (cin >> n2)
    {
        if (n2 < hex_digits.size())
        {
            result += hex_digits[n2];
        }
    }
    cout << "hex number is " << result << endl;
    // 通过n来查找字典hex_digits里的数字,赋给result的每一个字符

    // 编程练习
    // 把字符串所有字符替换为x
    string s5("It's ok");
    for (auto &c3 : s5) // 如果改成auto或者char(也就是不使用引用),则s5将不会被修改
    {
        c3 = 'x';
    }
    cout << "s5 = " << s5 << endl;
    // 默认初始化为空
    string s6;
    cout << s6[0] << endl;
    // 去除标点
    string s7;
    cout << "输入s7" << endl;
    cin >> s7;
    for (auto &c4 : s7)
    {
        if (!ispunct(c4))
        {
            cout << c4;
        }
    }
    cout << endl;

    // vectior:一种类模板,本身不是类,可以把他看作是一份说明书,如果在提供一些具体的类型信息,那么编译器就会根据这个说明书来创建一个实例化
    // 提供信息的方式为 ：在vector后面加上< 类型 >,这样编译器就可以根据说明书和类型创建一个实例化
    vector<int> ivec;            // ivec保存一个int类型的对象
    vector<vector<string>> file; // file保存的类型是vector这种对象
    // 由于vector容纳着其他对象，因此也被称为 容器，其中的每一个对象都有与之对应的一个索引，由于索引是一种引用而不是对象，因此没有对应的引用类型
    // 初始化vector，前提是对象要相同
    int val = 1;
    vector<int> v1;          // 默认初始化（空）
    vector<int> v2(v1);      // v2包含v1所以元素的副本
    vector<int> v3 = v2;     // 与上面一样
    vector<int> v4(3, val);  // 初始化为3个val,如果不加val,则将会初始化为默认的元素
    vector<int> v5{1, 2, 3}; // 初始化为1，2，3，在v5和{}之间可以加上=
    // 注意：1 拷贝初始化（=）只能提供一个初始值 2 如果是类内初始化，只能使用=或者{} 3 列表初始化只能使用{}，不能用()
    // 值初始化：只提供vector对象的元素数量而不用略去初始值，那么库会创建一个值初始化的元素初始值，并把它赋值给容器中所有元素。
    // 初始值由对象的类型决定，例如int，元素初始值是0而string是默认初始化
    vector<int> v6(10);    // 10个元素都是0
    vector<string> v7(10); // 10个元素,每个都是空string对象
    // 如果列表初始化里的值不能用来初始化vector，例如用10来初始化string，那么编译器就会尝试使用默认初始化。此时的10会被用于创建对象
    vector<string> v8{10, "OK"}; // v8有10个元素,每一个都是默认初始化的值(空)
    // 向vector中添加元素
    // 如果要创建一个含有0-9的容器，用列表太多，此时可以创建可以空列表，用vector的成员函数push_back来把值压入到容器的末尾back
    for (int i = 0; i < 10; i++)
        v1.push_back(i);
    // cin同理
    {
        int temp;
        while (cin >> temp)
        {
            v2.push_back(temp);
        }
    }
    // 高效写入容器带来的副作用就是严格的要求，其中之一是必须确保所写的循环正确，特别是当循环可能改变容量时
    // 不能使用range for 来向容器中添加元素
    // 容器操作除了push_back外,还有很多其他的操作,它们和string的一样,访问也是类似于string
    // 不能使用下标带添加元素,下标只能用于访问已存在的元素
    //  成绩分段人数统计
    vector<unsigned> score(11, 0);
    unsigned grade;
    cout << "请输入成绩" << endl;
    while (cin >> grade)
    {
        if (grade <= 100)
        {
            ++score[grade / 10];
        }
    }
    cout << "分段\t"; // 输出列表
    for (int i = 0; i <= 10; i++)
    {
        if (0 == i)
        {
            cout << "0~10\t";
        }
        else
            cout << i * 10 << "~" << i * 11 << "\t";
    }
    cout << endl
         << "人数\t";
    for (auto a1 : score)
        cout << a1 << "\t";
    cout << endl;

    // 迭代器：类似指针，可以用于访问一个容器的元素，因为有的容器不支持下标访问
    // 使用迭代器
    auto iterator_begin = v1.begin(), iterator_end = v1.end(); // iterator_begin指示容器第一个元素,而iterator_end指向容器最后一个元素的下一个
    // 成员函数begin返回第一个元素，而成员函数end返回尾元素的下一个位置(这个位置没有存在元素,只是做个标记),由于空容器begin和end指向一致,因此可以用二者来判断是否为空
    // 如果容器是常量（const），那么返回类型也是const_iterator,c++11提供cbegin和cend来专门用于返回常量类型
    // 由于一般不清楚（不在意）迭代器准确的类型，因此使用auto来声明最方便
    // 任何改变vector容量的操作，例如push_back会使得该vector对象的迭代器失效，具体原因后面解释

    // 迭代器运算:1 迭代器可以用==和!=来比较两个迭代器是否指示的元素是否一致
    // 2 *iterator 类似指针解引用,返回指向的元素的值
    // 3 ++iterator 与指针类似,使iterator指向下一个元素,--则指向上一个元素
    // 注意:由于end实际上并不指向具体的元素,因此对于指向end的迭代器不能解引用,++
    // 4 iteratot->member 解引用iterator并获取member成员,等于(*iterator).member
    // 以下只对于string与vector(前提是都是指向同一个的迭代器):除了上三点，还支持iterator+n,iterator-n,iterator+=n,iterator-=n,iter1-iter2(返回类型为defference_type),<=等运算

    // 把第一个字母大写
    s1 = " some thing?";
    for (auto i1 = s1.begin(); i1 != s1.end(); ++i1)
    {
        // 使用!=而非<是因为有的容器没有定义<,而全部容器都定义了!=和==,因此使用!=和==更加广泛
        if (!isspace(*i1)) // 确保第一个不是空格
        {
            *i1 = toupper(*i1);
            break;
        }
    }
    cout << "s1= " << s1 << endl;

    // 二分搜索
    for (int i = 1; i <= 10; i++)
        v1.push_back(i * i); // v1是vector<int>
    auto i1 = v1.begin(), i2 = v1.end();
    auto mid = i1 + (i2 - i1) / 2;
    int sought = 0;
    cout << "请输入要查找的数" << endl;
    cin >> sought;
    while (mid != i2 && *mid != sought && *v1.end() != sought)
    {
        if (sought < *mid)
        {
            i2 = mid;
        }
        else if (sought > *mid)
        {
            i1 = mid + 1;
        }
        mid = i1 + (i2 - i1) / 2;
        if (mid == i2)
            cout << "不存在" << endl;
    }
    if (mid != i2)
        cout << "该值在第 " << mid - v1.begin() + 1 << " 个位置" << endl;

    // 数组:除了C语言的int等,c++还有string数组,但是不存在引用数组
    string str1[3] = {"ok", "no", "\n"};
    int *array1[3] = {nullptr};
    int *(&r1)[3] = array1; // r1引用一个指针数组
    // int &u[3]//报错，不存在引用数组
    // 不允许整个数组的拷贝和赋值
    // 由于编译器会把数组转化为指针,因此auto推断数组名时结果是对应类型的指针
    int str2[3] = {1, 2, 3};
    auto p1(str2); // p1是int*

    // 但是decltype返回的是数组
    decltype(str2) a2 = {1, 2, 3};
    // 函数begin和end(不是容器的成员函数):虽然可以通过计算得到尾指针,但是容易出错,因此c++11提供了这两个函数
    // 这两个函数定义在iterator中
    // end函数返回的也是尾元素的下一个位置的指针(不是尾元素),因此不能解引用和递增
    int *b1 = begin(str2), *e1 = end(str2);
    while (b1 != e1)
    {
        cout << *b1 << endl;
        b1++;
    }

    // 与旧代码的接口
    // c_str():用string类型来初始化字符串指针
    string s8 = "OK";
    const char *p2 = s8.c_str();   // 如果执行完c_str后想要一直使用返回的数组,建议重新拷贝一份这个数组
    cout << "p2 = " << p2 << endl; // 不用解引用

    // 虽然不能使用vector来初始化数组,也不能直接用一个数组来初始化另一个数组,但是可以使用数组来初始化vector
    vector<int> v9(begin(str2), end(str2)); // 只需要指明拷贝区域的首地址和尾后地址
    for (auto a1 : v9)
        cout << a1 << endl;

    return 0;
}