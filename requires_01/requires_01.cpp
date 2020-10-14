#include <iostream>
#include <concepts>
#include <map>

/*
简单约束的形式是一个非约束表达式的表达式（可以是概念），如果这个表达式能够通过编译，或者这个概念为真，那么这个约束表达式返回的概念的布尔值可能为真，否则一定为假
如果下面的类型有begin和end函数则可以通过编译
类型约束的形式是 typename xxx;如果 xxx 类型存在则为真
*/
template<typename T>
concept weak_iterable = requires(T x)
{
	typename T::iterator;
	x.begin();
	x.end();
};

int main()
{
	std::cout << "is std::map iterable: "<< std::boolalpha << weak_iterable<std::map<int,int>> << std::endl;
	std::cout << "is std::pair iterable: " << std::boolalpha << weak_iterable<std::pair<int, int>> << std::endl;
	return 0;
}