#include "../include/expression.hpp"


template<typename T>
PowProduct<T>::PowProduct(const Expression<T> base, const Expression<T> power):
    base_ (base),
    power_ (power)
{}

template<typename T>
T PowProduct<T>::eval(std::map<std::string, T> context) const {
    T base = base_.eval(context);
    T power = power_.eval(context);
    T result{1};
    for (int i = 0; i < power; i++) {
        result *= base;
    }
    return result;
}

template<typename T>
std::string PowProduct<T>::to_string() const {
    return "(" + base_.to_string() + ")^(" + power_.to_string() + ")";
}

template<typename T>
Expression<T> PowProduct<T>::derivative() const {
    Expression<T> first_part  = power_ * Expression<T>(std::make_shared<PowProduct<T>>(base_, power_ - Expression<T>(1)));
    Expression<T> second_part = base_.derivative();
    return first_part * second_part;
}

