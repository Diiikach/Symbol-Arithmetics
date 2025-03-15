#include "../include/expression.hpp"
#include <cmath>


template<typename T>
SinFunc<T>::SinFunc(Expression<T> arg) const:
    arg_ (arg)
{}

template<typename T>
T SinFunc<T>::eval(std::map<std::string, T> context) const {
    T arg_num = arg_.eval(context);
    return std::sin(arg_num);
}

template<typename T>
std::string SinFunc<T>::to_string() const {
    return "sin (" + arg_.to_string() + ")";
}

template<typename T>
Expression<T> SinFunc<T>::derivative() const {
    Expression<T> first_part  = Expression<T>(std::make_shared<CosFunc<T>>(arg_));
    Expression<T> second_part = arg_.derivative();
    return first_part * second_part;
}

