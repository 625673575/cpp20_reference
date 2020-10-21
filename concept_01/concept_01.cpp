#include <concepts>
#include <memory>
#include <iostream>
#include <string>
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
		//AssignableFromDouble(const AssignableFromDouble& t) = delete;
		//AssignableFromDouble& operator=(const AssignableFromDouble& t) = delete;
		AssignableFromDouble() :d(0) {}
		AssignableFromDouble(double _d) :d(_d) {}
	};

	//swappable,with
	template<class U>
	void swappable_func(U t)requires std::swappable<U>{ }
	template<class U, class T>
	void swappable_with_func(U&& _u, T&& _t)requires std::swappable_with<U, T>{ std::swap(_u, _t); }

	//constructible_from
	template<class U>
	void constructible_from_func(U t)requires std::constructible_from<U, std::string, std::string>{ }
	struct ConstructableFromString {
		ConstructableFromString(std::string s1, std::string s2) {}
	};

	//destructible
	template<class T>
	void destructible_func(T t)requires std::destructible<T>{ }
	struct DestructorThrow {
		~DestructorThrow() noexcept(false) {}
	};

	/* copy can constructible from (const) reference,while move only consider the value
	move_constructible
	template< class T >
	concept move_constructible = std::constructible_from<T, T> && std::convertible_to<T, T>;

	template <class T>
	concept copy_constructible =
		std::move_constructible<T> &&
		std::constructible_from<T, T&> && std::convertible_to<T&, T> &&
		std::constructible_from<T, const T&> && std::convertible_to<const T&, T> &&
		std::constructible_from<T, const T> && std::convertible_to<const T, T>;
	*/

	//equality_comparable,equality_comparable_with
	template<class U>
	void equality_comparable_func(U t)requires std::equality_comparable<U>{ }
	template<class T, class U>
	void equality_comparable_with_func(T _from, U _to)requires std::equality_comparable_with<T, U> {}
	struct ComparableType {
		int a;
		std::strong_ordering operator<=>(const ComparableType&) const = default;
	};

	/*
	Object concepts
	movable -- specifies that an object of a type can be moved and swapped
	copyable -- specifies that an object of a type can be copied, moved, and swapped
	semiregular -- specifies that an object of a type can be copied, moved, swapped, and default constructed
	regular -- specifies that a type is regular, that is, it is both semiregular and equality_comparable
	*/

	//invocable, regular_invocable
	template<class F>
	void invocable_func(F t)requires std::invocable<F, int, float>{ }
	struct InvocableType {
		float operator()(float x, float y)const { return x + y; }//int can pass to float
	};
	template<class F>
	void regular_invocable_func(F t)requires std::regular_invocable<F, int&, float>{ }
	struct RegularInvocableType {
		float operator()(int& x, float y)const { return x + y; }
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

	swappable_func(" ");
	swappable_func(1);
	int a = 10, b = 100;
	swappable_with_func(a, b);
	std::cout << a << "  " << b << std::endl;
	auto da = std::make_unique<AssignableFromDouble>(0.1);
	auto db = std::make_unique<AssignableFromDouble>(0.2);
	swappable_with_func(da, db);
	std::cout << da->d << "  " << db->d << std::endl;

	AssignableFromDouble ca(0.8);
	AssignableFromDouble cb(0.9);
	swappable_with_func(ca, cb);//will cause error if you delete the copy constructor and operator==
	std::cout << ca.d << "  " << cb.d << std::endl;

	constructible_from_func(ConstructableFromString("1", "2"));
	//constructible_from_func(ca);//error,Can't construct from void type

	destructible_func(ca);//default destruct function set to nothrow(true)
	//destructible_func(DestructorNoThrow());// error explicit nothrow(false)

	//equality_comparable_with_func(1, "123"); //error ,int can't compare with char*
	equality_comparable_with_func(std::string(""), "123");//ok,char* is comparable with std::string

	//equality_comparable_func(AssignableFromDouble());
	equality_comparable_func(ComparableType());//OK,default operator<==> will make that class comparable

	//invocable_func(ca);//error no suitable operator(Args...)
	invocable_func(InvocableType());
	//regular_invocable_func(InvocableType());//error ,regular_invocable doesn't allow change its arguments,so reference or point is not allowed
	regular_invocable_func(RegularInvocableType());//must match exact type

	return 0;
}