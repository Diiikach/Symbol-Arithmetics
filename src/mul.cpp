#include "../include/expression.hpp"
#include <cmath>


template<typename T>
DotProduct<T>::DotProduct(Expression<T> left, Expression<T> right):
    left_  (left),
    right_ (right)
{}

template<typename T>
T DotProduct<T>::eval(std::map<std::string, T> context) const {
    T value_left  = left_.eval(context);
    T value_right = right_.eval(context);

    return value_left * value_right;
}

template<typename T>
std::string DotProduct<T>::to_string() const {
    return std::string("(")   + left_.to_string()  +
           std::string(" * ") + right_.to_string() +
           std::string(")");
}

template<typename T>
Expression<T> DotProduct<T>::derivative(const std::string& var) const {
    return left_.derivative(var) * right_ + left_ * right_.derivative(var);
}

