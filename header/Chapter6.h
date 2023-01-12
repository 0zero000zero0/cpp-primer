// 阶乘

int fact(int val) // 提供的形参必须能够转化为对应类型(int)
{
    int ret = 1;
    while (val > 1)
    {
        ret *= val--;
    }
    return ret;
    // return语句返回值(如果有的话),把控制权交给主调函数(可能是main,也可能是其他的调用这个函数的函数)
}

int count_calls()
{
    static int cnt = 0;
    return ++cnt;
}
