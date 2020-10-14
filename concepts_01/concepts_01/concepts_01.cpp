#include <type_traits>

// 声明一个数值类型的concept
template<typename T>
concept number = std::is_arithmetic<T>::value; // 创建对模板类型T std::is_arithmetic<T>::value为true的约束

// 使用具有约束的类型，调用该函数时，T类型必须符合std::is_arithmetic<T>::value等于true，否则编译报错
template<number U>
void func(U t)
{ }


struct A
{ };

int main()
{
	// 调用
	func<int>(10); // 正确，std::is_arithmetic<int>::value为true
	func<double>(20.0); // 正确，std::is_arithmetic<double>::value为true

	//func<A>(A()); // 错误，std::is_arithmetic<A>::value为false
}
