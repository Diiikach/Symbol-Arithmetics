#include "../include/expression.hpp"

template<typename T>
PlusProduct<T>::PlusProduct(Expression<T> left, Expression<T> right):
    left_  (left),
    right_ (right) {
}

template<typename T>
T PlusProduct<T>::eval(std::map<std::string, T> context) const {
    T value_left  = left_.eval(context);
    T value_right = right_.eval(context);

    return value_left + value_right;
}

template<typename T>
std::string PlusProduct<T>::to_string() const {
    return std::string("(")   + left_.to_string()  +
           std::string(" + ") + right_.to_string() +
           std::string(")");
}

template<typename T>
Expression<T>PlusProduct<T>::derivative() const {
    Expression<T> first_part  = left_.derivative();
    Expression<T> second_part = right_.derivative();
    return first_part + second_part;
}

