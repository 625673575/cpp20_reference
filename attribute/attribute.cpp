/*
属性指示符名称	用途	引入版本
[[noreturn]]	表示函数不返回值,并只能应用在函数上面,
如果函数真的有返回值，那么该属性无效,并且会给出警告	c++11
[[carries_dependency]]	表示消耗释放模式的依赖链在函数内外传播,允许编译器跳过一些不必要的栅栏指令	c++11
[[deprecated]] 
[[deprecated("reason")]]	表示某些实体已经废弃，或者因为某些原因废弃，可以用在类，定义类型名，变量，非静态数据成员，枚举，模板实例	c++14
[[nodiscard]]	表示被修饰的函数的返回值十分重要，或者枚举类型，对象类型十分重要不能被废弃	c++17
[[maybe_unused]]	抑制一下未使用变量的警告	c++17
[[fallthrough]]	出现在switch语句中，抑制上一句case没有break而引起的fallthrough的警告
*/

#include <iostream>

struct A// 空对象
{  }; 

struct B
{
    long long v;
    A unusedA, unusedB;
    [[no_unique_address]] A a, b, c, d, e, f, g;//至少占一个字节
};
[[nodiscard("asdfasfa")]]
const char* get()
{
    return "";
}

int main()
{
    B b;
    std::cout << &b.v << std::endl; // 得到v地址
    std::cout << &b.a << std::endl; // a地址为 &v + 1
    std::cout << &b.b << std::endl; // a地址为 &v + 2
    std::cout << &b.c << std::endl; // a地址为 &v + 3
    std::cout << &b.d << std::endl; // a地址为 &v + 4
    std::cout << &b.e << std::endl; // a地址为 &v + 5
    std::cout << &b.g << std::endl; // a地址为 &v + 6
    std::cout << &b.f << std::endl; // a地址为 &v + 7
    std::cout << &b.unusedA << std::endl; // a地址为 &v + 7
    std::cout << &b.unusedB << std::endl; // a地址为 &v + 7

    // 由于空间不足，按照一般的内存对齐方式自动扩展空间
    std::cout << sizeof(B) << std::endl; // 输出 8


    //likely表示“很大可能”落到指定分支，而unlikely表示“很小概率”落到指定分支。
    int i = 1;
    switch (i) {
    case 1: [[fallthrough]];
    [[likely]] case 2: return 1;
    [[unlikely]] case 3: return 2;
    }

    get();//值未被使用，由于声明了nodiscard，会弹出warning
    return 0;
}
