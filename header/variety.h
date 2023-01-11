
int test_variety = 0;
// const关键字可以使得变量只读,并且只在该文件内可以访问
// 由于只读的属性,const修饰的变量必须初始化
// 如果要跨文件使用const修饰的变量，那么在定义，声明时都必须加上extern
extern const int const_int = 666;

class test_class
{
  public:
    int ival;
};