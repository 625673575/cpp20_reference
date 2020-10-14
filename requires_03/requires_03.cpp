#include <type_traits>

template<typename T>
concept can_run = requires(T t)
{
    std::is_class<T>::value; // T是一个类型
    t(); // T类型有重载括号运算符，且是无参的
    t.run(); // T类型具有run()成员函数
    std::is_same_v<decltype(t.run()), int>; // T类型的run()函数的返回值为int类型
};

// concepts类型使用
template<can_run T>
int func(T t)
{
    t();
    return t.run(); // run()函数的返回值已被限定为int类型，所以此处可直接返回
}

struct A
{
    void run() { }
};

struct B
{
    void operator()() { }
};

struct C
{
    void operator()() { }
    void run() { }
};

struct D
{
    void operator()() { }
    int run() { return 0; }
};

int main()
{
    //func<int>(10); // 错误，这不是一个class或struct

    //func<A>(A()); // 编译错误，没有重载括号运算符
    //func<B>(B()); // 编译错误，没有run()函数
    //func<C>(C()); // 编译错误，run()函数返回值不是int类型
    int i = func<D>(D()); // 正确，编译通过
    return 0;
}