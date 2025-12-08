// Copyright 2025 Mary Maslennikova

#include <gtest/gtest.h>

#include "../lib_expression/expression.h"
#include "../lib_parser/parser.h"
#include "../lib_functions/functions.h"

TEST(TestParserLib, check_correct_parse) {
    std::string expr = "(2 + 4) * x";
    List<Lexem> list_lexem = Parser::parse(expr);
    Lexem l1("(", OpenedBracket);
    Lexem l2("2", Constant, 2);
    Lexem l3("+", Operator, DBL_MAX, addition_priority);
    Lexem l4("4", Constant, 4);
    Lexem l5(")", ClosedBracket);
    Lexem l6("*", Operator, DBL_MAX, multiplication_priority);
    Lexem l7("x", Variable);
    List<Lexem> expect;
    expect.push_back(l1);
    expect.push_back(l2);
    expect.push_back(l3);
    expect.push_back(l4);
    expect.push_back(l5);
    expect.push_back(l6);
    expect.push_back(l7);
    EXPECT_EQ(list_lexem, expect);
}
TEST(TestParserLib, check_for_the_exception_of_missing_an_operation) {
    std::string expr1 = "9h";
    std::string expr2 = "s7";
    std::string expr3 = "xy";
    std::string expr4 = "x_1x_2";
    EXPECT_ANY_THROW(Parser::parse(expr1));
    EXPECT_ANY_THROW(Parser::parse(expr2));
    EXPECT_ANY_THROW(Parser::parse(expr3));
    EXPECT_ANY_THROW(Parser::parse(expr4));
}
TEST(TestParserLib, check_the_function) {
    std::string expr1 = "sin(";
    std::string expr2 = "sin(-5)";
    std::string expr3 = "sin(+x)";
    std::string expr4 = "sin()";
    EXPECT_ANY_THROW(Parser::parse(expr1));
    EXPECT_NO_THROW(Parser::parse(expr2));
    EXPECT_ANY_THROW(Parser::parse(expr3));
    EXPECT_ANY_THROW(Parser::parse(expr4));
}
TEST(TestParserLib, check_the_opening_brackets) {
    std::string expr1 = "5(x+3)";
    std::string expr2 = "(-5 + x)";
    std::string expr3 = "-(x * y)";
    std::string expr4 = "x(3 * u)";
    std::string expr5 = "(5 + x)(6 + 5)";
    std::string expr6 = "()";
    std::string expr7 = "(+ x)";
    EXPECT_ANY_THROW(Parser::parse(expr1));
    EXPECT_NO_THROW(Parser::parse(expr2));
    EXPECT_NO_THROW(Parser::parse(expr3));
    EXPECT_ANY_THROW(Parser::parse(expr4));
    EXPECT_ANY_THROW(Parser::parse(expr5));
    EXPECT_ANY_THROW(Parser::parse(expr6));
    EXPECT_ANY_THROW(Parser::parse(expr7));
}
TEST(TestParserLib, check_the_module) {
    std::string expr1 = "|+x|";
    std::string expr2 = "|-x|";
    std::string expr3 = "|-(x * y)|";
    std::string expr4 = "|)";
    std::string expr5 = ")|";
    std::string expr6 = "|x+|";
    EXPECT_ANY_THROW(Parser::parse(expr1));
    EXPECT_NO_THROW(Parser::parse(expr2));
    EXPECT_NO_THROW(Parser::parse(expr3));
    EXPECT_ANY_THROW(Parser::parse(expr4));
    EXPECT_ANY_THROW(Parser::parse(expr5));
    EXPECT_ANY_THROW(Parser::parse(expr6));
}
TEST(TestParserLib, check_a_unary_minus) {
    std::string expr1 = "-|x|";
    std::string expr2 = "|-x|";
    std::string expr3 = "|-(x * y)|";
    std::string expr4 = "-5";
    std::string expr5 = "-x";
    std::string expr6 = "-)";
    std::string expr7 = "-|";
    EXPECT_NO_THROW(Parser::parse(expr1));
    EXPECT_NO_THROW(Parser::parse(expr2));
    EXPECT_NO_THROW(Parser::parse(expr3));
    EXPECT_NO_THROW(Parser::parse(expr4));
    EXPECT_NO_THROW(Parser::parse(expr5));
    EXPECT_ANY_THROW(Parser::parse(expr6));
    EXPECT_ANY_THROW(Parser::parse(expr7));
}
TEST(TestParserLib, check_a_diggit) {
    std::string expr1 = "66";
    EXPECT_NO_THROW(Parser::parse(expr1));
}
TEST(TestParserLib, check_the_closed_bracket) {
    std::string expr1 = "+)";
    std::string expr2 = "(|-x| + 7 * y)";
    std::string expr3 = "{(x + 8) * [7 - y]}";
    std::string expr4 = "(x + y) + 77)";
    std::string expr5 = "(x + 8]";
    std::string expr6 = "(x + y";
    EXPECT_ANY_THROW(Parser::parse(expr1));
    EXPECT_NO_THROW(Parser::parse(expr2));
    EXPECT_NO_THROW(Parser::parse(expr3));
    EXPECT_ANY_THROW(Parser::parse(expr4));
    EXPECT_ANY_THROW(Parser::parse(expr5));
    EXPECT_ANY_THROW(Parser::parse(expr6));
}
TEST(TestParserLib, check_the_operation) {
    std::string expr1 = "x+";
    std::string expr2 = "x - y";
    std::string expr3 = "*9";
    EXPECT_ANY_THROW(Parser::parse(expr1));
    EXPECT_NO_THROW(Parser::parse(expr2));
    EXPECT_ANY_THROW(Parser::parse(expr3));
}
TEST(TestFunctionLib, check_function) {
    EXPECT_NEAR(0.5, Functions::sin(30), 1e-8);
    EXPECT_NEAR(0.8191520442, Functions::cos(325), 1e-8);
    EXPECT_NEAR(-1.428148, Functions::tg(125), 1e-8);
    EXPECT_EQ(6.25, Functions::abs(-6.25));
}
TEST(TestExpressionLib, check_create_constructor) {
    std::string expr = "(x+3)^2 + y*sin(y)";
    ASSERT_NO_THROW(Expression(expr));
}
TEST(TestExpressionLib, check_lexems) {
    std::string expr = "(x+3)*y^2-sin(z/6)+|-(tg(|x-4|)+8)|";
    Expression expression(expr);
    EXPECT_EQ(expr, expression.to_string());
}
TEST(TestExpressionLib, check_polishRecord) {
    std::string expr = "(x+3)*y^2 - sin(z/6)";
    Expression expression(expr);
    Lexem l1("x", Variable);
    Lexem l2("3", Constant, 3);
    Lexem l3("+", Operator, DBL_MAX, addition_priority);
    Lexem l4("y", Variable);
    Lexem l5("2", Constant, 2);
    Lexem l6("^", Operator, DBL_MAX, pow_priority);
    Lexem l7("*", Operator, DBL_MAX, multiplication_priority);
    Lexem l8("z", Variable);
    Lexem l9("6", Constant, 6);
    Lexem l10("/", Operator, DBL_MAX, multiplication_priority);
    Lexem l11("sin", Function, DBL_MAX, function_priority, Functions::sin);
    Lexem l12("-", Operator, DBL_MAX, addition_priority);
    List<Lexem> exp;
    exp.push_back(l1);
    exp.push_back(l2);
    exp.push_back(l3);
    exp.push_back(l4);
    exp.push_back(l5);
    exp.push_back(l6);
    exp.push_back(l7);
    exp.push_back(l8);
    exp.push_back(l9);
    exp.push_back(l10);
    exp.push_back(l11);
    exp.push_back(l12);
    EXPECT_EQ(exp, expression.get_polishRecord());
}
TEST(TestExpressionLib, check_set_and_get_variables) {
    std::string expr = "(x+3)*y^2";
    Expression expression(expr);
    expression.set_variables("x", 65);
    expression.set_variables("y", 5.75);
    List<Lexem> variables;
    Lexem l1("x", Variable, 65);
    Lexem l2("y", Variable, 5.75);
    variables.push_back(l1);
    variables.push_back(l2);
    EXPECT_EQ(variables, expression.get_variables());
}
TEST(TestExpressionLib, check_calculate) {
    std::string expr1 = "(x+3)*y^2";
    Expression expression1(expr1);
    expression1.set_variables("x", 65);
    expression1.set_variables("y", 5.75);
    
    std::string expr2 = "(x+3)*y^2-sin(z/6)+|-(tg(|x-4|)+8)|";
    Expression expression2(expr2);
    expression2.set_variables("x", 127);
    expression2.set_variables("y", 4.35);
    expression2.set_variables("z", 300);
    EXPECT_NEAR(2248.25, expression1.calculate(), 1e-8);
    EXPECT_NEAR(2465.61909059, expression2.calculate(), 1e-8);
}