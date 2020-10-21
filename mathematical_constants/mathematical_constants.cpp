#include <numbers>
#include <iostream>
#include<iomanip>
using namespace std;
int main()
{
	double f = numbers::pi;
	cout << numbers::e << endl << numbers::pi << endl;
	cout << f << endl;
	cout << setiosflags(ios::fixed);
	cout << setprecision(0) << f << endl;
	cout << setprecision(2) << f << endl;
	cout << setprecision(12) << f << endl;

	std::cout << std::boolalpha; 
	std::cout << std::in_range<std::size_t>(-1) << '\n';
	std::cout << std::in_range<std::size_t>(42) << '\n';

	//std::cout << std::cmp_equal(1.0, 1) << '\n';//error C2338: The integer comparison functions only accept standard and extended integer types.
	std::cout << std::cmp_equal(1ul,1) << '\n';
}