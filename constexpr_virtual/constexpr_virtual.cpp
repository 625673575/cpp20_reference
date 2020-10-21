#include <iostream>
using namespace std;

struct X1 {
    virtual int f() const = 0;
};

struct X2 : public X1 {
    constexpr virtual int f() const { return 2; }
};

struct X3 : public X2 {
    virtual int f() const { return 3; }
};

struct X4 : public X3 {
    constexpr virtual int f() const { return 4; }
};


int main()
{
    constexpr X4 x4;
    constexpr int res = x4.f(); // == 4
    std::cout << "res is: " << res;
    return 0;

}
