#include "../include/expression.hpp"
#include <cmath>


template<typename T>
Value<T>::Value(const T value):
    value_ (value)
{}

template<typename T>
T Value<T>::eval(std::map<std::string, T> context) const {
    (void) context;
    return value_;
}

template<typename T>
std::string Value<T>::to_string() const {
    return std::to_string(value_);
}

template<typename T>
Expression<T> Value<T>::derivative(const std::string& var) const {
    return Expression<T>(static_cast<T>(0));
}
