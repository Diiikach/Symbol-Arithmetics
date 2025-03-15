#include "../include/expression.hpp"
#define _USE_MATH_DEFINES
#include "cmath"

template<typename T>
Expression<T>::Expression(std::shared_ptr<ExpressionImplementation<T>> impl) :
    impl_ (impl)
{}

template<typename T>
Expression<T>::Expression(std::string var) const:
    impl_ (std::make_shared<Variable<T>>(var))
{}
template<typename T>
Expression<T>::Expression(T val) const:
    impl_ (std::make_shared<Value<T>>(val))
{}

template<typename T>
T Expression<T>::eval(std::map<std::string, T> context) const {
    return impl_->eval(context);
}

template<typename T>
Expression<T> Expression<T>::operator+(const Expression<T>& that) const {
    return Expression<T>(std::make_shared<PlusProduct<T>>(*this, that));
}

template<typename T>
Expression<T>& Expression<T>::operator+=(const Expression<T>& that) {
    *this = *this + that;
    return *this;
}

template<typename T>
Expression<T> Expression<T>::operator-()  const {
    return Expression<T>(std::make_shared<UnaryMinusProduct<T>>(*this));
}

template<typename T>
Expression<T> Expression<T>::operator-(const Expression<T>& that) const {
    return Expression<T>(std::make_shared<PlusProduct<T>>(*this, that));
}

template<typename T>
Expression<T>& Expression<T>::operator-=(const Expression<T>& that) {
    *this = *this - that;
    return *this;
}

template<typename T>
Expression<T> Expression<T>::operator*(const Expression<T>& that) const {
    return Expression<T>(std::make_shared<DotProduct<T>>(*this, that));
}

template<typename T>
Expression<T>& Expression<T>::operator*=(const Expression<T>& that) {
    *this = *this * that;
    return *this;
}

template<typename T>
Expression<T> Expression<T>::operator/(const Expression<T>& that) const {
    return Expression<T>(std::make_shared<SlashProduct<T>>(*this, that));
}

template<typename T>
Expression<T> Expression<T>::exp(const Expression<T> &that) const {
    return Expression<T>(std::make_shared<ExpFunc<T>>(that));
}

template<typename T>
Expression<T>& Expression<T>::operator/=(const Expression<T>& that) {
    *this = *this / that;
    return *this;
}

template<typename T>
Expression<T> Expression<T>::ln() const {
    return Expression(std::make_shared<LnFunc<T>>(*this));
}

template<typename T>
Expression<T> Expression<T>::cos() const {
    return Expression(std::make_shared<CosFunc<T>>(*this));
}

template<typename T>
Expression<T> Expression<T>::sin() const {
    return Expression(std::make_shared<SinFunc<T>>(*this));
}

template<typename T>
Expression<T> Expression<T>::pow(const Expression<T> &that) const {
    return Expression(std::make_shared<PowProduct<T>>(*this, that));
}

template<typename T>
std::string Expression<T>::to_string() const {
    return impl_->to_string();
}

template<typename T>
Expression<T> Expression<T>::derivative() {
    return impl_->derivative();
}
