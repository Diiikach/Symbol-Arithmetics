#ifndef HEADER_GUARD_EXPRESSION_H
#define HEADER_GUARD_EXPRESSION_H

#include <string>
#include <map>
#include <memory>

// Abstract class
template <typename val_type>
class ExpressionImplementation {
public:
    ExpressionImplementation() = default;

    virtual ~ExpressionImplementation() = default;
    virtual val_type eval(std::map<std::string, val_type> context) const = 0;
    virtual std::string to_string() const = 0;
};

template <typename val_type>
class Expression {
public:
    explicit Expression(std::string var);
    explicit Expression(val_type val);


    Expression operator+ (const Expression& that);
    Expression& operator+=(const Expression& that);
    Expression  operator* (const Expression& that);
    Expression& operator*=(const Expression& that);
    Expression operator/ (const Expression& that);
    Expression& operator/=(const Expression& that);

    Expression pow(const Expression<val_type>& power);
    Expression sin();
    Expression cos();
    Expression exp(const Expression<val_type>& that);
    Expression ln();

    val_type eval(std::map<std::string, val_type> context) const;
    std::string to_string() const;
private:
    Expression(std::shared_ptr<ExpressionImplementation<val_type>> impl);

    std::shared_ptr<ExpressionImplementation<val_type>> impl_;

};

template <typename val_type>
class Value: public ExpressionImplementation<val_type> {
public:
     Value(val_type value);
     ~Value() override = default;

    val_type eval(std::map<std::string, val_type> context) const override;
    std::string to_string() const override;
private:
    val_type value_;
};

template <typename val_type>
class Variable: public ExpressionImplementation<val_type> {
public:
    Variable(std::string name);
    ~Variable() override = default;

    val_type eval(std::map<std::string, val_type> context) const override;
    std::string to_string() const override;
private:
    std::string name_;
};

template <typename val_type>
class DotProduct: public ExpressionImplementation<val_type> {
public:
    DotProduct(Expression<val_type> left, Expression<val_type> right);
    ~DotProduct() override = default;

    val_type eval(std::map<std::string, val_type> context) const override;
    std::string to_string() const override;
private:
    Expression<val_type> left_;
    Expression<val_type> right_;
};

template <typename val_type>
class SlashProduct: public ExpressionImplementation<val_type> {
public:
    SlashProduct(Expression<val_type> left, Expression<val_type> right);
    ~SlashProduct() override = default;

    val_type eval(std::map<std::string, val_type> context) const override;
    std::string to_string() const override;
private:
    Expression<val_type> left_;
    Expression<val_type> right_;
};

template <typename val_type>
class PlusProduct: public ExpressionImplementation<val_type> {
public:
    PlusProduct(Expression<val_type> left, Expression<val_type> right);
    ~PlusProduct() override = default;

    val_type eval(std::map<std::string, val_type> context) const override;
    std::string to_string() const override;
private:
    Expression<val_type> left_;
    Expression<val_type> right_;
};

template <typename val_type>
class MinusProduct: public ExpressionImplementation<val_type> {
public:
    MinusProduct(Expression<val_type> left, Expression<val_type> right);
    ~MinusProduct() override = default;

    val_type eval(std::map<std::string, val_type> context) const override;
    std::string to_string() const override;
private:
    Expression<val_type> left_;
    Expression<val_type> right_;
};

template <typename val_type>
class PowProduct: public ExpressionImplementation<val_type> {
public:
    PowProduct(Expression<val_type> base, Expression<val_type> power);
    ~PowProduct() override = default;

    val_type eval(std::map<std::string, val_type> context) const override;
    std::string to_string() const override;
private:
    Expression<val_type> base_;
    Expression<val_type> power_;
};

template <typename val_type>
class SinFunc: public ExpressionImplementation<val_type> {
public:
    SinFunc(Expression<val_type> arg);
    ~SinFunc() override = default;

    val_type eval(std::map<std::string, val_type> context) const override;
    std::string to_string() const override;
private:
    Expression<val_type> arg_;
};

template <typename val_type>
class CosFunc: public ExpressionImplementation<val_type> {
public:
    CosFunc(Expression<val_type>& arg);
    ~CosFunc() override = default;

    val_type eval(std::map<std::string, val_type> context) const override;
    std::string to_string() const override;
private:
    Expression<val_type> arg_;
};

template <typename val_type>
class LnFunc: public ExpressionImplementation<val_type> {
public:
    LnFunc(Expression<val_type> arg);
    ~LnFunc() override = default;

    val_type eval(std::map<std::string, val_type> context) const override;
    std::string to_string() const override;
private:
    Expression<val_type> arg_;
};

template <typename val_type>
class ExpFunc: public ExpressionImplementation<val_type> {
public:
    ExpFunc(Expression<val_type> arg);
    ~ExpFunc() override = default;

    val_type eval(std::map<std::string, val_type> context) const override;
    std::string to_string() const override;
private:
    Expression<val_type> arg_;
};

#endif

