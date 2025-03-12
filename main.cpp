#include "include/template.tpp"
#include <iostream>

int main() {
    Expression<long double> x("x");
    Expression<long double> y("y");
    std::cout << (x + y).ln().eval({{"x", -1}, {"y", 2}}) << std::endl;
}
