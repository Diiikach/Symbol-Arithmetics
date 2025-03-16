#include "include/template.tpp"
#include <iostream>

using namespace std;

int main() {
    auto a = Expression<long double>("x");
    auto b = a.pow(Expression<long double>(2));
    cout << b.derivative().to_string() << endl;
}
