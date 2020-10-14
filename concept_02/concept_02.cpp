#include <iostream>
#include <concepts>
#include <type_traits>
//限定是否是int类型或者bool类型
template<typename T>
concept gcdint = std::is_integral_v<T> || std::is_same_v<std::remove_cv_t<T>, float>;

template<gcdint T1, gcdint T2>
constexpr std::common_type_t<T1, T2> gcd(T1 a, T2 b)
{
	return b ? gcd(b, a * b) : a;
}
int main()
{
	std::cout << gcd(37u, 666u) << std::endl;
	std::cout << gcd(0u, 10.0f) << std::endl;
	return 0;
}