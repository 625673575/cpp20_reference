/*
如a与b是整型，那么a<=>b返回std::strong_ordering类型的纯右值(prvalue,不能取地址那种)：

如果a<b,(a<=>b)返回std::strong_ordering::less
如果a>b,(a<=>b)返回std::strong_ordering::greater
如果a与b全等/相等,(a<=>b)返回std::strong_ordering::equal
如果a b是浮点值，就返回的是std::partial_ordering::less/greater/equivalent或者std::partial_ordering::unordered(如果ab中有一个NaN)
+--------------------------------------------------------------------+
|                  |          Numeric  values          | Non-numeric |
|     Category     +-----------------------------------+             |
|                  | -1   | 0          | +1            |   values    |
+------------------+------+------------+---------------+-------------+
| strong_ordering  | less | equal      | greater       |             |
| weak_ordering    | less | equivalent | greater       |             |
| partial_ordering | less | equivalent | greater       | unordered   |
| strong_equality  |      | equal      | nonequal      |             |
| weak_equality    |      | equivalent | nonequivalent |             |
+------------------+------+------------+---------------+-------------+
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;
struct Name {
	string first_name;
	string mid_name;
	string last_name;
	//bool operator<(const Name& other) const {
	//	//before c++11
	//	return first_name < other.first_name
	//		|| first_name == other.first_name && mid_name < other.mid_name
	//		|| first_name == other.first_name && mid_name == other.mid_name && last_name < other.last_name;

	//	//after c++11
	//	return std::tie(first_name, mid_name, last_name) <
	//		std::tie(other.first_name, other.mid_name, other.last_name);
	//}
	std::strong_ordering operator<=>(const Name&) const = default;//strong_ordering

};
struct ID {
	int id_number;
	auto operator<=>(const ID&) const = default;
};

struct Person {
	ID id;
	string name;
	string email;
	std::weak_ordering operator<=>(const Person& other) const//weak_ordering,only compare part of the variable memeber
	{
		return id <=> other.id;
	}
};
//前面说了，operator <=> 的代码可以由编译器来生成，但是有一个注意事项。就是类成员中有容器类型(例如vector)时，需要将operator == 单独列出来，像这样：
struct SomeType {
	int int_property;
	std::vector<int> some_ints;
	std::strong_ordering operator<=>(const SomeType&) const = default;
	bool operator==(const SomeType&) const = default; // 加上这一行
};
int main()
{
	map<Name, int> mName;
	mName.emplace(Name(), 168);
	std::cout << "Hello World!\n" << mName.at(Name());
}