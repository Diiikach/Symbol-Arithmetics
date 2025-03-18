#include "../include/expression.hpp"


template<typename T>
UnaryMinusProduct<T>::UnaryMinusProduct(const Expression<T>& arg):
    arg_ (arg)
{}

template<typename T>
T UnaryMinusProduct<T>::eval(std::map<std::string, T> context) const {
    T arg_num = arg_.eval(context);
    return -arg_num;
}

template<typename T>
std::string UnaryMinusProduct<T>::to_string() const {
    return "(-" + arg_.to_string() + ")";
}

template<typename T>
Expression<T> UnaryMinusProduct<T>::derivative(const std::string& var) const {
    return -arg_.derivative(var);
}
