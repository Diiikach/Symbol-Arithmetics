#include "../include/expression.hpp"
#include <cmath>


template<typename T>
ExpFunc<T>::ExpFunc(Expression<T> arg) const:
    arg_ (arg)
{}

template<typename T>
T ExpFunc<T>::eval(std::map<std::string, T> context) const {
    T arg_num = arg_.eval(context);
    return std::exp(arg_num);
}

template<typename T>
std::string ExpFunc<T>::to_string() const {
    return "exp (" + arg_.to_string() + ")";
}

template<typename T>
Expression<T> ExpFunc<T>::derivative() const {
    Expression<T> first_part  = Expression<T>(std::make_shared<ExpFunc<T>>(*this));
    Expression<T> second_part = arg_.derivative();
    return first_part * second_part;
}