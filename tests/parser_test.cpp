#include <gtest/gtest.h>

#include "../include/expression.hpp"
#include "../include/template.tpp"

class ParserTest: public testing::Test {

protected:
    std::string s1;
    std::string s2;
    std::string s3;
    std::string s4;
    ParserTest(): s1("a + b"), s2("(23 * 23)"), s3("x^2"), s4("23*(15-1)")
    {}
};

TEST_F(ParserTest, WithoutBrackets) {
    EXPECT_EQ(Expression<int>::from_string(s1).eval({{"a", 1}, {"b", 2}}), 3);
    EXPECT_EQ(Expression<int>::from_string(s1).to_string(), "(a + b)");
}

TEST_F(ParserTest, WithBrackets) {
    EXPECT_EQ(Expression<int>::from_string(s2).eval({}), 23 * 23);
    EXPECT_EQ(Expression<int>::from_string(s4).eval({}), 23*14);
}