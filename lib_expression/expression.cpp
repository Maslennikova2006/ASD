// Copyright 2025 Mary Maslennikova

#include "../lib_expression/expression.h"
#include "../lib_parser/parser.h"
#include "../lib_stack/stack.h"
#include <iostream>

Expression::Expression(std::string& expr) {
    try {
        _lexems = Parser::parse(expr);
    }
    catch (std::exception e) {
        std::cerr << e.what() << std::endl;
    }
    _polishRecord = Parser::compilationPolishRecord(_lexems);
}
Expression::Expression(List<Lexem>& expr) {
    _lexems = expr;  // нужны ли проверки на корректность?
    _polishRecord = Parser::compilationPolishRecord(expr);
}
Expression::Expression(const Expression& other) {
    _lexems = other._lexems;
    _polishRecord = other._polishRecord;
}

void Expression::set_variables(std::string name, double value) {
    for (auto& lexem : _lexems) {
        if (lexem.name == name) {
            lexem.value = value;
            return;
        }
    }
    throw std::invalid_argument("No matching variables found!\n");
}

