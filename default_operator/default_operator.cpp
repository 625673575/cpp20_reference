#include <iostream>

struct C
{
	int i;
	// 参数为按值传递
	friend bool operator==(C, C) = default; // C++20起支持
};
int main()
{
	C a{ 1 };
	C b{ 2 };
	C a1{ 1 };
	std::cout << std::boolalpha << (a == b) << std::endl << (a == a1);
}