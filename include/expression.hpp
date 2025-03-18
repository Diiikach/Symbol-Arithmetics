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
    virtual Expression<T> derivative(const std::string& var) const = 0;
    virtual bool is_value() const {
        return false;
    }
};

template <typename T>
class Expression {
public:
    static Expression<T> from_string(std::string s);
    Expression(std::string var);
    Expression(T val);
    Expression(std::shared_ptr<ExpressionImplementation<T>> impl);


    Expression operator+ (const Expression& that) const;
    Expression& operator+=(const Expression& that);
    Expression operator- (const Expression& that) const;
    Expression& operator-=(const Expression& that);
    Expression  operator* (const Expression& that) const;
    Expression& operator*=(const Expression& that);
    Expression operator/ (const Expression& that) const;
    Expression& operator/=(const Expression& that);
    Expression operator-() const;

    Expression pow(const Expression<T>& power) const;
    Expression sin() const;
    Expression cos() const;
    Expression exp(const Expression<T>& that) const;
    Expression ln() const;

    T eval(std::map<std::string, T> context) const;
    std::string to_string() const;
    Expression derivative(const std::string& var) const;
    bool is_val() const;

    private:
        std::shared_ptr<ExpressionImplementation<T>> impl_;
        static Expression parse_expression_(int& i, const std::string& s);
        static Expression<T> produce_token_(std::string s);
};

template <typename T>
class Value: public ExpressionImplementation<T> {
public:
     Value(T value);
     ~Value() override = default;

    T eval(std::map<std::string, T> context) const override;
    std::string to_string() const override;
    Expression<T> derivative(const std::string& var) const override;
    bool is_value() const override  {
        return true;
    }

private:
    T value_;
};

template <typename T>
class Variable: public ExpressionImplementation<T> {
public:
    Variable(std::string name);
    ~Variable() override = default;

    T eval(std::map<std::string, T> context) const override;
    std::string to_string() const override;
    Expression<T> derivative(const std::string& var) const override;
private:
    std::string name_;
};

template <typename T>
class DotProduct: public ExpressionImplementation<T> {
public:
    DotProduct(Expression<T> left, Expression<T> right);
    ~DotProduct() override = default;

    T eval(std::map<std::string, T> context) const override;
    std::string to_string() const override;
    Expression<T> derivative(const std::string& var) const override;
private:
    Expression<T> left_;
    Expression<T> right_;
};

template <typename T>
class SlashProduct: public ExpressionImplementation<T> {
public:
    SlashProduct(Expression<T> left, Expression<T> right);
    ~SlashProduct() override = default;

    T eval(std::map<std::string, T> context) const override;
    std::string to_string() const override;
    Expression<T> derivative(const std::string& var) const override;
private:
    Expression<T> left_;
    Expression<T> right_;
};

template <typename T>
class PlusProduct: public ExpressionImplementation<T> {
public:
    PlusProduct(const Expression<T> left, const Expression<T> right);
    ~PlusProduct() override = default;

    T eval(std::map<std::string, T> context) const override;
    std::string to_string() const override;
    Expression<T> derivative(const std::string& var) const override;
private:
    Expression<T> left_;
    Expression<T> right_;
};

template <typename T>
class PowProduct: public ExpressionImplementation<T> {
public:
    PowProduct(const Expression<T> base, const Expression<T> power);
    ~PowProduct() override = default;

    T eval(std::map<std::string, T> context) const override;
    std::string to_string() const override;
    Expression<T> derivative(const std::string& var) const override;
private:
    Expression<T> base_;
    Expression<T> power_;
};

template <typename T>
class SinFunc: public ExpressionImplementation<T> {
public:
    SinFunc(Expression<T> arg);
    ~SinFunc() override = default;

    T eval(std::map<std::string, T> context) const override;
    std::string to_string() const override;
    Expression<T> derivative(const std::string& var) const override;
private:
    Expression<T> arg_;
};

template <typename T>
class CosFunc: public ExpressionImplementation<T> {
public:
    CosFunc(const Expression<T>& arg);
    ~CosFunc() override = default;

    T eval(std::map<std::string, T> context) const override;
    std::string to_string() const override;
    Expression<T> derivative(const std::string& var) const override;
private:
    Expression<T> arg_;
};

template <typename T>
class LnFunc: public ExpressionImplementation<T> {
public:
    LnFunc(Expression<T> arg);
    ~LnFunc() override = default;

    T eval(std::map<std::string, T> context) const override;
    std::string to_string() const override;
    Expression<T> derivative(const std::string& var) const override;
private:
    Expression<T> arg_;
};

template <typename T>
class ExpFunc: public ExpressionImplementation<T> {
public:
    ExpFunc(Expression<T> arg);
    ~ExpFunc() override = default;

    T eval(std::map<std::string, T> context) const override;
    std::string to_string() const override;
    Expression<T> derivative(const std::string& var) const override;
private:
    Expression<T> arg_;
};

template <typename T>
class UnaryMinusProduct: public ExpressionImplementation<T> {
public:
    UnaryMinusProduct(const Expression<T> &arg);
    ~UnaryMinusProduct() override = default;

    T eval(std::map<std::string, T> context) const override;
    std::string to_string() const override;
    Expression<T> derivative(const std::string& var) const override;
private:
    Expression<T> arg_;
};

class Token {
public:
    std::string body;

    enum class TOKEN_TYPE {
        EMPTY,
        UNIT,
    } type;
};

#endif

