#ifndef HEADER_GUARD_EXPRESSION_H
#define HEADER_GUARD_EXPRESSION_H

#include <string>
#include <map>
#include <memory>

template <typename T>
class Expression;



// Abstract class
template <typename T>
class ExpressionImplementation {
public:
    ExpressionImplementation() = default;
    virtual ~ExpressionImplementation() = default;
    virtual T eval(std::map<std::string, T> context) const = 0;
    virtual std::string to_string() const = 0;
    virtual Expression<T> derivative() const;
};

template <typename T>
class Expression {
public:
    Expression(std::string var);
    Expression(T val);

    Expression operator+ (const Expression& that) const;
    Expression& operator+=(const Expression& that);
    Expression operator- (const Expression& that) const;
    Expression& operator-=(const Expression& that);
    Expression  operator* (const Expression& that) const;
    Expression& operator*=(const Expression& that);
    Expression operator/ (const Expression& that) const;
    Expression& operator/=(const Expression& that);
    Expression operator-() const;
    Expression derivative();

    Expression pow(const Expression<T>& power) const;
    Expression sin() const;
    Expression cos() const;
    Expression exp(const Expression<T>& that) const;
    Expression ln() const;

    T eval(std::map<std::string, T> context) const;
    std::string to_string() const;
    Expression derivative() const;

    Expression(std::shared_ptr<ExpressionImplementation<T>> impl);

    private:
        std::shared_ptr<ExpressionImplementation<T>> impl_;

};

template <typename T>
class Value: public ExpressionImplementation<T> {
public:
     Value(T value);
     ~Value() override = default;

    T eval(std::map<std::string, T> context) const override;
    std::string to_string() const override;
    Expression<T> derivative() const override;

private:
    T value_;
};

template <typename T>
class Variable: public ExpressionImplementation<T> {
public:
    Variable(std::string name) const;
    ~Variable() override = default;

    T eval(std::map<std::string, T> context) const override;
    std::string to_string() const override;
    Expression<T> derivative() const override;
private:
    std::string name_;
};

template <typename T>
class DotProduct: public ExpressionImplementation<T> {
public:
    DotProduct(Expression<T> left, Expression<T> right) const;
    ~DotProduct() override = default;

    T eval(std::map<std::string, T> context) const override;
    std::string to_string() const override;
    Expression<T> derivative() const override;
private:
    Expression<T> left_;
    Expression<T> right_;
};

template <typename T>
class SlashProduct: public ExpressionImplementation<T> {
public:
    SlashProduct(Expression<T> left, Expression<T> right) const;
    ~SlashProduct() override = default;

    T eval(std::map<std::string, T> context) const override;
    std::string to_string() const override;
    Expression<T> derivative() const override;
private:
    Expression<T> left_;
    Expression<T> right_;
};

template <typename T>
class PlusProduct: public ExpressionImplementation<T> {
public:
    PlusProduct(const Expression<T> left, const Expression<T> right) const;
    ~PlusProduct() override = default;

    T eval(std::map<std::string, T> context) const override;
    std::string to_string() const override;
    Expression<T> derivative() const override;
private:
    Expression<T> left_;
    Expression<T> right_;
};

template <typename T>
class PowProduct: public ExpressionImplementation<T> {
public:
    PowProduct(const Expression<T> base, const Expression<T> power) const;
    ~PowProduct() override = default;

    T eval(std::map<std::string, T> context) const override;
    std::string to_string() const override;
    Expression<T> derivative() const override;
private:
    Expression<T> base_;
    Expression<T> power_;
};

template <typename T>
class SinFunc: public ExpressionImplementation<T> {
public:
    SinFunc(Expression<T> arg) const;
    ~SinFunc() override = default;

    T eval(std::map<std::string, T> context) const override;
    std::string to_string() const override;
    Expression<T> derivative() const override;
private:
    Expression<T> arg_;
};

template <typename T>
class CosFunc: public ExpressionImplementation<T> {
public:
    CosFunc(Expression<T>& arg) const;
    ~CosFunc() override = default;

    T eval(std::map<std::string, T> context) const override;
    std::string to_string() const override;
    Expression<T> derivative() const override;
private:
    Expression<T> arg_;
};

template <typename T>
class LnFunc: public ExpressionImplementation<T> {
public:
    LnFunc(Expression<T> arg) const;
    ~LnFunc() override = default;

    T eval(std::map<std::string, T> context) const override;
    std::string to_string() const override;
    Expression<T> derivative() const override;
private:
    Expression<T> arg_;
};

template <typename T>
class ExpFunc: public ExpressionImplementation<T> {
public:
    ExpFunc(Expression<T> arg) const;
    ~ExpFunc() override = default;

    T eval(std::map<std::string, T> context) const override;
    std::string to_string() const override;
    Expression<T> derivative() const override;
private:
    Expression<T> arg_;
};

template <typename T>
class UnaryMinusProduct: public ExpressionImplementation<T> {
public:
    UnaryMinusProduct(Expression<T> &arg) const;
    ~UnaryMinusProduct() override = default;

    T eval(std::map<std::string, T> context) const override;
    std::string to_string() const override;
    Expression<T> derivative() const override;
private:
    Expression<T> arg_;
};

#endif

