// Copyright 2025 Mary Maslennikova

#ifndef LIB_PARSER_PARSER_H_
#define LIB_PARSER_PARSER_H_

#include "../lib_list/list.h"
#include "../lib_lexem/lexem.h"
#include "../lib_stack/stack.h"

#define addition_priority 1
#define multiplication_priority 2
#define unary_priority 3
#define pow_priority 4
#define function_priority 5

namespace Parser {
    List<Lexem> parse(const std::string& expression);
    
    int follow_the_line(size_t ind, const std::string& expr);

    bool is_opened_bracket(char symbol);
    bool is_closed_bracket(char symbol);
    bool is_operation(char symbol);
    bool is_letters(char symbol);
    bool is_digit(char symbol);

    std::string extract_number(const std::string& expression, int index);
    std::string extract_variable_or_function(const std::string& expression, int index);
    double(*get_function(const std::string name))(double);

    char set_expectedBracket(char bracket);
    int set_priority(char operation);

    void parse_variable_or_function(size_t& ind, const std::string& expr, List<Lexem>& lexems, Stack<char>& brackets, bool& expectOperand);

    std::string print_error_location(size_t ind);
}

#endif  // LIB_PARSER_PARSER_H_
