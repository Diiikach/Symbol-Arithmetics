#include "../include/expression.hpp"
#define _USE_MATH_DEFINES
#include "cmath"
#include "stdexcept"

template<typename val_type>
Expression<val_type>::Expression(std::shared_ptr<ExpressionImplementation<val_type>> impl) :
    impl_ (impl)
{}

template<typename val_type>
Expression<val_type>::Expression(std::string var) :
    impl_ (std::make_shared<Variable<val_type>>(var))
{}
template<typename val_type>
Expression<val_type>::Expression(val_type val) :
    impl_ (std::make_shared<Value<val_type>>(val))
{}

template<typename val_type>
val_type Expression<val_type>::eval(std::map<std::string, val_type> context) const {
    return impl_->eval(context);
}

template<typename val_type>
Expression<val_type> Expression<val_type>::operator+(const Expression<val_type>& that) {
    return Expression<val_type>(std::make_shared<PlusProduct<val_type>>(*this, that));
}

template<typename val_type>
Expression<val_type>& Expression<val_type>::operator+=(const Expression<val_type>& that) {
    *this = *this + that;
    return *this;
}

template<typename val_type>
Expression<val_type> Expression<val_type>::operator*(const Expression<val_type>& that) {
    return Expression<val_type>(std::make_shared<DotProduct<val_type>>(*this, that));
}

template<typename val_type>
Expression<val_type>& Expression<val_type>::operator*=(const Expression<val_type>& that) {
    *this = *this * that;
    return *this;
}

template<typename val_type>
Expression<val_type> Expression<val_type>::operator/(const Expression<val_type>& that) {
    return Expression<val_type>(std::make_shared<SlashProduct<val_type>>(*this, that));
}

template<typename val_type>
Expression<val_type> Expression<val_type>::exp(const Expression<val_type> &that) {
    return Expression<val_type>(std::make_shared<ExpFunc<val_type>>(that));
}

template<typename val_type>
Expression<val_type>& Expression<val_type>::operator/=(const Expression<val_type>& that) {
    *this = *this / that;
    return *this;
}

template<typename val_type>
Expression<val_type> Expression<val_type>::ln() {
    return Expression(std::make_shared<LnFunc<val_type>>(*this));
}

template<typename val_type>
Expression<val_type> Expression<val_type>::cos() {
    return Expression(std::make_shared<CosFunc<val_type>>(*this));
}

template<typename val_type>
Expression<val_type> Expression<val_type>::sin() {
    return Expression(std::make_shared<SinFunc<val_type>>(*this));
}

template<typename val_type>
Expression<val_type> Expression<val_type>::pow(const Expression<val_type> &that) {
    return Expression(std::make_shared<PowProduct<val_type>>(*this, that));
}

template<typename val_type>
std::string Expression<val_type>::to_string() const {
    return impl_->to_string();
}

template<typename val_type>
Value<val_type>::Value(val_type value) :
    value_ (value)
{}

template<typename val_type>
val_type Value<val_type>::eval(std::map<std::string, val_type> context) const {
    (void) context;
    return value_;
}

template<typename val_type>
std::string Value<val_type>::to_string() const {
    return std::to_string(value_);
}

template<typename val_type>
Variable<val_type>::Variable(std::string name) :
    name_ (name)
{}

template<typename val_type>
val_type Variable<val_type>::eval(std::map<std::string, val_type> context) const {
    auto iter = context.find(name_);

    if (iter == context.end())
    {
        throw std::runtime_error("Variable \"" + name_ + "\" not present in evaluation context");
    }

    return iter->second;
}

template<typename val_type>
std::string Variable<val_type>::to_string() const {
    return name_;
}

template<typename val_type>
PlusProduct<val_type>::PlusProduct(Expression<val_type> left, Expression<val_type> right) :
    left_  (left),
    right_ (right)
{}

template<typename val_type>
val_type PlusProduct<val_type>::eval(std::map<std::string, val_type> context) const {
    val_type value_left  = left_.eval(context);
    val_type value_right = right_.eval(context);

    return value_left + value_right;
}

