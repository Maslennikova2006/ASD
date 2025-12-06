// Copyright 2025 Mary Maslennikova

#include <gtest/gtest.h>
#include "../lib_expression/expression.h"
#include "../lib_parser/parser.h"
//
//TEST(TestExpression, check_parse) {
//    std::string expr = "(2 + 4) * x";
//    List<Lexem> list_lexem = Parser::parse(expr);
//    Lexem l1("(", OpenBracket, 0, 5);
//    Lexem l2("2", Constant, 2);
//    Lexem l3("+", Operator, 0, 1);
//    Lexem l4("4", Constant, 4);
//    Lexem l5(")", ClosedBracket, 0, 5);
//    Lexem l6("*", Operator, 0, 2);
//    Lexem l7("x", Variable);
//    List<Lexem> expect;
//    expect.push_back(l1);
//    expect.push_back(l2);
//    expect.push_back(l3);
//    expect.push_back(l4);
//    expect.push_back(l5);
//    expect.push_back(l6);
//    expect.push_back(l7);
//    EXPECT_EQ(list_lexem, expect);
//}