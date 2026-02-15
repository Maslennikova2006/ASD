// Copyright 2026 Mary Maslennikova

#ifndef LIB_PARSER_PARSER_H_
#define LIB_PARSER_PARSER_H_

#include "../lib_monom/monom.h"
#include "../lib_list/list.h"

namespace Parser {
    Monom parse_monom(const std::string& str);  // может лучше возвращать массив?
    List<Monom> parse_polynom(const std::string& str);

    size_t follow_the_line(const std::string& str, size_t ind);
    bool is_digit(char symbol);
    std::string read_number(const std::string& str, size_t& ind);
    int read_power(const std::string& str, size_t& ind);

    std::string read_monom(std::string str, int& ind);
}

#endif  // LIB_PARSER_PARSER_H_