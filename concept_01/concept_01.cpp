#include <concepts>

namespace {
	struct A { };

	//same_as
	template<class U>
	void same_as_func(U t)requires std::same_as<U, int>{ }

	//derived_from

	struct NonDerivedClass {};
	struct BaseClass {};
	struct DerivedClass :BaseClass {};
	template<class Derived, class Base>
	auto derived_from_func(Derived _derived, Base _base) requires std::derived_from<Derived, Base>{}

	//convertible_to
	template<class From, class To>
	auto convertible_to_func(From _from, To _to) requires std::convertible_to<From, To>{}

	//common_reference_with,common_with
	template<class T, class U>
	auto common_reference_with_func(T _from, U _to)requires std::common_reference_with<T, U> {}

	//integral
	template<class U>
	void integral_func(U t)requires std::integral<U>{ }

	//signed_integral,unsigned_integral,floating_point
	template<class U>
	void signed_integral_func(U t)requires std::signed_integral<U>{ }
	template<class U>
	void unsigned_integral_func(U t)requires std::unsigned_integral<U>{ }
	template<class U>
	void floating_point_func(U t)requires std::floating_point<U>{ }

	//assignable_from
	template<class From, class To>
	auto assignable_from_func(From _from, To _to) requires std::assignable_from<From, To>{ _from = _to; }
	struct AssignableFromDouble {
		double d; 
		AssignableFromDouble():d(0){}
		AssignableFromDouble(double _d):d(_d){}
	};
}
int main() {
	//same_as usage
	same_as_func<int>(10); // OK,std::is_arithmetic<int>::value为true
	//same_as_func<double>(20.0); // OK,std::is_arithmetic<double>::value为true
	//same_as_func<A>(A()); // error,std::is_arithmetic<A>::value为false

	//derived_from usage
	derived_from_func(DerivedClass(), BaseClass());
	//derived_from_func(NonDerivedClass(), BaseClass()); //error

	//convertible_to usage
	convertible_to_func(DerivedClass(), BaseClass());//OK,convertiable
	convertible_to_func(100, 10.0f);//OK,convertiable
	//convertible_to_func("hello", 10.0f);//error

	//common_reference_with usage
	common_reference_with_func(100, 100);
	//common_reference_with_func("hello", 10.0f);//error

	integral_func(100);
	//integral_func(100.0f); error ,is not integer
	signed_integral_func(100);
	//signed_integral_func(100.0f);error,signed but not integer
	//signed_integral_func(100u);error,not signed
	unsigned_integral_func(100u);
	//unsigned_integral_func(100);
	floating_point_func(100.0);
	//floating_point_func(100)

	int a = 0;
	int& ra = a;
	assignable_from_func(ra, a);
	assignable_from_func(AssignableFromDouble(), 1.0);
	return 0;
}