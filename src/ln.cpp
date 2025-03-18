#include "../include/expression.hpp"
#include <cmath>


template<typename T>
LnFunc<T>::LnFunc(Expression<T> arg):
    arg_ (arg)
{}

template<typename T>
T LnFunc<T>::eval(std::map<std::string, T> context) const {
    T arg_num = arg_.eval(context);
    if (arg_num <= 0) {
        throw std::invalid_argument("argument must be positive");
    }
    return std::log(arg_num);
}

template<typename T>
std::string LnFunc<T>::to_string() const {
    return "ln (" + arg_.to_string() + ")";
}

template<typename T>
Expression<T> LnFunc<T>::derivative(const std::string& var) const {
    Expression<T> first_part  = Expression<T>(1) / arg_;
    Expression<T> second_part = arg_.derivative(var);
    return first_part * second_part;
}
