constexpr int add100_constexpr(int n) {
    return n + 100;
}

consteval int add100_consteval(int n) {
    return n + 100;
}

int main() {
    constexpr int c_constexpr = add100_consteval(200);
    int x = 200;
    // int d_consteval = add100_consteval(x);   // 编译失败
    int d_constexpr = add100_constexpr(x);      //编译成功，constexpr并非强制限定为常量表达式
    return 0;
}