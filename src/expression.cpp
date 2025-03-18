#include "cmath"
#include <sstream>
#include "../include/expression.hpp"

#define _USE_MATH_DEFINES

template<typename T>
Expression<T>::Expression(std::shared_ptr<ExpressionImplementation<T>> impl) :
    impl_ (impl)
{}

template<typename T>
Expression<T>::Expression(std::string var) :
    impl_ (std::make_shared<Variable<T>>(var))
{}

template<typename T>
Expression<T>::Expression(T val) :
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
    return Expression<T>(std::make_shared<PlusProduct<T>>(*this, -that));
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
Expression<T> Expression<T>::pow(const Expression<T> &that)  const{
    return Expression(std::make_shared<PowProduct<T>>(*this, that));
}

template<typename T>
std::string Expression<T>::to_string() const {
    return impl_->to_string();
}

template<typename T>
Expression<T> Expression<T>::derivative(const std::string& var) const {
    return impl_->derivative(var);
}

template<typename T>
Expression<T> Expression<T>::from_string(const std::string s) {
    int pointer = 0;
    return parse_expression_(pointer, s);
}

// Disclaimer!!!
/// Pasrsing is always a shit, so...

template<typename T>
Expression<T> Expression<T>::produce_token_(std::string s) {
    if (s.starts_with("sin(") && s.ends_with(")")) {
        int next_token_length = s.size() - 5;
        if (next_token_length <= 0) {
            throw std::runtime_error("Invalid syntax: sin func called at empty argument;");
        }
        return Expression<T>(std::make_shared<SinFunc<T>>(produce_token_(s.substr(4, next_token_length))));
    }
    if (s.starts_with("cos(") && s.ends_with(")")) {
        int next_token_length = s.size() - 5;
        if (next_token_length <= 0) {
            throw std::runtime_error("Invalid syntax: cos func called at empty argument;");
        }
        return Expression<T>(std::make_shared<CosFunc<T>>(produce_token_(s.substr(4, next_token_length))));
    }
    if (s.starts_with("exp(") && s.ends_with(")")) {
        int next_token_length = s.size() - 5;
        if (next_token_length <= 0) {
            throw std::runtime_error("Invalid syntax: exp func called at empty argument;");
        }
        return Expression<T>(std::make_shared<ExpFunc<T>>(produce_token_(s.substr(4, next_token_length))));
    }
    if (s.starts_with("ln(") && s.ends_with(")")) {
        int next_token_length = s.size() - 4;
        if (next_token_length <= 0) {
            throw std::runtime_error("Invalid syntax: ln func called at empty argument;");
        }
        return Expression<T>(std::make_shared<LnFunc<T>>(produce_token_(s.substr(3, next_token_length))));
    }
    bool all_digits = true;
    for (char el : s) {
        all_digits &= isdigit(el) || el == '.';
    }
    if (all_digits) {
        std::stringstream ss;
        ss << s;
        T val;
        ss >> val;
        return Expression(val);
    }
    return Expression(s);
}

// recursive function that run up to string and tries to get Expression
template<typename T>
Expression<T> Expression<T>::parse_expression_(int& i, const std::string& s) {
    Expression result(0);
    char last_operation = 0;
    bool first_token {false};
    std::string current_token;
    int scope_count = 0;
    for (; i < s.size(); i++) {
        if (s[i] == '(') {
            scope_count++;
        } else if (s[i] == ')') {
            scope_count--;
        }
        if (scope_count < 0)
            break;
        // skip all spaces
        if (s[i] == ' ') continue;
        if (s[i] == '+' || s[i] == '-' || s[i] == '^' || s[i] == '*' || s[i] == '/' || (s[i] == '(' && current_token.empty())) {
            Expression current_expression(0);
            if (s[i] != '(') {
                if (static_cast<int>(last_operation) != 0 && current_token.empty()) {
                    throw std::runtime_error("Invalid syntax: two operation symbols near each other; at position " + std::to_string(i + 1));
                }
                if (!first_token && s[i] != '-'){
                    throw std::runtime_error("Invalid syntax: pair operation is used on single argument; at position " + std::to_string(i + 1));
                }
                first_token = true;
                current_expression = Expression::produce_token_(current_token);
                current_token = "";
            } else {
                i++;
                current_expression = Expression::parse_expression_(i, s);
            }
            if (static_cast<int>(last_operation) == 0) {
                result = current_expression;
            } else {
                if        (last_operation == '+') {
                    result = result + current_expression;
                } else if (last_operation == '-') {
                    result = result - current_expression;
                } else if (last_operation == '*') {
                    result = result * current_expression;
                } else if (last_operation == '/') {
                    result = result / current_expression;
                } else if (last_operation == '^') {
                    result = result.pow(current_expression);
                }
            }
            if (s[i] != '(')
                last_operation = s[i];
        } else {
            first_token = true;
            current_token += s[i];
        }
    }
    if (!current_token.empty()) {
        Expression current_expression = produce_token_(current_token);
        if        (last_operation == '+') {
            result = result + current_expression;
        } else if (last_operation == '-') {
            result = result - current_expression;
        } else if (last_operation == '*') {
            result = result * current_expression;
        } else if (last_operation == '/') {
            result = result / current_expression;
        } else if (last_operation == '^') {
            result = result.pow(current_expression);
        } else {
            result = current_expression;
        }
    }
    return result;
}