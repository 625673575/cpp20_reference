#include <iostream>
#include <string>
#include <concepts>

//在模板中requires限定T类型的范围

template<typename T>
concept Integral = std::is_integral<T>::value;

template<typename T>
requires Integral<T>
T Add(T a, T b)
{
	return a + b;
}

template<typename T>
T Add1(T a, T b) requires Integral<T>
{
	return a + b;
}

template<Integral T>
T Add2(T a, T b)
{
	return a + b;
}
int main(int argn, char** argv)
{
	auto c = Add(10, 5);
	auto c1 = Add(10, 5);
	auto c2 = Add(10, 5);
	//auto c = Add(10.3, 5.2);
	std::cout << c << c1 << c2 << std::endl;
	return 0;
}