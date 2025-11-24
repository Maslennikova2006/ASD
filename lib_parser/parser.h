// Copyright 2025 Mary Maslennikova

#ifndef LIB_PARSER_PARSER_H_
#define LIB_PARSER_PARSER_H_

#include "../lib_list/list.h"
#include "../lib_lexem/lexem.h"

namespace Parser {
    List<Lexem> parse(const std::string& expression);
    std::string extractNumber(const std::string& expression, int index);
    std::string extractVariableOrFunction(const std::string& expression, int index);
    double(*getFunction(const std::string name))(double);

    List<Lexem> compilationPolishRecord(const List<Lexem>& lexems);
}

#endif  // LIB_PARSER_PARSER_H_
