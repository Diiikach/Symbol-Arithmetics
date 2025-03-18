#include <gtest/gtest.h>

#include "../include/expression.hpp"
#include "../include/template.tpp"

class ExpressionTest: public testing::Test {

protected:
    Expression<int> exp1;
    Expression<int> exp2;
    Expression<int> exp3;
    ExpressionTest(): exp1(Expression(23)), exp2(Expression(123)), exp3(Expression<int>("x"))
    {}
};


TEST_F(ExpressionTest, OperationsProductToString) {
    EXPECT_EQ((exp1 * exp2).to_string(), "(23 * 123)");
    EXPECT_EQ((exp1 / exp2).to_string(), "(23 / 123)");
    EXPECT_EQ((exp1 + exp2).to_string(), "(23 + 123)");
    EXPECT_EQ((exp1 - exp2).to_string(), "(23 + (-123))");
    EXPECT_EQ(exp1.pow(exp2).to_string(), "(23)^(123)");
    EXPECT_EQ(Expression(1).ln().eval({}), 0);
}

TEST_F(ExpressionTest, DerivativeTest) {
    EXPECT_EQ(exp1.derivative("x").to_string(), "0");
    EXPECT_EQ(exp3.derivative("x").to_string(), "1");
    EXPECT_EQ((exp1 * exp3).derivative("x").eval({{"x", 1}}), 23);
}
