#include <cmath>
#include "../include/expression.hpp"


template<typename T>
CosFunc<T>::CosFunc(const Expression<T>& arg):
    arg_ (arg)
{}

template<typename T>
T CosFunc<T>::eval(std::map<std::string, T> context) const {
    T arg_num = arg_.eval(context);
    return std::cos(arg_num);
}

template<typename T>
std::string CosFunc<T>::to_string() const {
    return "cos (" + arg_.to_string() + ")";
}

template<typename T>
Expression<T> CosFunc<T>::derivative(const std::string& var) const {
    Expression<T> first_part  = -Expression<T>(std::make_shared<SinFunc<T>>(arg_));
    Expression<T> second_part = arg_.derivative(var);
    return first_part * second_part;
}