template<typename val_type>
std::string PlusProduct<val_type>::to_string() const {
    return std::string("(")   + left_.to_string()  +
           std::string(" + ") + right_.to_string() +
           std::string(")");
}

template<typename val_type>
DotProduct<val_type>::DotProduct(Expression<val_type> left, Expression<val_type> right) :
    left_  (left),
    right_ (right)
{}

template<typename val_type>
val_type DotProduct<val_type>::eval(std::map<std::string, val_type> context) const {
    val_type value_left  = left_.eval(context);
    val_type value_right = right_.eval(context);

    return value_left * value_right;
}

template<typename val_type>
std::string DotProduct<val_type>::to_string() const {
    return std::string("(")   + left_.to_string()  +
           std::string(" * ") + right_.to_string() +
           std::string(")");
}

template<typename val_type>
SlashProduct<val_type>::SlashProduct(Expression<val_type> left, Expression<val_type> right) :
    left_  (left),
    right_ (right)
{}

template<typename val_type>
val_type SlashProduct<val_type>::eval(std::map<std::string, val_type> context) const {
    val_type value_left  = left_.eval(context);
    val_type value_right = right_.eval(context);

    return value_left / value_right;
}

template<typename val_type>
std::string SlashProduct<val_type>::to_string() const {
    return std::string("(")   + left_.to_string()  +
           std::string(" / ") + right_.to_string() +
           std::string(")");
}

template<typename val_type>
LnFunc<val_type>::LnFunc(Expression<val_type> arg) :
    arg_ (arg)
{}

template<typename val_type>
val_type LnFunc<val_type>::eval(std::map<std::string, val_type> context) const {
    val_type arg_num = arg_.eval(context);
    return std::log(arg_num);
}

template<typename val_type>
std::string LnFunc<val_type>::to_string() const {
    return "ln (" + arg_.to_string() + ")";
}

template<typename val_type>
ExpFunc<val_type>::ExpFunc(Expression<val_type> arg) :
    arg_ (arg)
{}

template<typename val_type>
val_type ExpFunc<val_type>::eval(std::map<std::string, val_type> context) const {
    val_type arg_num = arg_.eval(context);
    return std::exp(arg_num);
}

template<typename val_type>
std::string ExpFunc<val_type>::to_string() const {
    return "exp (" + arg_.to_string() + ")";
}

template<typename val_type>
SinFunc<val_type>::SinFunc(Expression<val_type> arg) :
    arg_ (arg)
{}

template<typename val_type>
val_type SinFunc<val_type>::eval(std::map<std::string, val_type> context) const {
    val_type arg_num = arg_.eval(context);
    return std::sin(arg_num);
}

template<typename val_type>
std::string SinFunc<val_type>::to_string() const {
    return "sin (" + arg_.to_string() + ")";
}

template<typename val_type>
CosFunc<val_type>::CosFunc(Expression<val_type>& arg) :
    arg_ (arg)
{}

template<typename val_type>
val_type CosFunc<val_type>::eval(std::map<std::string, val_type> context) const {
    val_type arg_num = arg_.eval(context);
    return std::cos(arg_num);
}

template<typename val_type>
std::string CosFunc<val_type>::to_string() const {
    return "cos (" + arg_.to_string() + ")";
}

template<typename val_type>
PowProduct<val_type>::PowProduct(Expression<val_type> base, Expression<val_type> power) :
    base_ (base),
    power_ (power)
{}

template<typename val_type>
val_type PowProduct<val_type>::eval(std::map<std::string, val_type> context) const {
    val_type base = base_.eval(context);
    val_type power = power_.eval(context);
    val_type result{1};
    for (int i = 0; i < power; i++) {
        result *= base;
    }
    return result;
}

template<typename val_type>
std::string PowProduct<val_type>::to_string() const {
    return "(" + base_.to_string() + ")^(" + power_.to_string() + ")";
}
