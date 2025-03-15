#include <utility>

#include "../include/expression.hpp"


template<typename T>
Variable<T>::Variable(std::string name) const:
    name_ (std::move(name))
{}

template<typename T>
T Variable<T>::eval(std::map<std::string, T> context) const {
    auto iter = context.find(name_);
    if (iter == context.end())
    {
        throw std::runtime_error("Variable \"" + name_ + "\" not present in evaluation context");
    }
    return iter->second;
}

template<typename T>
std::string Variable<T>::to_string() const {
    return name_;
}

template<typename T>
Expression<T> Variable<T>::derivative() const {
    return Expression<T>(1);
}
