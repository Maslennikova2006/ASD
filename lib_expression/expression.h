// Copyright 2025 Mary Maslennikova

#ifndef LIB_EXPRESSION_EXPRESSION_H_
#define LIB_EXPRESSION_EXPRESSION_H_

#include <stdexcept>
#include <string>
#include "../lib_list/list.h"
#include "../lib_lexem/lexem.h"

class Expression {
    List<Lexem> _lexems;
    List<Lexem> _polishRecord;

public:
    Expression();
    Expression(std::string& expr);
    Expression(List<Lexem>& expr);
    Expression(const Expression& other);

    void set_variables(std::string name, double value);
    List<Lexem> get_variables();

    List<Lexem> get_polishRecord();

    double calculate();

    std::string to_string();
private:
    List<Lexem> compilation_polishRecord(const List<Lexem>& lexems);
};
#endif  // LIB_EXPRESSION_EXPRESSION_H_

