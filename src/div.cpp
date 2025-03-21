#include "../include/expression.hpp"
#include <cmath>


template<typename T>
SlashProduct<T>::SlashProduct(Expression<T> left, Expression<T> right):
    left_  (left),
    right_ (right)
{}

template<typename T>
T SlashProduct<T>::eval(std::map<std::string, T> context) const {
    T value_left  = left_.eval(context);
    T value_right = right_.eval(context);
    if (value_right <= 0) {
        throw std::runtime_error("Division by 0");
    }
    return value_left / value_right;
}

template<typename T>
std::string SlashProduct<T>::to_string() const {
    return std::string("(")   + left_.to_string()  +
           std::string(" / ") + right_.to_string() +
           std::string(")");
}

template<typename T>
Expression<T> SlashProduct<T>::derivative(const std::string& var) const {
    Expression<T> numerator_part   = left_.derivative(var) * right_ - left_ * right_.derivative(var);
    Expression<T> denominator_part = right_ * right_;
    return numerator_part / denominator_part;
}
