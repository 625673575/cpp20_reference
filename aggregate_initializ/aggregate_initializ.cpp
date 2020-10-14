
#include <iostream>
template <typename T>
struct S
{
	T x;
	T y;
};

template <typename T>
struct C
{
	S<T> s;
	T t;
};

template <typename T>
struct D
{
	S<int> s;
	T t;
};

template <typename T>
struct I
{
	using type = T;
};

template <typename T>
struct E
{
	typename I<T>::type i;
	T t;
};

int main()
{

	//C c1 = { 1, 2 }; // error: deduction failed
	//C c2 = { 1, 2, 3 }; // error: deduction failed
	C c3 = { {1u, 2u}, 3 }; // OK, C<int> deduced
	//D d1 = { 1, 2 }; // error: deduction failed
	D d2 = { 1, 2, 3 }; // OK, braces elided, D<int> deduced
	E e1 = { 1, 2 }; // OK, E<int> deduced
	return 0;
}