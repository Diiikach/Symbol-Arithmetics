#include "include/template.tpp"
#include <iostream>

int main() {
    Expression<long double> x("x");
    Expression<long double> y("y");
    std::cout << (-y).eval({{"x", -1}, {"y", 2}}) << std::endl;
}
